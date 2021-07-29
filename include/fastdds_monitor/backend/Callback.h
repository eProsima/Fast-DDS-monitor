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
 * @file Callback.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_CALLBACK_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_CALLBACK_H

#include <fastdds_monitor/backend/backend_types.h>

namespace backend {

/*
 * Struct that store the callback information required by the GUI.
 * It encapsulates the id and the kind of the new entity discovered.
 */
struct Callback
{
    //! Void constructor to use copy constructor afterwards
    Callback()
    {
    }

    //! Standard constructor with the two fields required
    Callback(
            backend::EntityId entity_id,
            backend::EntityKind entity_kind,
            bool is_update = false)
        : entity_id(entity_id)
        , entity_kind(entity_kind)
        , is_update(is_update)
    {
    }

    //! Information of the \c EntityId the callback refers
    backend::EntityId entity_id;
    //! Information of the \c EntityKind the callback refers
    backend::EntityKind entity_kind;
    //! If the calback refers to a new discovered entity or it is an update
    bool is_update;
};

} // namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_CALLBACK_H
