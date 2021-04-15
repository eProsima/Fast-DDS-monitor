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
 * @file DDSEntity.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DDSENTITY_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DDSENTITY_HPP_

#include "Entity.hpp"

namespace eprosima {
namespace statistics_backend {

#define DEFAULT_GUID "01:0f:XX:XX"

/**
 * Encapsulates the common functionality for Participant, DataReader and DataWriter
 * It contains a \c guid and \c qos information
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
    void guid(const std::string guid)
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
    void qos(Info qos)
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
