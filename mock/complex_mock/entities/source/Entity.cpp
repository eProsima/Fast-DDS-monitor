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
    json_obj["alias"] = alias();
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

bool Entity::alive() const
{
    return true;
}

} // namespace statistics_backend
} // namespace eprosima
