
#include <iostream>

#include <include/backend/SyncBackendConnection.h>
#include <include/model/ListItem.h>
#include <include/model/ListModel.h>
#include <include/model/SubListedListModel.h>
#include <include/model/dds/ParticipantModelItem.h>
#include <include/model/dds/EndpointModelItem.h>
#include <include/model/dds/LocatorModelItem.h>
#include <include/model/logical/TopicModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/physical/HostModelItem.h>
#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>
#include <include/backend/backend_utils.h>
#include <include/model/tree/TreeModel.h>

#include <fastdds-statistics-backend/StatisticsBackend.hpp>
#include <json.hpp>

#include <QDebug>

namespace backend {

using namespace eprosima::statistics_backend;
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

ListItem* SyncBackendConnection::_create_locator_data(backend::EntityId id)
{
    std::cout << "Creating Locator " << id << std::endl;
    return new LocatorModelItem(id);
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
    auto endpoint_item_sublist = static_cast<SubListedListItem*>(endpoint_item);

    return __update_entity_data(
                endpoint_item_sublist,
                EntityType::LOCATOR,
                update_locator_data,
                _create_locator_data);
}

bool SyncBackendConnection::update_locator_data(ListItem* locator_item)
{
    // Locator does not have update
    static_cast<void>(locator_item);
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
                EntityType::PARTICIPANT,
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
    for (auto subentity_id : StatisticsBackend::get_entities(type, id))
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
    for (auto subentity_id : StatisticsBackend::get_entities(type, id))
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

bool SyncBackendConnection::set_listener(Listener* listener)
{
    StatisticsBackend::set_physical_listener(listener);
    return true;
}

bool SyncBackendConnection::unset_listener()
{
    StatisticsBackend::set_physical_listener(nullptr);
    return true;
}


bool SyncBackendConnection::init_monitor(int domain)
{
    StatisticsBackend::init_monitor(domain);
    return true;
}

bool SyncBackendConnection::init_monitor(QString locators)
{
    StatisticsBackend::init_monitor(locators.toStdString());
    return true;
}

json SyncBackendConnection::get_info(EntityId id)
{
    return StatisticsBackend::get_info(id);
}

json SyncBackendConnection::get_summary(backend::EntityId id)
{
    json summary;

    // Throughput
    summary["Throughput"]["mean"] =
            std::to_string(StatisticsBackend::get_data(
                DataKind::PUBLICATION_THROUGHPUT,
                id,
                1,
                StatisticKind::MEAN)[0].second);

    // Latency
    summary["Latency"]["mean"] = "0";

    return summary;
}


} //namespace backend
