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

#include <fastdds_statistics_backend/StatisticsBackend.hpp>
#include <fastdds_statistics_backend/listener/DomainListener.hpp>
#include <fastdds_statistics_backend/listener/PhysicalListener.hpp>
#include <fastdds_statistics_backend/types/types.hpp>

namespace eprosima {
namespace statistics_backend {

// Dynamic ID to identify new domains started
static int ID = 10;

static std::map<int, std::string> names = {
    {1, "Host_0"},
    {2, "User_0"},
    {3, "Process_0"},
    {4, "Domain_0"},
    {5, "Topic_0"},
    {6, "Participant_0"},
    {7, "Writer_0"},
    {8, "Reader_0"},
    {9, "Locator_0"},
    {0, "an entity has no name"}
};

/*
 * This mock works with a static model formed by the following entities:
 *
 * Host         : Host_0                                    : 1
 *
 * User         : User_0(Host_1)                            : 2
 *
 * Process      : Process_0(User_0)                         : 3
 *
 * Domain       : Domain_0                                  : 4
 *
 * Topic        : Topic_0(Domain_0)                         : 5
 *
 * Participant  : Participant_0(Process_0, Domain_0)        : 6
 *
 * DataWriter   : DW_0(Participant_0, topic_0)              : 7
 *
 * DataReader   : DR_0(Participant_0, topic_0)              : 8
 *
 * Locator      : locator_0(Participant_0, DW_0, DR_0)      : 9
 *
 * With this simple static schema is possible to imlpement a trivial <get_entities> function
 * which would be one of the most difficult functions to implement in the backend.
 */

// Prints a success message and do nothing
void StatisticsBackend::set_physical_listener(
        PhysicalListener* listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    static_cast<void>(listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
}

// Prints a success message and returns an ID not used before (which do not represent any existing entity)
EntityId StatisticsBackend::init_monitor(
        DomainId domain,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask,
        std::string app_id,
        std::string app_metadata)
{
    static_cast<void>(domain);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    static_cast<void>(app_id);
    static_cast<void>(app_metadata);
    return EntityId(++ID);
}

// Prints a success message and returns an ID not used before (which do not represent any existing entity)
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
    return EntityId(++ID);
}

// Returns a vector with one id of the unique entity of <entity_type> kind
std::vector<EntityId> StatisticsBackend::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
    static_cast<void>(entity_id);

    std::vector<EntityId> result;

    switch (entity_type)
    {
        case EntityKind::HOST:
            result.push_back(1);
            break;

        case EntityKind::USER:
            result.push_back(2);
            break;

        case EntityKind::PROCESS:
            result.push_back(3);
            break;

        case EntityKind::DOMAIN_ENTITY:
            result.push_back(4);
            break;

        case EntityKind::TOPIC:
            result.push_back(5);
            break;

        case EntityKind::PARTICIPANT:
            result.push_back(6);
            break;

        case EntityKind::DATAWRITER:
            result.push_back(7);
            break;

        case EntityKind::DATAREADER:
            result.push_back(8);
            break;

        case EntityKind::LOCATOR:
            result.push_back(9);
            break;

        default:
            break;
    }

