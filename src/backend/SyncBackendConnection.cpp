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

ListItem* SyncBackendConnection::create_host_data_(
        EntityId id)
{
    qDebug() << "Creating Host " << backend::backend_id_to_models_id(id);
    return new HostModelItem(id, EntityKind::HOST, get_info(id));
}

ListItem* SyncBackendConnection::create_user_data_(
        EntityId id)
{
    qDebug() << "Creating User " << backend::backend_id_to_models_id(id);
    return new UserModelItem(id, EntityKind::USER, get_info(id));
}

ListItem* SyncBackendConnection::create_process_data_(
        EntityId id)
{
    qDebug() << "Creating Process " << backend::backend_id_to_models_id(id);
    return new ProcessModelItem(id, EntityKind::PROCESS, get_info(id));
}

ListItem* SyncBackendConnection::create_domain_data_(
        EntityId id)
{
    qDebug() << "Creating Domain " << backend::backend_id_to_models_id(id);
    return new DomainModelItem(id, EntityKind::DOMAIN, get_info(id));
}

ListItem* SyncBackendConnection::create_topic_data_(
        EntityId id)
{
    qDebug() << "Creating Topic " << backend::backend_id_to_models_id(id);
    return new TopicModelItem(id, EntityKind::TOPIC, get_info(id));
}

ListItem* SyncBackendConnection::create_participant_data_(
        backend::EntityId id)
{
    qDebug() << "Creating Participant " << backend::backend_id_to_models_id(id);
    return new ParticipantModelItem(id, EntityKind::PARTICIPANT, get_info(id));
}

ListItem* SyncBackendConnection::create_datawriter_data_(
        backend::EntityId id)
{
    qDebug() << "Creating DataWriter " << backend::backend_id_to_models_id(id);
    return new EndpointModelItem(id, EntityKind::DATAWRITER, get_info(id));
}

ListItem* SyncBackendConnection::create_datareader_data_(
        backend::EntityId id)
{
    qDebug() << "Creating DataReader " << backend::backend_id_to_models_id(id);
    return new EndpointModelItem(id, EntityKind::DATAREADER, get_info(id));
}

ListItem* SyncBackendConnection::create_locator_data_(
        backend::EntityId id)
{
    qDebug() << "Creating Locator " << backend::backend_id_to_models_id(id);
    return new LocatorModelItem(id, EntityKind::LOCATOR, get_info(id));
}

/// UPDATE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_host_item(
        ListItem* host_item)
{
    // update the internal info
    bool res = update_item_info_(host_item);

    auto host_item_sublist = static_cast<SubListedListItem*>(host_item);

    return update_subitems_(
        host_item_sublist,
        EntityKind::USER,
        &SyncBackendConnection::update_user_item,
        &SyncBackendConnection::create_user_data_) || res;
}

bool SyncBackendConnection::update_user_item(
        ListItem* user_item)
{
    // update the internal info
    bool res = update_item_info_(user_item);

    auto user_item_sublist = static_cast<SubListedListItem*>(user_item);

    return update_subitems_(
        user_item_sublist,
        EntityKind::PROCESS,
        &SyncBackendConnection::update_process_item,
        &SyncBackendConnection::create_process_data_) || res;
}

bool SyncBackendConnection::update_process_item(
        ListItem* process_item)
{
    static_cast<void>(process_item);

    // update the internal info
    bool res = update_item_info_(process_item);

    // Process does not have update
    return res;
}

bool SyncBackendConnection::update_domain_item(
        ListItem* domain_item)
{
    // update the internal info
    bool res = update_item_info_(domain_item);

    auto domain_item_sublist = static_cast<SubListedListItem*>(domain_item);

    return update_subitems_(
        domain_item_sublist,
        EntityKind::TOPIC,
        &SyncBackendConnection::update_topic_item,
        &SyncBackendConnection::create_topic_data_) || res;
}

bool SyncBackendConnection::update_topic_item(
        ListItem* topic_item)
{
    static_cast<void>(topic_item);

    // update the internal info
    bool res = update_item_info_(topic_item);

    // Process does not have update
    return res;
}

