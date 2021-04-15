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
 * @file Callback.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_CALLBACK_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_CALLBACK_H

#include <include/backend/backend_types.h>

namespace backend {

/*
 * Struct that store the callback information required by the GUI
 * It encapsulates the id and the kind of the new entity discovered
 */
struct Callback
{
    //! Void constructor to use copy constructor afterwards
    Callback()
    {
    }

    //! Standard constructor with the two fields required
    Callback(backend::EntityId new_entity, backend::EntityKind new_entity_kind)
        : new_entity(new_entity)
        , new_entity_kind(new_entity_kind)
    {}

    //! Information of the new \c EntityId found
    backend::EntityId new_entity;
    //! Information of the new \c EntityKind found
    backend::EntityKind new_entity_kind;
};

}

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_CALLBACK_H
