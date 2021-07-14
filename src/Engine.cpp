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
#include <fastdds_monitor/statistics/dynamic/DynamicStatisticsData.h>
#include <fastdds_monitor/statistics/historic/HistoricStatisticsData.h>

using EntityInfo = backend::EntityInfo;

Engine::Engine()
    : enabled_(false)
    , last_entity_clicked_(backend::ID_ALL)
    , last_entity_clicked_kind_(backend::EntityKind::INVALID)
    , last_physical_logical_entity_clicked_(backend::ID_ALL)
    , last_physical_logical_entity_clicked_kind_(backend::EntityKind::INVALID)
    , inactive_visible_(true)
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
        QString locators)
{
    std::lock_guard<std::recursive_mutex> lock(initializing_monitor_);

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

    if (domain_id.is_valid())
    {
        add_status_domain_(backend_connection_.get_name(domain_id), utils::now());

        // WARNING
        // When a new Domain is created its entities begin to appear in callbacks
        // If the dds model is updated with this model, the callbacks will refer to new entities but they
        // will be already in the model as the model will call backend to update it completly
        // This, entity_clicked must be called but do not update dds model (but reset it)
        entity_clicked(domain_id, backend::EntityKind::DOMAIN, false);

        update_entity(domain_id, &Engine::update_domain);
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
    physical_model_->clear();
    return backend_connection_.update_physical_model(physical_model_, inactive_visible());
}

bool Engine::update_host(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_host(physical_model_, id, new_entity, inactive_visible());
}

bool Engine::update_user(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_user(physical_model_, id, new_entity, inactive_visible());
}

bool Engine::update_process(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_process(physical_model_, id, new_entity, inactive_visible());
}

// LOGICAL PARTITION
bool Engine::fill_logical_data_()
{
    logical_model_->clear();
    return backend_connection_.update_logical_model(logical_model_, inactive_visible());
}

// TODO reimplement these functions so it is not needed to call the whole fill
bool Engine::update_domain(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_domain(logical_model_, id, new_entity, inactive_visible());
}

bool Engine::update_topic(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_topic(logical_model_, id, new_entity, inactive_visible());
}

// DDS PARTITION
bool Engine::fill_dds_data_()
{
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_physical_logical_entity_clicked_,
                   inactive_visible());
}

void Engine::reset_dds_data()
{
    participants_model_->clear();
}

bool Engine::update_dds_data(
        const backend::EntityId& id /*ID_ALL*/)
{
    return backend_connection_.update_dds_model(participants_model_, id, inactive_visible());
}

// Update the model with a new or updated entity
bool Engine::update_participant(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_participant(
        participants_model_,
        id,
        new_entity,
        last_physical_logical_entity_clicked_,
        inactive_visible());
}

bool Engine::update_datawriter(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_datawriter(
        participants_model_,
        id,
        new_entity,
        inactive_visible());
}

bool Engine::update_datareader(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_datareader(
        participants_model_,
        id,
        new_entity,
        inactive_visible());
}

bool Engine::update_locator(
        const backend::EntityId& id,
        bool new_entity /* true */)
{
    return backend_connection_.update_locator(
        participants_model_,
        id,
        new_entity,
        inactive_visible());
}

bool Engine::entity_clicked(
        backend::EntityId id,
        backend::EntityKind kind,
        bool update_dds /* = true */,
        bool reset_dds /* = true */)
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
        // Reset dds model and update if needed
        if (reset_dds)
        {
            reset_dds_data();
        }
        if (update_dds)
        {
            res = update_dds_data(id) || res;
        }

        last_physical_logical_entity_clicked_ = id;
        last_physical_logical_entity_clicked_kind_ = kind;
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
        return backend_connection_.update_get_data_dialog_entity_id(
            source_entity_id_model_,
            entity_kind,
            inactive_visible());
    }
    else if (entity_model_id == "getDataDialogDestinationEntityId")
    {
        destination_entity_id_model_->clear();
        return backend_connection_.update_get_data_dialog_entity_id(
            destination_entity_id_model_,
            entity_kind,
            inactive_visible());
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
        if (!std::isnan(data.second))
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

    switch (callback.entity_kind)
    {
        case backend::EntityKind::HOST:
            return update_entity(callback.entity_id, &Engine::update_host, !callback.is_update);

        case backend::EntityKind::USER:
            return update_entity(callback.entity_id, &Engine::update_user, !callback.is_update);

        case backend::EntityKind::PROCESS:
            return update_entity(callback.entity_id, &Engine::update_process, !callback.is_update);

        case backend::EntityKind::DOMAIN:
            return update_entity(callback.entity_id, &Engine::update_domain, !callback.is_update);

        case backend::EntityKind::TOPIC:
            return update_entity(callback.entity_id, &Engine::update_topic, !callback.is_update);

        case backend::EntityKind::PARTICIPANT:
            return update_entity(callback.entity_id, &Engine::update_participant, !callback.is_update);

        case backend::EntityKind::DATAWRITER:
            return update_entity(callback.entity_id, &Engine::update_datawriter, !callback.is_update);

        case backend::EntityKind::DATAREADER:
            return update_entity(callback.entity_id, &Engine::update_datareader, !callback.is_update);

        case backend::EntityKind::LOCATOR:
            return update_entity(callback.entity_id, &Engine::update_locator, !callback.is_update);

        default:
            qWarning() << "Update callback of an Entity with unknown EntityKind";
            return false;
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

    eprosima::statistics_backend::Timestamp time_from_ =
            backend::Timestamp(std::chrono::milliseconds(parameters.time_from)); // This value is reused for every series

    for (std::size_t i = 0; i < parameters.series_ids.size(); i++)
    {
        backend::StatisticKind statistics_kind_ = backend::string_to_statistic_kind(parameters.statistics_kinds[i]);
        // If statistics_kind is NONE, then the number of bins is 0 to retrieve all the data available
        // Otherwise the bins is 1 so only one data is updated
        uint16_t bins_ = (statistics_kind_ == backend::StatisticKind::NONE) ? 0 : 1;

        std::vector<backend::StatisticsData> new_points = backend_connection_.get_data(
            backend::string_to_data_kind(parameters.data_kind),
            backend::models_id_to_backend_id(parameters.source_ids[i]),
            backend::models_id_to_backend_id(parameters.target_ids[i]),
            bins_,                      // 0 when NONE , 1 otherwise
            statistics_kind_,
            time_from_, // New limit value
            time_to_timestamp_);                 // Last time value taken in last call

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

    // Refresh specific model
    // TODO when callbacks on info update are implemented this could be erased
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
        bool (Engine::* update_function)(const backend::EntityId&, bool),
        bool new_entity /* true */)
{
    bool res = false;

    // Only update the info if the updated entity is the one that is being shown
    if (last_entity_clicked_ == entity_updated)
    {
        res = fill_entity_info_(last_entity_clicked_) || res;
        res = fill_summary_(last_entity_clicked_) || res;
    }

    res = (this->*update_function)(entity_updated, new_entity) || res;

    return res;
}

void Engine::change_inactive_visible()
{
    inactive_visible_ = !inactive_visible_;
    fill_physical_data_();
    fill_logical_data_();
    fill_dds_data_();
}

bool Engine::inactive_visible() const
{
    return inactive_visible_;
}

QString Engine::get_data_kind_units(const QString& data_kind)
{
    return utils::to_QString(backend_connection_.get_data_kind_units(backend::string_to_data_kind(data_kind)));
}
