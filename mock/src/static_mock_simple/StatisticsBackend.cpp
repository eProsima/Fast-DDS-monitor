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

#include <random>
#include <vector>
#include <iostream>

#include <fastdds-statistics-backend/types/types.hpp>
#include <fastdds-statistics-backend/StatisticsBackend.hpp>
#include <fastdds-statistics-backend/listener/DomainListener.hpp>
#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>

namespace eprosima {
namespace statistics_backend {

/*
 * Host     : Host_0
 *
 * User     : User_0(Host_1)
 *
 * Process  : Process_0(User_0)
 *
 * Domain   : Domain_0
 *
 * Topic    : Topic_0(Domain_0)
 *
 * Participant  : Participant_0(Process_0, Domain_0)
 *
 * DataWriter   : DW_0(Participant_0, topic_0)
 *
 * DataReader   : DR_0(Participant_0, topic_0)
 *
 * Locator  : locator_0(Participant_0, DW_0, DR_0)
 */

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
    }

    static_cast<void>(listener);
    static_cast<void>(callback_mask);
}

EntityId StatisticsBackend::init_monitor(
        DomainId domain,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    std::cout << "CONGRATULATIONS, you have init a monitor in domain " << domain << std::endl;
    static_cast<void>(domain);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    return "DOMAIN MONITOR";
}

EntityId StatisticsBackend::init_monitor(
        std::string discovery_server_locators,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    std::cout << "CONGRATULATIONS, you have init a monitor with locators " << discovery_server_locators << std::endl;
    static_cast<void>(discovery_server_locators);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    return "DISCOVERY SERVER MONITOR";
}

std::vector<EntityId> StatisticsBackend::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
    std::cout << "CONGRATULATIONS, you have asked for entity " << entity_id << std::endl;

    static_cast<void>(entity_id);

    std::vector<EntityId> result;

    switch (entity_type)
    {
        case EntityKind::HOST:
            result.push_back("Host_0");
            break;

        case EntityKind::USER:
            result.push_back("User_0");
            break;

        case EntityKind::PROCESS:
            result.push_back("Process_0");
            break;

        case EntityKind::DOMAIN:
            result.push_back("Domain_0");
            break;

        case EntityKind::TOPIC:
            result.push_back("Topic_0");
            break;

        case EntityKind::PARTICIPANT:
            result.push_back("Participant_0");
            break;

        case EntityKind::DATAWRITER:
            result.push_back("Writer_0");
            break;

        case EntityKind::DATAREADER:
            result.push_back("Reader_0");
            break;

        case EntityKind::LOCATOR:
            result.push_back("Locator_0");
            break;

        default:
            break;
    }

    return result;
}

Info StatisticsBackend::get_info(
        EntityId entity_id)
{
    std::cout << "CONGRATULATIONS, you have asked for info from " << entity_id << std::endl;
    Info json_obj = R"({
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

    json_obj["name"] = entity_id;

    return json_obj;
}

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

std::vector<StatisticsData> StatisticsBackend::get_data(
        DataKind data_type,
        EntityId entity_id,
        uint16_t bins,
        Timestamp t_from,
        Timestamp t_to,
        StatisticKind statistic)
{
    std::cout << "CONGRATULATIONS, you have asked for the data of " << entity_id << std::endl;

    static_cast<void> (statistic);
    srand(int(entity_id[0]) * int(data_type));

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

} //namespace statistics_backend
} //namespace eprosima
