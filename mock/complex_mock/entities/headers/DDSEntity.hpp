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
 * @file DDSEntity.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DDSENTITY_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DDSENTITY_HPP_

#include "Entity.hpp"

namespace eprosima {
namespace statistics_backend {

#define DEFAULT_GUID "01:0f:XX:XX"

/**
 * Encapsulates the common functionality for Participant, DataReader and DataWriter.
 * It contains a \c guid and \c qos information.
 */
class DDSEntity : public Entity
{
public:

    //! Using Entity constructors
    using Entity::Entity;

    /**
     * @brief Overwrite of \c get_info method from Entity
     *
     * @return \c get_info from Entity plus guid and QoS
     */
    Info get_info() const override
    {
        Info info = Entity::get_info();
        info["guid"] = guid();
        info["QoS"] = qos();

        return info;
    }

    /**
     * @brief guid getter
     *
     * @return entity guid
     */
    std::string guid() const
    {
        return guid_;
    }

    /**
     * @brief guid setter
     *
     * @param guid new guid
     */
    void guid(
            const std::string guid)
    {
        guid_ = guid;
    }

    /**
     * @brief qos getter
     *
     * @return entity qos
     */
    Info qos() const
    {
        return qos_;
    }

    /**
     * @brief qos setter
     *
     * @param qos new qos
     */
    void qos(
            Info qos)
    {
        qos_ = qos;
    }

private:

    //! Guid
    std::string guid_ = DEFAULT_GUID;

    //! Qos in json structure
    Info qos_;
};

//! Type name for entity shared pointer
using DDSEntityPointer = std::shared_ptr<DDSEntity>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DDSENTITY_HPP_
