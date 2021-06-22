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

#include <chrono>

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
#include <fastdds_monitor/model/dds/ParticipantModelItem.h>
#include <fastdds_monitor/model/logical/DomainModelItem.h>
#include <fastdds_monitor/model/physical/HostModelItem.h>
#include <fastdds_monitor/model/statistics/EntityItem.h>
#include <fastdds_monitor/model/SubListedListItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/model/tree/TreeModel.h>
#include <fastdds_monitor/statistics/StatisticsData.h>

using EntityInfo = backend::EntityInfo;

Engine::Engine()
    : enabled_(false)
    , last_entity_clicked_(backend::ID_ALL)
    , last_entity_clicked_kind_(backend::EntityKind::INVALID)
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

    info_model_ = new models::TreeModel();
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

    statistics_data_ = new StatisticsData();
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

    rootContext()->setContextProperty("statisticsData", statistics_data_);
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
        if (listener_)
        {
            backend_connection_.unset_listener();
            delete listener_;
        }

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

        if (info_model_)
        {
            delete info_model_;
        }

        if (summary_model_)
        {
            delete summary_model_;
        }
    }
}

void Engine::init_monitor(
        int domain)
{
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
        QString locators)
{
    backend::EntityId domain_id = backend_connection_.init_monitor(locators);

    if (domain_id.is_valid())
    {
        shared_init_monitor_(domain_id);
    }
    else
    {
        process_error(
            "Error trying to initialize monitor in Discovery Server with locators: " + utils::to_string(locators),
            ErrorType::INIT_MONITOR);
    }
}

void Engine::shared_init_monitor_(
        backend::EntityId domain_id)
{
    // if init_monitor fail it does not arrive here

    add_status_domain_(backend_connection_.get_name(domain_id), utils::now());

    entity_clicked(domain_id, backend::EntityKind::DOMAIN);

    if (domain_id.is_valid())
    {
        update_domain_data(domain_id);
        last_entity_clicked_ = domain_id;
    }
}

bool Engine::fill_entity_info_(
        backend::EntityId id /*ID_ALL*/)
{
    if (id == backend::ID_ALL)
    {
        EntityInfo default_info;
        default_info["No entity"] = "Double click over any entity to see its values";
        info_model_->update(default_info);
    }
    else
    {
        info_model_->update(backend_connection_.get_info(id));
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
    return backend_connection_.update_physical_model(physical_model_);
}

// TODO reimplement these functions so it is not needed to call the whole fill
bool Engine::update_host_data(
        backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend_connection_.update_physical_model(physical_model_);
}

bool Engine::update_user_data(
        backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend_connection_.update_physical_model(physical_model_);
}

bool Engine::update_process_data(
        backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend_connection_.update_physical_model(physical_model_);
}

// LOGICAL PARTITION
bool Engine::fill_logical_data_()
{
    return backend_connection_.update_logical_model(logical_model_);
}

bool Engine::update_domain_data(
        backend::EntityId id)
{
    static_cast<void>(id);
    logical_model_->clear();
    return backend_connection_.update_logical_model(logical_model_);
}

bool Engine::update_topic_data(
        backend::EntityId id)
{
    static_cast<void>(id);
    logical_model_->clear();
    return backend_connection_.update_logical_model(logical_model_);
}

// DDS PARTITION
bool Engine::fill_dds_data_()
{
    return backend_connection_.update_dds_model(participants_model_, last_entity_clicked_);
}

bool Engine::update_reset_dds_data(
        backend::EntityId id /*ID_ALL*/)
{
    participants_model_->clear();
    return update_dds_data(id);
}

bool Engine::update_dds_data(
        backend::EntityId id /*ID_ALL*/)
{
    return backend_connection_.update_dds_model(participants_model_, id);
}

// Update the model with a new or updated entity
bool Engine::update_participant_data(
        backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_entity_clicked_);
}

bool Engine::update_endpoint_data(
        backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_entity_clicked_);
}

bool Engine::update_locator_data(
        backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_entity_clicked_);
}

bool Engine::entity_clicked(
        backend::EntityId id,
        backend::EntityKind kind)
{
    bool res = false;

    // Set as clicked entity
    last_entity_clicked_ = id;
    last_entity_clicked_kind_ = kind;

    // All Entities in Physical and Logical Models affect over the participant view
    if ((kind == backend::EntityKind::HOST) ||
            (kind == backend::EntityKind::USER) ||
            (kind == backend::EntityKind::PROCESS) ||
            (kind == backend::EntityKind::DOMAIN) ||
            (kind == backend::EntityKind::TOPIC) ||
            (kind == backend::EntityKind::INVALID))
    {
        // update whit related dds entities
        res = update_reset_dds_data(id) || res;
    }

    // All entities including DDS
    res = fill_entity_info_(id) || res;
    res = fill_summary_(id) || res;

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
        return backend_connection_.update_get_data_dialog_entity_id(source_entity_id_model_, entity_kind);
    }
    else if (entity_model_id == "getDataDialogDestinationEntityId")
    {
        destination_entity_id_model_->clear();
        return backend_connection_.update_get_data_dialog_entity_id(destination_entity_id_model_, entity_kind);
    }
    else
    {
        return false;
    }
}

