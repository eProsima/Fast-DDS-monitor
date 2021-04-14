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
 * @file Domain.cpp
 */

#include "../headers/Domain.hpp"
#include "../headers/Participant.hpp"
#include "../headers/Topic.hpp"
#include "../utils.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> Domain::get_entities(
    const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
    case EntityKind::HOST:
    case EntityKind::USER:
    case EntityKind::PROCESS:
        return get_entities_related(participants_, entity_type);

    case EntityKind::PARTICIPANT:
        return get_ids(participants_);

    case EntityKind::DOMAIN :
        return ids;

    case EntityKind::TOPIC :
        return get_ids(topics_);

    case EntityKind::DATAWRITER :
    case EntityKind::DATAREADER :
    case EntityKind::LOCATOR :
        return get_entities_related(topics_, entity_type);

    default:
        return ids;
    }
}

std::vector<EntityPointer> Domain::participants()
{
    std::vector<EntityPointer> pointers;
    for (auto entity : participants_)
    {
        pointers.push_back(entity.second);
    }

    return pointers;
}

std::vector<EntityPointer> Domain::topics()
{
    std::vector<EntityPointer> pointers;
    for (auto entity : topics_)
    {
        pointers.push_back(entity.second);
    }

    return pointers;
}

void Domain::add_participant(const EntityPointer participant)
{
    participants_[participant->id()] = participant;
}

void Domain::add_topic(const EntityPointer topic)
{
    topics_[topic->id()] = topic;
}

} // namespace statistics_backend
} // namespace eprosima
