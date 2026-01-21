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
 * @file Participant.cpp
 */

#include "../headers/Domain.hpp"
#include "../headers/Endpoint.hpp"
#include "../headers/Participant.hpp"
#include "../headers/Process.hpp"
#include "../utils.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> Participant::get_entities(
        const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
        case EntityKind::HOST:
        case EntityKind::USER:
            return process_->get_entities(entity_type);

        case EntityKind::PROCESS:
            ids.push_back(process_->id());
            return ids;

        case EntityKind::PARTICIPANT:
            return ids;

        case EntityKind::DOMAIN_ENTITY:
            ids.push_back(domain_->id());
            return ids;

        case EntityKind::DATAWRITER:
        case EntityKind::DATAREADER:
            return get_entities_kind(endpoints_, entity_type);

        case EntityKind::TOPIC:
        case EntityKind::LOCATOR:
            return get_entities_related(endpoints_, entity_type);

        default:
            return ids;
    }
}

void Participant::add_endpoint(
        const EntityPointer endpoint)
{
    endpoints_[endpoint->id()] = endpoint;
}

void Participant::domain(
        const EntityPointer domain)
{
    domain_ = domain;
}

void Participant::process(
        const EntityPointer process)
{
    process_ = process;
}

} // namespace statistics_backend
} // namespace eprosima
