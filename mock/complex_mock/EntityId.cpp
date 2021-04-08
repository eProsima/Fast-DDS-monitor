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

#include <fastdds-statistics-backend/types/EntityId.hpp>

#include "database/Database.hpp"

namespace eprosima {
namespace statistics_backend {

// Mock up the EntityId default constructor to auto increment value
EntityId::EntityId()
    : value_(ENTITY_ID_INVALID)
{
}

EntityId::EntityId(
        int64_t value)
    : value_(value)
{
}

EntityId EntityId::all()
{
    return EntityId(ENTITY_ID_ALL);
}

EntityId EntityId::invalid()
{
    return EntityId(ENTITY_ID_INVALID);
}

bool EntityId::is_valid()
{
    return (value_ >= 0);
}

void EntityId::invalidate()
{
    value_ = ENTITY_ID_INVALID;
}

int64_t EntityId::value() const
{
    return value_;
}

} // namespace statistics_backend
} // namespace eprosima
