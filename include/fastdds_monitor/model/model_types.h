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
 * @file model_types.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_MODELTYPES_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_MODELTYPES_H

#include <QString>

namespace models {

//! The type of EntityId within the models is a QString came by the conversion of backend \c EntityId into string
using EntityId = QString;

//! Reference the EntityId::all() in models
constexpr const char* ID_ALL = "all";
//! Reference the EntityId::invalid() in models
constexpr const char* ID_INVALID = "invalid";

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_MODELTYPES_H
