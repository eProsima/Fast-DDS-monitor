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
 * @file utils.cpp
 */

#include <random>
#include <sstream>

#include <fastdds_statistics_backend/types/types.hpp>

#include "utils.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> get_ids(
        const std::map<EntityId, EntityPointer> map)
{
    return keys<EntityId, EntityPointer>(map);
}

std::vector<EntityId> get_entities_related(
        const std::map<EntityId, EntityPointer> map,
        const EntityKind entity_type)
{
    std::vector<EntityId> result;
    for (auto entity : map)
    {
        // Call get_entities for each entity in the map
        auto entities = entity.second->get_entities(entity_type);
        result.insert(result.end(), entities.begin(), entities.end());
    }
    return result;
}

std::vector<EntityId> get_entities_kind(
        const std::map<EntityId, EntityPointer> map,
        const EntityKind entity_type)
{
    std::vector<EntityId> result;
    for (auto entity : map)
    {
        if (entity.second->kind() == entity_type)
        {
            // Only add to the vector those that are of entity_type
            result.push_back(entity.first);
        }
    }
    return result;
}

std::string entityId_to_string(
        EntityId id)
{
    std::ostringstream oss;
    oss << id;
    return oss.str();
}

} // namespace statistics_backend
} // namespace eprosima
