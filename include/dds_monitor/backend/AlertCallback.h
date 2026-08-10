// Copyright 2025 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima DDS Monitor.
//
// eProsima DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file AlertCallback.h
 */

#ifndef _EPROSIMA_DDS_MONITOR_BACKEND_ALERT_CALLBACK_H
#define _EPROSIMA_DDS_MONITOR_BACKEND_ALERT_CALLBACK_H

#include <dds_monitor/backend/backend_types.h>
#include <fastdds_statistics_backend/types/Alerts.hpp>


namespace backend {

enum AlertCallbackKind
{
    ALERT_TRIGGERED,
    ALERT_TIMEOUT
};

struct AlertCallback
{
    AlertCallback() = default;
    backend::EntityId domain_id;
    backend::EntityId entity_id;
    std::string entity_guid;
    backend::AlertInfo alert_info;
    std::string trigger_data;
    AlertCallbackKind kind;
};

} // namespace backend

#endif // _EPROSIMA_DDS_MONITOR_BACKEND_ALERT_CALLBACK_H