bool Engine::on_add_statistics_data_series(
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
    qreal max_value = 0;
    qreal min_value = 0;

    for (backend::StatisticsData data : statistic_data)
    {
        points.append(QPointF(
                    std::chrono::duration_cast<std::chrono::milliseconds>(data.first.time_since_epoch()).count(),
                    data.second));
        max_value = (data.second > max_value) ? data.second : max_value;
        min_value = (data.second < min_value) ? data.second : max_value;
    }

    // Remove previous data
    statistics_data_->clear();
    statistics_data_->appendData(points);

    QDateTime startDate;
    startDate.setMSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            time_from.time_since_epoch()).count());
    QDateTime endDate;
    endDate.setMSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            time_to.time_since_epoch()).count());

    statistics_data_->setAxisYMax(max_value);
    statistics_data_->setAxisYMin(min_value);
    statistics_data_->setAxisXMax(endDate.toMSecsSinceEpoch());
    statistics_data_->setAxisXMin(startDate.toMSecsSinceEpoch());

    return true;
}

void Engine::refresh_engine()
{
    // TODO this should be changed from erase all models and re draw them
    clear_callback_log_();
    clear_issue_info_();
    entity_clicked(backend::ID_ALL, backend::EntityKind::INVALID);
    process_callback_queue();
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

    qDebug() << "Processing callback: " << backend::backend_id_to_models_id(first_callback.new_entity);

    return read_callback_(first_callback);
}

bool Engine::read_callback_(
        backend::Callback callback)
{
    // // Add callback to log model
    add_log_callback_("New entity " + backend_connection_.get_name(callback.new_entity) + " discovered",
            utils::now());

    // Add one to the number of discovered entities
    sum_entity_number_issue(1);

    switch (callback.new_entity_kind)
    {
        case backend::EntityKind::HOST:
        case backend::EntityKind::USER:
        case backend::EntityKind::PROCESS:
            return fill_physical_data_();

        case backend::EntityKind::DOMAIN:
        case backend::EntityKind::TOPIC:
            return fill_logical_data_();

        default:
            // DDS Model entities
            // TODO this is only needed when new entity is related with the last_clicked entity
            return fill_dds_data_();
    }
}

void Engine::refresh_summary()
{
    fill_summary_(last_entity_clicked_);
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
        backend::DataKind data_kind,
        quint64 last_x,
        quint64 refresh_size,
        std::vector<backend::EntityId> source_ids,
        std::vector<backend::EntityId> target_ids,
        std::vector<backend::StatisticKind> statistics_kinds)
{
    std::vector<QPointF> new_series_points(source_ids.size());

    // Check that source target and kinds has same size
    if (source_ids.size() != target_ids.size() ||
        source_ids.size() != statistics_kinds.size())
    {
        // BAD PARAMENTERS
        qCritical() << "Bad parameters in function update_dynamic_chartbox."
                << "sources: " << source_ids.size()
                << "targets: " << target_ids.size()
                << "statistics kind: " << statistics_kinds.size();

        // Update the model with an empty vector so the time saves coherence in chart
        dynamic_data_->update(chartbox_id, new_series_points);
        return;
    }

    backend::Timestamp time_to = backend::Timestamp(std::chrono::milliseconds(last_x));
    backend::Timestamp time_from = backend::Timestamp(std::chrono::milliseconds(last_x + refresh_size));

    for (std::size_t i = 0; i < source_ids.size(); i++)
    {
        std::vector<backend::StatisticsData> new_point = backend_connection_.get_data(
            data_kind,
            source_ids[i],
            target_ids[i],
            1,                      // Only ask for one data
            statistics_kinds[i],
            time_to,                 // Last time value taken in last call
            time_from); // New limit value

        // Check that get_data call has not failed
        if (new_point.size() != 1)
        {
            qInfo() << "get_data call has failed in series: " << i;

            new_series_points[i] = QPointF(
                    std::chrono::duration_cast<std::chrono::milliseconds>(new_point[0].first.time_since_epoch()).count(),
                    std::numeric_limits<double>::quiet_NaN());
        }
        else
        {
            // Add point to list of new points
            new_series_points[i] = QPointF(
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        new_point[0].first.time_since_epoch()).count(),
                    new_point[0].second);
        }
    }

    // Update Model with series
    dynamic_data_->update(chartbox_id, new_series_points);
}
