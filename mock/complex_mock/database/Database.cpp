// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    run_.store(true);

    {
        // std::unique_lock<std::mutex> lock(run_mutex_);
        cv_run_.notify_all();
    }

    {
        // std::unique_lock<std::mutex> lock(callback_mutex_start_);
        cv_callback_start_.notify_all();
    }
}

void Database::stop()
{
    run_.store(false);

    {
        // std::unique_lock<std::mutex> lock(run_mutex_);
        cv_run_.notify_all();
    }

    {
        // std::unique_lock<std::mutex> lock(callback_mutex_);
        cv_callback_.notify_all();
    }
}

void Database::listener(PhysicalListener* listener)
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    listener_ = listener;
}

Database::Database()
    : last_id_(0)
    , listener_(nullptr)
    , run_(false)
{
    std::cout << "Database constructor" << std::endl;

    generate_data_thread_ = std::thread(&Database::generate_random_data_thread, this);
    listener_thread_ = std::thread(&Database::callback_listener_thread, this);

    std::cout << "Database constructor finish" << std::endl;
}

Database::~Database()
{
    stop();

    generate_data_thread_.join();
    listener_thread_.join();

    // This must be done from where the listener has been created
    //     delete listener_;
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
            return std::vector<EntityId>();
        }
    }
}

Info Database::get_info(EntityId entity_id)
{
    if (entity_id == EntityId::all())
    {
        Info summary;

        // Add durability
        summary["domains"] = count_domains();
        summary["entities"] = count_entities();

        return summary;
    }

    auto entity = get_entity(entity_id);
    if (entity)
    {
        return entity->get_info();
    }
    else
    {
        return Info();
    }
}

EntityId Database::add_domain()
{
    std::cout << "add domain" << std::endl;

    // Generates the Domain entity
    DomainPointer domain = RandomGenerator::random_domain();

    std::cout << "domain random generated " << domain->id() << std::endl;

    // Add the Entity to the entities map
    add_entity(domain, domain->id());

    std::cout << "domain added" << std::endl;

    // Add domain in domains list
    {
        const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
        domains_.push_back(domain->id());
    }

    std::cout << "domain add into domains" << std::endl;

    // Generates random Entities to fill this domain
    add_entities(RandomGenerator::init_random_domain(domain), domain->id());

    std::cout << "domain random generate new entities" << std::endl;

    start();

    return domain->id();
}

void Database::add_entity(EntityPointer entity, EntityId domain)
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    std::cout << "Creating entity: " << entity->name() << std::endl;
    entities_[entity->id()] = entity;
    new_entities_.push_back(std::tuple<EntityId, EntityKind, EntityId>(entity->id(), entity->kind(), domain));

    {
        // std::unique_lock<std::mutex> lock(callback_mutex_);
        cv_callback_.notify_one();
    }
}

void Database::add_entities(std::vector<EntityPointer> entities, EntityId domain)
{
    for (EntityPointer entity : entities)
    {
        add_entity(entity, domain);
    }
}

size_t Database::count_domains()
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    return domains_.size();
}

size_t Database::count_entities()
{
    const std::lock_guard<std::recursive_mutex> lock(data_mutex_);
    return entities_.size();
}

void Database::generate_random_data_thread()
{
    std::cout << "Random Data Generator Thread starting" << std::endl;

    // Wait till is ready to generate data
    std::unique_lock<std::mutex> lock(run_mutex_);
    cv_run_.wait(lock, [this]{return run_.load();});

    std::cout << "Random Data Generator Thread running" << std::endl;

    int entity_count = 0;

    // Start the loop while it does not stop
    while(run_.load())
    {
        std::cout << "Random Data Generator Thread init loop" << std::endl;

        // Sleep a time depending the number of domains we have
        uint32_t sleep_seconds = (count_domains() <= 1) ? DATA_GENERATION_TIME : DATA_GENERATION_TIME / count_domains();
        std::this_thread::sleep_for(std::chrono::seconds(sleep_seconds));

        // Exit with stop if it has activated while sleeping
        if (!run_.load())
        {
            break;
        }

        // Each time a new domain will create an entity
        // Beware that when new domains are created, this would not be equitative in first n (# domains) iterations
        uint32_t domain_index = entity_count % count_domains();

        // Generates a new dds Entity
        DomainPointer domain = std::dynamic_pointer_cast<Domain>(entities_[domains_[domain_index]]);
        add_entities(RandomGenerator::random_dds_entity(domain), domain->id());
    }

    std::cout << "Random Data Generator Thread stopping" << std::endl;
}

void Database::callback_listener_thread()
{
    std::cout << "Callback Listener Thread starting" << std::endl;

    // Wait till is ready to create callbacks
    // This is needed because if not it will end before run_ has set to true
    std::unique_lock<std::mutex> lock(callback_mutex_start_);
    cv_callback_start_.wait(lock, [this]{return (!new_entities_.empty());});

    std::cout << "Callback Listener Thread running" << std::endl;

    while(run_.load())
    {
        // Wait till is ready to generate data
        std::unique_lock<std::mutex> lock(callback_mutex_);
        cv_callback_.wait(lock, [this]{return (!new_entities_.empty());});

        std::cout << "Callback Listener Thread notifying" << std::endl;

        // Non initialize status
        DomainListener::Status status;

        // While there are new entities to notify
        while (run_.load() && !new_entities_.empty())
        {
            // Sleep to let the creation pass
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            std::tuple<EntityId, EntityKind, EntityId> entity;

            // It locks the mutes to pop elements from new entities array
            {
                const std::lock_guard<std::recursive_mutex> lock(data_mutex_);

                // Gets the element and erase it
                entity = new_entities_.back();
                new_entities_.pop_back();
            }

            // If listener is not set, the callback is not called and so the notification is lost
            if (listener_)
            {
                switch (std::get<1>(entity))
                {
                case EntityKind::HOST:
                    listener_->on_host_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                case EntityKind::USER:
                    listener_->on_user_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                case EntityKind::PROCESS:
                    listener_->on_process_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                case EntityKind::TOPIC:
                    listener_->on_topic_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                case EntityKind::PARTICIPANT:
                    listener_->on_participant_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                case EntityKind::DATAREADER :
                    listener_->on_datareader_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                case EntityKind::DATAWRITER:
                    listener_->on_datawriter_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                case EntityKind::LOCATOR:
                    listener_->on_locator_discovery(std::get<2>(entity), std::get<0>(entity), status);
                    break;

                default:
                    break;
                }
            }
        }
    }

    std::cout << "Callback Listener Thread stopping" << std::endl;
}

EntityPointer Database::get_entity(EntityId id)
{
    auto it = entities_.find(id);

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


} // namespace statistics_backend
} // namespace eprosima
