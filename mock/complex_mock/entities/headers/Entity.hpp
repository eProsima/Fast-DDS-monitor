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

#include <fastdds_statistics_backend/types/types.hpp>

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENTITY_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENTITY_HPP_

namespace eprosima {
namespace statistics_backend {

/**
 * All Entities in the Database are subclasses of \c Entity .
 * This class represents the interface for each entity kind.
 *
 * The entities along the Database are referenced one to each other when they are directly related.
 * These entities hold a shared pointer to those connected entities.
 *
 * In order to simplify the logic, all Entities would containe \c EntityPointer instead of more.
 * specific pointers for every subentity or superentity they have.
 */
class Entity
{
public:

    /**
     * @brief Entity standard constructor
     *
     * @param id new entity id (must be unique)
     * @param name new entity name
     */
    Entity(
            EntityId& id,
            std::string name)
        : id_(id)
        , name_(name)
        , alias_(name)
    {
    }

    virtual ~Entity()
    {
    }

    /**
     * @brief Get all entity ids of a kind related with this one
     *
     * @warning It is not implemented to remove duplicate ids
     *
     * @param entity_type kind of entities to retrieve information
     *
     * @return vector of entity ids
     */
    virtual std::vector<EntityId> get_entities(
            const EntityKind entity_type) const;

    /**
     * @brief Get info of entity
     *
     * This function must be override in subentities that has extra information.
     * It is recommended to call the father method in every subentity implementation.
     *
     * @return entity name
     */
    virtual Info get_info() const;

    /**
     * @brief Get name of entity
     *
     * @return entity name
     */
    std::string name() const
    {
        return name_;
    }

    //! Alias getter
    std::string alias() const
    {
        return alias_;
    }

    //! Alias setter
    void alias(
            std::string alias)
    {
        alias_ = alias;
    }

    /**
     * @brief Get id of entity
     *
     * @return entity id
     */
    EntityId id() const
    {
        return id_;
    }

    /**
     * @brief Get kind of entity
     *
     * This method must be implemented by every subclass
     *
     * @return entity kind
     */
    virtual EntityKind kind() const;

    /**
     * Whether the entity is alive
     *
     * @return true by default
     */
    virtual bool alive() const;

private:

    //! Id of the entity
    const EntityId id_;

    //! Name of the entity
    const std::string name_;

    //! Name of the entity
    std::string alias_;
};

//! Type name for entity shared pointer
using EntityPointer = std::shared_ptr<Entity>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENTITY_HPP_
