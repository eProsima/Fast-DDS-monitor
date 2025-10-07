// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file AlertCallback.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_ALERT_CALLBACK_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_ALERT_CALLBACK_H

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_statistics_backend/types/Alerts.hpp>


namespace backend {

enum AlertCallbackKind
{
    ALERT_TRIGGERED,
    ALERT_UNMATCHED
};

struct AlertCallback
{
    AlertCallback() = default;

    AlertCallback(
            backend::EntityId domain_entity_id,
            backend::AlertInfo alert_info)
        : domain_id(domain_entity_id)
        , alert_info(alert_info)
        , kind(AlertCallbackKind::ALERT_UNMATCHED)
    {
    }

    AlertCallback(
            backend::EntityId domain_entity_id,
            backend::EntityId entity_id,
            backend::AlertInfo alert_info,
            double trigger_data)
        : domain_id(domain_entity_id)
        , entity_id(entity_id)
        , alert_info(alert_info)
        , trigger_data(trigger_data)
        , kind(AlertCallbackKind::ALERT_TRIGGERED)
    {
    }


    backend::EntityId domain_id;
    backend::EntityId entity_id;
    backend::AlertInfo alert_info;
    double trigger_data;
    AlertCallbackKind kind;
};

} // namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_ALERT_CALLBACK_H
