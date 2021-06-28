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
 * @file SyncBackendConnection.cpp
 */

#include <iostream>

#include <QDebug>

#include <fastdds_statistics_backend/StatisticsBackend.hpp>
#include <fastdds_statistics_backend/exception/Exception.hpp>

#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/model/dds/EndpointModelItem.h>
#include <fastdds_monitor/model/dds/LocatorModelItem.h>
#include <fastdds_monitor/model/dds/ParticipantModelItem.h>
#include <fastdds_monitor/model/ListItem.h>
#include <fastdds_monitor/model/ListModel.h>
#include <fastdds_monitor/model/logical/DomainModelItem.h>
#include <fastdds_monitor/model/logical/TopicModelItem.h>
#include <fastdds_monitor/model/physical/HostModelItem.h>
#include <fastdds_monitor/model/physical/ProcessModelItem.h>
#include <fastdds_monitor/model/physical/UserModelItem.h>
#include <fastdds_monitor/model/statistics/EntityItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/model/tree/TreeModel.h>

namespace backend {

using namespace eprosima::statistics_backend;
using namespace models;

bool SyncBackendConnection::set_listener(
        Listener* listener)
{
    try
    {
        StatisticsBackend::set_physical_listener(listener);
        return true;
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail setting listener: " << e.what();
        return false;
    }
}

bool SyncBackendConnection::unset_listener()
{
    try
    {
        StatisticsBackend::set_physical_listener(nullptr);
        return true;
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail unsetting listener: " << e.what();
        return false;
    }
}

EntityId SyncBackendConnection::init_monitor(
        int domain)
{
    try
    {
        return StatisticsBackend::init_monitor(domain);
    }
    catch (const Error& e)
    {
        qWarning() << "Error initializing monitor " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter initializing monitor " << e.what();
    }

    return EntityId::invalid();
}

EntityId SyncBackendConnection::init_monitor(
        QString locators)
{
    try
    {
        return StatisticsBackend::init_monitor(locators.toStdString());
    }
    catch (const Error& e)
    {
        qWarning() << "Error initializing monitor " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter initializing monitor " << e.what();
    }

    return EntityId::invalid();
}

EntityInfo SyncBackendConnection::get_info(
        EntityId id)
{
    try
    {
        return StatisticsBackend::get_info(id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity info: " << e.what();
        return EntityInfo();
    }
}

bool SyncBackendConnection::get_alive(
        EntityId id)
{
    try
    {
        return StatisticsBackend::is_active(id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity alive status: " << e.what();
        return true;
    }
}

EntityKind SyncBackendConnection::get_type(
        EntityId id)
{
    try
    {
        return StatisticsBackend::get_type(id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity type: " << e.what();
        return EntityKind::INVALID;
    }
}

std::vector<EntityId> SyncBackendConnection::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
    try
    {
        return StatisticsBackend::get_entities(entity_type, entity_id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entities: " << e.what();
        return std::vector<EntityId>();
    }
}

EntityInfo SyncBackendConnection::get_summary(
        backend::EntityId id)
{
    EntityInfo summary;

    // Values to represent in summary
    std::vector<std::pair<DataKind, StatisticKind>> configurations = {
        std::make_pair(DataKind::NETWORK_LATENCY, StatisticKind::MEDIAN),
        std::make_pair(DataKind::NETWORK_LATENCY, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::FASTDDS_LATENCY, StatisticKind::MEDIAN),
        std::make_pair(DataKind::FASTDDS_LATENCY, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::PUBLICATION_THROUGHPUT, StatisticKind::MEDIAN),
        std::make_pair(DataKind::PUBLICATION_THROUGHPUT, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::SUBSCRIPTION_THROUGHPUT, StatisticKind::MEDIAN),
        std::make_pair(DataKind::SUBSCRIPTION_THROUGHPUT, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::RTPS_BYTES_SENT, StatisticKind::MEDIAN),
        std::make_pair(DataKind::RTPS_BYTES_LOST, StatisticKind::MEDIAN),
        std::make_pair(DataKind::RESENT_DATA, StatisticKind::MEAN),
        std::make_pair(DataKind::HEARTBEAT_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::ACKNACK_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::NACKFRAG_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::GAP_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::DATA_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::PDP_PACKETS, StatisticKind::SUM),
        std::make_pair(DataKind::EDP_PACKETS, StatisticKind::SUM)
    };

    for (auto configuration : configurations)
    {
        // For every configuration, call get data and get the value (time is not used) of the only element received.
        // For DataKinds without targets, setting the id value does not affect, for those with targets,
        // get the target as every entity related with this one.

        auto data = get_data(
            configuration.first,                    // DataKind of the series
            id,                                     // Id of source
            id,                                     // Id of everything connected to source
            1,                                      // Just one bin to get all data available
            configuration.second);                  // StatisticKind

        // Check that there is data to report, if not set or NaN give Nan value
        if (data.empty() || std::isnan(data[0].second))
        {
            summary[backend::data_kind_to_string(configuration.first)]
            [backend::statistic_kind_to_string(configuration.second)]
                = "NaN";
        }
        else
        {
            summary[backend::data_kind_to_string(configuration.first)]
            [backend::statistic_kind_to_string(configuration.second)]
                = data[0].second; // get the value of the first (only) element
        }
    }

    return summary;
}

std::string SyncBackendConnection::get_name(
        EntityId id)
{
    return backend::get_info_value(get_info(id), "name");
}

std::vector<StatisticsData> SyncBackendConnection::get_data(
        DataKind data_kind,
        EntityId source_entity_id,
        EntityId target_entity_id,
        uint16_t bins,
        StatisticKind statistic_kind,
        Timestamp start_time,
        Timestamp end_time)
{
    bool two_entities_data = false;
    std::vector<EntityId> source_ids;
    std::vector<EntityId> target_ids;

    try
    {
        for (auto kinds_supported : StatisticsBackend::get_data_supported_entity_kinds(data_kind))
        {
            // Get the entities of the kind required for the data type that are related with the entity source
            auto source_ids_tmp = get_entities(kinds_supported.first, source_entity_id);
            source_ids.insert(source_ids.end(), source_ids_tmp.begin(), source_ids_tmp.end());

            // Get the entities of the kind required for the data type that are related with the entity target
            if (kinds_supported.second != EntityKind::INVALID)
            {
                // If the target entity is required but not given, the source is used
                // This is usefule for two entities DataKinds when want to ask for all the targets for a source entity
                // Useful for summary
                two_entities_data = true;
                if (!target_entity_id.is_valid())
                {
                    target_entity_id = source_entity_id;
                }
                auto target_ids_tmp = get_entities(kinds_supported.second, target_entity_id);
                target_ids.insert(target_ids.end(), target_ids_tmp.begin(), target_ids_tmp.end());
            }
        }

        if (two_entities_data)
        {
            return StatisticsBackend::get_data(
                data_kind,
                source_ids,
                target_ids,
                bins,
                start_time,
                end_time,
                statistic_kind);
        }
        else
        {
            return StatisticsBackend::get_data(
                data_kind,
                source_ids,
                bins,
                start_time,
                end_time,
                statistic_kind);
        }
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting data: " << e.what();
        return std::vector<StatisticsData>();
    }
}

} //namespace backend
