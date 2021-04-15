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
 * @file RandomGenerator.cpp
 */

#include <memory>
#include <string>

#include "Database.hpp"
#include "RandomGenerator.hpp"

#include "../entities/utils.hpp"
#include "../entities/headers/Entity.hpp"
#include "../entities/headers/Host.hpp"
#include "../entities/headers/User.hpp"
#include "../entities/headers/Process.hpp"
#include "../entities/headers/Domain.hpp"
#include "../entities/headers/Locator.hpp"
#include "../entities/headers/Participant.hpp"
#include "../entities/headers/Endpoint.hpp"
#include "../entities/headers/Topic.hpp"
#include "../entities/headers/DataWriter.hpp"
#include "../entities/headers/DataReader.hpp"

namespace eprosima {
namespace statistics_backend {

int RandomGenerator::random_range(int max, unsigned int seed) /* = 0 */
{
    if (seed != 0)
    {
        srand(seed);
    }

    return rand() % max;
}

std::vector<EntityPointer> RandomGenerator::init_random_domain(DomainPointer domain)
{
    // This implementation only creates a std struct with one of each kind (2 locators)
    HostPointer host = new_host_();

    UserPointer user = new_user_(host);

    ProcessPointer process = new_process_(user);

    ParticipantPointer part = new_participant_(domain, process);

    TopicPointer topic = new_topic_(domain);

    EndpointPointer writer = new_datawriter_(part, topic);

    EndpointPointer reader = new_datareader_(part, topic);

    // Locator shared for Writer and Reader
    LocatorPointer locator = new_locator_(writer);
    reader->add_locator(locator);
    locator->add_endpoint(reader);

    // Locator only for Writer
    LocatorPointer locatorw = new_locator_(writer);

    return std::vector<EntityPointer>({host, user, process, part, topic, writer, reader, locator, locatorw});
}

std::vector<EntityPointer> RandomGenerator::add_random_entity(DomainPointer domain)
{
    int aux_ran = random_range(100);

    if (aux_ran < ENDPOINT_PERC)
    {
        return random_endpoint_(domain);
    }
    else if (aux_ran < (ENDPOINT_PERC + TOPIC_PERC))
    {
        return random_topic_(domain);
    }
    else
    {
        return random_participant_(domain);
    }
}

std::vector<EntityPointer> RandomGenerator::random_topic_(DomainPointer domain)
{
    // Get a participant in domain
    std::vector<EntityPointer> parts = domain->participants();
    assert (!parts.empty());
    ParticipantPointer part = std::dynamic_pointer_cast<Participant>(random_choice(parts));

    // Get a locator in participant
    std::vector<EntityId> locator_ids = part->get_entities(EntityKind::LOCATOR);
    assert (!locator_ids.empty());
    LocatorPointer locator = std::dynamic_pointer_cast<Locator>(
        Database::get_instance()->get_entity(random_choice(locator_ids)));

    // Creates Topic
    TopicPointer topic = new_topic_(domain);

    // Creates a new endpoint
    EndpointPointer endpoint = new_endpoint_(part, topic, locator);

    return std::vector<EntityPointer>({topic, endpoint});
}

std::vector<EntityPointer> RandomGenerator::random_participant_(DomainPointer domain)
{
    // Get a user in domain
    std::vector<EntityId> user_ids = domain->get_entities(EntityKind::USER);
    assert (!user_ids.empty());
    UserPointer user = std::dynamic_pointer_cast<User>(
        Database::get_instance()->get_entity(random_choice(user_ids)));

    // Get a topic in domain
    std::vector<EntityPointer> topics = domain->topics();
    assert (!topics.empty());
    TopicPointer topic = std::dynamic_pointer_cast<Topic>(random_choice(topics));

    // Get a locator in User
    std::vector<EntityId> locator_ids = user->get_entities(EntityKind::LOCATOR);
    assert (!locator_ids.empty());
    LocatorPointer locator = std::dynamic_pointer_cast<Locator>(
        Database::get_instance()->get_entity(random_choice(locator_ids)));

    // Creates Process
    ProcessPointer process = new_process_(user);

    // Creates a Participant
    ParticipantPointer participant = new_participant_(domain, process);

    // Creates endpoint
    EndpointPointer endpoint = new_endpoint_(participant, topic, locator);

    return std::vector<EntityPointer>({process, participant, endpoint});
}

std::vector<EntityPointer> RandomGenerator::random_endpoint_(DomainPointer domain)
{
    // Get a participant in domain
    std::vector<EntityPointer> parts = domain->participants();
    assert (!parts.empty());
    ParticipantPointer part = std::dynamic_pointer_cast<Participant>(random_choice(parts));

    // Get a topic in domain
    std::vector<EntityPointer> topics = domain->topics();
    assert (!topics.empty());
    TopicPointer topic = std::dynamic_pointer_cast<Topic>(random_choice(topics));

    // Get a locator in participant
    std::vector<EntityId> locator_ids = part->get_entities(EntityKind::LOCATOR);
    assert (!locator_ids.empty());
    LocatorPointer locator = std::dynamic_pointer_cast<Locator>(
        Database::get_instance()->get_entity(random_choice(locator_ids)));

    EndpointPointer endpoint = new_endpoint_(part, topic, locator);

    return std::vector<EntityPointer>({endpoint});
}

DomainPointer RandomGenerator::random_domain()
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    DomainPointer entity_p = std::make_shared<Domain>(id, "Domain_" + entityId_to_string(id));
    return entity_p;
}

HostPointer RandomGenerator::new_host_()
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    HostPointer entity_p = std::make_shared<Host>(id, "Host_" + entityId_to_string(id));
    return entity_p;
}

