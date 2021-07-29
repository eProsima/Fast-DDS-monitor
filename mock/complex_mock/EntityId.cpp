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
 * @file EntityId.cpp
 */

#include <fastdds_statistics_backend/types/EntityId.hpp>

namespace eprosima {
namespace statistics_backend {

/*
 * Standar EntityId
 * No modifications made over the std EntityId implementation
 */

EntityId::EntityId() noexcept
    : value_(ENTITY_ID_INVALID)
{
}

EntityId::EntityId(
        int64_t value) noexcept
    : value_(value)
{
}

EntityId EntityId::all() noexcept
{
    return EntityId(ENTITY_ID_ALL);
}

EntityId EntityId::invalid() noexcept
{
    return EntityId(ENTITY_ID_INVALID);
}

bool EntityId::is_valid() const noexcept
{
    return (value_ >= 0);
}

void EntityId::invalidate() noexcept
{
    value_ = ENTITY_ID_INVALID;
}

int64_t EntityId::value() const noexcept
{
    return value_;
}

} // namespace statistics_backend
} // namespace eprosima
