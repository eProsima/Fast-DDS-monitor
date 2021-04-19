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
    EntityKind kind() const
    {
        return EntityKind::DATAREADER;
    }

};

//! Type name for entity shared pointer
using DataReaderPointer = std::shared_ptr<DataReader>;

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_DATAREADER_HPP_
