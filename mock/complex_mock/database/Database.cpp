// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file Database.cpp
 */

#include <iostream>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <stdlib.h>
#include <thread>
#include <memory>
#include <tuple>

#include "Database.hpp"
#include "RandomGenerator.hpp"

namespace eprosima {
namespace statistics_backend {

void Database::start()
{
    start_.store(true);
    run_.store(true);

    // Notify the Data Generation Thread
    cv_run_.notify_all();

    // Notify the Callback Thread
    cv_callback_start_.notify_all();
}

void Database::stop()
{
    // Must set start as true in case start() has not been called yet. If not, the threads will keep waiting.
    start_.store(true);
    run_.store(false);

    // Notify the Data Generation Thread to wake up. It will close because run_ is deactivated
    // In case it has not been started, the Thread will immediately finish as run_ is deactivated
    cv_run_.notify_all();

    // In case it is closed before a domain has been set, it notifies to start the thread
    cv_callback_start_.notify_all();

    // Notify the Callback Thread
    cv_callback_.notify_all();
}

void Database::listener(
        PhysicalListener* listener)
{
    // Stop is called from Application in case the listener is null
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    listener_ = listener;
}

Database::Database()
    : last_id_(0)
    , listener_(nullptr)
    , start_(false)
    , run_(false)
{
    generate_entity_thread_ = std::thread(&Database::generate_random_entity_thread_, this);
    listener_thread_ = std::thread(&Database::callback_listener_thread_, this);
}

Database::~Database()
{
    stop();

    generate_entity_thread_.join();
    listener_thread_.join();
}

int64_t Database::next_id()
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    return ++last_id_;
}

std::map<EntityId, EntityPointer>& Database::get_all_entities()
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    return entities_;
}

std::vector<EntityId> Database::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
    if (entity_id == EntityId::all())
    {
        // Ask for all entities of a kind
        std::vector<EntityId> result;
        for (auto entity : entities_)
        {
            if (entity.second->kind() == entity_type)
            {
                result.push_back(entity.first);
            }
        }
        return result;
    }
    else
    {
        // Ask for entities of a kind from a specific entity
        auto entity = get_entity(entity_id);
        if (entity)
        {
            return entity->get_entities(entity_type);
        }
        else
        {
            // Error case, it has been asked an Id that is not in the Database
            return std::vector<EntityId>();
        }
    }
}

Info Database::get_info(
        EntityId entity_id)
{
    if (entity_id == EntityId::all())
    {
        // Information asked for id ALL returns a summary of number of domains and entities
        Info summary;

        // Add durability
        summary["domains"] = count_domains();
        summary["entities"] = count_entities_();

        return summary;
    }

    eprosima::statistics_backend::EntityPointer entity = get_entity(entity_id);
    if (entity)
    {
        return entity->get_info();
    }
    else
    {
        // Error case, it has been asked an Id that is not in the Database
        return Info();
    }
}

EntityId Database::add_domain()
{
    // Generates the Domain entity
    DomainPointer domain = RandomGenerator::random_domain();

    // Add the Entity to the entities map
    add_entity_(domain, domain->id());

    // Add domain in domains list
    {
        const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
        domains_.push_back(domain->id());
    }

    // Generates random Entities to fill this domain
    add_entities_(RandomGenerator::init_random_domain(domain), domain->id());

    // Repetead calls to start are idempotent. The first call is the only required.
    start();

    return domain->id();
}

void Database::add_entity_(
        EntityPointer entity,
        EntityId domain)
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    std::cout << "DATABASE: Creating entity: " << entity->name() << std::endl;
    entities_[entity->id()] = entity;

    // Create callback and notify thread
    new_entities_.push_back(std::tuple<EntityId, EntityKind, EntityId>(entity->id(), entity->kind(), domain));
    cv_callback_.notify_one();
}

void Database::add_entities_(
        std::vector<EntityPointer> entities,
        EntityId domain)
{
    for (EntityPointer entity : entities)
    {
        add_entity_(entity, domain);
    }
}

size_t Database::count_domains()
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    return domains_.size();
}

size_t Database::count_entities_()
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    return entities_.size();
}

