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

#include <fastdds_statistics_backend/StatisticsBackend.hpp>
#include <fastdds_statistics_backend/exception/Exception.hpp>

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
#include <fastdds_monitor/model/statistics/EntityItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/model/tree/TreeModel.h>

namespace backend {

using namespace eprosima::statistics_backend;
using namespace models;

bool SyncBackendConnection::update_host(
    models::ListModel* physical_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    // Host model is already physical model
    return update_one_entity_in_model_(
        physical_model,
        id,
        new_entity,
        inactive_visible,
        &SyncBackendConnection::create_host_data_);
}

bool SyncBackendConnection::update_user(
    models::ListModel* physical_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    // Get Host model where this user belongs
    ListModel* host_model = get_model_(physical_model, id, EntityKind::HOST);

    if (host_model == nullptr)
    {
        qWarning() << "Error getting host model for user " << id.value();
        return false;
    }

    return update_one_entity_in_model_(
        host_model,
        id,
        new_entity,
        inactive_visible,
        &SyncBackendConnection::create_user_data_);
}

bool SyncBackendConnection::update_process(
    models::ListModel* physical_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    // Get Host model where this process belongs
    ListModel* host_model = get_model_(physical_model, id, EntityKind::HOST);

    if (host_model == nullptr)
    {
        qWarning() << "Error getting host model for process " << id.value();
        return false;
    }

    // Get User model where this process belongs
    ListModel* user_model = get_model_(host_model, id, EntityKind::USER);

    if (user_model == nullptr)
    {
        qWarning() << "Error getting host model for process " << id.value();
        return false;
    }

    return update_one_entity_in_model_(
        user_model,
        id,
        new_entity,
        inactive_visible,
        &SyncBackendConnection::create_user_data_);
}

ListModel* SyncBackendConnection::get_model_(
    models::ListModel* parent_model,
    EntityId id,
    EntityKind parent_kind)
{
    // Look for parent id in model
    EntityId parent_id;

    try
    {
        auto parents = StatisticsBackend::get_entities(parent_kind, id);

        // It must be just one host
        if (parents.size() != 1)
        {
            qCritical() << "Parents related with entity " << id.value() << " are expected to be 1 but are: "
                        << parents.size();
            return nullptr;
        }
        else
        {
            parent_id = parents[0];
        }
    }
    catch(const std::exception& e)
    {
        qWarning() << "Fail getting entities: " << e.what();
        return nullptr;
    }

    // Once we have the host id, we get the item related to it in the physical model
    ListItem* parent_item = parent_model->find(parent_id);

    if (parent_item == nullptr)
    {
        qWarning() << "Parent item of entity " << id.value() << " does not exist";
        return nullptr;
    }

    // Parent must be SubListedListItem so it can contain something, so this cast should not fail
    auto parent_sublist = static_cast<SubListedListItem*>(parent_item);

    if (parent_sublist == nullptr)
    {
        qCritical() << "Parent item was not SubListed.";
        return nullptr;
    }

    return parent_sublist->submodel();
}

bool SyncBackendConnection::update_one_entity_in_model_(
    models::ListModel* model,
    EntityId id,
    bool new_entity,
    bool inactive_visible,
    ListItem* (SyncBackendConnection::* create_function)(EntityId))
{
    // Check if element already exists
    int index = model->rowIndexFromId(id);

    // The element does not exist
    if (index == -1)
    {
        // If it didnt exist yet something has gone wrong in backend
        if (!new_entity)
        {
            qWarning() << "Trying to update an entity that did not exist";
        }

        // Get alive status of entity.
        // This is faster than asking for the whole info, which in some cases will not be needed.
        bool active = get_alive(id);
        if (inactive_visible || active)
        {
            model->appendRow((this->*create_function)(id));
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // If it existed already something has gone wrong in backend
        if (new_entity)
        {
            qWarning() << "Trying to create an entity that already exists";
        }

        // Get item from model from the index already calculated
        ListItem* item = model->at(index);

        // Get alive status of entity.
        bool active = get_alive(id);

        // If it is not alive and inactive are not visible, this entity must be erased from model
        if (!inactive_visible && !active)
        {
            // Remove the item from the model
            model->removeRow(index);

            // Destroy Item object
            // In case it has subitems they will be destroy as well
            delete item;

            return true;
        }
        else
        {
            // In case the entity must keep existing, just update its info
            return update_item_info_(item);
        }
    }
}

} //namespace backend
