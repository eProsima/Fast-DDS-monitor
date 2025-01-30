// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file SyncBackendConnection.cpp
 *
 * This file includes the .ipp files with the class divided \c SyncBackendConnection implementation.
 */

#include <iostream>
#include <sstream>

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
#include <fastdds_monitor/utils.h>

namespace backend {

using namespace eprosima::statistics_backend;
using namespace models;

ListItem* SyncBackendConnection::create_host_data_(
        EntityId id)
{
    qDebug() << "Creating Host " << backend::backend_id_to_models_id(id);
    return new HostModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_user_data_(
        EntityId id)
{
    qDebug() << "Creating User " << backend::backend_id_to_models_id(id);
    return new UserModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_process_data_(
        EntityId id)
{
    qDebug() << "Creating Process " << backend::backend_id_to_models_id(id);
    return new ProcessModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_domain_data_(
        EntityId id)
{
    qDebug() << "Creating Domain " << backend::backend_id_to_models_id(id);
    return new DomainModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_topic_data_(
        EntityId id)
{
    qDebug() << "Creating Topic " << backend::backend_id_to_models_id(id);
    return new TopicModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_participant_data_(
        backend::EntityId id)
{
    qDebug() << "Creating Participant " << backend::backend_id_to_models_id(id);
    return new ParticipantModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_datawriter_data_(
        backend::EntityId id)
{
    qDebug() << "Creating DataWriter " << backend::backend_id_to_models_id(id);
    return new EndpointModelItem(id, get_info(id), EntityKind::DATAWRITER);
}

ListItem* SyncBackendConnection::create_datareader_data_(
        backend::EntityId id)
{
    qDebug() << "Creating DataReader " << backend::backend_id_to_models_id(id);
    return new EndpointModelItem(id, get_info(id), EntityKind::DATAREADER);
}

ListItem* SyncBackendConnection::create_locator_data_(
        backend::EntityId id)
{
    qDebug() << "Creating Locator " << backend::backend_id_to_models_id(id);
    return new LocatorModelItem(id, get_info(id));
}

/// UPDATE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_host_item(
        ListItem* host_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    auto host_item_sublist = static_cast<SubListedListItem*>(host_item);

    return update_model_(
        host_item_sublist->submodel(),
        EntityKind::USER,
        host_item->get_entity_id(),
        &SyncBackendConnection::update_user_item,
        &SyncBackendConnection::create_user_data_,
        inactive_visible,
        metatraffic_visible);
}

bool SyncBackendConnection::update_user_item(
        ListItem* user_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    auto user_item_sublist = static_cast<SubListedListItem*>(user_item);

    return update_model_(
        user_item_sublist->submodel(),
        EntityKind::PROCESS,
        user_item->get_entity_id(),
        &SyncBackendConnection::update_process_item,
        &SyncBackendConnection::create_process_data_,
        inactive_visible,
        metatraffic_visible);
}

bool SyncBackendConnection::update_process_item(
        ListItem* process_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    // Process does not have update
    static_cast<void>(process_item);
    static_cast<void>(inactive_visible);
    static_cast<void>(metatraffic_visible);
    return false;
}

bool SyncBackendConnection::update_domain_item(
        ListItem* domain_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    auto domain_item_sublist = static_cast<SubListedListItem*>(domain_item);

    return update_model_(
        domain_item_sublist->submodel(),
        EntityKind::TOPIC,
        domain_item->get_entity_id(),
        &SyncBackendConnection::update_topic_item,
        &SyncBackendConnection::create_topic_data_,
        inactive_visible,
        metatraffic_visible);
}

bool SyncBackendConnection::update_topic_item(
        ListItem* topic_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    // Process does not have update
    static_cast<void>(topic_item);
    static_cast<void>(inactive_visible);
    static_cast<void>(metatraffic_visible);
    return false;
}

bool SyncBackendConnection::update_participant_item(
        ListItem* participant_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    auto participant_item_sublist = static_cast<SubListedListItem*>(participant_item);

    bool res = update_model_(
        participant_item_sublist->submodel(),
        EntityKind::DATAREADER,
        participant_item->get_entity_id(),
        &SyncBackendConnection::update_endpoint_item,
        &SyncBackendConnection::create_datareader_data_,
        inactive_visible,
        metatraffic_visible);

    res = update_model_(
        participant_item_sublist->submodel(),
        EntityKind::DATAWRITER,
        participant_item->get_entity_id(),
        &SyncBackendConnection::update_endpoint_item,
        &SyncBackendConnection::create_datawriter_data_,
        inactive_visible,
        metatraffic_visible) || res;

    return res;
}

bool SyncBackendConnection::update_endpoint_item(
        ListItem* endpoint_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    auto endpoint_item_sublist = static_cast<SubListedListItem*>(endpoint_item);

    return update_model_(
        endpoint_item_sublist->submodel(),
        EntityKind::LOCATOR,
        endpoint_item->get_entity_id(),
        &SyncBackendConnection::update_locator_item,
        &SyncBackendConnection::create_locator_data_,
        inactive_visible,
        metatraffic_visible);
}

bool SyncBackendConnection::update_locator_item(
        ListItem* locator_item,
        bool inactive_visible,
        bool metatraffic_visible)
{
    // Locator does not have update
    static_cast<void>(locator_item);
    static_cast<void>(inactive_visible);
    static_cast<void>(metatraffic_visible);
    return false;
}

/// UPDATE STRUCTURE PRIVATE FUNCTIONS
bool SyncBackendConnection::update_physical_model(
        models::ListModel* physical_model,
        bool inactive_visible,
        bool metatraffic_visible)
{
    qDebug() << "Update Physical Data";

    return update_model_(
        physical_model,
        EntityKind::HOST,
        ID_ALL,
        &SyncBackendConnection::update_host_item,
        &SyncBackendConnection::create_host_data_,
        inactive_visible,
        metatraffic_visible);
}

bool SyncBackendConnection::update_logical_model(
        models::ListModel* logical_model,
        bool inactive_visible,
        bool metatraffic_visible)
{
    qDebug() << "Update Logical Data";

    return update_model_(
        logical_model,
        EntityKind::DOMAIN_ENTITY,
        ID_ALL,
        &SyncBackendConnection::update_domain_item,
        &SyncBackendConnection::create_domain_data_,
        inactive_visible,
        metatraffic_visible);
}

bool SyncBackendConnection::update_dds_model(
        models::ListModel* dds_model,
        EntityId id,
        bool inactive_visible,
        bool metatraffic_visible)
{
    qDebug() << "Update DDS Data";

    return update_model_(
        dds_model,
        EntityKind::PARTICIPANT,
        id,
        &SyncBackendConnection::update_participant_item,
        &SyncBackendConnection::create_participant_data_,
        inactive_visible,
        metatraffic_visible);
}

bool SyncBackendConnection::update_get_data_dialog_entity_id(
        models::ListModel* entity_model,
        EntityKind entity_kind,
        bool inactive_visible,
        bool metatraffic_visible)
{
    bool changed = false;

    for (auto entity_id : get_entities(entity_kind, ID_ALL))
    {
        // Only get entities active or non-metatraffic if requested so
        if ((inactive_visible || get_alive(entity_id)) && (metatraffic_visible || !is_metatraffic(entity_id)))
        {
            entity_model->appendRow(new EntityItem(entity_id, entity_kind, get_info(entity_id)));
            changed = true;
        }
    }

    return changed;
}

bool SyncBackendConnection::update_item_(
        ListItem* item,
        bool (SyncBackendConnection::* update_function)(ListItem*, bool, bool),
        bool inactive_visible,
        bool metatraffic_visible)
{
    bool res = update_item_info_(item);
    return (this->*update_function)(item, inactive_visible, metatraffic_visible) || res;
}

bool SyncBackendConnection::update_item_info_(
        ListItem* item)
{
    // Query for this item info and updte it
    item->info(get_info(item->get_entity_id()));
    item->triggerItemUpdate();
    return true;
}

bool SyncBackendConnection::update_model_(
        ListModel* model,
        EntityKind type,
        EntityId id,
        bool (SyncBackendConnection::* update_function)(ListItem*, bool, bool),
        ListItem* (SyncBackendConnection::* create_function)(EntityId),
        bool inactive_visible,
        bool metatraffic_visible)
{
    bool changed = false;

    // For each User get all processes
    for (auto subentity_id : get_entities(type, id))
    {
        // Check if it exists already
        int index = model->rowIndexFromId(subentity_id);

        // If it does not exist, it creates it and add a Row with it
        // If it exists it updates its info
        if (index == -1)
        {
            // Only create the new entity if is alive or inactive are visible,
            // and if is metatraffic or metatraffic is visible
            if ((inactive_visible || get_alive(subentity_id))
                    && (metatraffic_visible || !is_metatraffic(subentity_id)))
            {
                // Creates the Item object and update its data
                model->appendRow((this->*create_function)(subentity_id));
                changed = true;
                models::ListItem* subentity_item = model->find(subentity_id);

                changed = update_item_(subentity_item, update_function, inactive_visible,
                                metatraffic_visible) || changed;
            }
        }

        // In case this entity is inactive and inactive are not being displayed,
        // or if it is metatraffic and metatraffic are not being displayed, remove it
        else if ((!inactive_visible && !get_alive(subentity_id))
                || (!metatraffic_visible && is_metatraffic(subentity_id)))
        {
            models::ListItem* subentity_item = model->at(index);

            // Remove the row
            model->removeRow(index);

            // Remove its subentities and the object ListItem
            delete subentity_item;

            changed = true;
        }

        // Otherwise just update the entity
        else
        {
            models::ListItem* subentity_item = model->at(index);
            changed = update_item_(subentity_item, update_function, inactive_visible, metatraffic_visible)
                    || changed;
        }
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
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

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
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

        return false;
    }
}

EntityId SyncBackendConnection::init_monitor(
        int domain)
{
    try
    {
        return StatisticsBackend::init_monitor(domain, nullptr, CallbackMask::all(),
                       DataKindMask::none(), FASTDDS_MONITOR_APP);
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
        std::string discovery_server_locators)
{
    try
    {
        return StatisticsBackend::init_monitor(
            discovery_server_locators,
            nullptr, CallbackMask::all(), DataKindMask::none(), FASTDDS_MONITOR_APP);
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
        // Refactor json info so there are no vectors
        return backend::refactor_json(StatisticsBackend::get_info(id));
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity info: " << e.what();
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

        return EntityInfo();
    }
}

backend::EntityId SyncBackendConnection::get_endpoint_topic_id(
        backend::EntityId endpoint_id)
{
    return StatisticsBackend::get_endpoint_topic_id(endpoint_id);
}

backend::EntityId SyncBackendConnection::get_domain_id(
        backend::EntityId entity_id)
{
    return StatisticsBackend::get_domain_id(entity_id);
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
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

        return true;
    }
}

bool SyncBackendConnection::is_metatraffic(
        EntityId id)
{
    try
    {
        return StatisticsBackend::is_metatraffic(id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity metatraffic attribute: " << e.what();
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

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
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

        return EntityKind::INVALID;
    }
}

backend::EntityId SyncBackendConnection::get_entity_by_guid(
        const std::string& guid)
{
    try
    {
        return StatisticsBackend::get_entity_by_guid(guid);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting entity by guid " << e.what();
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

        return EntityId::invalid();
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
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

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

        // Check that there is data to report, if not set or NaN do not show this statistic data.
        if (!data.empty() && !std::isnan(data[0].second))
        {
            // get the value of the first (only) element
            summary[backend::data_kind_to_string(configuration.first)]
            [backend::statistic_kind_to_string(configuration.second)]
                = utils::double_to_string(data[0].second) + " [" + get_data_kind_units(configuration.first) + "]";
        }
    }

    return summary;
}

std::string SyncBackendConnection::get_name(
        EntityId id)
{
    return backend::get_info_value(get_info(id), "name");
}

std::string SyncBackendConnection::get_alias(
        EntityId id)
{
    return backend::get_info_value(get_info(id), "alias");
}

std::string SyncBackendConnection::get_data_type_name(
        backend::EntityId id)
{
    return backend::get_info_value(get_info(id), "data_type");
}

std::string SyncBackendConnection::get_guid(
        backend::EntityId id)
{
    return backend::get_info_value(get_info(id), "guid");
}

StatusLevel SyncBackendConnection:: get_status(
        EntityId id)
{
    return StatisticsBackend::get_status(id);
}

std::vector<StatisticsData> SyncBackendConnection::get_data(
        DataKind data_kind,
        EntityId source_entity_id,
        EntityId target_entity_id,
        uint16_t bins,
        StatisticKind statistic_kind,
        Timestamp start_time /* = Timestamp() */,
        Timestamp end_time /* = std::chrono::system_clock::now() */)
{
    std::vector<EntityId> source_ids;
    std::vector<EntityId> target_ids;

    bool two_entities_data = build_source_target_entities_vectors(
        data_kind, source_entity_id, target_entity_id, source_ids, target_ids);

    if (source_ids.empty())
    {
        return std::vector<StatisticsData>();
    }

    try
    {
        std::vector<StatisticsData> res;

        if (two_entities_data)
        {
            res = StatisticsBackend::get_data(
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
            res = StatisticsBackend::get_data(
                data_kind,
                source_ids,
                bins,
                start_time,
                end_time,
                statistic_kind);
        }

        // Change units depending on the dataKind
        filter(res, data_kind);
        change_unit_magnitude(res, data_kind);
        sort(res);

        return res;
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting data: " << e.what();
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

        return std::vector<StatisticsData>();
    }
}

void SyncBackendConnection::dump(
        const std::string file,
        bool clear)
{
    return StatisticsBackend::dump_database(file, clear);
}

void SyncBackendConnection::clear_entities()
{
    return StatisticsBackend::clear_inactive_entities();
}

void SyncBackendConnection::clear_statistics_data(
        Timestamp time_to /* = the_end_of_time() */)
{
    return StatisticsBackend::clear_statistics_data(time_to);
}

bool SyncBackendConnection::entity_exists(
        EntityId entity_id)
{
    return !get_info(entity_id).empty();
}

bool SyncBackendConnection::data_available(
        DataKind data_kind,
        EntityId source_entity_id,
        EntityId target_entity_id,
        Timestamp start_time /* = Timestamp() */,
        Timestamp end_time /* = std::chrono::system_clock::now() */)
{
    // TODO: Replace by the actual function in the backend when it is implemented.
    std::vector<StatisticsData> data = get_data(
        data_kind, source_entity_id, target_entity_id, 1, StatisticKind::NONE, start_time, end_time);
    return !data.empty();
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        ConnectionListSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        DeadlineMissedSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        IncompatibleQosSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        InconsistentTopicSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        LivelinessChangedSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        LivelinessLostSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        ProxySample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        SampleLostSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

bool SyncBackendConnection::get_status_data(
        EntityId id,
        ExtendedIncompatibleQosSample& sample)
{
    try
    {
        StatisticsBackend::get_status_data(id, sample);
        return true;
    }
    catch (const Error& e)
    {
        qWarning() << "Error retrieving sample: " << e.what();
    }
    catch (const BadParameter& e)
    {
        qWarning() << "Bad Parameter retrieving sample " << e.what();
    }
    return false;
}

std::string SyncBackendConnection::get_deserialized_guid(
        const backend::GUID_s& data)
{
    return StatisticsBackend::deserialize_guid(data);
}

backend::GUID_s SyncBackendConnection::get_serialize_guid(
        const std::string& guid_str)
{
    try
    {
        return StatisticsBackend::serialize_guid(guid_str);
    }
    catch (const std::exception& e)
    {
        qWarning() << "Error generating GUID from string " << e.what();
    }
    return backend::GUID_s();
}

bool SyncBackendConnection::build_source_target_entities_vectors(
        DataKind data_kind,
        EntityId source_entity_id,
        EntityId target_entity_id,
        std::vector<EntityId>& source_ids,
        std::vector<EntityId>& target_ids)
{
    bool two_entities_data = false;
    source_ids.clear();
    target_ids.clear();

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
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting the supported entity kinds for data kind "
                   << utils::to_QString(backend::data_kind_to_string(data_kind)) << ": " << e.what();
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

        return false;
    }

    return two_entities_data;
}

Graph SyncBackendConnection::get_domain_view_graph (
        const EntityId& domain_id)
{
    try
    {
        return StatisticsBackend::get_domain_view_graph(domain_id);
    }
    catch (const Exception& e)
    {
        qWarning() << "Fail getting the domain view JSON graph for entity id "
                   << domain_id.value() << ":" << e.what();
        static_cast<void>(e); // In release qWarning does not compile and so e is not used
        return Graph();
    }
}

std::string SyncBackendConnection::get_type_idl(
        const EntityId& id)
{
    try
    {
        return StatisticsBackend::get_type_idl(id);
    }
    catch (const std::exception& e)
    {
        qWarning() << "Fail getting the IDL type for entity id " << id.value() << ": " << e.what();
        return "";
    }
}

void SyncBackendConnection::change_unit_magnitude(
        std::vector<StatisticsData>& data,
        DataKind data_kind)
{
    switch (data_kind)
    {
        case DataKind::FASTDDS_LATENCY:
        case DataKind::NETWORK_LATENCY:

            // Convert from ns to ns
            std::for_each(data.begin(), data.end(),
                    [](StatisticsData& point)
                    {
                        point.second /= 1000;
                    });
            break;

        default:
            break;
    }
}

void SyncBackendConnection::filter(
        std::vector<StatisticsData>& data,
        DataKind data_kind)
{
    if (get_data_kind_units(data_kind) == "count")
    {
        // To count units, change NaN data with 0
        std::for_each(data.begin(), data.end(),
                [](StatisticsData& point)
                {
                    if (std::isnan(point.second))
                    {
                        point.second = 0;
                    }
                });
    }
    else
    {
        // To non count units, erase NaNs
        data.erase(
            std::remove_if(data.begin(), data.end(),
            [](const StatisticsData& point)
            {
                return std::isnan(point.second);
            }),
            data.end());
    }
}

void SyncBackendConnection::sort(
        std::vector<StatisticsData>& data)
{
    std::sort(data.begin(), data.end());
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
        static_cast<void>(e); // In release qWarning does not compile and so e is not used

    }
}

bool SyncBackendConnection::update_host(
        models::ListModel* physical_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
{
    // Host model is already physical model
    return update_one_entity_in_model_(
        physical_model,
        id,
        new_entity,
        &SyncBackendConnection::create_host_data_,
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_user(
        models::ListModel* physical_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
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
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_process(
        models::ListModel* physical_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
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
        qWarning() << "Error getting user model for process " << id.value();
        return false;
    }

    return update_one_entity_in_model_(
        user_model,
        id,
        new_entity,
        &SyncBackendConnection::create_user_data_,
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_domain(
        models::ListModel* logical_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
{
    // Domain model is already logical model
    return update_one_entity_in_model_(
        logical_model,
        id,
        new_entity,
        &SyncBackendConnection::create_domain_data_,
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_topic(
        models::ListModel* logical_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
{
    // Get Domain model where this Topic belongs
    ListModel* domain_model = get_model_(logical_model, id, EntityKind::DOMAIN_ENTITY);

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
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_participant(
        models::ListModel* dds_model,
        EntityId id,
        bool new_entity,
        EntityId related_entity_id,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
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
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_datawriter(
        models::ListModel* dds_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
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
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_datareader(
        models::ListModel* dds_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
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
        inactive_visible,
        metatraffic_visible,
        last_clicked);
}

bool SyncBackendConnection::update_locator(
        models::ListModel* dds_model,
        EntityId id,
        bool new_entity,
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
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
        std::vector<ListModel*> dw_models = get_locator_models_(participant_model, id, EntityKind::DATAWRITER);

        for (auto dw_model : dw_models)
        {
            if (dw_model != nullptr)
            {
                res = update_one_entity_in_model_(
                    dw_model,
                    id,
                    new_entity,
                    &SyncBackendConnection::create_locator_data_,
                    inactive_visible,
                    metatraffic_visible,
                    last_clicked) || res;
            }
        }


        // Get DataReader model where this locator belongs
        std::vector<ListModel*> dr_models = get_locator_models_(participant_model, id, EntityKind::DATAREADER);

        for (auto dr_model : dr_models)
        {
            if (dr_model != nullptr)
            {
                res = update_one_entity_in_model_(
                    dr_model,
                    id,
                    new_entity,
                    &SyncBackendConnection::create_locator_data_,
                    inactive_visible,
                    metatraffic_visible,
                    last_clicked) || res;
            }
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

    std::vector<backend::EntityId> parents = get_entities(parent_kind, id);

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

std::vector<ListModel*> SyncBackendConnection::get_locator_models_(
        models::ListModel* parent_model,
        EntityId id,
        EntityKind parent_kind)
{
    std::vector<ListModel*> models;
    std::vector<backend::EntityId> parents;

    parents = get_entities(parent_kind, id);

    for (backend::EntityId parent_id : parents)
    {
        // Once we have the datareader/datawriter id, we get the item related to it in the participants model
        ListItem* parent_item = parent_model->find(parent_id);

        if (parent_item == nullptr)
        {
            // It is not an error in dds model
            qDebug() << "Parent item of entity " << id.value() << " does not exist";
            continue;
        }

        // Parent must be SubListedListItem so it can contain something, so this cast should not fail
        auto parent_sublist = static_cast<SubListedListItem*>(parent_item);

        if (parent_sublist == nullptr)
        {
            qCritical() << "Parent item was not SubListed.";
            continue;
        }

        models.push_back(parent_sublist->submodel());
    }

    return models;
}

bool SyncBackendConnection::update_one_entity_in_model_(
        models::ListModel* model,
        EntityId id,
        bool new_entity,
        ListItem* (SyncBackendConnection::* create_function)(EntityId),
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked)
{
    // Check if element already exists
    int index = model->rowIndexFromId(id);

    // The element does not exist
    if (index == -1)
    {
        // If it didnt exist yet something has gone wrong in backend
        if (!new_entity)
        {
            #ifdef QT_DEBUG
            qWarning() << "Trying to update an entity that did not exist";
            #endif // ifdef QT_DEBUG
        }

        // Get alive status and metatraffic attribute of entity.
        // This is faster than asking for the whole info, which in some cases will not be needed.
        bool active = get_alive(id);
        bool metatraffic = is_metatraffic(id);
        if ((inactive_visible || active) && (metatraffic_visible || !metatraffic))
        {
            ListItem* item = (this->*create_function)(id);
            item->clicked(last_clicked);
            model->appendRow(item);
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

        // Get alive status and metatraffic attribute of entity. Take it from Backend and not from item because item has
        // not been uploaded yet.
        bool active = get_alive(id);
        bool metatraffic = is_metatraffic(id);

        // If it is not alive and inactive are not visible,
        // or if it is metatraffic and metatraffic are not visible, this entity must be erased from model
        if ((!inactive_visible && !active) || (!metatraffic_visible && metatraffic))
        {
            // Remove the item from the model
            // This destroys the pointer of the item
            model->removeRow(index);

            return true;
        }
        else
        {
            // In case the entity must keep existing, just update its info
            item->clicked(last_clicked);
            return update_item_info_(item);
        }
    }
}

std::string SyncBackendConnection::get_data_kind_units(
        DataKind data_kind)
{
    switch (data_kind)
    {
        case DataKind::FASTDDS_LATENCY:
#ifdef _WIN32
            return "us";
#else
            return "\u00b5s";
#endif // ifdef _WIN32
        case DataKind::NETWORK_LATENCY:
#ifdef _WIN32
            return "us";
#else
            return "\u00b5s";
#endif // ifdef _WIN32
        case DataKind::PUBLICATION_THROUGHPUT:
            return "B/s";
        case DataKind::SUBSCRIPTION_THROUGHPUT:
            return "B/s";
        case DataKind::RTPS_PACKETS_SENT:
            return "count";
        case DataKind::RTPS_BYTES_SENT:
            return "B";
        case DataKind::RTPS_PACKETS_LOST:
            return "count";
        case DataKind::RTPS_BYTES_LOST:
            return "B";
        case DataKind::RESENT_DATA:
            return "count";
        case DataKind::HEARTBEAT_COUNT:
            return "count";
        case DataKind::ACKNACK_COUNT:
            return "count";
        case DataKind::NACKFRAG_COUNT:
            return "count";
        case DataKind::GAP_COUNT:
            return "count";
        case DataKind::DATA_COUNT:
            return "count";
        case DataKind::PDP_PACKETS:
            return "count";
        case DataKind::EDP_PACKETS:
            return "count";
        case DataKind::DISCOVERY_TIME:
            return "ms";
        case DataKind::SAMPLE_DATAS:
            return "count";
        default:
            return "-";
    }
}

std::vector<std::string> SyncBackendConnection::ds_supported_transports()
{
    return std::vector<std::string>({"UDPv4", "UDPv6", "TCPv4", "TCPv6"});
}

std::vector<std::string> SyncBackendConnection::get_statistic_kinds()
{
    return std::vector<std::string>({
            "MEAN",
            "STANDARD_DEVIATION",
            "MAX",
            "MIN",
            "MEDIAN",
#if !defined(NDEBUG)
            "COUNT",
#endif // if !defined(NDEBUG)
            "SUM",
            "RAW DATA"
        });
}

std::vector<std::string> SyncBackendConnection::get_data_kinds()
{
    return std::vector<std::string>({
            "FASTDDS_LATENCY",
            "PUBLICATION_THROUGHPUT",
            "SUBSCRIPTION_THROUGHPUT",
            // The following data kinds are currently under development and are therefore only displayed if the monitor
            // is compiled in Debug.
#if !defined(NDEBUG)
            "NETWORK_LATENCY",
            "RTPS_PACKETS_SENT",
            "RTPS_BYTES_SENT",
            "RTPS_PACKETS_LOST",
            "RTPS_BYTES_LOST",
            "DISCOVERY_TIME",
            "SAMPLE_DATAS",
#endif // #if !defined(NDEBUG)
            "RESENT_DATA",
            "HEARTBEAT_COUNT",
            "ACKNACK_COUNT",
            "NACKFRAG_COUNT",
            "GAP_COUNT",
            "DATA_COUNT",
            "PDP_PACKETS",
            "EDP_PACKETS"
        });
}

std::vector<std::pair<EntityKind, EntityKind>> SyncBackendConnection::get_data_supported_entity_kinds(
        DataKind data_kind)
{
    try
    {
        return StatisticsBackend::get_data_supported_entity_kinds(data_kind);
    }
    catch (const std::exception& e)
    {
        qWarning() << "Fail getting target entity for "
                   << utils::to_QString(backend::data_kind_to_string(data_kind)) << "data kind: " << e.what();
        static_cast<void>(e); // In release qWarning does not compile and so e is not used
        return std::vector<std::pair<EntityKind, EntityKind>>();
    }
}

bool SyncBackendConnection::data_kind_has_target(
        const DataKind& data_kind)
{
    for (std::pair<EntityKind, EntityKind> entity_kind_pair : get_data_supported_entity_kinds(data_kind))
    {
        if (entity_kind_pair.second == EntityKind::INVALID)
        {
            return false;
        }
    }
    return true;
}

} //namespace backend