void Database::generate_random_entity_thread_()
{
    std::cout << "DATABASE Random Data Generator Thread starting" << std::endl;

    // Wait till is ready to generate data
    {
        std::unique_lock<std::mutex> lock(run_mutex_);
        cv_run_.wait(lock, [this]
                {
                    return start_.load();
                });
    }

    std::cout << "DATABASE Random Data Generator Thread running" << std::endl;

    // Index to round robin over domains
    int domain_rr = 0;

    // Start the loop while it does not stop
    while (run_.load())
    {
        // Sleep a time depending the number of domains we have
        // It is max(DATA_GENERATION_TIME seconds - # of domains, MIN_DATA_GENERATION_TIME
        size_t sleep_seconds = (count_domains() <= 1) ? DATA_GENERATION_TIME : DATA_GENERATION_TIME - count_domains();
        sleep_seconds = (sleep_seconds < MIN_DATA_GENERATION_TIME) ? MIN_DATA_GENERATION_TIME : sleep_seconds;

        // Wait to represent data receiving and unlock if stop has been clicked
        {
            std::unique_lock<std::mutex> lock(run_mutex_);
            cv_run_.wait_for(lock, std::chrono::seconds(sleep_seconds));
        }

        // Exit with stop if it has activated while sleeping
        if (!run_.load())
        {
            break;
        }

        // Each time a new domain will create an entity
        // Beware that when new domains are created, this would not be equitative in first n (# domains) iterations
        size_t domain_index = domain_rr++ % count_domains();

        // Generates a new dds Entity
        DomainPointer domain = std::dynamic_pointer_cast<Domain>(entities_[domains_[domain_index]]);
        add_entities_(RandomGenerator::add_random_entity(domain), domain->id());
    }

    std::cout << "DATABASE Random Data Generator Thread stopping" << std::endl;
}

void Database::callback_listener_thread_()
{
    std::cout << "DATABASE Callback Listener Thread starting" << std::endl;

    // Wait till is ready to create callbacks
    // This is needed because if not it will end before run_ has set to true
    std::unique_lock<std::mutex> lock(callback_mutex_start_);
    cv_callback_start_.wait(lock, [this]
            {
                return start_.load();
            });

    std::cout << "DATABASE Callback Listener Thread running" << std::endl;

    while (run_.load())
    {
        // Wait till is ready to generate data
        std::unique_lock<std::mutex> lock_callbacks(callback_mutex_);
        cv_callback_.wait(lock_callbacks, [this]
                {
                    return (!run_.load() || !new_entities_.empty());
                });

        // Exit with stop if it has activated while sleeping
        if (!run_.load())
        {
            break;
        }

        // Non initialize status
        DomainListener::Status status;

        status.current_count_change = 1;

        // While there are new entities to notify
        while (run_.load() && !new_entities_.empty())
        {
            // Sleep to let the creation pass
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            std::tuple<EntityId, EntityKind, EntityId> entity;

            // It locks the mutes to pop elements from new entities array
            {
                const std::lock_guard<std::recursive_mutex> lock_entities(data_mutex_);

                // Gets the element and erase it
                entity = new_entities_.front();
                new_entities_.erase(new_entities_.begin());
            }

            // If listener is not set, the callback is not called and so the notification is lost
            if (listener_)
            {
                switch (std::get<1>(entity))
                {
                    case EntityKind::HOST:
                        listener_->on_host_discovery(std::get<0>(entity), status);
                        break;

                    case EntityKind::USER:
                        listener_->on_user_discovery(std::get<0>(entity), status);
                        break;

                    case EntityKind::PROCESS:
                        listener_->on_process_discovery(std::get<0>(entity), status);
                        break;

                    case EntityKind::TOPIC:
                        listener_->on_topic_discovery(std::get<2>(entity), std::get<0>(entity), status);
                        break;

                    case EntityKind::PARTICIPANT:
                        listener_->on_participant_discovery(std::get<2>(entity), std::get<0>(entity), status);
                        break;

                    case EntityKind::DATAREADER:
                        listener_->on_datareader_discovery(std::get<2>(entity), std::get<0>(entity), status);
                        break;

                    case EntityKind::DATAWRITER:
                        listener_->on_datawriter_discovery(std::get<2>(entity), std::get<0>(entity), status);
                        break;

                    case EntityKind::LOCATOR:
                        listener_->on_locator_discovery(std::get<0>(entity), status);
                        break;

                    default:
                        break;
                }

                // add status callback
                listener_->on_status_reported(std::get<2>(entity), std::get<0>(entity), StatusKind::PROXY);
            }
        }

    }

    std::cout << "DATABASE Callback Listener Thread stopping" << std::endl;
}

EntityPointer Database::get_entity(
        EntityId id)
{
    std::map<EntityId, EntityPointer>::iterator it = entities_.find(id);

    if (it == entities_.end())
    {
        std::cerr << "Entity " << id << " does not exist" << std::endl;
        return nullptr;
    }
    else
    {
        return it->second;
    }
}

void Database::set_alias(
        EntityId id,
        std::string new_alias)
{
    std::map<EntityId, EntityPointer>::iterator it = entities_.find(id);

    if (it != entities_.end())
    {
        it->second->alias(new_alias);
    }
}

bool Database::get_active(
        EntityId id)
{
    Info info = get_info(id);

    if (info.contains("alive"))
    {
        return info["alive"];
    }
    else
    {
        return true;
    }
}

} // namespace statistics_backend
} // namespace eprosima
