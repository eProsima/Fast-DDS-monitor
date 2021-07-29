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
 * @file Topic.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_TOPIC_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_TOPIC_HPP_

#include "Entity.hpp"

namespace eprosima {
namespace statistics_backend {

//! Topic Entity in Database
class Topic : public Entity
{
public:

    //! Using Entity constructors
    using Entity::Entity;

    //! Override of \c get_entities Entity method
    std::vector<EntityId> get_entities(
            const EntityKind entity_type) const override;

    //! Add Entity to Endpoint list
    void add_endpoint(
            EntityPointer endpoint);

    //! Add Domain as connected Entity
    void domain(
            EntityPointer domain);

    //! Overwrite of \c kind method from Entity
    EntityKind kind() const override
    {
        return EntityKind::TOPIC;
    }

    //! Field \c type getter
    std::string type() const;

    //! Override of \c get_info Entity method
    Info get_info() const override;

private:

    //! Collection of endpoints subentities
    std::map<EntityId, EntityPointer> endpoints_;

    //! Domain superentity
    EntityPointer domain_;
};

//! Type name for entity shared pointer
using TopicPointer = std::shared_ptr<Topic>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_TOPIC_HPP_
