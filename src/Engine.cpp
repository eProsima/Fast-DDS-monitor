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

#include <chrono>
#include <sstream>

#include <QDateTime>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QtCore/QRandomGenerator>
#include <qqmlcontext.h>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/backend/Listener.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/Controller.h>
#include <fastdds_monitor/Engine.h>
#include <fastdds_monitor/io/csv.h>
#include <fastdds_monitor/model/dds/ParticipantModelItem.h>
#include <fastdds_monitor/model/logical/DomainModelItem.h>
#include <fastdds_monitor/model/physical/HostModelItem.h>
#include <fastdds_monitor/model/statistics/EntityItem.h>
#include <fastdds_monitor/model/SubListedListItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/model/tree/TreeModel.h>
#include <fastdds_monitor/statistics/StatisticsData.h>
#include <fastdds_monitor/statistics/dynamic/DynamicStatisticsData.h>
#include <fastdds_monitor/statistics/historic/HistoricStatisticsData.h>

using EntityInfo = backend::EntityInfo;

Engine::Engine()
    : enabled_(false)
    , last_dds_entity_clicked_(backend::ID_ALL)
    , last_dds_entity_clicked_kind_(backend::EntityKind::INVALID)
    , last_physical_logical_entity_clicked_(backend::ID_ALL)
    , last_physical_logical_entity_clicked_kind_(backend::EntityKind::INVALID)
    , inactive_visible_(true)
    , metatraffic_visible_(false)
{
}

QObject* Engine::enable()
{
    // Initialize async backend
    listener_ = new backend::Listener(this);
    backend_connection_.set_listener(listener_);

    // Initialize models
    participants_model_ = new models::SubListedListModel(new models::ParticipantModelItem());
    fill_dds_data_();

    physical_model_ = new models::SubListedListModel(new models::HostModelItem());
    fill_physical_data_();

    logical_model_ = new models::SubListedListModel(new models::DomainModelItem());
    fill_logical_data_();

    info_model_ = new models::InfoModel();
    fill_first_entity_info_();

    summary_model_ = new models::TreeModel();
    fill_summary_(backend::ID_ALL);

    // Creates a default structure for issue json and fills the tree model with it
    issue_model_ = new models::TreeModel();
    generate_new_issue_info_();
    fill_issue_();

    // Creates a default json structure for logging messages and fills the tree model with it
    log_model_ = new models::TreeModel();
    generate_new_log_info_();
    fill_log_();

    // Creates a default json structure for status messages and fills the tree model with it
    status_model_ = new models::TreeModel();
    generate_new_status_info_();
    fill_status_();

    source_entity_id_model_ = new models::ListModel(new models::EntityItem());
    fill_available_entity_id_list_(backend::EntityKind::HOST, "getDataDialogSourceEntityId");
    destination_entity_id_model_ = new models::ListModel(new models::EntityItem());
    fill_available_entity_id_list_(backend::EntityKind::HOST, "getDataDialogDestinationEntityId");

    historic_statistics_data_ = new HistoricStatisticsData();
    dynamic_statistics_data_ = new DynamicStatisticsData();
    controller_ = new Controller(this);

    // Set the initial time
    initial_time_ = std::chrono::system_clock::now();

    // Initialized qml
    rootContext()->setContextProperty("participantModel", participants_model_);
    rootContext()->setContextProperty("hostModel", physical_model_);
    rootContext()->setContextProperty("domainModel",  logical_model_);

    rootContext()->setContextProperty("qosModel", info_model_);
    rootContext()->setContextProperty("summaryModel", summary_model_);
    rootContext()->setContextProperty("issueModel", issue_model_);
    rootContext()->setContextProperty("logModel", log_model_);
    rootContext()->setContextProperty("statusModel", status_model_);

    rootContext()->setContextProperty("entityModelFirst", source_entity_id_model_);
    rootContext()->setContextProperty("entityModelSecond", destination_entity_id_model_);

    rootContext()->setContextProperty("historicData", historic_statistics_data_);
    rootContext()->setContextProperty("dynamicData", dynamic_statistics_data_);
    rootContext()->setContextProperty("controller", controller_);

    addImportPath(":/imports");
    load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    // Connect Callback Listener to this object
    QObject::connect(
        this,
        &Engine::new_callback_signal,
        this,
        &Engine::new_callback_slot);

    // Set enable as True
    enabled_ = true;

    return rootObjects().value(0);
}

