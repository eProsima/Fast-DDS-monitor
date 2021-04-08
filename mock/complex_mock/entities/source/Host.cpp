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

#include "../utils.hpp"
#include "../headers/Host.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> Host::get_entities(
    const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
    case EntityKind::HOST:
        return ids;

    case EntityKind::USER:
        return get_ids(users_);

    case EntityKind::PROCESS:
    case EntityKind::DOMAIN :
    case EntityKind::TOPIC :
    case EntityKind::PARTICIPANT:
    case EntityKind::DATAWRITER :
    case EntityKind::DATAREADER :
    case EntityKind::LOCATOR :
        return get_entities_related(users_, entity_type);

    default:
        return ids;
    }
}

void Host::add_user(const EntityPointer user)
{
    users_[user->id()] = user;
}

} // namespace statistics_backend
} // namespace eprosima
