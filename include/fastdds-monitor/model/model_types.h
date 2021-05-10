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
 * @file model_types.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_MODELTYPES_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_MODELTYPES_H

#include <QString>

namespace models {

//! The type of EntityId within the models is a QString came by the conversion of backend \c EntityId into string
using EntityId = QString;

//! Reference the EntityId::all() in models
constexpr const char * ID_ALL = "all";
//! Reference the EntityId::invalid() in models
constexpr const char * ID_INVALID = "invalid";

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_MODELTYPES_H