Engine::~Engine()
{
    if  (enabled_)
    {
        // First free the listener to stop new entities from appear
        if (listener_)
        {
            backend_connection_.unset_listener();
            delete listener_;
        }

        // View models
        if (participants_model_)
        {
            delete participants_model_;
        }

        if (physical_model_)
        {
            delete physical_model_;
        }

        if (logical_model_)
        {
            delete logical_model_;
        }

        // Info models
        if (summary_model_)
        {
            delete summary_model_;
        }

        if (info_model_)
        {
            delete info_model_;
        }

        if (issue_model_)
        {
            delete issue_model_;
        }

        if (log_model_)
        {
            delete log_model_;
        }

        if (status_model_)
        {
            delete status_model_;
        }

        // Auxiliar models
        if (source_entity_id_model_)
        {
            delete source_entity_id_model_;
        }

        if (destination_entity_id_model_)
        {
            delete destination_entity_id_model_;
        }

        // Interactive models
        if (historic_statistics_data_)
        {
            delete historic_statistics_data_;
        }

        if (dynamic_statistics_data_)
        {
            delete dynamic_statistics_data_;
        }
        // WARNING: destroying this object heads to an error in javascript because cannot access methods of null:
        // qrc:/qml/AboutDialog.qml:57: TypeError: Cannot call method '...' of null
        // The elements that fail are:
        // system_info; qt_version; fastdds_statistics_backend_version; fastdds_version;
        // build_date; git_commit; fastdds_monitor_version; inactive_visible
        if (controller_)
        {
            // delete controller_;
        }
    }
}

void Engine::init_monitor(
        int domain)
{
    std::lock_guard<std::recursive_mutex> lock(initializing_monitor_);

    backend::EntityId domain_id = backend_connection_.init_monitor(domain);

    if (domain_id.is_valid())
    {
        shared_init_monitor_(domain_id);
    }
    else
    {
        process_error(
            "Error trying to initialize monitor with DomainId: " + std::to_string(domain),
            ErrorType::INIT_MONITOR);
    }
}

void Engine::init_monitor(
        QString discovery_server_guid_prefix,
        QString discovery_server_locators)
{
    std::lock_guard<std::recursive_mutex> lock(initializing_monitor_);

    backend::EntityId domain_id = backend_connection_.init_monitor(
        utils::to_string(discovery_server_guid_prefix),
        utils::to_string(discovery_server_locators));

    if (domain_id.is_valid())
    {
        shared_init_monitor_(domain_id);
    }
    else
    {
        process_error(
            "Error trying to initialize monitor in Discovery Server with GUID " +
            utils::to_string(discovery_server_guid_prefix) +
            " and locators " + utils::to_string(discovery_server_locators),
            ErrorType::INIT_DS_MONITOR);
    }
}

void Engine::shared_init_monitor_(
        backend::EntityId domain_id)
{
    // if init_monitor fail it does not arrive here

    if (domain_id.is_valid())
    {
        add_status_domain_(backend_connection_.get_name(domain_id), utils::now());

        // WARNING
        // When a new Domain is created its entities begin to appear in callbacks
        // If the dds model is updated with this model, the callbacks will refer to new entities but they
        // will be already in the model as the model will call backend to update it completly
        // This, entity_clicked must be called but do not update dds model (but reset it)
        update_entity(domain_id, &Engine::update_domain, true, false);

        entity_clicked(domain_id, backend::EntityKind::DOMAIN, false);
    }
}

bool Engine::fill_entity_info_(
        backend::EntityId id /*ID_ALL*/)
{
    if (id == backend::ID_ALL)
    {
        EntityInfo default_info;
        default_info["No entity"] = "Click over any entity to see its values";
        info_model_->update(default_info);
        info_model_->update_selected_entity(
            backend::entity_kind_to_QString(backend::EntityKind::INVALID),
            "No entity selected");
    }
    else
    {
        EntityInfo entity_info = backend_connection_.get_info(id);
        info_model_->update(entity_info);
        info_model_->update_selected_entity(
            utils::to_QString(entity_info["kind"]),
            utils::to_QString(entity_info["alias"]));
    }
    return true;
}