bool SyncBackendConnection::update_participant_item(
        ListItem* participant_item)
{
    // update the internal info
    bool res = update_item_info_(participant_item);

    auto participant_item_sublist = static_cast<SubListedListItem*>(participant_item);

    res = update_subitems_(
        participant_item_sublist,
        EntityKind::DATAREADER,
        &SyncBackendConnection::update_endpoint_item,
        &SyncBackendConnection::create_datareader_data_) || res;

    res = update_subitems_(
        participant_item_sublist,
        EntityKind::DATAWRITER,
        &SyncBackendConnection::update_endpoint_item,
        &SyncBackendConnection::create_datawriter_data_) || res;

    return res;
}

bool SyncBackendConnection::update_endpoint_item(
        ListItem* endpoint_item)
{
    // update the internal info
    bool res = update_item_info_(endpoint_item);

    auto endpoint_item_sublist = static_cast<SubListedListItem*>(endpoint_item);

    return update_subitems_(
        endpoint_item_sublist,
        EntityKind::LOCATOR,
        &SyncBackendConnection::update_locator_item,
        &SyncBackendConnection::create_locator_data_) || res;
}

bool SyncBackendConnection::update_locator_item(
        ListItem* locator_item)
{
    static_cast<void>(locator_item);

    // update the internal info
    bool res = update_item_info_(locator_item);

    // Locator does not have update
    return res;
}

/// UPDATE STRUCTURE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_physical_model(
        models::ListModel* physical_model)
{
    qDebug() << "Update Physical Data";

    return update_model_(
        physical_model,
        EntityKind::HOST,
        ID_ALL,
        &SyncBackendConnection::update_host_item,
        &SyncBackendConnection::create_host_data_);
}

bool SyncBackendConnection::update_logical_model(
        models::ListModel* logical_model)
{
    qDebug() << "Update Logical Data";

    return update_model_(
        logical_model,
        EntityKind::DOMAIN,
        ID_ALL,
        &SyncBackendConnection::update_domain_item,
        &SyncBackendConnection::create_domain_data_);
}

bool SyncBackendConnection::update_dds_model(
        models::ListModel* dds_model,
        EntityId id)
{
    qDebug() << "Update DDS Data";

    return update_model_(
        dds_model,
        EntityKind::PARTICIPANT,
        id,
        &SyncBackendConnection::update_participant_item,
        &SyncBackendConnection::create_participant_data_);
}

bool SyncBackendConnection::update_get_data_dialog_entity_id(
        models::ListModel* entity_model,
        EntityKind entity_kind)
{
    bool changed = false;

    try
    {
        for (auto entity_id : StatisticsBackend::get_entities(entity_kind, ID_ALL))
        {
            entity_model->appendRow(new EntityItem(entity_id, entity_kind, StatisticsBackend::get_info(entity_id)));
            changed = true;
        }
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail updating get data dialog: " << e.what();
        return false;
    }

    return changed;
}

bool SyncBackendConnection::update_item_info_(
        ListItem* item)
{
    try
    {
        // Query for this item info and updte it
        item->info(StatisticsBackend::get_info(item->get_entity_id()));
        return true;
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail updating item info: " << e.what();
        return false;
    }
}

// Template functions to update
bool SyncBackendConnection::update_subitems_(
        SubListedListItem* item,
        EntityKind type,
        bool (SyncBackendConnection::* update_function)(ListItem*),
        ListItem* (SyncBackendConnection::* create_function)(EntityId),
        bool alive_allow)
{
    bool changed = false;

    // Get Item id
    EntityId id = item->get_entity_id();

    try
    {
        // For each User get all processes
        for (auto subentity_id : StatisticsBackend::get_entities(type, id))
        {
            // Check if it exists already
            models::ListItem* subentity_item = item->submodel()->find(backend::backend_id_to_models_id(subentity_id));

            // If it does not exist, it creates it and add a Row with it
            // If it exists it updates its info
            if (nullptr == subentity_item)
            {
                auto e = (this->*create_function)(subentity_id);

                item->submodel()->appendRow(e);
                changed = true;
                subentity_item = item->submodel()->find(backend::backend_id_to_models_id(subentity_id));

                // It shold not fail after including it in row
                assert(subentity_item);
            }
            changed = (this->*update_function)(subentity_item) || changed;
        }
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail updating subitems: " << e.what();
    }

    return changed;
}

