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

    // Using Entity constructors
    using Entity::Entity;

    //! Override of \c get_entities Entity method
    std::vector<EntityId> get_entities(
        const EntityKind entity_type) const override;

    //! Get Participants under Entity
    std::vector<EntityPointer> participants();
    //! Get Topics under Entity
    std::vector<EntityPointer> topics();

    //! Add Entity to Participant list
    void add_participant(EntityPointer participant);
    //! Add Entity to Topic list
    void add_topic(EntityPointer topic);

    //! Overwrite of \c kind method from Entity
    EntityKind kind() const
    {
        return EntityKind::DOMAIN;
    }

private:
    std::map<EntityId, EntityPointer> participants_;
    std::map<EntityId, EntityPointer> topics_;
};

//! Type name for entity shared pointer
using DomainPointer = std::shared_ptr<Domain>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DOMAIN_HPP_
