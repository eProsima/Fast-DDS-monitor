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
 * @file Process.cpp
 */

#include "../headers/Process.hpp"
#include "../utils.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> Process::get_entities(
        const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
        case EntityKind::HOST:
            return user_->get_entities(entity_type);

        case EntityKind::USER:
            ids.push_back(user_->id());
            return ids;

        case EntityKind::PROCESS:
            return ids;

        case EntityKind::PARTICIPANT:
            return get_ids(participants_);

        case EntityKind::DOMAIN_ENTITY:
        case EntityKind::TOPIC:
        case EntityKind::DATAWRITER:
        case EntityKind::DATAREADER:
        case EntityKind::LOCATOR:
            return get_entities_related(participants_, entity_type);

        default:
            return ids;
    }
}

void Process::add_participant(
        const EntityPointer participant)
{
    participants_[participant->id()] = participant;
}

void Process::user(
        const EntityPointer user)
{
    user_ = user;
}

std::string Process::pid() const
{
    return std::to_string(id().value());
}

Info Process::get_info() const
{
    Info info = Entity::get_info();
    info["pid"] = pid();
    info["alive"] = false;

    return info;
}

} // namespace statistics_backend
} // namespace eprosima
