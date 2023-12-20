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
 * @file StatusCallback.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_STATUS_CALLBACK_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_STATUS_CALLBACK_H

#include <fastdds_monitor/backend/backend_types.h>

namespace backend {

/*
 * Struct that store the status callback information required by the GUI.
 * It encapsulates the domain id, entity id and the kind of the new status reported.
 */
struct StatusCallback
{
    //! Void constructor to use copy constructor afterwards
    StatusCallback()
    {
    }

    //! Standard constructor with the two fields required
    StatusCallback(
            backend::EntityId domain_entity_id,
            backend::EntityId entity_id,
            backend::StatusKind status_kind)
        : domain_entity_id(domain_entity_id)
        , entity_id(entity_id)
        , status_kind(status_kind)
    {
    }

    //! Information of the domain \c EntityId the callback refers
    backend::EntityId domain_entity_id;
    //! Information of the \c EntityId the callback refers
    backend::EntityId entity_id;
    //! Information of the \c StatusKind the callback refers
    backend::StatusKind status_kind;
};

} // namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_STATUS_CALLBACK_H
