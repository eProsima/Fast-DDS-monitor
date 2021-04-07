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
#include "../headers/Topic.hpp"
#include "../headers/Domain.hpp"
#include "../headers/Endpoint.hpp"

namespace eprosima {
namespace statistics_backend {

std::vector<EntityId> Topic::get_entities(
    const EntityKind entity_type) const
{
    std::vector<EntityId> ids;

    switch (entity_type)
    {
    case EntityKind::HOST:
    case EntityKind::USER:
    case EntityKind::PROCESS:
    case EntityKind::PARTICIPANT:
        return get_entities_related(endpoints_, entity_type);

    case EntityKind::DOMAIN :
        ids.push_back(domain_->id());
        return ids;

    case EntityKind::TOPIC :
        return ids;

    case EntityKind::DATAWRITER :
    case EntityKind::DATAREADER :
        return get_entities_kind(endpoints_, entity_type);

    case EntityKind::LOCATOR :
        return get_entities_related(endpoints_, entity_type);

    default:
        return ids;
    }
}

void Topic::add_endpoint(const EntityPointer endpoint)
{
    endpoints_[endpoint->id()] = endpoint;
}

void Topic::domain(const EntityPointer domain)
{
    domain_ = domain;
}


} // namespace statistics_backend
} // namespace eprosima
