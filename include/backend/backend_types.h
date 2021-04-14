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
 * @file backend_types.h
 * @brief import of backend types to use in Qt
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDTYPES_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDTYPES_H

#include <QString>

#include <fastdds-statistics-backend/types/types.hpp>

namespace backend {

//! Add a type of each kind with same name under \c backend namespace
using EntityId = eprosima::statistics_backend::EntityId;
using EntityKind = eprosima::statistics_backend::EntityKind;
using DataKind = eprosima::statistics_backend::DataKind;
using StatisticKind = eprosima::statistics_backend::StatisticKind;
using EntityInfo = eprosima::statistics_backend::Info;

//! Reference the ID_ALL in the project
extern const EntityId ID_ALL;
//! Reference the ID_NONE in the project
extern const EntityId ID_NONE;

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDTYPES_H