bool SyncBackendConnection::update_model_(
        ListModel* model,
        EntityKind type,
        EntityId id,
        bool (SyncBackendConnection::* update_function)(ListItem*),
        ListItem* (SyncBackendConnection::* create_function)(EntityId))
{
    bool changed = false;

    try
    {
        // For each User get all processes
        for (auto subentity_id : StatisticsBackend::get_entities(type, id))
        {
            // Check if it exists already
            models::ListItem* subentity_item = model->find(backend::backend_id_to_models_id(subentity_id));

            // If it does not exist, it creates it and add a Row with it
            // If it exists it updates its info
            if (nullptr == subentity_item)
            {
                model->appendRow((this->*create_function)(subentity_id));
                changed = true;
                subentity_item = model->find(backend::backend_id_to_models_id(subentity_id));

                // It shold not fail after including it in row
                assert(subentity_item);
            }
            changed = (this->*update_function)(subentity_item) || changed;
        }
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail updating model: " << e.what();
    }

    return changed;
}

bool SyncBackendConnection::set_listener(
        Listener* listener)
{
    try
    {
        StatisticsBackend::set_physical_listener(listener);
        return true;
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail setting listener: " << e.what();
        return false;
    }
}

bool SyncBackendConnection::unset_listener()
{
    try
    {
        StatisticsBackend::set_physical_listener(nullptr);
        return true;
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail unsetting listener: " << e.what();
        return false;
    }
}

EntityId SyncBackendConnection::init_monitor(
        int domain)
{
    try
    {
        return StatisticsBackend::init_monitor(domain);
    }
    catch (const Error& e)
    {
        qWarning() << "Error initializing monitor " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter initializing monitor " << e.what();
    }

    return EntityId::invalid();
}

EntityId SyncBackendConnection::init_monitor(
        QString locators)
{
    try
    {
        return StatisticsBackend::init_monitor(locators.toStdString());
    }
    catch (const Error& e)
    {
        qWarning() << "Error initializing monitor " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter initializing monitor " << e.what();
    }

    return EntityId::invalid();
}

