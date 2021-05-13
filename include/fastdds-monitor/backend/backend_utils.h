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
 * @file backend_utils.h
 * @brief collection of util general porpose functions related with bakend
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDUTILS_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDUTILS_H

#include <string>

#include <QString>

#include <fastdds-monitor/backend/backend_types.h>
#include <fastdds-monitor/model/model_types.h>
#include <fastdds-monitor/utils.h>

namespace backend {

//! Convert an \c EntityId into a QString
models::EntityId backend_id_to_models_id(
        const EntityId id);

/**
 * @brief Convert a QML model \c EntityID (Qstring) into a backend \c EntityId
 * @param id model \c EntityId
 * @return backend \c EntityId
 */
EntityId models_id_to_backend_id(
        const models::EntityId id);

/**
 * @brief Get the value related with a specific tag inside a \c EntityInfo structure (json format)
 * @param info \c EntityInfo structure
 * @param key tag to find the value
 * @return value in QString format
 */
std::string get_info_value(
        EntityInfo info,
        std::string key);

//! Converts the \c EntityKind to QString
QString entity_kind_to_QString(
        const EntityKind& entity_kind);

//! Converts the \c DataKind to string
std::string data_kind_to_string(
        const DataKind& data_kind);

//! Converts the \c StatisticKind to string
std::string statistic_kind_to_string(
        const StatisticKind& statistic_kind);

//! Retrieves the \c EntityKind related with its name in QString
backend::EntityKind string_to_entity_kind(
        const QString& entity_kind);

//! Retrieves the \c DataKind related with its name in QString
backend::DataKind string_to_data_kind(
        const QString& data_kind);

//! Retrieves the \c StatisticKind related with its name in QString
backend::StatisticKind string_to_statistic_kind(
        const QString& statistic_kind);

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDUTILS_H