bool Engine::fill_summary_(
        backend::EntityId id /*ID_ALL*/)
{
    summary_model_->update(backend_connection_.get_summary(id));
    return true;
}

bool Engine::fill_issue_()
{
    issue_model_->update(issue_info_);
    return true;
}

bool Engine::fill_log_()
{
    log_model_->update(log_info_);
    return true;
}

bool Engine::fill_status_()
{
    status_model_->update(status_info_);
    return true;
}

void Engine::generate_new_issue_info_()
{
    EntityInfo info;

    info["Issues"] = EntityInfo();

    issue_info_ = info;
}

void Engine::generate_new_log_info_()
{
    EntityInfo info;

    info["Callbacks"] = EntityInfo();

    log_info_ = info;
}

void Engine::generate_new_status_info_()
{
    EntityInfo info;

    info["Entities"] = EntityInfo();
    info["Entities"]["Domains"] = EntityInfo();
    info["Entities"]["Entities"] = 0;

    status_info_ = info;
}

void Engine::sum_entity_number_issue(
        int n)
{
    status_info_["Entities"]["Entities"] = status_info_["Entities"]["Entities"].get<double>() + n;
    fill_status_();
}

bool Engine::add_status_domain_(
        std::string name,
        std::string time)
{
    status_info_["Entities"]["Domains"][time] = name;
    fill_status_();
    add_log_callback_("Monitor initialized in domain " + name, time);

    return true;
}

bool Engine::add_log_callback_(
        std::string callback,
        std::string time)
{
    log_info_["Callbacks"][time] = callback;
    fill_log_();

    return true;
}

void Engine::clear_callback_log_()
{
    log_info_["Callbacks"] = EntityInfo();
    fill_log_();
}

bool Engine::add_issue_info_(
        std::string issue,
        std::string time)
{
    issue_info_["Issues"][time] = issue;
    fill_issue_();

    return true;
}

void Engine::clear_issue_info_()
{
    issue_info_["Issues"] = EntityInfo();
    fill_issue_();
}

bool Engine::fill_first_entity_info_()
{
    EntityInfo info = R"({"No monitors active.":"Start a monitor in a specific domain"})"_json;
    info_model_->update(info);
    return true;
}

/// Backend API
bool Engine::fill_physical_data_()
{
    physical_model_->clear();
    return backend_connection_.update_physical_model(physical_model_, inactive_visible(), metatraffic_visible());
}

bool Engine::update_host(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_host(physical_model_, id, new_entity, inactive_visible(), metatraffic_visible(),
                   last_clicked);
}

bool Engine::update_user(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_user(physical_model_, id, new_entity, inactive_visible(), metatraffic_visible(),
                   last_clicked);
}

bool Engine::update_process(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_process(physical_model_, id, new_entity, inactive_visible(),
                   metatraffic_visible(), last_clicked);
}

// LOGICAL PARTITION
bool Engine::fill_logical_data_()
{
    logical_model_->clear();
    return backend_connection_.update_logical_model(logical_model_, inactive_visible(), metatraffic_visible());
}

bool Engine::update_domain(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_domain(logical_model_, id, new_entity, inactive_visible(), metatraffic_visible(),
                   last_clicked);
}

bool Engine::update_topic(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_topic(logical_model_, id, new_entity, inactive_visible(), metatraffic_visible(),
                   last_clicked);
}

// DDS PARTITION
bool Engine::fill_dds_data_()
{
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_physical_logical_entity_clicked_,
                   inactive_visible(), metatraffic_visible());
}

void Engine::reset_dds_data()
{
    participants_model_->clear();
}

bool Engine::update_dds_data(
        const backend::EntityId& id /*ID_ALL*/)
{
    return backend_connection_.update_dds_model(participants_model_, id, inactive_visible(), metatraffic_visible());
}

// Update the model with a new or updated entity
bool Engine::update_participant(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_participant(
        participants_model_,
        id,
        new_entity,
        last_physical_logical_entity_clicked_,
        inactive_visible(),
        metatraffic_visible(),
        last_clicked);
}

