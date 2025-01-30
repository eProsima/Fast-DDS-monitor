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
 * @file Endpoint.cpp
 */

#include "../headers/Endpoint.hpp"
#include "../utils.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> Endpoint::get_entities(
        const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
        case EntityKind::HOST:
        case EntityKind::USER:
        case EntityKind::PROCESS:
            return participant_->get_entities(entity_type);

        case EntityKind::PARTICIPANT:
            ids.push_back(participant_->id());
            return ids;

        case EntityKind::DOMAIN_ENTITY:

        case EntityKind::DATAWRITER:
        case EntityKind::DATAREADER:
            return ids;

        case EntityKind::TOPIC:
            ids.push_back(topic_->id());
            return ids;

        case EntityKind::LOCATOR:
            return get_ids(locators_);

        default:
            return ids;
    }
}

void Endpoint::add_locator(
        const EntityPointer locator)
{
    locators_[locator->id()] = locator;
}

void Endpoint::participant(
        const EntityPointer participant)
{
    participant_ = participant;
}

void Endpoint::topic(
        const EntityPointer topic)
{
    topic_ = topic;
}

std::string Endpoint::topic_name() const
{
    return topic_->name();
}

Info Endpoint::get_info() const
{
    Info info = DDSEntity::get_info();
    info["topic"] = topic_name();
    return info;
}

} // namespace statistics_backend
} // namespace eprosima
