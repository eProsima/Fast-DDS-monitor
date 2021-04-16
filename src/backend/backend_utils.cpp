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

#include <sstream>      // std::ostringstream

#include <fastdds-statistics-backend/StatisticsBackend.hpp>

#include <fastdds-monitor/backend/backend_types.h>
#include <fastdds-monitor/model/model_types.h>
#include <fastdds-monitor/utils.h>

namespace backend{

const EntityId ID_ALL = EntityId::all();
const EntityId ID_NONE = EntityId::invalid();

QString id_to_QString(const EntityId id)
{
    std::ostringstream stream;
    stream << id;
    return utils::to_QString(stream.str());
}

EntityId models_id_to_backend_id(const models::EntityId id)
{
    return EntityId(id.toInt());
}

QString get_name(const EntityId id)
{
    return utils::to_QString(
                eprosima::statistics_backend::StatisticsBackend::get_info(id)["name"]);
}

// PROCESS
QString process_pid(backend::EntityId process_id)
{
    // TODO
    return id_to_QString(process_id);
}

// DDS GUID
QString entity_guid(backend::EntityId id)
{
    // TODO
   return id_to_QString(id);
}

// TOPIC
QString topic_type(backend::EntityId id)
{
    // TODO
    return id_to_QString(id);
}

EntityInfo get_info(backend::EntityId id)
{
    return eprosima::statistics_backend::StatisticsBackend::get_info(id);
}

EntityKind string_to_entity_kind(
        const QString& entity_kind)
{
    static std::unordered_map<std::string, EntityKind> const conversionTable = {
        {"Host", EntityKind::HOST},
        {"User", EntityKind::USER},
        {"Process", EntityKind::PROCESS},
        {"Domain", EntityKind::DOMAIN},
        {"Topic", EntityKind::TOPIC},
        {"Participant", EntityKind::PARTICIPANT},
        {"DomainParticipant", EntityKind::PARTICIPANT},
        {"DataWriter", EntityKind::DATAWRITER},
        {"DataReader", EntityKind::DATAREADER},
        {"Locator", EntityKind::LOCATOR}
    };

    auto it = conversionTable.find(utils::to_string(entity_kind));
    if (it != conversionTable.end())
    {
      return it->second;
    }
    else
    {
        return EntityKind::INVALID;
    }
}

DataKind string_to_data_kind(
       const QString& data_kind)
{
    static std::unordered_map<std::string, DataKind> const conversionTable = {
        {"FASTDDS_LATENCY", DataKind::FASTDDS_LATENCY},
        {"NETWORK_LATENCY", DataKind::NETWORK_LATENCY},
        {"PUBLICATION_THROUGHPUT", DataKind::PUBLICATION_THROUGHPUT},
        {"SUBSCRIPTION_THROUGHPUT", DataKind::SUBSCRIPTION_THROUGHPUT},
        {"RTPS_PACKETS_SENT", DataKind::RTPS_PACKETS_SENT},
        {"RTPS_BYTES_SENT", DataKind::RTPS_BYTES_SENT},
        {"RTPS_PACKETS_LOST", DataKind::RTPS_PACKETS_LOST},
        {"RTPS_BYTES_LOST", DataKind::RTPS_BYTES_LOST},
        {"RESENT_DATA", DataKind::RESENT_DATA},
        {"HEARTBEAT_COUNT", DataKind::HEARTBEAT_COUNT},
        {"ACKNACK_COUNT", DataKind::ACKNACK_COUNT},
        {"NACKFRAG_COUNT", DataKind::NACKFRAG_COUNT},
        {"GAP_COUNT", DataKind::GAP_COUNT},
        {"DATA_COUNT", DataKind::DATA_COUNT},
        {"PDP_PACKETS", DataKind::PDP_PACKETS},
        {"EDP_PACKETS", DataKind::EDP_PACKETS},
        {"DISCOVERY_TIME", DataKind::DISCOVERY_TIME},
        {"SAMPLE_DATAS", DataKind::SAMPLE_DATAS}
   };

   auto it = conversionTable.find(utils::to_string(data_kind));
   if (it != conversionTable.end())
   {
     return it->second;
   }
   else
   {
       // TODO: Change to a non valid DataKind
       return DataKind::NONE;
   }
}

StatisticKind string_to_statistic_kind(
       const QString& statistic_kind)
{
    static std::unordered_map<std::string, StatisticKind> const conversionTable = {
        {"NONE", StatisticKind::NONE},
        {"MEAN", StatisticKind::MEAN},
        {"STANDARD_DEVIATION", StatisticKind::STANDARD_DEVIATION},
        {"MAX", StatisticKind::MAX},
        {"MIN", StatisticKind::MIN},
        {"MEDIAN", StatisticKind::MEDIAN},
        {"COUNT", StatisticKind::COUNT},
        {"SUM", StatisticKind::SUM}
   };

   auto it = conversionTable.find(utils::to_string(statistic_kind));
   if (it != conversionTable.end())
   {
     return it->second;
   }
   else
   {
       return StatisticKind::NONE;
   }
}

std::string get_info_value(EntityInfo info, std::string key)
{
    if (info.contains(key))
    {
        return info[key];
    }
    else
    {
        return ("No key " + key);
    }
}

} // namespace backend
