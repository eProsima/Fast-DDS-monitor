
#include <iostream>

#include <include/backend/SyncBackendConnection.h>
#include <include/model/ListItem.h>
#include <include/model/ListModel.h>
#include <include/model/SubListedListModel.h>
#include <include/model/dds/ParticipantModelItem.h>
#include <include/model/dds/EndpointModelItem.h>
#include <include/model/logical/TopicModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/physical/HostModelItem.h>
#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>
#include <include/backend/backend_utils.h>
#include <include/model/tree/TreeModel.h>

#include <core/StatisticsBackend.hpp>
#include <json.hpp>

#include <QDebug>

namespace backend {

using namespace eprosima::fastdds::dds::statistics;
using namespace models;

/// CREATE PRIVATE FUNCTIONS
ListItem* SyncBackendConnection::_create_process_data(EntityId id)
{
    std::cout << "Creating Process " << id << std::endl;
//    struct timespec ts = { 10, 0 };
//    nanosleep(&ts, NULL);
//    std::cout << "Unlock Creating Process " << id << std::endl;
    return new ProcessModelItem(id);
}

ListItem* SyncBackendConnection::_create_host_data(EntityId id)
{
    std::cout << "Creating Host " << id << std::endl;
    return new HostModelItem(id);
}

ListItem* SyncBackendConnection::_create_user_data(EntityId id)
{
    std::cout << "Creating User " << id << std::endl;
    return new UserModelItem(id);
}

ListItem* SyncBackendConnection::_create_domain_data(EntityId id)
{
    std::cout << "Creating Domain " << id << std::endl;
    return new DomainModelItem(id);
}

ListItem* SyncBackendConnection::_create_topic_data(EntityId id)
{
    std::cout << "Creating Topic " << id << std::endl;
    return new TopicModelItem(id);
}

ListItem* SyncBackendConnection::_create_participant_data(backend::EntityId id)
{
    std::cout << "Creating Participant " << id << std::endl;
    return new ParticipantModelItem(id);
}

ListItem* SyncBackendConnection::_create_endpoint_data(backend::EntityId id)
{
    std::cout << "Creating Endpoint " << id << std::endl;
    return new EndpointModelItem(id);
}

/// UPDATE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_host_data(ListItem* host_item)
{
    auto host_item_sublist = static_cast<SubListedListItem*>(host_item);

    return __update_entity_data(
                host_item_sublist,
                EntityType::USER,
                update_user_data,
                _create_user_data);
}

bool SyncBackendConnection::update_user_data(ListItem* user_item)
{
    auto user_item_sublist = static_cast<SubListedListItem*>(user_item);

    return __update_entity_data(
                user_item_sublist,
                EntityType::PROCESS,
                update_process_data,
                _create_process_data);
}

bool SyncBackendConnection::update_process_data(ListItem* process_item)
{
    // Process does not have update
    static_cast<void>(process_item);
    return false;
}

bool SyncBackendConnection::update_domain_data(ListItem* domain_item)
{
    auto domain_item_sublist = static_cast<SubListedListItem*>(domain_item);

    return __update_entity_data(
                domain_item_sublist,
                EntityType::TOPIC,
                update_topic_data,
                _create_topic_data);
}

bool SyncBackendConnection::update_topic_data(ListItem* topic_item)
{
    // Process does not have update
    static_cast<void>(topic_item);
    return false;
}


bool SyncBackendConnection::update_participant_data(ListItem* participant_item)
{
    auto participant_item_sublist = static_cast<SubListedListItem*>(participant_item);

    bool res = __update_entity_data(
                participant_item_sublist,
                EntityType::DATAREADER,
                update_endpoint_data,
                _create_endpoint_data);

    res = __update_entity_data(
                participant_item_sublist,
                EntityType::DATAWRITER,
                update_endpoint_data,
                _create_endpoint_data) || res;

    return res;
}

bool SyncBackendConnection::update_endpoint_data(ListItem* endpoint_item)
{
    // Endpoint does not have update
    static_cast<void>(endpoint_item);
    return false;
}

/// UPDATE STRUCTURE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_physical_data(models::ListModel* physical_model)
{
    return __update_model_data(
                physical_model,
                EntityType::HOST,
                ALL_ID_BACKEND,
                update_host_data,
                _create_host_data);
}

bool SyncBackendConnection::update_logical_data(models::ListModel* logical_model)
{
    return __update_model_data(
                logical_model,
                EntityType::DOMAIN,
                ALL_ID_BACKEND,
                update_domain_data,
                _create_domain_data);
}

bool SyncBackendConnection::update_dds_data(models::ListModel* dds_model, EntityId id)
{
    return __update_model_data(
                dds_model,
                EntityType::DOMAIN,
                id,
                update_participant_data,
                _create_participant_data);
}

// Template functions to update
bool SyncBackendConnection::__update_entity_data(
        SubListedListItem* item,
        EntityType type,
        bool (*update_function)(ListItem*),
        ListItem* (*create_function)(EntityId))
{
    bool changed = false;

    // Get Item id
    EntityId id = item->get_entityId();

    // For each User get all processes
    for (auto subentity_id : backend_object()->get_entities(type, id))
    {
        // Check if it exists already
        models::ListItem* subentity_item = item->submodel()->find(backend::id_to_QString(subentity_id));

        // If it does not exist, it creates it and add a Row with it
        // If it exists it updates its info
        if (nullptr == subentity_item)
        {
            item->submodel()->appendRow(create_function(subentity_id));
            changed = true;
            subentity_item = item->submodel()->find(backend::id_to_QString(subentity_id));

            // It shold not fail after including it in row
            assert(subentity_item);
        }
        changed = update_function(subentity_item) or changed;
    }

    return changed;
}

bool SyncBackendConnection::__update_model_data(
        ListModel* model,
        EntityType type,
        EntityId id,
        bool (*update_function)(ListItem*),
        ListItem* (*create_function)(EntityId))
{
    bool changed = false;

    // For each User get all processes
    for (auto subentity_id : backend_object()->get_entities(type, id))
    {
        // Check if it exists already
        models::ListItem* subentity_item = model->find(backend::id_to_QString(subentity_id));

        // If it does not exist, it creates it and add a Row with it
        // If it exists it updates its info
        if (nullptr == subentity_item)
        {
            model->appendRow(create_function(subentity_id));
            changed = true;
            subentity_item = model->find(backend::id_to_QString(subentity_id));

            // It shold not fail after including it in row
            assert(subentity_item);
        }
        changed = update_function(subentity_item) or changed;
    }

    return changed;
}

bool SyncBackendConnection::init_monitor(int domain)
{
    std::cout << "Initializing monitor " << domain;
    return false;
}

bool SyncBackendConnection::init_monitor(QString locators)
{
    std::cout << "Initializing monitor " << locators.toStdString();
    return false;
}

json SyncBackendConnection::get_qos(EntityId id)
{
    // TODO get the QoS info from backend
    static_cast<void>(id);
    nlohmann::json json_obj = R"({
        "data_sharing":
        {
            "domain_ids":
            [
                0
            ],
            "kind": "AUTO",
            "max_domains": 1,
            "shm_directory": "/dev/shm"
        },
        "deadline":
        {
            "period":
            {
                "nanoseconds": 50,
                "seconds": 10
            }
        },
        "destination_order":
        {
            "kind": "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS"
        },
        "disable_positive_acks":
        {
            "duration":
            {
                "nanoseconds": 100,
                "seconds": 0
            },
            "enabled": true
        },
        "durability":
        {
            "kind": "VOLATILE_DURABILITY_QOS"
        },
        "durability_service":
        {
            "history_depth": "1",
            "history_kind": "KEEP_LAST_HISTORY_QOS",
            "max_instances": "30",
            "max_samples": "3000",
            "max_samples_per_instance": "100",
            "service_cleanup_delay":
            {
                "nanoseconds": 0,
                "seconds": 5
            }
        },
        "group_data": "9d46781410ff",
        "latency_budget":
        {
            "duration":
            {
                "nanoseconds": 50,
                "seconds": 10
            }
        },
        "lifespan":
        {
            "duration":
            {
                "nanoseconds": 0,
                "seconds": 10000
            }
        },
        "liveliness":
        {
            "announcement_period":
            {
                "nanoseconds": 0,
                "seconds": 3
            },
            "lease_duration":
            {
                "nanoseconds": 0,
                "seconds": 10
            },
            "kind": "AUTOMATIC_LIVELINESS_QOS"
        },
        "ownership":
        {
            "kind": "SHARED_OWNERSHIP_QOS"
        },
        "partition":
        [
            "partition_1",
            "partition_2"
        ],
        "presentation":
        {
            "access_scope": "INSTANCE_PRESENTATION_QOS",
            "coherent_access": false,
            "ordered_access": false
        },
        "reliability":
        {
            "kind": "RELIABLE_RELIABILITY_QOS",
            "max_blocking_time":
            {
                "nanoseconds": 0,
                "seconds": 3
            }
        },
        "representation":
        [
        ],
        "time_based_filter":
        {
            "minimum_separation":
            {
                "seconds": 12,
                "nanoseconds": 0
            }
        },
        "topic_data": "5b33419a",
        "type_consistency":
        {
            "force_type_validation": false,
            "ignore_member_names": false,
            "ignore_sequence_bounds": true,
            "ignore_string_bounds": true,
            "kind": "DISALLOW_TYPE_COERCION",
            "prevent_type_widening": false
        },
        "user_data": "ff00"
    })"_json;

    json_obj["id"] = id;

    return json_obj;
}

} //namespace backend
