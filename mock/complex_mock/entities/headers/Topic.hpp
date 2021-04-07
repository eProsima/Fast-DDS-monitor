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
 * @file Topic.hpp
 */

#ifndef _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_TOPIC_HPP_
#define _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_TOPIC_HPP_

#include "Entity.hpp"

namespace eprosima {
namespace statistics_backend {

class Topic : public Entity
{
public:

    using Entity::Entity;

    std::vector<EntityId> get_entities(
        const EntityKind entity_type) const override;

    void add_endpoint(EntityPointer endpoint);

    void domain(EntityPointer domain);

    EntityKind kind() const
    {
        return EntityKind::TOPIC;
    }

private:
    std::map<EntityId, EntityPointer> endpoints_;
    EntityPointer domain_;
};

using TopicPointer = std::shared_ptr<Topic>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_TOPIC_HPP_