UserPointer RandomGenerator::new_user_(HostPointer host)
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    UserPointer entity_p = std::make_shared<User>(id, "User_" + entityId_to_string(id));

    entity_p->host(host);
    host->add_user(entity_p);

    return entity_p;
}

ProcessPointer RandomGenerator::new_process_(UserPointer user)
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    ProcessPointer entity_p = std::make_shared<Process>(id, "Process_" + entityId_to_string(id));

    entity_p->user(user);
    user->add_process(entity_p);

    return entity_p;
}

TopicPointer RandomGenerator::new_topic_(DomainPointer domain)
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    TopicPointer entity_p = std::make_shared<Topic>(id, "Topic_" + entityId_to_string(id));

    entity_p->domain(domain);
    domain->add_topic(entity_p);

    return entity_p;
}

ParticipantPointer RandomGenerator::new_participant_(DomainPointer domain, ProcessPointer process)
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    ParticipantPointer entity_p = std::make_shared<Participant>(id, "Participant_" + entityId_to_string(id));

    entity_p->guid("01:0f:" + entityId_to_string(id) + ":" + entityId_to_string(id));
    entity_p->qos(random_qos());

    entity_p->domain(domain);
    entity_p->process(process);

    domain->add_participant(entity_p);
    process->add_participant(entity_p);

    return entity_p;
}

EndpointPointer RandomGenerator::new_datawriter_(ParticipantPointer participant, TopicPointer topic)
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    DataWriterPointer entity_p = std::make_shared<DataWriter>(id, "DataWriter_" + entityId_to_string(id));

    entity_p->guid("01:0f:" + entityId_to_string(id) + ":" + entityId_to_string(id));
    entity_p->qos(random_qos());

    entity_p->participant(participant);
    entity_p->topic(topic);

    participant->add_endpoint(entity_p);
    topic->add_endpoint(entity_p);

    return entity_p;
}

EndpointPointer RandomGenerator::new_datareader_(ParticipantPointer participant, TopicPointer topic)
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    DataReaderPointer entity_p = std::make_shared<DataReader>(id, "DataReader_" + entityId_to_string(id));

    entity_p->guid(entityId_to_string(id) + ":" + entityId_to_string(id));
    entity_p->qos(random_qos());

    entity_p->participant(participant);
    entity_p->topic(topic);

    participant->add_endpoint(entity_p);
    topic->add_endpoint(entity_p);

    return entity_p;
}

LocatorPointer RandomGenerator::new_locator_(EndpointPointer endpoint)
{
    EntityId id = EntityId(Database::get_instance()->next_id());
    LocatorPointer entity_p = std::make_shared<Locator>(id, "Locator_" + entityId_to_string(id));

    entity_p->add_endpoint(endpoint);

    endpoint->add_locator(entity_p);

    return entity_p;
}

EndpointPointer RandomGenerator::new_endpoint_(
    ParticipantPointer participant,
    TopicPointer topic,
    LocatorPointer locator)
{
    EndpointPointer entity_p;
    if (random_range(2))
    {
        entity_p = new_datareader_(participant, topic);
    }
    else
    {
        entity_p = new_datawriter_(participant, topic);
    }

    entity_p->add_locator(locator);
    locator->add_endpoint(entity_p);

    return entity_p;
}


