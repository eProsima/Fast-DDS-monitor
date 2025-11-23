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

        case EntityKind::DOMAIN_ENTITY:
            return ids;

        case EntityKind::TOPIC:
            return get_ids(topics_);

        case EntityKind::DATAWRITER:
        case EntityKind::DATAREADER:
        case EntityKind::LOCATOR:
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

void Domain::add_participant(
        const EntityPointer participant)
{
    participants_[participant->id()] = participant;
}

void Domain::add_topic(
        const EntityPointer topic)
{
    topics_[topic->id()] = topic;
}

} // namespace statistics_backend
} // namespace eprosima
