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
 * @file Participant.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_PARTICIPANT_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_PARTICIPANT_HPP_

#include "DDSEntity.hpp"

namespace eprosima {
namespace statistics_backend {

class Participant : public DDSEntity
{
public:

    //! Using DDSEntity constructors
    using DDSEntity::DDSEntity;

    //! Override of \c get_entities Entity method
    std::vector<EntityId> get_entities(
            const EntityKind entity_type) const override;

    //! Add Entity to Endpoint list
    void add_endpoint(
            EntityPointer endpoint);

    //! Add Process as connected Entity
    void process(
            EntityPointer process);
    //! Add Domain as connected Entity
    void domain(
            EntityPointer domain);

    //! Overwrite of \c kind method from Entity
    EntityKind kind() const override
    {
        return EntityKind::PARTICIPANT;
    }

private:

    //! Collection of endpoints subentities
    std::map<EntityId, EntityPointer> endpoints_;

    //! Process superentity
    EntityPointer process_;

    //! Domain superentity
    EntityPointer domain_;
};

//! Type name for entity shared pointer
using ParticipantPointer = std::shared_ptr<Participant>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_PARTICIPANT_HPP_
