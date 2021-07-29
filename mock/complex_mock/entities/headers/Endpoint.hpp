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
 * @file Endpoint.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENDPOINT_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENDPOINT_HPP_

#include "DDSEntity.hpp"

namespace eprosima {
namespace statistics_backend {

//! Represents the Superclass for DataWriter and DataReader
class Endpoint : public DDSEntity
{
public:

    //! Using Entity constructors
    using DDSEntity::DDSEntity;

    //! Override of \c get_entities Entity method
    std::vector<EntityId> get_entities(
            const EntityKind entity_type) const override;

    //! Add Entity to Locator list
    void add_locator(
            EntityPointer locator);

    //! Add Participant as connected Entity
    void participant(
            EntityPointer participant);
    //! Add Topic as connected Entity
    void topic(
            EntityPointer topic);

    //! Get the topic name related
    std::string topic_name() const;

    //! Override \c get_info from \c Entity to add \c topic
    Info get_info() const override;

private:

    //! Collection of Locators subentities
    std::map<EntityId, EntityPointer> locators_;

    //! Participant superentity
    EntityPointer participant_;

    //! Topic superentity
    EntityPointer topic_;
};

//! Type name for entity shared pointer
using EndpointPointer = std::shared_ptr<Endpoint>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENDPOINT_HPP_
