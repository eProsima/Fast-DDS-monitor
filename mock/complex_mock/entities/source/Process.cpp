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

        case EntityKind::DOMAIN:
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
