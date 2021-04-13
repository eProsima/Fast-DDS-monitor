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

    // It chooeses randomly between creating a topic, a participant or an endpoint
    static std::vector<EntityPointer> add_random_entity(DomainPointer domain);

protected:

    static const int ENDPOINT_PERC = 50;
    static const int TOPIC_PERC = 30;
    static const int PARTICIPANT_PERC = 20;

    static HostPointer new_host_();
    static UserPointer new_user_(HostPointer host);
    static ProcessPointer new_process_(UserPointer user);
    static TopicPointer new_topic_(DomainPointer domain);
    static ParticipantPointer new_participant_(DomainPointer domain, ProcessPointer process);
    static EndpointPointer new_datawriter_(ParticipantPointer participant, TopicPointer topic);
    static EndpointPointer new_datareader_(ParticipantPointer participant, TopicPointer topic);
    static EndpointPointer new_endpoint_(ParticipantPointer participant, TopicPointer topic, LocatorPointer locator);
    static LocatorPointer new_locator_(EndpointPointer endpoint);

    // Create a new topic in domain, and creates a new endpoint in this topic in a random participant
    static std::vector<EntityPointer> random_topic_(DomainPointer domain);

    // Creates a new Participant in a new Process in a random Host and a random endpoint underneath
    static std::vector<EntityPointer> random_participant_(DomainPointer domain);

    // Creates a new Random Endpoint under a random Participant and with Random Locator
    static std::vector<EntityPointer> random_endpoint_(DomainPointer domain);

    static int random_range(int max, unsigned int seed = 0);

    template <class T>
    static T random_choice(std::vector<T> vector)
    {
        return vector[random_range(vector.size())];
    }
};

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_RANDOMGENERATOR_HPP_