bool Engine::update_datawriter(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_datawriter(
        participants_model_,
        id,
        new_entity,
        inactive_visible(),
        metatraffic_visible(),
        last_clicked);
}

bool Engine::update_datareader(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_datareader(
        participants_model_,
        id,
        new_entity,
        inactive_visible(),
        metatraffic_visible(),
        last_clicked);
}

bool Engine::update_locator(
        const backend::EntityId& id,
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    return backend_connection_.update_locator(
        participants_model_,
        id,
        new_entity,
        inactive_visible(),
        metatraffic_visible(),
        last_clicked);
}

bool Engine::entity_clicked(
        backend::EntityId id,
        backend::EntityKind kind,
        bool update_dds /* = true */,
        bool reset_dds /* = true */)
{
    bool res = false;

    switch (kind)
    {
        case backend::EntityKind::PARTICIPANT:
        case backend::EntityKind::DATAREADER:
        case backend::EntityKind::DATAWRITER:
        case backend::EntityKind::LOCATOR:

            // In case the new entity is the same already clicked, skip
            if (id == last_dds_entity_clicked_)
            {
                break;
            }

            // Unclick last entity
            res = entity_dds_unclick_() || res;

            // Set as clicked entity
            last_dds_entity_clicked_ = id;
            last_dds_entity_clicked_kind_ = kind;

            res = update_entity_generic(id, kind, true, true) || res;

            break;

        case backend::EntityKind::HOST:
        case backend::EntityKind::USER:
        case backend::EntityKind::PROCESS:
        case backend::EntityKind::DOMAIN:
        case backend::EntityKind::TOPIC:

            // In case the new entity is the same already clicked, skip
            if (id == last_physical_logical_entity_clicked_)
            {
                break;
            }

            // Unclick last entity
            res = entity_physical_logical_unclick_() || res;

            // In physical and logical case, unclick also dds entity
            res = entity_dds_unclick_() || res;

            // Update new entity
            res = update_entity_generic(id, kind, true, true) || res;

            // Set as clicked entity
            last_physical_logical_entity_clicked_ = id;
            last_physical_logical_entity_clicked_kind_ = kind;

            // Reset dds model and update if needed
            if (reset_dds)
            {
                reset_dds_data();
            }
            if (update_dds)
            {
                res = update_dds_data(id) || res;
            }

            break;

        case backend::EntityKind::INVALID:

            // In case the new entity is the same already clicked, skip
            if (last_physical_logical_entity_clicked_kind_ == backend::EntityKind::INVALID)
            {
                return false;
            }

            // Unclick all
            res = entity_unclick_() || res;

            // Set as clicked entity
            last_dds_entity_clicked_ = id;
            last_dds_entity_clicked_kind_ = kind;
            last_physical_logical_entity_clicked_ = id;
            last_physical_logical_entity_clicked_kind_ = kind;

            // Reset dds model and update if needed
            if (reset_dds)
            {
                reset_dds_data();
            }
            if (update_dds)
            {
                res = update_dds_data(id) || res;
            }

            break;

        default:
            break;
    }

    // All entities
    res = fill_entity_info_(id) || res;
    res = fill_summary_(id) || res;

    return res;
}

bool Engine::entity_dds_unclick_()
{
    if (last_dds_entity_clicked_.is_valid_and_unique())
    {
        bool res = update_entity_generic(last_dds_entity_clicked_, last_dds_entity_clicked_kind_, true, false);

        last_dds_entity_clicked_ = backend::ID_ALL;
        last_dds_entity_clicked_kind_ = backend::EntityKind::INVALID;

        return res;
    }
    return false;
}

bool Engine::entity_physical_logical_unclick_()
{
    if (last_physical_logical_entity_clicked_.is_valid_and_unique())
    {
        bool res = update_entity_generic(
            last_physical_logical_entity_clicked_,
            last_physical_logical_entity_clicked_kind_,
            true,
            false);

        last_physical_logical_entity_clicked_ = backend::ID_ALL;
        last_physical_logical_entity_clicked_kind_ = backend::EntityKind::INVALID;

        return res;
    }
    return false;
}

