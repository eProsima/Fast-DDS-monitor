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
 * @file Entity.cpp
 */

#include "../headers/Entity.hpp"
#include "../utils.hpp"

namespace eprosima {
namespace statistics_backend {

Info Entity::get_info() const
{
    Info json_obj;

    json_obj["id"] = entityId_to_string(id());
    json_obj["name"] = name();
    json_obj["kind"] = kind();

    return json_obj;
}

std::vector<EntityId> Entity::get_entities(
        const EntityKind entity_type) const
{
    static_cast<void>(entity_type);
    return std::vector<EntityId>();
}

EntityKind Entity::kind() const
{
    return EntityKind::INVALID;
}


} // namespace statistics_backend
} // namespace eprosima
