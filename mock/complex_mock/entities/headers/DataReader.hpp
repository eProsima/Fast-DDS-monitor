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
 * @file DataReader.hpp
 */

#include "Endpoint.hpp"

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DATAREADER_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DATAREADER_HPP_

namespace eprosima {
namespace statistics_backend {

//! DataReader Entity in Database
class DataReader : public Endpoint
{
public:

    //! Using Endpoint constructors
    using Endpoint::Endpoint;

    //! Overwrite of \c kind method from Entity
    EntityKind kind() const override
    {
        return EntityKind::DATAREADER;
    }

};

//! Type name for entity shared pointer
using DataReaderPointer = std::shared_ptr<DataReader>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DATAREADER_HPP_