bool Engine::entity_unclick_()
{
    bool res = false;

    // Need to be separated because || does not compute second if first value is true
    res = entity_dds_unclick_() || res;
    res = entity_physical_logical_unclick_() || res;

    return res;
}

bool Engine::fill_available_entity_id_list_(
        backend::EntityKind entity_kind,
        QString entity_model_id)
{
    return on_selected_entity_kind(entity_kind, entity_model_id);
}

bool Engine::on_selected_entity_kind(
        backend::EntityKind entity_kind,
        QString entity_model_id)
{
    if (entity_model_id == "getDataDialogSourceEntityId")
    {
        source_entity_id_model_->clear();
        return backend_connection_.update_get_data_dialog_entity_id(
            source_entity_id_model_,
            entity_kind,
            inactive_visible(),
            metatraffic_visible());
    }
    else if (entity_model_id == "getDataDialogDestinationEntityId")
    {
        destination_entity_id_model_->clear();
        return backend_connection_.update_get_data_dialog_entity_id(
            destination_entity_id_model_,
            entity_kind,
            inactive_visible(),
            metatraffic_visible());
    }
    else
    {
        return false;
    }
}

QtCharts::QVXYModelMapper* Engine::on_add_statistics_data_series(
        quint64 chartbox_id,
        backend::DataKind data_kind,
        backend::EntityId source_entity_id,
        backend::EntityId target_entity_id,
        quint16 bins,
        quint64 start_time,
        bool start_time_default,
        quint64 end_time,
        bool end_time_default,
        backend::StatisticKind statistic_kind)
{
    backend::Timestamp time_from =
            start_time_default ? initial_time_ : backend::Timestamp(std::chrono::milliseconds(start_time));
    backend::Timestamp time_to =
            end_time_default ? std::chrono::system_clock::now() : backend::Timestamp(std::chrono::milliseconds(end_time));

    std::vector<backend::StatisticsData> statistic_data = backend_connection_.get_data(
        data_kind,
        source_entity_id,
        target_entity_id,
        bins,
        statistic_kind,
        time_from,
        time_to);

    QVector<QPointF> points;
    points.reserve(static_cast<int>(statistic_data.size()));

    for (backend::StatisticsData data : statistic_data)
    {
        if (!std::isnan(data.second)) // This should not be needed as filter is done before... But lets keep it
        {
            points.append(QPointF(
                        std::chrono::duration_cast<std::chrono::milliseconds>(data.first.time_since_epoch()).count(),
                        data.second));
        }
    }

    // In case there are Nans at the beggining or end of the series, it adapts the chartbox to the real axis
    historic_statistics_data_->newXValue(
        chartbox_id,
        start_time_default
        ? std::chrono::duration_cast<std::chrono::milliseconds>(initial_time_.time_since_epoch()).count()
        : start_time);
    historic_statistics_data_->newXValue(
        chartbox_id,
        end_time_default
        ? std::chrono::duration_cast<std::chrono::milliseconds>(
            time_to.time_since_epoch()).count()
        : end_time);

    return historic_statistics_data_->add_series(chartbox_id, points);
}

void Engine::refresh_engine()
{
    entity_clicked(backend::ID_ALL, backend::EntityKind::INVALID);
}

void Engine::clear_log()
{
    clear_callback_log_();
    // In case there are expected callbacks emit signal to read them and
    // update the models from the graphic thread
    emit new_callback_signal();
}

void Engine::clear_issues()
{
    clear_issue_info_();
}

void Engine::process_callback_queue()
{
    // It iterates while run_ is activate and the queue has elements
    while (!callback_queue_.empty())
    {
        process_callback_();
    }
}

bool Engine::are_callbacks_to_process_()
{
    std::lock_guard<std::recursive_mutex> ml(callback_queue_mutex_);
    return callback_queue_.empty();
}

bool Engine::add_callback(
        backend::Callback callback)
{
    std::lock_guard<std::recursive_mutex> ml(callback_queue_mutex_);
    callback_queue_.append(callback);

    // Emit signal to specify there are new data
    emit new_callback_signal();

    return true;
}

void Engine::new_callback_slot()
{
    process_callback_queue();
}

