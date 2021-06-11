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
