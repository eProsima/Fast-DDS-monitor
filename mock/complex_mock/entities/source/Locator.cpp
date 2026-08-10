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
 * @file Locator.cpp
 */

#include "../headers/Endpoint.hpp"
#include "../headers/Locator.hpp"
#include "../utils.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> Locator::get_entities(
        const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
        case EntityKind::HOST:
        case EntityKind::USER:
        case EntityKind::PROCESS:
        case EntityKind::PARTICIPANT:
        case EntityKind::DOMAIN_ENTITY:
        case EntityKind::TOPIC:
            return get_entities_related(endpoints_, entity_type);

        case EntityKind::DATAWRITER:
        case EntityKind::DATAREADER:
            return get_entities_kind(endpoints_, entity_type);

        case EntityKind::LOCATOR:
            return ids;

        default:
            return ids;
    }
}

void Locator::add_endpoint(
        const EntityPointer endpoint)
{
    endpoints_[endpoint->id()] = endpoint;
}

} // namespace statistics_backend
} // namespace eprosima
