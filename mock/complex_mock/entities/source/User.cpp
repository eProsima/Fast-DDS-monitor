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
 * @file User.cpp
 */

#include "../headers/User.hpp"
#include "../utils.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> User::get_entities(
        const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
        case EntityKind::HOST:
            ids.push_back(host_->id());
            return ids;

        case EntityKind::USER:
            return ids;

        case EntityKind::PROCESS:
            return get_ids(processes_);

        case EntityKind::DOMAIN_ENTITY:
        case EntityKind::TOPIC:
        case EntityKind::PARTICIPANT:
        case EntityKind::DATAWRITER:
        case EntityKind::DATAREADER:
        case EntityKind::LOCATOR:
            return get_entities_related(processes_, entity_type);

        default:
            return ids;
    }
}

void User::add_process(
        const EntityPointer process)
{
    processes_[process->id()] = process;
}

void User::host(
        const EntityPointer host)
{
    host_ = host;
}

} // namespace statistics_backend
} // namespace eprosima
