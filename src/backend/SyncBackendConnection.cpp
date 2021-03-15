
#include <iostream>

#include <include/backend/SyncBackendConnection.h>
#include <include/model/ListItem.h>
#include <include/model/ListModel.h>
#include <include/model/SubListedListModel.h>
//#include <include/model/dds/ParticipantModelItem.h>
//#include <include/model/dds/EndpointModelItem.h>
#include <include/model/logical/TopicModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/physical/HostModelItem.h>
#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>
#include <include/backend/backend_utils.h>
#include <core/StatisticsBackend.hpp>

namespace backend {

using namespace eprosima::fastdds::dds::statistics;
using namespace models;

/// Backend API
bool SyncBackendConnection::fill_physical_data(models::ListModel* physical_model)
{
    return _update_physical_data(physical_model);
}

// TODO reimplement these functions so it is not needed to call the whole fill
bool SyncBackendConnection::update_host_data(models::ListModel* physical_model, EntityId id)
{
    static_cast<void>(id);
    return _update_physical_data(physical_model);
}
bool SyncBackendConnection::update_user_data(models::ListModel* physical_model, EntityId id)
{
    static_cast<void>(id);
    return _update_physical_data(physical_model);
}
bool SyncBackendConnection::update_process_data(models::ListModel* physical_model, EntityId id)
{
    static_cast<void>(id);
    return _update_physical_data(physical_model);
}

// LOGICAL PARTITION
bool SyncBackendConnection::fill_logical_data(models::ListModel* logical_model)
{
    return _update_logical_data(logical_model);
}

bool SyncBackendConnection::update_domain_data(models::ListModel* logical_model, EntityId id)
{
    static_cast<void>(id);
    return _update_logical_data(logical_model);
}

bool SyncBackendConnection::update_topic_data(models::ListModel* logical_model, EntityId id)
{
    static_cast<void>(id);
    return _update_logical_data(logical_model);
}

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

/// UPDATE PRIVATE FUNCTIONS
bool SyncBackendConnection::_update_host_data(ListItem* host_item)
{
    auto host_item_sublist = static_cast<SubListedListItem*>(host_item);

    return __update_entity_data(
                host_item_sublist,
                EntityType::USER,
                _update_user_data,
                _create_user_data);
}

bool SyncBackendConnection::_update_user_data(ListItem* user_item)
{
    auto user_item_sublist = static_cast<SubListedListItem*>(user_item);

    return __update_entity_data(
                user_item_sublist,
                EntityType::PROCESS,
                _update_process_data,
                _create_process_data);
}

bool SyncBackendConnection::_update_process_data(ListItem* process_item)
{
    // Process does not have update
    static_cast<void>(process_item);
    return false;
}

bool SyncBackendConnection::_update_domain_data(ListItem* domain_item)
{
    auto domain_item_sublist = static_cast<SubListedListItem*>(domain_item);

    return __update_entity_data(
                domain_item_sublist,
                EntityType::TOPIC,
                _update_topic_data,
                _create_topic_data);
}

bool SyncBackendConnection::_update_topic_data(ListItem* topic_item)
{
    // Process does not have update
    static_cast<void>(topic_item);
    return false;
}

/// UPDATE StrUCTURE PRIVATE FUNCTIONS
bool SyncBackendConnection::_update_physical_data(models::ListModel* physical_model)
{
    return __update_model_data(
                physical_model,
                EntityType::HOST,
                _update_host_data,
                _create_host_data);
}

bool SyncBackendConnection::_update_logical_data(models::ListModel* logical_model)
{
    return __update_model_data(
                logical_model,
                EntityType::DOMAIN,
                _update_domain_data,
                _create_domain_data);
}

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
        bool (*update_function)(ListItem*),
        ListItem* (*create_function)(EntityId))
{
    bool changed = false;

    // For each User get all processes
    for (auto subentity_id : backend_object()->get_entities(type))
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

} //namespace backend