bool Engine::process_callback_()
{
    backend::Callback first_callback;

    {
        std::lock_guard<std::recursive_mutex> ml(callback_queue_mutex_);
        first_callback = callback_queue_.front();
        callback_queue_.pop_front();
    }

    qDebug() << "Processing callback: " << backend::backend_id_to_models_id(first_callback.entity_id);

    return read_callback_(first_callback);
}

bool Engine::read_callback_(
        backend::Callback callback)
{
    // It should not read callbacks while a domain is being initialized
    std::lock_guard<std::recursive_mutex> lock(initializing_monitor_);

    if (callback.is_update)
    {
        // Add callback of updating entity to log model
        add_log_callback_("Update info in entity " + backend_connection_.get_name(callback.entity_id),
                utils::now());
    }
    else
    {
        // Add callback to log model
        add_log_callback_("New entity " + backend_connection_.get_name(callback.entity_id) + " discovered",
                utils::now());

        // Add one to the number of discovered entities
        sum_entity_number_issue(1);
    }

    return update_entity_generic(
        callback.entity_id, callback.entity_kind, callback.is_update);
}

bool Engine::update_entity_generic(
        backend::EntityId entity_id,
        backend::EntityKind entity_kind,
        bool is_update /* false */,
        bool is_last_clicked /* false */)
{
    switch (entity_kind)
    {
        case backend::EntityKind::HOST:
            return update_entity(
                entity_id, &Engine::update_host, !is_update, is_last_clicked);

        case backend::EntityKind::USER:
            return update_entity(
                entity_id, &Engine::update_user, !is_update, is_last_clicked);

        case backend::EntityKind::PROCESS:
            return update_entity(
                entity_id, &Engine::update_process, !is_update, is_last_clicked);

        case backend::EntityKind::DOMAIN:
            return update_entity(
                entity_id, &Engine::update_domain, !is_update, is_last_clicked);

        case backend::EntityKind::TOPIC:
            return update_entity(
                entity_id, &Engine::update_topic, !is_update, is_last_clicked);

        case backend::EntityKind::PARTICIPANT:
            return update_entity(
                entity_id, &Engine::update_participant, !is_update, is_last_clicked);

        case backend::EntityKind::DATAWRITER:
            return update_entity(
                entity_id, &Engine::update_datawriter, !is_update, is_last_clicked);

        case backend::EntityKind::DATAREADER:
            return update_entity(
                entity_id, &Engine::update_datareader, !is_update, is_last_clicked);

        case backend::EntityKind::LOCATOR:
            return update_entity(
                entity_id, &Engine::update_locator, !is_update, is_last_clicked);

        default:
            qWarning() << "Update callback of an Entity with unknown EntityKind";
            return false;
    }
}

void Engine::refresh_summary()
{
    fill_summary_(last_dds_entity_clicked_);
}

void Engine::process_error(
        std::string error_msg,
        ErrorType error_type /* = ErrorType::GENERIC */)
{
    add_issue_info_(error_msg, utils::now());
    controller_->send_error(utils::to_QString(error_msg), error_type);
}

