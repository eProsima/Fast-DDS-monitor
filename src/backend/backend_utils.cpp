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

#include <sstream>      // std::ostringstream
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/model_types.h>
#include <fastdds_monitor/utils.h>

#include <QDebug>

namespace backend {

const EntityId ID_ALL = EntityId::all();
const EntityId ID_NONE = EntityId::invalid();

models::EntityId backend_id_to_models_id(
        const EntityId& id)
{
    std::ostringstream stream;
    if (id == ID_ALL)
    {
        stream << models::ID_ALL;
    }
    else if (id == ID_NONE)
    {
        stream << models::ID_INVALID;
    }
    else
    {
        stream << id;
    }
    return utils::to_QString(stream.str());
}

EntityId models_id_to_backend_id(
        const models::EntityId& id)
{
    std::ostringstream stream;
    if (id == models::ID_ALL)
    {
        return EntityId::all();
    }
    else if (id == models::ID_INVALID || id == "")
    {
        return EntityId::invalid();
    }
    else
    {
        return EntityId(id.toInt());
    }
}

QString entity_kind_to_QString(
        const EntityKind& entity_kind)
{
    switch (entity_kind)
    {
        case EntityKind::HOST:
            return "Host";
        case EntityKind::USER:
            return "User";
        case EntityKind::PROCESS:
            return "Process";
        case EntityKind::DOMAIN:
            return "Domain";
        case EntityKind::TOPIC:
            return "Topic";
        case EntityKind::PARTICIPANT:
            return "DomainParticipant";
        case EntityKind::DATAWRITER:
            return "DataWriter";
        case EntityKind::DATAREADER:
            return "DataReader";
        case EntityKind::LOCATOR:
            return "Locator";
        default:
            return "INVALID";
    }
}

std::string statistic_kind_to_string(
        const StatisticKind& statistic_kind)
{
    switch (statistic_kind)
    {
        case StatisticKind::COUNT:
            return "COUNT";
        case StatisticKind::MAX:
            return "MAX";
        case StatisticKind::MEAN:
            return "MEAN";
        case StatisticKind::MEDIAN:
            return "MEDIAN";
        case StatisticKind::MIN:
            return "MIN";
        case StatisticKind::STANDARD_DEVIATION:
            return "STANDARD_DEVIATION";
        case StatisticKind::SUM:
            return "SUM";
        default:
            return "RAW DATA";
    }
}

std::string data_kind_to_string(
        const DataKind& data_kind)
{
    switch (data_kind)
    {
        case DataKind::FASTDDS_LATENCY:
            return "FASTDDS_LATENCY";
        case DataKind::NETWORK_LATENCY:
            return "NETWORK_LATENCY";
        case DataKind::PUBLICATION_THROUGHPUT:
            return "PUBLICATION_THROUGHPUT";
        case DataKind::SUBSCRIPTION_THROUGHPUT:
            return "SUBSCRIPTION_THROUGHPUT";
        case DataKind::RTPS_PACKETS_SENT:
            return "RTPS_PACKETS_SENT";
        case DataKind::RTPS_BYTES_SENT:
            return "RTPS_BYTES_SENT";
        case DataKind::RTPS_PACKETS_LOST:
            return "RTPS_PACKETS_LOST";
        case DataKind::RTPS_BYTES_LOST:
            return "RTPS_BYTES_LOST";
        case DataKind::RESENT_DATA:
            return "RESENT_DATA";
        case DataKind::HEARTBEAT_COUNT:
            return "HEARTBEAT_COUNT";
        case DataKind::ACKNACK_COUNT:
            return "ACKNACK_COUNT";
        case DataKind::NACKFRAG_COUNT:
            return "NACKFRAG_COUNT";
        case DataKind::GAP_COUNT:
            return "GAP_COUNT";
        case DataKind::DATA_COUNT:
            return "DATA_COUNT";
        case DataKind::PDP_PACKETS:
            return "PDP_PACKETS";
        case DataKind::EDP_PACKETS:
            return "EDP_PACKETS";
        case DataKind::DISCOVERY_TIME:
            return "DISCOVERY_TIME";
        case DataKind::SAMPLE_DATAS:
            return "SAMPLE_DATAS";
        default:
            return "INVALID";
    }
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
        return DataKind::INVALID;
    }
}

StatisticKind string_to_statistic_kind(
        const QString& statistic_kind)
{
    static std::unordered_map<std::string, StatisticKind> const conversionTable = {
        {"MEAN", StatisticKind::MEAN},
        {"STANDARD_DEVIATION", StatisticKind::STANDARD_DEVIATION},
        {"MAX", StatisticKind::MAX},
        {"MIN", StatisticKind::MIN},
        {"MEDIAN", StatisticKind::MEDIAN},
        {"COUNT", StatisticKind::COUNT},
        {"SUM", StatisticKind::SUM},
        {"RAW DATA", StatisticKind::NONE}
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

std::string get_info_value(
        const EntityInfo& info,
        const std::string& key)
{
    if (info.contains(key))
    {
        if (info[key].is_string())
        {
            return info[key].get<std::string>();
        }
        else if (info[key].is_number_integer())
        {
            return std::to_string(info[key].get<int>());
        }
        else if (info[key].is_number_float())
        {
            return std::to_string(info[key].get<double>());
        }
        else if (info[key].is_boolean())
        {
            return std::to_string(info[key].get<bool>());
        }
        else
        {
            return info[key].dump();
        }
    }
    else
    {
        return ("No key " + key);
    }
}

std::string get_alias(
        const EntityInfo& info)
{
    if (info.contains("alias"))
    {
        return info["alias"].get<std::string>();
    }
    else
    {
        return get_info_value(info, "name");
    }
}

bool get_info_alive(
        const EntityInfo& info)
{
    if (info.contains("alive"))
    {
        return info["alive"].get<bool>();
    }
    else
    {
        // In case alive is not retrieved, it counts as an alive entity
        return true;
    }
}

bool get_info_metatraffic(
        const EntityInfo& info)
{
    if (info.contains("metatraffic"))
    {
        return info["metatraffic"].get<bool>();
    }
    else
    {
        // In case metatraffic is not retrieved, it counts as a non-metatraffic entity
        return false;
    }
}

backend::EntityInfo refactor_json(
        backend::EntityInfo json_data)
{
    if (json_data.is_array())
    {
        // In this case it is already a correct json
        // Iterate over elements and refactor them
        int counter = 0;
        backend::EntityInfo new_json;
        for (auto& element : json_data)
        {
            new_json[std::to_string(counter++)] = refactor_json(element);
        }

        return new_json;
    }
    else if (json_data.is_object())
    {
        // In this case it is already a correct json
        // Iterate over elements and refactor them
        for (auto& element : json_data.items())
        {
            json_data[element.key()] = refactor_json(element.value());
        }
    }

    // Otherwise is primitive or null and it is already correct
    return json_data;
}

std::string timestamp_to_string(
        const backend::Timestamp timestamp)
{
    auto timestamp_t = std::chrono::system_clock::to_time_t(timestamp);
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()).count();
    msec %= 1000;
    std::stringstream ss;

#ifdef _WIN32
    struct tm timestamp_tm;
    _localtime64_s(&timestamp_tm, &timestamp_t);
    ss << std::put_time(&timestamp_tm, "%F %T") << "." << std::setw(3) << std::setfill('0') << msec;
#else
    ss << std::put_time(localtime(&timestamp_t), "%F %T") << "." << std::setw(3) << std::setfill('0') << msec;
#endif // ifdef _WIN32

    return ss.str();
}

} // namespace backend
