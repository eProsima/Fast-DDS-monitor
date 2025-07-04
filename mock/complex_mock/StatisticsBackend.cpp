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
 * @file StatisticsBackend.cpp
 */

#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <map>

#include <fastdds_statistics_backend/types/types.hpp>
#include <fastdds_statistics_backend/StatisticsBackend.hpp>
#include <fastdds_statistics_backend/listener/DomainListener.hpp>
#include <fastdds_statistics_backend/listener/PhysicalListener.hpp>

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
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);

    if (!listener)
    {
        Database::get_instance()->stop();
    }

    Database::get_instance()->listener(listener);
}

// Call Discovery Server init_monitor
EntityId StatisticsBackend::init_monitor(
        DomainId domain,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask,
        std::string app_id,
        std::string app_metadata,
        std::string easy_mode_ip)
{
    static_cast<void>(easy_mode_ip);
    return init_monitor(std::to_string(domain), domain_listener, callback_mask, data_mask, app_id, app_metadata);
}

// Add a new Domain in the Database
// First Domain added sets the random seed
EntityId StatisticsBackend::init_monitor(
        std::string discovery_server_locators,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask,
        std::string app_id,
        std::string app_metadata)
{
    static_cast<void>(discovery_server_locators);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    static_cast<void>(app_id);
    static_cast<void>(app_metadata);

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
    return domain_id;
}

// Add a new Domain in the Database
// First Domain added sets the random seed
EntityId StatisticsBackend::init_monitor_with_profile(
        const std::string& profile_name,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask,
        std::string app_id,
        std::string app_metadata)
{
    static_cast<void>(profile_name);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    static_cast<void>(app_id);
    static_cast<void>(app_metadata);

    if (Database::get_instance()->count_domains() == 0)
    {
        if (!profile_name.empty())
        {
            srand(profile_name[0]);
        }
        else
        {
            srand(0);
        }
    }

    EntityId domain_id = Database::get_instance()->add_domain();
    return domain_id;
}

// Uses the entities in Database to get the entity vectors
std::vector<EntityId> StatisticsBackend::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
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
    return Database::get_instance()->get_info(entity_id);
}

// Call get_data for one entity data
std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        const std::vector<EntityId>& entity_ids_source,
        const std::vector<EntityId>& entity_ids_target,
        uint16_t bins,
        Timestamp t_from,
        Timestamp t_to,
        StatisticKind statistic)
{
    static_cast<void>(entity_ids_target);
    return get_data(data_type, entity_ids_source, bins, t_from, t_to, statistic);
}

// Returns a random vector of data generated
// The vector has a <bins> number of elements, sorted for first pair element = time
// Each element time in each pair is coherent with the query
std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        const std::vector<EntityId>& entity_ids,
        uint16_t bins,
        Timestamp t_from,
        Timestamp t_to,
        StatisticKind statistic)
{
    static_cast<void> (data_type);
    static_cast<void> (entity_ids);
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
        const std::vector<EntityId>& entity_ids_source,
        const std::vector<EntityId>& entity_ids_target,
        uint16_t bins,
        StatisticKind statistic)
{
    return get_data(
        data_type,
        entity_ids_source,
        entity_ids_target,
        bins,
        Timestamp(),
        std::chrono::system_clock::now(),
        statistic);
}

// Call get_data with different default values
std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        const std::vector<EntityId>& entity_ids,
        uint16_t bins,
        StatisticKind statistic)
{
    return get_data(
        data_type,
        entity_ids,
        bins,
        Timestamp(),
        std::chrono::system_clock::now(),
        statistic);
}

std::vector<std::pair<EntityKind, EntityKind>> StatisticsBackend::get_data_supported_entity_kinds(
        DataKind data_kind)
{
    static std::map<DataKind, std::vector<std::pair<EntityKind, EntityKind>>> data_to_entity_map =
    {
        {DataKind::INVALID, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::INVALID, EntityKind::INVALID)})},

        {DataKind::FASTDDS_LATENCY, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::DATAREADER)})},

        {DataKind::NETWORK_LATENCY, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::LOCATOR, EntityKind::LOCATOR)})},

        {DataKind::PUBLICATION_THROUGHPUT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::INVALID)})},

        {DataKind::SUBSCRIPTION_THROUGHPUT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAREADER, EntityKind::INVALID)})},

        {DataKind::RTPS_PACKETS_SENT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::LOCATOR)})},

        {DataKind::RTPS_BYTES_SENT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::LOCATOR)})},

        {DataKind::RTPS_PACKETS_LOST, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::LOCATOR)})},

        {DataKind::RTPS_BYTES_LOST, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::LOCATOR)})},

        {DataKind::RESENT_DATA, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::INVALID)})},

        {DataKind::HEARTBEAT_COUNT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::INVALID)})},

        {DataKind::ACKNACK_COUNT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAREADER, EntityKind::INVALID)})},

        {DataKind::NACKFRAG_COUNT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAREADER, EntityKind::INVALID)})},

        {DataKind::GAP_COUNT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::INVALID)})},

        {DataKind::DATA_COUNT, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::INVALID)})},

        {DataKind::PDP_PACKETS, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::PARTICIPANT, EntityKind::INVALID)})},

        {DataKind::EDP_PACKETS, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::PARTICIPANT, EntityKind::INVALID)})},

        {DataKind::DISCOVERY_TIME, std::vector<std::pair<EntityKind, EntityKind>>(
                    {
                        std::pair<EntityKind, EntityKind> (EntityKind::PARTICIPANT, EntityKind::PARTICIPANT),
                        std::pair<EntityKind, EntityKind> (EntityKind::PARTICIPANT, EntityKind::DATAWRITER),
                        std::pair<EntityKind, EntityKind> (EntityKind::PARTICIPANT, EntityKind::DATAREADER)})},

        {DataKind::SAMPLE_DATAS, std::vector<std::pair<EntityKind, EntityKind>>(
             {std::pair<EntityKind, EntityKind> (EntityKind::DATAWRITER, EntityKind::INVALID)})}
    };

    return data_to_entity_map[data_kind];
}

void StatisticsBackend::set_alias(
        EntityId entity_id,
        const std::string& alias)
{
    Database::get_instance()->set_alias(entity_id, alias);
}

bool StatisticsBackend::is_active(
        EntityId entity_id)
{
    return Database::get_instance()->get_active(entity_id);
}

} //namespace statistics_backend
} //namespace eprosima
