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

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_UTILS_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_UTILS_HPP_

namespace eprosima {
namespace statistics_backend {

/**
 * @brief Return a vector with the keys of a map
 *
 * @param map map to get the keys
 *
 * @return keys of a map
 */
template<class K, class V>
std::vector<K> keys(
        const std::map<K, V> map)
{
    std::vector<K> result;
    for (auto element : map)
    {
        result.push_back(element.first);
    }
    return result;
}

/**
 * @brief Return a vector with the ids in a map of entities
 *
 * @param map map of entities
 *
 * @return ids of entities in map
 */
std::vector<EntityId> get_ids(
        const std::map<EntityId, EntityPointer> map);

/**
 * @brief Return the concatenation of calling \c get_entities for all the entities in a map
 *
 * It is used to make the query of get_entities over a subset of entities
 *
 * @warning Does not remove duplicity
 *
 * @param map map of entitites
 * @param entity_type kind of entities to query
 *
 * @return vector of ids
 */
std::vector<EntityId> get_entities_related(
        const std::map<EntityId, EntityPointer> map,
        const EntityKind entity_type);

/**
 * @brief Return the entity ids of all entities in a map that are of kind \c entity_type
 *
 * It is used to separate \c DataWriter and \c DataReaders in \c Endpoint map of a \c Participant
 *
 * @param map map of entities
 * @param entity_type kind of entities to query
 *
 * @return vector of ids
 */
std::vector<EntityId> get_entities_kind(
        const std::map<EntityId, EntityPointer> map,
        const EntityKind entity_type);

/**
 * @brief Convert an id to String
 *
 * @param id id
 *
 * @return string referencing the id
 */
std::string entityId_to_string(
        EntityId id);

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_UTILS_HPP_