void Engine::update_dynamic_chartbox(
        quint64 chartbox_id,
        quint64 time_to)
{
    // Get time into Timestamp
    backend::Timestamp time_to_timestamp_ = backend::Timestamp(std::chrono::milliseconds(time_to));

    /////
    // Get the parameters to get data
    // time_from, data_kind, source_ids, target_ids, statistics_kinds
    const UpdateParameters parameters = dynamic_statistics_data_->get_update_parameters(chartbox_id);

    /////
    // Collect the data for each series and store it in a point vector
    std::map<quint64, QVector<QPointF>> new_series_points;
    for (auto id : parameters.series_ids)
    {
        new_series_points[id] = QVector<QPointF>();
    }

    // Check that source target and kinds has same size
    if (parameters.source_ids.size() != parameters.target_ids.size() ||
            parameters.source_ids.size() != parameters.statistics_kinds.size())
    {
        // BAD PARAMETERS
        qCritical() << "Bad parameters in function update_dynamic_chartbox."
                    << "sources: " << parameters.source_ids.size()
                    << "targets: " << parameters.target_ids.size()
                    << "statistics kind: " << parameters.statistics_kinds.size();

        // Update the model with an empty vector so the time saves coherence in chart
        dynamic_statistics_data_->update(chartbox_id, new_series_points, time_to);
        return;
    }


    for (std::size_t i = 0; i < parameters.series_ids.size(); i++)
    {
        backend::StatisticKind statistics_kind_ = backend::string_to_statistic_kind(parameters.statistics_kinds[i]);

        eprosima::statistics_backend::Timestamp time_from_ =
                backend::Timestamp(std::chrono::milliseconds(parameters.time_from));

        // If statistics_kind is NONE, then the number of bins is 0 to retrieve all the data available
        // Otherwise the bins is 1 so only one data is updated
        uint16_t bins_ = (statistics_kind_ == backend::StatisticKind::NONE) ? 0 : 1;

        std::vector<backend::StatisticsData> new_points;

        if ((statistics_kind_ == backend::StatisticKind::NONE) || !parameters.cumulative[i])
        {
            new_points = backend_connection_.get_data(
                backend::string_to_data_kind(parameters.data_kind),
                backend::models_id_to_backend_id(parameters.source_ids[i]),
                backend::models_id_to_backend_id(parameters.target_ids[i]),
                bins_,                      // 0 when NONE , 1 otherwise
                statistics_kind_,
                time_from_,                 // New limit value
                time_to_timestamp_);        // Last time value taken in last call
        }
        else
        {
            if (backend_connection_.data_available(
                        backend::string_to_data_kind(parameters.data_kind),
                        backend::models_id_to_backend_id(parameters.source_ids[i]),
                        backend::models_id_to_backend_id(parameters.target_ids[i]),
                        time_from_,
                        time_to_timestamp_))
            {
                if (parameters.cumulative_interval[i] > 0)
                {
                    time_from_ = time_to_timestamp_ -
                            std::chrono::seconds(parameters.cumulative_interval[i]);
                }
                else
                {
                    time_from_ = initial_time_;
                }

                new_points = backend_connection_.get_data(
                    backend::string_to_data_kind(parameters.data_kind),
                    backend::models_id_to_backend_id(parameters.source_ids[i]),
                    backend::models_id_to_backend_id(parameters.target_ids[i]),
                    bins_,                      // 0 when NONE , 1 otherwise
                    statistics_kind_,
                    time_from_,
                    time_to_timestamp_);        // Last time value taken in last call
            }
        }

        // Check that get_data call has not failed
        if (new_points.empty())
        {
            qDebug() << "get_data call has not retrieved datapoints in series: " << parameters.series_ids[i];
        }
        else
        {
            for (auto point : new_points)
            {
                if (!std::isnan(point.second))
                {
                    // Add points to list of new points
                    new_series_points[parameters.series_ids[i]].push_back(QPointF(
                                std::chrono::duration_cast<std::chrono::milliseconds>(
                                    point.first.time_since_epoch()).count(),
                                point.second));
                }
            }
        }
    }

    /////
    // Update series with data AND now value
    dynamic_statistics_data_->update(chartbox_id, new_series_points, time_to);
}

void Engine::set_alias(
        const backend::EntityId& entity_id,
        const std::string& new_alias,
        const backend::EntityKind& entity_kind)
{
    backend_connection_.set_alias(entity_id, new_alias);

    if (last_dds_entity_clicked_ == entity_id)
    {
        info_model_->update_selected_entity(backend::backend_id_to_models_id(entity_id), utils::to_QString(new_alias));
    }

    // Refresh specific model
    switch (entity_kind)
    {
        case backend::EntityKind::HOST:
            update_entity(entity_id, &Engine::update_host, false);
            break;

        case backend::EntityKind::USER:
            update_entity(entity_id, &Engine::update_user, false);
            break;

        case backend::EntityKind::PROCESS:
            update_entity(entity_id, &Engine::update_process, false);
            break;

        case backend::EntityKind::DOMAIN:
            update_entity(entity_id, &Engine::update_domain, false);
            break;

        case backend::EntityKind::TOPIC:
            update_entity(entity_id, &Engine::update_topic, false);
            break;

        case backend::EntityKind::PARTICIPANT:
            update_entity(entity_id, &Engine::update_participant, false);
            break;

        case backend::EntityKind::DATAWRITER:
            update_entity(entity_id, &Engine::update_datawriter, false);
            break;

        case backend::EntityKind::DATAREADER:
            update_entity(entity_id, &Engine::update_datareader, false);
            break;

        case backend::EntityKind::LOCATOR:
            update_entity(entity_id, &Engine::update_locator, false);
            break;

        default:
            qWarning() << "Updated alias of an unknown EntityKind";
            break;
    }
}

