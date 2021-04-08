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
 * @file RandomGenerator.hpp
 */

#ifndef _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_RANDOMGENERATOR_HPP_
#define _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_RANDOMGENERATOR_HPP_

#include <fastdds-statistics-backend/types/types.hpp>

#include "../entities/headers/Entity.hpp"
#include "../entities/headers/Host.hpp"
#include "../entities/headers/User.hpp"
#include "../entities/headers/Process.hpp"
#include "../entities/headers/Domain.hpp"
#include "../entities/headers/Locator.hpp"
#include "../entities/headers/Participant.hpp"
#include "../entities/headers/Endpoint.hpp"
#include "../entities/headers/Topic.hpp"

namespace eprosima {
namespace statistics_backend {

struct RandomGenerator
{
    static Info random_qos(EntityId seed);

    static std::vector<EntityPointer> init_random_domain(DomainPointer domain);
    static DomainPointer random_domain();

    static std::vector<EntityPointer> random_dds_entity(DomainPointer domain);

protected:

    static HostPointer random_host();
    static UserPointer random_user(HostPointer host);
    static ProcessPointer random_process(UserPointer user);
    static TopicPointer random_topic(DomainPointer domain);
    static ParticipantPointer random_participant(DomainPointer domain, ProcessPointer process);
    static EndpointPointer random_datawriter(ParticipantPointer participant, TopicPointer topic);
    static EndpointPointer random_datareader(ParticipantPointer participant, TopicPointer topic);
    static LocatorPointer random_locator(EndpointPointer endpoint);
};

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_RANDOMGENERATOR_HPP_