Info RandomGenerator::random_qos()
{
    // Seed rand number
    int aux_ran;

    Info qos;

    // Add durability
    qos["durability"] = Info();
    aux_ran = random_range(4);

    if (aux_ran == 0)
    {
        qos["durability"]["kind"] = "VOLATILE_DURABILITY_QOS";
    }
    else if (aux_ran == 1)
    {
        qos["durability"]["kind"] = "TRANSIENT_LOCAL_DURABILITY_QOS";
    }
    else if (aux_ran == 2)
    {
        qos["durability"]["kind"] = "TRANSIENT_DURABILITY_QOS";
    }
    else
    {
        qos["durability"]["kind"] = "PERSISTENT_DURABILITY_QOS";
    }

    // Add Reliability
    qos["reliability"] = Info();
    aux_ran = random_range(2);

    if (aux_ran == 0)
    {
        qos["reliability"]["kind"] = "BEST_EFFORT_RELIABILITY_QOS";
    }
    else if (aux_ran == 1)
    {
        qos["reliability"]["kind"] = "RELIABLE_RELIABILITY_QOS";
        qos["reliability"]["max_blocking_time"] = Info();
        qos["reliability"]["max_blocking_time"]["nanoseconds"] = random_range(1000000000);
        qos["reliability"]["max_blocking_time"]["seconds"] = random_range(100);
    }

    return qos;

    // Complete QoS information

    // Info json_obj = R"({
    //     "data_sharing":
    //     {
    //         "domain_ids":
    //         [
    //             0
    //         ],
    //         "kind": "AUTO",
    //         "max_domains": 1,
    //         "shm_directory": "/dev/shm"
    //     },
    //     "deadline":
    //     {
    //         "period":
    //         {
    //             "nanoseconds": 50,
    //             "seconds": 10
    //         }
    //     },
    //     "destination_order":
    //     {
    //         "kind": "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS"
    //     },
    //     "disable_positive_acks":
    //     {
    //         "duration":
    //         {
    //             "nanoseconds": 100,
    //             "seconds": 0
    //         },
    //         "enabled": true
    //     },
    //     "durability":
    //     {
    //         "kind": "VOLATILE_DURABILITY_QOS"
    //     },
    //     "durability_service":
    //     {
    //         "history_depth": "1",
    //         "history_kind": "KEEP_LAST_HISTORY_QOS",
    //         "max_instances": "30",
    //         "max_samples": "3000",
    //         "max_samples_per_instance": "100",
    //         "service_cleanup_delay":
    //         {
    //             "nanoseconds": 0,
    //             "seconds": 5
    //         }
    //     },
    //     "group_data": "9d46781410ff",
    //     "latency_budget":
    //     {
    //         "duration":
    //         {
    //             "nanoseconds": 50,
    //             "seconds": 10
    //         }
    //     },
    //     "lifespan":
    //     {
    //         "duration":
    //         {
    //             "nanoseconds": 0,
    //             "seconds": 10000
    //         }
    //     },
    //     "liveliness":
    //     {
    //         "announcement_period":
    //         {
    //             "nanoseconds": 0,
    //             "seconds": 3
    //         },
    //         "lease_duration":
    //         {
    //             "nanoseconds": 0,
    //             "seconds": 10
    //         },
    //         "kind": "AUTOMATIC_LIVELINESS_QOS"
    //     },
    //     "ownership":
    //     {
    //         "kind": "SHARED_OWNERSHIP_QOS"
    //     },
    //     "partition":
    //     [
    //         "partition_1",
    //         "partition_2"
    //     ],
    //     "presentation":
    //     {
    //         "access_scope": "INSTANCE_PRESENTATION_QOS",
    //         "coherent_access": false,
    //         "ordered_access": false
    //     },
    //     "reliability":
    //     {
    //         "kind": "RELIABLE_RELIABILITY_QOS",
    //         "max_blocking_time":
    //         {
    //             "nanoseconds": 0,
    //             "seconds": 3
    //         }
    //     },
    //     "representation":
    //     [
    //     ],
    //     "time_based_filter":
    //     {
    //         "minimum_separation":
    //         {
    //             "seconds": 12,
    //             "nanoseconds": 0
    //         }
    //     },
    //     "topic_data": "5b33419a",
    //     "type_consistency":
    //     {
    //         "force_type_validation": false,
    //         "ignore_member_names": false,
    //         "ignore_sequence_bounds": true,
    //         "ignore_string_bounds": true,
    //         "kind": "DISALLOW_TYPE_COERCION",
    //         "prevent_type_widening": false
    //     },
    //     "user_data": "ff00"
    // })"_json;

    // json_obj["id"] = entity_id;

    // return json_obj;
}

} // namespace statistics_backend
} // namespace eprosima
