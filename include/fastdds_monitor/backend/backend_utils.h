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
 * @file backend_utils.h
 * @brief collection of util general porpose functions related with bakend
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDUTILS_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDUTILS_H

#include <string>

#include <QString>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/model_types.h>
#include <fastdds_monitor/utils.h>

namespace backend {

//! Convert an \c EntityId into a QString
models::EntityId backend_id_to_models_id(
        const EntityId& id);

/**
 * @brief Convert a QML model \c EntityID (Qstring) into a backend \c EntityId
 * @param id model \c EntityId
 * @return backend \c EntityId
 */
EntityId models_id_to_backend_id(
        const models::EntityId& id);

/**
 * @brief Get the value related with a specific tag inside a \c EntityInfo structure (json format)
 * @param info \c EntityInfo structure
 * @param key tag to find the value
 * @return value in QString format
 */
std::string get_info_value(
        const EntityInfo& info,
        const std::string& key);

//! Look for attribute alias in info. If it does not exist returns name.
std::string get_alias(
        const EntityInfo& info);

/**
 * @brief Get the alive status in \c EntityInfo structure (json format). True by default.
 * @param info \c EntityInfo structure
 * @return alive status value
 */
bool get_info_alive(
        const EntityInfo& info);

/**
 * @brief Get the metatraffic value in \c EntityInfo structure (json format). True by default.
 * @param info \c EntityInfo structure
 * @return metatraffic value
 */
bool get_info_metatraffic(
        const EntityInfo& info);

//! Converts the \c EntityKind to QString
QString entity_kind_to_QString(
        const EntityKind& entity_kind);

//! Converts the \c DataKind to string
std::string data_kind_to_string(
        const DataKind& data_kind);

//! Converts the \c StatisticKind to string
std::string statistic_kind_to_string(
        const StatisticKind& statistic_kind);

//! Converts the \c StatusKind to string
std::string status_kind_to_string(
        const StatusKind& status_kind);

//! Converts the \c StatusLevel to string
std::string status_level_to_string(
        const StatusLevel& status_level);

//! Retrieves the \c EntityKind related with its name in QString
backend::EntityKind string_to_entity_kind(
        const QString& entity_kind);

//! Retrieves the \c DataKind related with its name in QString
backend::DataKind string_to_data_kind(
        const QString& data_kind);

//! Retrieves the \c StatisticKind related with its name in QString
backend::StatisticKind string_to_statistic_kind(
        const QString& statistic_kind);

//! recursive function to convert array json subelements to dictionaries indexed by numbers
backend::EntityInfo refactor_json(
        backend::EntityInfo json_data);

//! Serialize the timestamp of a given data value
std::string timestamp_to_string(
        const backend::Timestamp timestamp);

std::string policy_id_to_string(
        const uint32_t& id);

std::string entity_status_description(
        const backend::StatusKind kind);

std::string policy_documentation_description(
        const uint32_t& id);

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDUTILS_H
