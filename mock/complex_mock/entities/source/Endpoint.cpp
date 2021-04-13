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
#include "../headers/Endpoint.hpp"

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

    case EntityKind::DOMAIN :

    case EntityKind::DATAWRITER :
    case EntityKind::DATAREADER :
        return ids;

    case EntityKind::TOPIC :
        ids.push_back(topic_->id());
        return ids;

    case EntityKind::LOCATOR :
        return get_ids(locators_);

    default:
        return ids;
    }
}

void Endpoint::add_locator(const EntityPointer locator)
{
    locators_[locator->id()] = locator;
}

void Endpoint::participant(const EntityPointer participant)
{
    participant_ = participant;
}

void Endpoint::topic(const EntityPointer topic)
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
