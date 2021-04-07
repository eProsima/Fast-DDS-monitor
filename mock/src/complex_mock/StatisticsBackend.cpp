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

#include "database/Database.hpp"

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

// Implemented without Mask
void StatisticsBackend::set_physical_listener(
        PhysicalListener* listener,
        CallbackMask callback_mask)
{
    if (listener)
    {
        std::cout << "CONGRATULATIONS, you have set the physical listener" << std::endl;
        // TODO initiate thread to create random data
    }
    else
    {
        std::cout << "CONGRATULATIONS, you have unset the physical listener" << std::endl;
    }


    Database::get_instance()->listener(listener);

    static_cast<void>(callback_mask);
}

// Domains are not implemented. It only allows to change between existint domains / DS
EntityId StatisticsBackend::init_monitor(
        DomainId domain,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    std::cout << "CONGRATULATIONS, you have init a monitor in domain " << domain << std::endl;

    return init_monitor(std::to_string(domain), domain_listener, callback_mask, data_mask);
}

// DS are not implemented. It only allows to change between existint domains / DS
EntityId StatisticsBackend::init_monitor(
        std::string discovery_server_locators,
        DomainListener* domain_listener,
        CallbackMask callback_mask,
        DataKindMask data_mask)
{
    std::cout << "CONGRATULATIONS, you have init a monitor with locators " << discovery_server_locators << std::endl;

    EntityId domain_id = Database::get_instance()->add_domain();

    static_cast<void>(discovery_server_locators);
    static_cast<void>(domain_listener);
    static_cast<void>(callback_mask);
    static_cast<void>(data_mask);
    return domain_id;
}

// Uses the values in Database to get the entities
std::vector<EntityId> StatisticsBackend::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
    std::cout << "CONGRATULATIONS, you have asked for entity " << entity_id << std::endl;

    return Database::get_instance()->get_entities(entity_type, entity_id);
}

// Returns the info from an entity
Info StatisticsBackend::get_info(
        EntityId entity_id)
{
    std::cout << "CONGRATULATIONS, you have asked for info from " << entity_id << std::endl;

    return Database::get_instance()->get_info(entity_id);
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

// Implement as random data, generated with EntityId seed and depending on bins
// TODO: attach data to Entities and create it dynamically
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
    srand(entity_id.value() * int(data_type));

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

// Overload of get_data with different default values
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

// Overload of get_data with different default values
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