    return result;
}

// Returns the EntityKind of the entity with id entity_id
EntityKind StatisticsBackend::get_type(
        EntityId entity_id)
{
    switch (entity_id.value())
    {
        case 1:
            return EntityKind::HOST;

        case 2:
            return EntityKind::USER;

        case 3:
            return EntityKind::PROCESS;

        case 4:
            return EntityKind::DOMAIN_ENTITY;

        case 5:
            return EntityKind::TOPIC;

        case 6:
            return EntityKind::PARTICIPANT;

        case 7:
            return EntityKind::DATAWRITER;

        case 8:
            return EntityKind::DATAREADER;

        case 9:
            return EntityKind::LOCATOR;

        default:
            return EntityKind::INVALID;
    }
}

// Returns an info key values:
//  - qos       : a Fast DDS complete qos (the same for all entities, as an example)
//  - name      : name of the entity Kind + "_0"
//  - id        : id of the entity kind (the one given as argument)
//  - active    : false for physical entities
Info StatisticsBackend::get_info(
        EntityId entity_id)
{
    Info json_obj =
            R"({
        "qos":{
            "data_sharing":
            {
                "domain_ids":
                [
                    0
                ],
                "kind": "AUTO",
                "max_domains": 1,
                "shm_directory": "/dev/shm"
            },
            "deadline":
            {
                "period":
                {
                    "nanoseconds": 50,
                    "seconds": 10
                }
            },
            "destination_order":
            {
                "kind": "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS"
            },
            "disable_positive_acks":
            {
                "duration":
                {
                    "nanoseconds": 100,
                    "seconds": 0
                },
                "enabled": true
            },
            "durability":
            {
                "kind": "VOLATILE_DURABILITY_QOS"
            },
            "durability_service":
            {
                "history_depth": "1",
                "history_kind": "KEEP_LAST_HISTORY_QOS",
                "max_instances": "30",
                "max_samples": "3000",
                "max_samples_per_instance": "100",
                "service_cleanup_delay":
                {
                    "nanoseconds": 0,
                    "seconds": 5
                }
            },
            "group_data": "9d46781410ff",
            "latency_budget":
            {
                "duration":
                {
                    "nanoseconds": 50,
                    "seconds": 10
                }
            },
            "lifespan":
            {
                "duration":
                {
                    "nanoseconds": 0,
                    "seconds": 10000
                }
            },
            "liveliness":
            {
                "announcement_period":
                {
                    "nanoseconds": 0,
                    "seconds": 3
                },
                "lease_duration":
                {
                    "nanoseconds": 0,
                    "seconds": 10
                },
                "kind": "AUTOMATIC_LIVELINESS_QOS"
            },
            "ownership":
            {
                "kind": "SHARED_OWNERSHIP_QOS"
            },
            "partition":
            [
                "partition_1",
                "partition_2"
            ],
            "presentation":
            {
                "access_scope": "INSTANCE_PRESENTATION_QOS",
                "coherent_access": false,
                "ordered_access": false
            },
            "reliability":
            {
                "kind": "RELIABLE_RELIABILITY_QOS",
                "max_blocking_time":
                {
                    "nanoseconds": 0,
                    "seconds": 3
                }
            },
            "representation":
            [
            ],
            "time_based_filter":
            {
                "minimum_separation":
                {
                    "seconds": 12,
                    "nanoseconds": 0
                }
            },
            "topic_data": "5b33419a",
            "type_consistency":
            {
                "force_type_validation": false,
                "ignore_member_names": false,
                "ignore_sequence_bounds": true,
                "ignore_string_bounds": true,
                "kind": "DISALLOW_TYPE_COERCION",
                "prevent_type_widening": false
            },
            "user_data": "ff00"
        }
    })"_json;

    json_obj["id"] = entity_id.value();

    if (entity_id.value() < 1 || entity_id.value() > 9)
    {
        json_obj["name"] = names[0];
    }
    else
    {
        json_obj["name"] = names[static_cast<int>(entity_id.value())];
    }

    if (entity_id.value() == 2 || entity_id.value() == 3)
    {
        json_obj["alive"] = false;
    }

    json_obj["alias"] = json_obj["name"];

    return json_obj;
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

// Returns a random vector of data generated using the seed: <id(as int) * data_type(as int)>
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
    static_cast<void> (statistic);

    if (entity_ids.empty())
    {
        srand(0);
    }
    else
    {
        srand(int(entity_ids[0].value()) * int(data_type));
    }

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
    if (entity_id.value() < 1 || entity_id.value() > 9)
    {
        names[0] = alias;
    }
    else
    {
        names[static_cast<int>(entity_id.value())] = alias;
    }
}

bool StatisticsBackend::is_active(
        EntityId entity_id)
{
    switch (entity_id.value())
    {
        case 2:
        case 3:
            return false;

        default:
            return true;
    }
}

} //namespace statistics_backend
} //namespace eprosima
