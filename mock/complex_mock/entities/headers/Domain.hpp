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
 * @file Domain.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DOMAIN_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DOMAIN_HPP_

#include "Entity.hpp"

namespace eprosima {
namespace statistics_backend {

//! Domain Entity in Database
class Domain : public Entity
{
public:

    //! Using Entity constructors
    using Entity::Entity;

    //! Override of \c get_entities Entity method
    std::vector<EntityId> get_entities(
            const EntityKind entity_type) const override;

    //! Get Participants under Entity
    std::vector<EntityPointer> participants();
    //! Get Topics under Entity
    std::vector<EntityPointer> topics();

    //! Add Entity to Participant list
    void add_participant(
            EntityPointer participant);
    //! Add Entity to Topic list
    void add_topic(
            EntityPointer topic);

    //! Overwrite of \c kind method from Entity
    EntityKind kind() const override
    {
        return EntityKind::DOMAIN_ENTITY;
    }

private:

    //! Collection of Participants subentities
    std::map<EntityId, EntityPointer> participants_;

    //! Collection of Topics subentities
    std::map<EntityId, EntityPointer> topics_;
};

//! Type name for entity shared pointer
using DomainPointer = std::shared_ptr<Domain>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DOMAIN_HPP_
