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
 * @file SyncBackendConnection_updateOne.cpp
 */

#include <QDebug>

#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/model/ListItem.h>
#include <fastdds_monitor/model/ListModel.h>
#include <fastdds_monitor/model/SubListedListModel.h>

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
        &SyncBackendConnection::create_host_data_,
        inactive_visible);
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
        &SyncBackendConnection::create_user_data_,
        inactive_visible);
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
        &SyncBackendConnection::create_user_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_domain(
    models::ListModel* logical_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    // Domain model is already logical model
    return update_one_entity_in_model_(
        logical_model,
        id,
        new_entity,
        &SyncBackendConnection::create_domain_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_topic(
    models::ListModel* logical_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    // Get Domain model where this Topic belongs
    ListModel* domain_model = get_model_(logical_model, id, EntityKind::DOMAIN);

    if (domain_model == nullptr)
    {
        qWarning() << "Error getting domain model for topic " << id.value();
        return false;
    }

    return update_one_entity_in_model_(
        domain_model,
        id,
        new_entity,
        &SyncBackendConnection::create_topic_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_participant(
    models::ListModel* dds_model,
    EntityId id,
    bool new_entity,
    EntityId related_entity_id,
    bool inactive_visible)
{
    // Check if the participant belongs to the entity context
    auto participants_related = get_entities(EntityKind::PARTICIPANT, related_entity_id);

    // If the related entity does not have this participant as related, the participant will not appear
    if (std::find(participants_related.begin(), participants_related.end(), id) == participants_related.end())
    {
        return false;
    }

    // Domain model is already logical model
    return update_one_entity_in_model_(
        dds_model,
        id,
        new_entity,
        &SyncBackendConnection::create_participant_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_datawriter(
    models::ListModel* dds_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    // Get Host model where this datawriter belongs
    ListModel* participant_model = get_model_(dds_model, id, EntityKind::PARTICIPANT);

    // If the participant model does not exist is because the participant is not related with the last entity
    // clicked and so its subentities should not appear, so no update is done
    if (participant_model == nullptr)
    {
        qDebug() << "Missing participant model for datawriter " << id.value();
        return false;
    }

    return update_one_entity_in_model_(
        participant_model,
        id,
        new_entity,
        &SyncBackendConnection::create_datawriter_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_datareader(
    models::ListModel* dds_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    // Get Host model where this datareader belongs
    ListModel* participant_model = get_model_(dds_model, id, EntityKind::PARTICIPANT);

    // If the participant model does not exist is because the participant is not related with the last entity
    // clicked and so its subentities should not appear, so no update is done
    if (participant_model == nullptr)
    {
        qDebug() << "Missing participant model for datareader " << id.value();
        return false;
    }

    return update_one_entity_in_model_(
        participant_model,
        id,
        new_entity,
        &SyncBackendConnection::create_datareader_data_,
        inactive_visible);
}

bool SyncBackendConnection::update_locator(
    models::ListModel* dds_model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    bool res = false;

    // In Locator case, it could be several models where this locator belongs to
    for (auto participant_id : get_entities(EntityKind::PARTICIPANT, id))
    {
        // Get Participant model (if it is visible)
        ListItem* participant_item = dds_model->find(participant_id);

        // Check if participant item exists in view
        if (participant_item == nullptr)
        {
            continue;
        }

        // Parent must be SubListedListItem so it can contain something, so this cast should not fail
        SubListedListItem* participant_sublist = static_cast<SubListedListItem*>(participant_item);

        if (participant_sublist == nullptr)
        {
            qCritical() << "Parent item of locator " << id.value() << " was not SubListed.";
            continue;
        }

        ListModel* participant_model = participant_sublist->submodel();

        if (participant_model == nullptr)
        {
            qCritical() << "Parent item of locator " << id.value() << " has not submodule";
            continue;
        }

        // Check in DataReader and DataWriters models of this participant
        // Get DataWriter model where this locator belongs
        ListModel* dw_model = get_model_(participant_model, id, EntityKind::DATAWRITER);

        if (dw_model != nullptr)
        {
            res = update_one_entity_in_model_(
                dw_model,
                id,
                new_entity,
                &SyncBackendConnection::create_locator_data_,
                inactive_visible) || res;
        }


        // Get DataReader model where this locator belongs
        ListModel* dr_model = get_model_(participant_model, id, EntityKind::DATAREADER);

        if (dr_model != nullptr)
        {
            res = update_one_entity_in_model_(
                dr_model,
                id,
                new_entity,
                &SyncBackendConnection::create_locator_data_,
                inactive_visible) || res;
        }
    }

    return res;
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
        auto parents = get_entities(parent_kind, id);

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
        // It is not an error in dds model
        qDebug() << "Parent item of entity " << id.value() << " does not exist";
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
    ListItem* (SyncBackendConnection::* create_function)(EntityId),
    bool inactive_visible)
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
            // Item object is deleted in removeRows
            model->removeRow(index);

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