bool Engine::update_entity(
        const backend::EntityId& entity_updated,
        bool (Engine::* update_function)(const backend::EntityId&, bool, bool),
        bool new_entity, /* true */
        bool last_clicked /* false */)
{
    bool res = false;

    // Only update the info if the updated entity is the one that is being shown
    if (last_clicked)
    {
        res = fill_entity_info_(last_dds_entity_clicked_) || res;
        res = fill_summary_(last_dds_entity_clicked_) || res;
    }

    res = (this->*update_function)(entity_updated, new_entity, last_clicked) || res;

    return res;
}

void Engine::change_inactive_visible()
{
    inactive_visible_ = !inactive_visible_;
    fill_physical_data_();
    fill_logical_data_();
    fill_dds_data_();
    refresh_engine();
}

void Engine::change_metatraffic_visible()
{
    metatraffic_visible_ = !metatraffic_visible_;
    fill_physical_data_();
    fill_logical_data_();
    fill_dds_data_();
    refresh_engine();
}

bool Engine::inactive_visible() const
{
    return inactive_visible_;
}

bool Engine::metatraffic_visible() const
{
    return metatraffic_visible_;
}

std::string Engine::get_data_kind_units(
        const QString& data_kind)
{
    return backend_connection_.get_data_kind_units(backend::string_to_data_kind(data_kind));
}

void Engine::save_csv(
        const QString& file_name,
        const QList<quint64>& chartbox_ids,
        const QList<quint64>& series_indexes,
        const QStringList& data_kinds,
        const QStringList& chartbox_names,
        const QStringList& label_names)
{
    // Check input vectors are same size
    int size = chartbox_ids.size();
    assert (series_indexes.size() == size);
    assert (data_kinds.size() == size);
    assert (chartbox_names.size() == size);
    assert (label_names.size() == size);

    // get all data
    std::vector<QVector<QPointF>> datas(size);

    for (int i = 0; i < size; ++i)
    {
        // It looks up if it belongs to dynamic or historic before getting its data
        if (historic_statistics_data_->contains_chartbox(chartbox_ids[i]))
        {
            datas[i] = historic_statistics_data_->get_data(chartbox_ids[i], series_indexes[i]);
        }
        else if (dynamic_statistics_data_->contains_chartbox(chartbox_ids[i]))
        {
            datas[i] = dynamic_statistics_data_->get_data(chartbox_ids[i], series_indexes[i]);
        }
        else
        {
            // Chartbox does not exist
            qCritical() << "Chartbox with id " << chartbox_ids[i] << " does not exist.";
            assert(false);
        }
    }

    // get units
    std::vector<std::string> data_units(size);
    for (int i = 0; i < size; ++i)
    {
        data_units[i] = get_data_kind_units(data_kinds[i]);
    }

    // call csv write
    if (io::HandlerCSV::write_series_to_csv(
                file_name,
                datas,
                data_kinds,
                chartbox_names,
                label_names,
                data_units))
    {
        qDebug() << "CSV file written successfully to file " << file_name;
    }
    else
    {
        qWarning() << "Error writing CSV file " << file_name;
    }
}

std::vector<std::string> Engine::ds_supported_transports()
{
    return backend_connection_.ds_supported_transports();
}

std::vector<std::string> Engine::get_statistic_kinds()
{
    return backend_connection_.get_statistic_kinds();
}

std::vector<std::string> Engine::get_data_kinds()
{
    return backend_connection_.get_data_kinds();
}

bool Engine::data_kind_has_target(
        const QString& data_kind)
{
    return backend_connection_.data_kind_has_target(backend::string_to_data_kind(data_kind));
}
