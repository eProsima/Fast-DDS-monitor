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
#include "../headers/User.hpp"

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

    case EntityKind::DOMAIN :
    case EntityKind::TOPIC :
    case EntityKind::PARTICIPANT:
    case EntityKind::DATAWRITER :
    case EntityKind::DATAREADER :
    case EntityKind::LOCATOR :
        return get_entities_related(processes_, entity_type);

    default:
        return ids;
    }
}

void User::add_process(const EntityPointer process)
{
    processes_[process->id()] = process;
}

void User::host(const EntityPointer host)
{
    host_ = host;
}


} // namespace statistics_backend
} // namespace eprosima
