/* Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file StatisticsBackend.cpp
 */

#include <random>
#include <vector>
#include <iostream>

#include <fastdds-statistics-backend/types/types.hpp>
#include <fastdds-statistics-backend/StatisticsBackend.hpp>
#include <fastdds-statistics-backend/listener/DomainListener.hpp>
#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>

#include "database/Database.hpp"

namespace eprosima {
namespace statistics_backend {

/*
 * This mock works with a dynamic model that generates new random entities:
 * It creates new entities by these rules:
 *   - Random Seed = First character of the first domain initialized
 *   - Period (sec) = max(16 - # domains, 3)
 *   - Each iteration creates (each time in different Domain):
 *      - New DataWriter / DataReader
 *      - New Topic + New DW / DR
 *      - New Process + New Participant + New DW / DR
 *   - New Domains are created each time <init_monitor> is called, and one entity of each kind under it
 *
 * The data of each entity is randomly generated without seed.
 */

// Stores the listener pointer in database to execute callbacks
// When Listener is <nullptr> it stops the data generator
void StatisticsBackend::set_physical_listener(
        PhysicalListener* listener,
        CallbackMask callback_mask)
{
    if (listener)
    {
        std::cout << "CONGRATULATIONS, you have set the physical listener" << std::endl;
    }
    else
    {
        std::cout << "CONGRATULATIONS, you have unset the physical listener" << std::endl;
        Database::get_instance()->stop();
    }

    Database::get_instance()->listener(listener);

    static_cast<void>(callback_mask);
}

// Call Discovery Server init_monitor
EntityId StatisticsBackend::init_monitor(
        DomainId domain,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    return init_monitor(std::to_string(domain), domain_listener, callback_mask, data_mask);
}

// Add a new Domain in the Database
// First Domain added sets the random seed
EntityId StatisticsBackend::init_monitor(
        std::string discovery_server_locators,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    std::cout << "CONGRATULATIONS, you have init a monitor in " << discovery_server_locators << std::endl;

    if (Database::get_instance()->count_domains() == 0)
    {
        if (!discovery_server_locators.empty())
        {
            srand(discovery_server_locators[0]);
        }
        else
        {
            srand(0);
        }
    }

    EntityId domain_id = Database::get_instance()->add_domain();

    static_cast<void>(discovery_server_locators);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    return domain_id;
}

// Uses the entities in Database to get the entity vectors
std::vector<EntityId> StatisticsBackend::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
    std::cout << "CONGRATULATIONS, you have asked for entity " << entity_id << std::endl;

    return Database::get_instance()->get_entities(entity_type, entity_id);
}

// Returns the EntityKind of the entity with id entity_id
EntityKind StatisticsBackend::get_type(
        EntityId entity_id)
{
    return Database::get_instance()->get_entity(entity_id)->kind();
}

// Returns the info from an entity in Database
Info StatisticsBackend::get_info(
        EntityId entity_id)
{
    std::cout << "CONGRATULATIONS, you have asked for info from " << entity_id << std::endl;

    return Database::get_instance()->get_info(entity_id);
}

// Call get_data for one entity data
std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        EntityId entity_id_source,
        EntityId entity_id_target,
        uint16_t bins,
        Timestamp t_from,
        Timestamp t_to,
        StatisticKind statistic)
{
    static_cast<void>(entity_id_target);
    return get_data(data_type, entity_id_source, bins, t_from, t_to, statistic);
}

// Returns a random vector of data generated
// The vector has a <bins> number of elements, sorted for first pair element = time
// Each element time in each pair is coherent with the query
std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        EntityId entity_id,
        uint16_t bins,
        Timestamp t_from,
        Timestamp t_to,
        StatisticKind statistic)
{
    std::cout << "CONGRATULATIONS, you have asked for the data of " << entity_id << std::endl;

    static_cast<void> (data_type);
    static_cast<void> (statistic);

    if (0 == bins)
    {
        bins = 100;
    }

    auto ini_time = std::chrono::time_point_cast<std::chrono::milliseconds>(t_from);
    auto end_time = std::chrono::time_point_cast<std::chrono::milliseconds>(t_to);

    auto step_time = (end_time - ini_time) / bins;

    std::vector<StatisticsData> result(bins);
    for (int i = 0; i < bins; i++)
    {
        result[i].first = ini_time + (step_time * i);
        result[i].second = static_cast<double> (rand() % 1000);
    }

    return result;
}

// Call get_data with different default values
std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        EntityId entity_id_source,
        EntityId entity_id_target,
        uint16_t bins,
        StatisticKind statistic)
{
    return get_data(
        data_type,
        entity_id_source,
        entity_id_target,
        bins,
        Timestamp(),
        std::chrono::system_clock::now(),
        statistic);
}

// Call get_data with different default values
std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        EntityId entity_id,
        uint16_t bins,
        StatisticKind statistic)
{
    return get_data(
        data_type,
        entity_id,
        bins,
        Timestamp(),
        std::chrono::system_clock::now(),
        statistic);
}

} //namespace statistics_backend
} //namespace eprosima
