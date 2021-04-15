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
    void add_locator(EntityPointer locator);

    //! Add Participant as connected Entity
    void participant(EntityPointer participant);
    //! Add Topic as connected Entity
    void topic(EntityPointer topic);

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
