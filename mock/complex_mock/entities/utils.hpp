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
 * @file Entity.hpp
 */

#include <fastdds-statistics-backend/types/types.hpp>
#include "headers/Entity.hpp"

#ifndef _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_UTILS_HPP_
#define _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_UTILS_HPP_

namespace eprosima {
namespace statistics_backend {

template<class K, class V>
std::vector<K> keys(const std::map<K, V> map)
{
    std::vector<K> result;
    for (auto element : map)
    {
        result.push_back(element.first);
    }
    return result;
}

std::vector<EntityId> get_ids(const std::map<EntityId, EntityPointer> map);

std::vector<EntityId> get_entities_related(
    const std::map<EntityId, EntityPointer> map,
    const EntityKind entity_type);

std::vector<EntityId> get_entities_kind(
    const std::map<EntityId, EntityPointer> map,
    const EntityKind entity_type);

std::string entityId_to_string(EntityId id);

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_UTILS_HPP_
