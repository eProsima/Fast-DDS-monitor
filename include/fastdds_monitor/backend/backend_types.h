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
 * @file backend_types.h
 * @brief import of backend types to use in Qt
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDTYPES_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDTYPES_H

#include <QString>

#include <fastdds_statistics_backend/types/Alerts.hpp>
#include <fastdds_statistics_backend/types/app_names.h>
#include <fastdds_statistics_backend/types/JSONTags.h>
#include <fastdds_statistics_backend/types/types.hpp>
#include <fastdds_statistics_backend/topic_types/types.hpp>


namespace backend {

//! Add a type of each kind with same name under \c backend namespace
using EntityId = eprosima::statistics_backend::EntityId;
using EntityKind = eprosima::statistics_backend::EntityKind;
using DataKind = eprosima::statistics_backend::DataKind;
using StatusKind = eprosima::statistics_backend::StatusKind;
using StatusLevel = eprosima::statistics_backend::StatusLevel;
using StatisticKind = eprosima::statistics_backend::StatisticKind;
using AlertKind = eprosima::statistics_backend::AlertKind;
using AlertInfo = eprosima::statistics_backend::AlertInfo;
using EntityInfo = eprosima::statistics_backend::Info;
using Timestamp = eprosima::statistics_backend::Timestamp;
using GUID_s = eprosima::fastdds::statistics::detail::GUID_s;

// Status types from backend
using ConnectionListSample = eprosima::statistics_backend::ConnectionListSample;
using DeadlineMissedSample = eprosima::statistics_backend::DeadlineMissedSample;
using IncompatibleQosSample = eprosima::statistics_backend::IncompatibleQosSample;
using InconsistentTopicSample = eprosima::statistics_backend::InconsistentTopicSample;
using LivelinessChangedSample = eprosima::statistics_backend::LivelinessChangedSample;
using LivelinessLostSample = eprosima::statistics_backend::LivelinessLostSample;
using ProxySample = eprosima::statistics_backend::ProxySample;
using SampleLostSample = eprosima::statistics_backend::SampleLostSample;
using ExtendedIncompatibleQoSStatusSeq = eprosima::fastdds::statistics::ExtendedIncompatibleQoSStatusSeq_s;
using ExtendedIncompatibleQoSStatus = eprosima::fastdds::statistics::ExtendedIncompatibleQoSStatus_s;
//using StatusesSizeSample = eprosima::statistics_backend::StatusesSizeSample;

//! Reference the ID_ALL in the project
extern const EntityId ID_ALL;
//! Reference the ID_NONE in the project
extern const EntityId ID_NONE;

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_BACKENDTYPES_H
