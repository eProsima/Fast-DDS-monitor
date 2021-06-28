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
 * @file SyncBackendConnection_updateAll.cpp
 */

#include <QDebug>

#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/model/dds/EndpointModelItem.h>
#include <fastdds_monitor/model/dds/LocatorModelItem.h>
#include <fastdds_monitor/model/dds/ParticipantModelItem.h>
#include <fastdds_monitor/model/ListItem.h>
#include <fastdds_monitor/model/ListModel.h>
#include <fastdds_monitor/model/logical/DomainModelItem.h>
#include <fastdds_monitor/model/logical/TopicModelItem.h>
#include <fastdds_monitor/model/physical/HostModelItem.h>
#include <fastdds_monitor/model/physical/ProcessModelItem.h>
#include <fastdds_monitor/model/physical/UserModelItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>

namespace backend {

using namespace eprosima::statistics_backend;
using namespace models;

bool SyncBackendConnection::update_host_item(
        ListItem* host_item,
        bool inactive_visible /* true */)
{
    auto host_item_sublist = static_cast<SubListedListItem*>(host_item);

    return update_model_(
        host_item_sublist->submodel(),
        EntityKind::USER,
        host_item->get_entity_id(),
        &SyncBackendConnection::update_user_item,
        &SyncBackendConnection::create_user_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_user_item(
        ListItem* user_item,
        bool inactive_visible /* true */)
{
    auto user_item_sublist = static_cast<SubListedListItem*>(user_item);

    return update_model_(
        user_item_sublist->submodel(),
        EntityKind::PROCESS,
        user_item->get_entity_id(),
        &SyncBackendConnection::update_process_item,
        &SyncBackendConnection::create_process_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_process_item(
        ListItem* process_item,
        bool inactive_visible /* true */)
{
    // Process does not have update
    static_cast<void>(process_item);
    static_cast<void>(inactive_visible);
    return false;
}

bool SyncBackendConnection::update_domain_item(
        ListItem* domain_item,
        bool inactive_visible /* true */)
{
    auto domain_item_sublist = static_cast<SubListedListItem*>(domain_item);

    return update_model_(
        domain_item_sublist->submodel(),
        EntityKind::TOPIC,
        domain_item->get_entity_id(),
        &SyncBackendConnection::update_topic_item,
        &SyncBackendConnection::create_topic_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_topic_item(
        ListItem* topic_item,
        bool inactive_visible /* true */)
{
    // Process does not have update
    static_cast<void>(topic_item);
    static_cast<void>(inactive_visible);
    return false;
}

bool SyncBackendConnection::update_participant_item(
        ListItem* participant_item,
        bool inactive_visible /* true */)
{
    auto participant_item_sublist = static_cast<SubListedListItem*>(participant_item);

    bool res = update_model_(
        participant_item_sublist->submodel(),
        EntityKind::DATAREADER,
        participant_item->get_entity_id(),
        &SyncBackendConnection::update_endpoint_item,
        &SyncBackendConnection::create_datareader_data_,
        inactive_visible);

    res = update_model_(
        participant_item_sublist->submodel(),
        EntityKind::DATAWRITER,
        participant_item->get_entity_id(),
        &SyncBackendConnection::update_endpoint_item,
        &SyncBackendConnection::create_datawriter_data_,
        inactive_visible) || res;

    return res;
}

bool SyncBackendConnection::update_endpoint_item(
        ListItem* endpoint_item,
        bool inactive_visible /* true */)
{
    auto endpoint_item_sublist = static_cast<SubListedListItem*>(endpoint_item);

    return update_model_(
        endpoint_item_sublist->submodel(),
        EntityKind::LOCATOR,
        endpoint_item->get_entity_id(),
        &SyncBackendConnection::update_locator_item,
        &SyncBackendConnection::create_locator_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_locator_item(
        ListItem* locator_item,
        bool inactive_visible /* true */)
{
    // Locator does not have update
    static_cast<void>(locator_item);
    static_cast<void>(inactive_visible);
    return false;
}

/// UPDATE STRUCTURE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_physical_model(
        models::ListModel* physical_model,
        bool inactive_visible /* true */)
{
    qDebug() << "Update Physical Data";

    return update_model_(
        physical_model,
        EntityKind::HOST,
        ID_ALL,
        &SyncBackendConnection::update_host_item,
        &SyncBackendConnection::create_host_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_logical_model(
        models::ListModel* logical_model,
        bool inactive_visible /* true */)
{
    qDebug() << "Update Logical Data";

    return update_model_(
        logical_model,
        EntityKind::DOMAIN,
        ID_ALL,
        &SyncBackendConnection::update_domain_item,
        &SyncBackendConnection::create_domain_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_dds_model(
        models::ListModel* dds_model,
        EntityId id,
        bool inactive_visible /* true */)
{
    qDebug() << "Update DDS Data";

    return update_model_(
        dds_model,
        EntityKind::PARTICIPANT,
        id,
        &SyncBackendConnection::update_participant_item,
        &SyncBackendConnection::create_participant_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_item_(
        ListItem* item,
        bool (SyncBackendConnection::* update_function)(ListItem*, bool),
        bool inactive_visible /* true */)
{
    bool res = update_item_info_(item);
    return (this->*update_function)(item, inactive_visible) || res;
}

bool SyncBackendConnection::update_item_info_(
        ListItem* item)
{
    try
    {
        // Query for this item info and updte it
        item->info(get_info(item->get_entity_id()));
        return true;
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail updating item info: " << e.what();
        return false;
    }
}

bool SyncBackendConnection::update_model_(
        ListModel* model,
        EntityKind type,
        EntityId id,
        bool (SyncBackendConnection::* update_function)(ListItem*, bool),
        ListItem* (SyncBackendConnection::* create_function)(EntityId),
        bool inactive_visible /* true */)
{
    bool changed = false;

    try
    {
        // For each User get all processes
        for (auto subentity_id : get_entities(type, id))
        {
            // Check if it exists already
            int index = model->rowIndexFromId(subentity_id);

            // If it does not exist, it creates it and add a Row with it
            // If it exists it updates its info
            if (index == -1)
            {
                // Only create the new entity if is alive or inactive are visible
                if (inactive_visible || get_alive(subentity_id))
                {
                    // Creates the Item object and update its data
                    model->appendRow((this->*create_function)(subentity_id));
                    changed = true;
                    models::ListItem* subentity_item = model->find(subentity_id);

                    changed = update_item_(subentity_item, update_function, inactive_visible) || changed;
                }
            }

            // In case this entity is inactive and inactive are not being displayed, remove ir
            else if (!inactive_visible && !get_alive(subentity_id))
            {
                // Remove the row
                // Item object is deleted in removeRows
                model->removeRow(index);

                changed = true;
            }

            // Otherwise just update the entity
            else
            {
                models::ListItem* subentity_item = model->at(index);
                changed = update_item_(subentity_item, update_function, inactive_visible) || changed;
            }
        }
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail updating model: " << e.what();
    }

    return changed;
}

} //namespace backend
