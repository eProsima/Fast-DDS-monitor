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
 * @file Entity.hpp
 */

#include <fastdds_statistics_backend/types/types.hpp>

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
