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
 * @file SyncBackendConnection.cpp
 */

#include <iostream>

#include <QDebug>

#include <fastdds-statistics-backend/StatisticsBackend.hpp>
#include <json.hpp>

#include <include/backend/SyncBackendConnection.h>
#include <include/backend/backend_utils.h>
#include <include/model/EntityItem.h>
#include <include/model/ListItem.h>
#include <include/model/ListModel.h>
#include <include/model/SubListedListModel.h>
#include <include/model/dds/EndpointModelItem.h>
#include <include/model/dds/LocatorModelItem.h>
#include <include/model/dds/ParticipantModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/logical/TopicModelItem.h>
#include <include/model/physical/HostModelItem.h>
#include <include/model/physical/ProcessModelItem.h>
#include <include/model/physical/UserModelItem.h>
#include <include/model/tree/TreeModel.h>

namespace backend {

using namespace eprosima::statistics_backend;
using namespace models;

ListItem* SyncBackendConnection::create_process_data_(EntityId id)
{
    qDebug() << "Creating Process " << id << std::endl;
    return new ProcessModelItem(id);
}

ListItem* SyncBackendConnection::create_host_data_(EntityId id)
{
    qDebug() << "Creating Host " << id << std::endl;
    return new HostModelItem(id);
}

ListItem* SyncBackendConnection::create_user_data_(EntityId id)
{
    qDebug() << "Creating User " << id << std::endl;
    return new UserModelItem(id);
}

ListItem* SyncBackendConnection::create_domain_data_(EntityId id)
{
    qDebug() << "Creating Domain " << id << std::endl;
    return new DomainModelItem(id);
}

ListItem* SyncBackendConnection::create_topic_data_(EntityId id)
{
    qDebug() << "Creating Topic " << id << std::endl;
    return new TopicModelItem(id);
}

ListItem* SyncBackendConnection::create_participant_data_(backend::EntityId id)
{
    qDebug() << "Creating Participant " << id << std::endl;
    return new ParticipantModelItem(id);
}

ListItem* SyncBackendConnection::create_endpoint_data_(backend::EntityId id)
{
    qDebug() << "Creating Endpoint " << id << std::endl;
    return new EndpointModelItem(id);
}

ListItem* SyncBackendConnection::create_locator_data_(backend::EntityId id)
{
    qDebug() << "Creating Locator " << id << std::endl;
    return new LocatorModelItem(id);
}

/// UPDATE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_host_data(ListItem* host_item)
{
    auto host_item_sublist = static_cast<SubListedListItem*>(host_item);

    return update_item_(
                host_item_sublist,
                EntityKind::USER,
                update_user_data,
                create_user_data_);
}

bool SyncBackendConnection::update_user_data(ListItem* user_item)
{
    auto user_item_sublist = static_cast<SubListedListItem*>(user_item);

    return update_item_(
                user_item_sublist,
                EntityKind::PROCESS,
                update_process_data,
                create_process_data_);
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

    return update_item_(
                domain_item_sublist,
                EntityKind::TOPIC,
                update_topic_data,
                create_topic_data_);
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

    bool res = update_item_(
                participant_item_sublist,
                EntityKind::DATAREADER,
                update_endpoint_data,
                create_endpoint_data_);

    res = update_item_(
                participant_item_sublist,
                EntityKind::DATAWRITER,
                update_endpoint_data,
                create_endpoint_data_) || res;

    return res;
}

bool SyncBackendConnection::update_endpoint_data(ListItem* endpoint_item)
{
    auto endpoint_item_sublist = static_cast<SubListedListItem*>(endpoint_item);

    return update_item_(
                endpoint_item_sublist,
                EntityKind::LOCATOR,
                update_locator_data,
                create_locator_data_);
}

bool SyncBackendConnection::update_locator_data(ListItem* locator_item)
{
    // Locator does not have update
    static_cast<void>(locator_item);
    return false;
}

/// UPDATE STRUCTURE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_physical_model(models::ListModel* physical_model)
{
    qDebug() << "Update Physical Data" << std::endl;

    return update_model_(
                physical_model,
                EntityKind::HOST,
                ID_ALL,
                update_host_data,
                create_host_data_);
}

bool SyncBackendConnection::update_logical_model(models::ListModel* logical_model)
{
    qDebug() << "Update Logical Data" << std::endl;

    return update_model_(
                logical_model,
                EntityKind::DOMAIN,
                ID_ALL,
                update_domain_data,
                create_domain_data_);
}

bool SyncBackendConnection::update_dds_model(models::ListModel* dds_model, EntityId id)
{
    qDebug() << "Update DDS Data" << std::endl;

    return update_model_(
                dds_model,
                EntityKind::PARTICIPANT,
                id,
                update_participant_data,
                create_participant_data_);
}

bool SyncBackendConnection::update_get_data_dialog_entity_id(models::ListModel* entity_model, EntityKind entity_kind)
{

    bool changed = false;

    for (auto entity_id : StatisticsBackend::get_entities(entity_kind, ID_ALL))
    {
        entity_model->appendRow(new EntityItem(entity_id));
        changed = true;
    }

    return changed;
}


// Template functions to update
bool SyncBackendConnection::update_item_(
        SubListedListItem* item,
        EntityKind type,
        bool (*update_function)(ListItem*),
        ListItem* (*create_function)(EntityId))
{
    bool changed = false;

    // Get Item id
    EntityId id = item->get_entity_id();

    // Query for this item info and updte it
    item->info(StatisticsBacked::get_info(id))

    // For each User get all processes
    for (auto subentity_id : StatisticsBackend::get_entities(type, id))
    {
        // Check if it exists already
        models::ListItem* subentity_item = item->submodel()->find(backend::id_to_QString(subentity_id));

        // If it does not exist, it creates it and add a Row with it
        // If it exists it updates its info
        if (nullptr == subentity_item)
        {
            qDebug() << "Looking for info " << subentity_id << std::endl;

            auto e = create_function(subentity_id);

            qDebug() << "Appending row " << subentity_id << std::endl;

            item->submodel()->appendRow(e);
            changed = true;
            subentity_item = item->submodel()->find(backend::id_to_QString(subentity_id));

            // It shold not fail after including it in row
            assert(subentity_item);
        }
        changed = update_function(subentity_item) or changed;
    }

    return changed;
}

bool SyncBackendConnection::update_model_(
        ListModel* model,
        EntityKind type,
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


EntityId SyncBackendConnection::init_monitor(int domain)
{
    return StatisticsBackend::init_monitor(domain);
}

EntityId SyncBackendConnection::init_monitor(QString locators)
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
    summary["Latency"]["mean"] = "-0";

    return summary;
}

std::string SyncBackendConnection::get_name(EntityId id)
{
    return StatisticsBackend::get_info(id)["name"];
}

std::vector<StatisticsData> SyncBackendConnection::get_data(
        DataKind data_kind,
        EntityId source_entity_id,
        EntityId target_entity_id,
        uint16_t bins,
        Timestamp start_time,
        Timestamp end_time,
        StatisticKind statistic_kind)
{
    if (target_entity_id.is_valid())
    {
        return StatisticsBackend::get_data(
                    data_kind,
                    source_entity_id,
                    bins,
                    start_time,
                    end_time,
                    statistic_kind);
    }
    else
    {
        return StatisticsBackend::get_data(
                    data_kind,
                    source_entity_id,
                    target_entity_id,
                    bins,
                    start_time,
                    end_time,
                    statistic_kind);
    }
}

} //namespace backend
