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
 * @file Participant.hpp
 */

#ifndef _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_PARTICIPANT_HPP_
#define _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_PARTICIPANT_HPP_

#include "DDSEntity.hpp"

namespace eprosima {
namespace statistics_backend {

class Participant : public DDSEntity
{
public:

    // Using DDSEntity constructors
    using DDSEntity::DDSEntity;

    //! Override of \c get_entities Entity method
    std::vector<EntityId> get_entities(
        const EntityKind entity_type) const override;

    //! Add Entity to Endpoint list
    void add_endpoint(EntityPointer endpoint);

    //! Add Process as connected Entity
    void process(EntityPointer process);
    //! Add Domain as connected Entity
    void domain(EntityPointer domain);

    //! Overwrite of \c kind method from Entity
    EntityKind kind() const
    {
        return EntityKind::PARTICIPANT;
    }

private:
    std::map<EntityId, EntityPointer> endpoints_;
    EntityPointer process_;
    EntityPointer domain_;
};

//! Type name for entity shared pointer
using ParticipantPointer = std::shared_ptr<Participant>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_PARTICIPANT_HPP_
