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

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_RANDOMGENERATOR_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_RANDOMGENERATOR_HPP_

#include <fastdds-statistics-backend/types/types.hpp>

#include "../entities/headers/Domain.hpp"
#include "../entities/headers/Endpoint.hpp"
#include "../entities/headers/Entity.hpp"
#include "../entities/headers/Host.hpp"
#include "../entities/headers/Locator.hpp"
#include "../entities/headers/Participant.hpp"
#include "../entities/headers/Process.hpp"
#include "../entities/headers/Topic.hpp"
#include "../entities/headers/User.hpp"

namespace eprosima {
namespace statistics_backend {

/**
 * Class to encapsulate static methods to generate entities randomly
 */
struct RandomGenerator
{
public:
    /**
     * @brief Return a raStatic classndom QoS
     *
     * Set two tags: "durability" , "reliability" with valid random QoS information
     */
    static Info random_qos();

    /**
     * @brief Return new entities created under a Domain
     *
     * Create one new entity of each kind (except Domain) and make the connections between them and the domain.
     * Two Locators are created, one connected to DataWriter and DataReader, and one only connected with DtaWriter.
     *
     * @return Vector with pointers to every new entity created
     */
    static std::vector<EntityPointer> init_random_domain(DomainPointer domain);

    /**
     * @brief Return a new Domain Entity
     *
     * Create a new Domain Entity with a unique ID.
     *
     * @return Pointer to the new Domain created
     */
    static DomainPointer random_domain();

    /**
     * @brief Create new Entities of random kind
     *
     * Randomly chooses between creating:
     * - new Endpoint
     * - new Process + new Participant + new Endpoint
     * - new Topic + new Endpoint
     *
     * @return Vector with pointers to every new entity created
     */
    static std::vector<EntityPointer> add_random_entity(DomainPointer domain);

protected:

    /////
    // Probabilities

    //! Probability in percentage of creating a new endpoint in <add_random_entity> method
    static const int ENDPOINT_PERC = 50;

    //! Probability in percentage of creating a new topic in <add_random_entity> method
    static const int TOPIC_PERC = 30;

    //! Probability in percentage of creating a new process in <add_random_entity> method
    static const int PARTICIPANT_PERC = 20;

    /////
    // New entities factories

    // The name generated for each entity is <kind>_<id>

    //! Create a new Entity Host
    static HostPointer new_host_();

    //! Create a new Entity User below a host and connect them
    static UserPointer new_user_(HostPointer host);

    //! Create a new Entity Process below a user and connect them
    static ProcessPointer new_process_(UserPointer user);

    //! Create a new Entity Topic below a Domain and connect them
    static TopicPointer new_topic_(DomainPointer domain);

    //! Create a new Entity Participant below a Domain and a Process and connect them
    static ParticipantPointer new_participant_(DomainPointer domain, ProcessPointer process);

    //! Create a new Entity DataWriter below a Topic and a Participant and connect them
    static EndpointPointer new_datawriter_(ParticipantPointer participant, TopicPointer topic);

    //! Create a new Entity DataReader below a Topic and a Participant and connect them
    static EndpointPointer new_datareader_(ParticipantPointer participant, TopicPointer topic);

    //! Create a new Endpoint randomly between DataWriter and DataReader below a Topic and a Participant and connect them
    static EndpointPointer new_endpoint_(ParticipantPointer participant, TopicPointer topic, LocatorPointer locator);

    //! Create a new Entity Locator below an Endpoint and connect them
    static LocatorPointer new_locator_(EndpointPointer endpoint);

    /////
    // Multiple random factories

    //! Create a new topic in domain, and creates a new endpoint in this topic in a random participant
    static std::vector<EntityPointer> random_topic_(DomainPointer domain);

    //! Creates a new Participant in a new Process in a random User and a random endpoint underneath
    static std::vector<EntityPointer> random_participant_(DomainPointer domain);

    //! Creates a new Random Endpoint under a random Participant and with Random Locator
    static std::vector<EntityPointer> random_endpoint_(DomainPointer domain);

    /////
    // Random util methods

    /**
     * Return a value in range [0, max) using the seed <seed>
     * If <seed> = 0 the random seed is not set
     */
    static int random_range(int max, unsigned int seed = 0);

    //! Return a random value inside a vector
    template <class T>
    static T random_choice(std::vector<T> vector)
    {
        return vector[random_range(vector.size())];
    }
};

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_RANDOMGENERATOR_HPP_