EntityInfo SyncBackendConnection::get_info(
        EntityId id)
{
    try
    {
        return StatisticsBackend::get_info(id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity info: " << e.what();
        return EntityInfo();
    }
}

bool SyncBackendConnection::get_alive(
        EntityId id)
{
    try
    {
        return StatisticsBackend::is_active(id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity alive status: " << e.what();
        return true;
    }
}

EntityKind SyncBackendConnection::get_type(
        EntityId id)
{
    try
    {
        return StatisticsBackend::get_type(id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity type: " << e.what();
        return EntityKind::INVALID;
    }
}

std::vector<EntityId> SyncBackendConnection::get_entities(
        EntityKind entity_type,
        EntityId entity_id)
{
    try
    {
        return StatisticsBackend::get_entities(entity_type, entity_id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entities: " << e.what();
        return std::vector<EntityId>();
    }
}

EntityInfo SyncBackendConnection::get_summary(
        backend::EntityId id)
{
    EntityInfo summary;

    // Values to represent in summary
    std::vector<std::pair<DataKind, StatisticKind>> configurations = {
        std::make_pair(DataKind::NETWORK_LATENCY, StatisticKind::MEDIAN),
        std::make_pair(DataKind::NETWORK_LATENCY, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::FASTDDS_LATENCY, StatisticKind::MEDIAN),
        std::make_pair(DataKind::FASTDDS_LATENCY, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::PUBLICATION_THROUGHPUT, StatisticKind::MEDIAN),
        std::make_pair(DataKind::PUBLICATION_THROUGHPUT, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::SUBSCRIPTION_THROUGHPUT, StatisticKind::MEDIAN),
        std::make_pair(DataKind::SUBSCRIPTION_THROUGHPUT, StatisticKind::STANDARD_DEVIATION),
        std::make_pair(DataKind::RTPS_BYTES_SENT, StatisticKind::MEDIAN),
        std::make_pair(DataKind::RTPS_BYTES_LOST, StatisticKind::MEDIAN),
        std::make_pair(DataKind::RESENT_DATA, StatisticKind::MEAN),
        std::make_pair(DataKind::HEARTBEAT_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::ACKNACK_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::NACKFRAG_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::GAP_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::DATA_COUNT, StatisticKind::SUM),
        std::make_pair(DataKind::PDP_PACKETS, StatisticKind::SUM),
        std::make_pair(DataKind::EDP_PACKETS, StatisticKind::SUM)
    };

    for (auto configuration : configurations)
    {
        // For every configuration, call get data and get the value (time is not used) of the only element received.
        // For DataKinds without targets, setting the id value does not affect, for those with targets,
        // get the target as every entity related with this one.

        auto data = get_data(
            configuration.first,                    // DataKind of the series
            id,                                     // Id of source
            id,                                     // Id of everything connected to source
            1,                                      // Just one bin to get all data available
            configuration.second);                  // StatisticKind

        // Check that there is data to report, if not set or NaN give Nan value
        if (data.empty() || std::isnan(data[0].second))
        {
            summary[backend::data_kind_to_string(configuration.first)]
            [backend::statistic_kind_to_string(configuration.second)]
                = "NaN";
        }
        else
        {
            summary[backend::data_kind_to_string(configuration.first)]
            [backend::statistic_kind_to_string(configuration.second)]
                = data[0].second; // get the value of the first (only) element
        }
    }

    return summary;
}

std::string SyncBackendConnection::get_name(
        EntityId id)
{
    return backend::get_info_value(get_info(id), "name");
}

std::vector<StatisticsData> SyncBackendConnection::get_data(
        DataKind data_kind,
        EntityId source_entity_id,
        EntityId target_entity_id,
        uint16_t bins,
        StatisticKind statistic_kind,
        Timestamp start_time,
        Timestamp end_time)
{
    bool two_entities_data = false;
    std::vector<EntityId> source_ids;
    std::vector<EntityId> target_ids;

    try
    {
        for (auto kinds_supported : StatisticsBackend::get_data_supported_entity_kinds(data_kind))
        {
            // Get the entities of the kind required for the data type that are related with the entity source
            auto source_ids_tmp = get_entities(kinds_supported.first, source_entity_id);
            source_ids.insert(source_ids.end(), source_ids_tmp.begin(), source_ids_tmp.end());

            // Get the entities of the kind required for the data type that are related with the entity target
            if (kinds_supported.second != EntityKind::INVALID)
            {
                // If the target entity is required but not given, the source is used
                // This is usefule for two entities DataKinds when want to ask for all the targets for a source entity
                // Useful for summary
                two_entities_data = true;
                if (!target_entity_id.is_valid())
                {
                    target_entity_id = source_entity_id;
                }
                auto target_ids_tmp = get_entities(kinds_supported.second, target_entity_id);
                target_ids.insert(target_ids.end(), target_ids_tmp.begin(), target_ids_tmp.end());
            }
        }

        if (two_entities_data)
        {
            return StatisticsBackend::get_data(
                data_kind,
                source_ids,
                target_ids,
                bins,
                start_time,
                end_time,
                statistic_kind);
        }
        else
        {
            return StatisticsBackend::get_data(
                data_kind,
                source_ids,
                bins,
                start_time,
                end_time,
                statistic_kind);
        }
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting data: " << e.what();
        return std::vector<StatisticsData>();
    }
}

void SyncBackendConnection::set_alias(
        const backend::EntityId& id,
        const std::string& new_alias)
{
    try
    {
        StatisticsBackend::set_alias(id, new_alias);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail setting new alias for entity: " << id.value();
    }
}

bool update_host(
    models::SubListedListModel* model,
    EntityId id,
    bool new_entity,
    bool inactive_visible)
{
    return update_one_entity_in_model(
        model,
        id,
        new_entity,
        inactive_visible,
        &SyncBackendConnection::create_host_data_);
}

bool update_one_entity_in_model(
    models::SubListedListModel* model,
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
            model->appendRow(create_function(id));
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
            // Clear the item so the submodules are erased
            item->clear();

            // Remove the item from the model
            model->removeRow(index);

            // Destroy Item object
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
