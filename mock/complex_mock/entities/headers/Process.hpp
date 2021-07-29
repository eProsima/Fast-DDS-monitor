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
 * @file Process.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_PROCESS_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_PROCESS_HPP_

#include "Entity.hpp"

namespace eprosima {
namespace statistics_backend {

//! Process Entity in Database
class Process : public Entity
{
public:

    //! Using Entity constructors
    using Entity::Entity;

    //! Override of \c get_entities Entity method
    std::vector<EntityId> get_entities(
            const EntityKind entity_type) const override;

    //! Add Entity to Participant list
    void add_participant(
            EntityPointer participant);

    //! Add User as connected Entity
    void user(
            EntityPointer user);

    //! Overwrite of \c kind method from Entity
    EntityKind kind() const override
    {
        return EntityKind::PROCESS;
    }

    //! Field \c pid getter
    std::string pid() const;

    //! Override of \c get_info Entity method
    Info get_info() const override;

    //! Overwrite alive so Process is always not alive
    bool alive() const override
    {
        return false;
    }

private:

    //! Collection of participants subentities
    std::map<EntityId, EntityPointer> participants_;

    //! Reference to user superentity
    EntityPointer user_;
};

//! Type name for entity shared pointer
using ProcessPointer = std::shared_ptr<Process>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_PROCESS_HPP_
