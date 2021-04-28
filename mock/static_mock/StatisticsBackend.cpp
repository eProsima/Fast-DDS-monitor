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

#include <fastdds-statistics-backend/StatisticsBackend.hpp>
#include <fastdds-statistics-backend/listener/DomainListener.hpp>
#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>
#include <fastdds-statistics-backend/types/types.hpp>

namespace eprosima {
namespace statistics_backend {

// Dynamic ID to identify new domains started
static int ID = 10;

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
        CallbackMask callback_mask)
{
    static_cast<void>(listener);
    static_cast<void>(callback_mask);
}

// Prints a success message and returns an ID not used before (which do not represent any existing entity)
EntityId StatisticsBackend::init_monitor(
        DomainId domain,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    static_cast<void>(domain);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    return EntityId(++ID);
}

// Prints a success message and returns an ID not used before (which do not represent any existing entity)
EntityId StatisticsBackend::init_monitor(
        std::string discovery_server_locators,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    static_cast<void>(discovery_server_locators);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
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

        case EntityKind::DOMAIN:
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
            return EntityKind::DOMAIN;

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
//  - qos   : a Fast DDS complete qos (the same for all entities, as an example)
//  - name  : name of the entity Kind + "_0"
//  - id    : id of the entity kind (the one given as argument)
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

    switch (entity_id.value())
    {
        case 1:
            json_obj["name"] = "Host_0";
            break;

        case 2:
            json_obj["name"] = "User_0";
            break;

        case 3:
            json_obj["name"] = "Process_0";
            break;

        case 4:
            json_obj["name"] = "Domain_0";
            break;

        case 5:
            json_obj["name"] = "Topic_0";
            break;

        case 6:
            json_obj["name"] = "Participant_0";
            break;

        case 7:
            json_obj["name"] = "Writer_0";
            break;

        case 8:
            json_obj["name"] = "Reader_0";
            break;

        case 9:
            json_obj["name"] = "Locator_0";
            break;

        default:
            json_obj["name"] = "a domain has no name";
            break;
    }

    return json_obj;
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

// Returns a random vector of data generated using the seed: <id(as int) * data_type(as int)>
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
    static_cast<void> (statistic);
    srand(int(entity_id.value()) * int(data_type));

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
