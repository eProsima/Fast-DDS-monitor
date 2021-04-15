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

#include <include/Controller.h>
#include <include/Engine.h>
#include <include/backend/Listener.h>
#include <include/backend/SyncBackendConnection.h>
#include <include/backend/backend_types.h>
#include <include/model/EntityItem.h>
#include <include/model/SubListedListItem.h>
#include <include/model/SubListedListModel.h>
#include <include/model/dds/ParticipantModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/physical/HostModelItem.h>
#include <include/model/tree/TreeModel.h>
#include <include/statistics/StatisticsData.h>

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


    source_entity_id_model_ = new models::ListModel(new models::EntityItem());
    fill_available_entity_id_list_(backend::EntityKind::HOST, "getDataDialogSourceEntityId");
    destination_entity_id_model_ = new models::ListModel(new models::EntityItem());
    fill_available_entity_id_list_(backend::EntityKind::HOST, "getDataDialogDestinationEntityId");

    statistics_data_ = new StatisticsData();
    controller_ = new Controller(this);

    // Initialized qml
    rootContext()->setContextProperty("participantModel", participants_model_);
    rootContext()->setContextProperty("hostModel", physical_model_);
    rootContext()->setContextProperty("domainModel",  logical_model_);

    rootContext()->setContextProperty("qosModel", info_model_);
    rootContext()->setContextProperty("summaryModel", summary_model_);
    rootContext()->setContextProperty("issueModel", issue_model_);

    rootContext()->setContextProperty("entityModelFirst", source_entity_id_model_);
    rootContext()->setContextProperty("entityModelSecond", destination_entity_id_model_);

    rootContext()->setContextProperty("statisticsData", statistics_data_);
    rootContext()->setContextProperty("controller", controller_);

    // qmlRegisterType<Controller>("Controller", 1, 0, "Controller");
    load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    // Connect Callback Listener
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
    if  (enabled_){
        if (listener_){
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


void Engine::init_monitor(int domain)
{
    shared_init_monitor_(backend_connection_.init_monitor(domain));
}

void Engine::init_monitor(QString locators)
{
    shared_init_monitor_(backend_connection_.init_monitor(locators));
}

void Engine::shared_init_monitor_(backend::EntityId domain_id)
{
    add_issue_domain_(backend_connection_.get_name(domain_id), utils::now());

    entity_clicked(domain_id, backend::EntityKind::DOMAIN);

    if (domain_id.is_valid())
    {
        update_domain_data(domain_id);
        last_entity_clicked_ = domain_id;
    }
}

bool Engine::fill_entity_info_(backend::EntityId id /*ID_ALL*/)
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


bool Engine::fill_summary_(backend::EntityId id /*ID_ALL*/)
{
    summary_model_->update(backend_connection_.get_summary(id));
    return true;
}

bool Engine::fill_issue_()
{
    issue_model_->update(issue_info_);
    return true;
}

void Engine::generate_new_issue_info_()
{
    EntityInfo info;

    info["Callbacks"] = EntityInfo();
    info["Issues"] = EntityInfo();
    info["Entities"] = EntityInfo();
    info["Entities"]["Domains"] = EntityInfo();
    info["Entities"]["Entities"] = 0;

    issue_info_ = info;
}

void Engine::sum_entity_number_issue(int n)
{
    issue_info_["Entities"]["Entities"] = issue_info_["Entities"]["Entities"].get<double>() + n;
    fill_issue_();
}

bool Engine::add_issue_domain_(std::string name, std::string time)
{
    issue_info_["Entities"]["Domains"][time] = name;
    add_issue_callback_("Monitor initialized in domain " + name, time);
    fill_issue_();

    return true;
}

bool Engine::add_issue_callback_(std::string callback, std::string time)
{
    issue_info_["Callbacks"][time] = callback;
    fill_issue_();

    return true;
}

void Engine::clear_callback_issue_()
{
    issue_info_["Callbacks"] = EntityInfo();
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
bool Engine::update_host_data(backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend_connection_.update_physical_model(physical_model_);
}
bool Engine::update_user_data(backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend_connection_.update_physical_model(physical_model_);
}
bool Engine::update_process_data(backend::EntityId id)
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

bool Engine::update_domain_data(backend::EntityId id)
{
    static_cast<void>(id);
    logical_model_->clear();
    return backend_connection_.update_logical_model(logical_model_);
}

bool Engine::update_topic_data(backend::EntityId id)
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
bool Engine::update_participant_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_entity_clicked_);
}

bool Engine::update_endpoint_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_entity_clicked_);
}

bool Engine::update_locator_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend_connection_.update_dds_model(participants_model_, last_entity_clicked_);
}

bool Engine::entity_clicked(backend::EntityId id, backend::EntityKind kind)
{
    bool res = false;

    switch (kind)
    {
    case backend::EntityKind::HOST:
    case backend::EntityKind::USER:
    case backend::EntityKind::PROCESS:
    case backend::EntityKind::DOMAIN:
    case backend::EntityKind::TOPIC:
    case backend::EntityKind::INVALID: // all case
        // All Entities in Physical and Logical Models
        // Those entities affect over the participant view

        // Set as clicked entity to update whit new dds entities
        last_entity_clicked_ = id;
        last_entity_clicked_kind_ = kind;

        res = update_reset_dds_data(id) or res;

        // Without break as it needs to do as well the info update
        [[fallthrough]];
    default:
        // DDS Entities
        res = fill_entity_info_(id) or res;
        res = fill_summary_(id) or res;
        break;
    }

    return res;
}

bool Engine::fill_available_entity_id_list_(backend::EntityKind entity_kind, QString entity_model_id)
{
    return on_selected_entity_kind(entity_kind, entity_model_id);
}

bool Engine::on_selected_entity_kind(backend::EntityKind entity_kind, QString entity_model_id)
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
            start_time_default ? backend::Timestamp() : backend::Timestamp(std::chrono::milliseconds(start_time));
    backend::Timestamp time_to =
            end_time_default ? std::chrono::system_clock::now() : backend::Timestamp(std::chrono::milliseconds(end_time));

    std::vector<backend::StatisticsData> statistic_data = backend_connection_.get_data(
                data_kind,
                source_entity_id,
                target_entity_id,
                bins,
                time_from,
                time_to,
                statistic_kind);

    QVector<QPointF> points;
    points.reserve(statistic_data.size());
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
                    statistic_data.front().first.time_since_epoch()).count());
    QDateTime endDate;
    endDate.setMSecsSinceEpoch(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    statistic_data.back().first.time_since_epoch()).count());

    statistics_data_->setAxisYMax(max_value);
    statistics_data_->setAxisYMin(min_value);
    statistics_data_->setAxisXMax(endDate.toMSecsSinceEpoch());
    statistics_data_->setAxisXMin(startDate.toMSecsSinceEpoch());

    return true;
}

void Engine::refresh_engine()
{
    qDebug() << "REFRESH";
    // TODO this should be changed from erase all models and re draw them
    clear_callback_issue_();
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

bool Engine::add_callback(backend::Callback callback)
{
    std::lock_guard<std::recursive_mutex> ml(callback_queue_mutex_);
    callback_queue_.append(callback);

    // Add callback to issue model
    add_issue_callback_("New entity " + backend_connection_.get_name(callback.new_entity) + " discovered", utils::now());

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

    qDebug() << "Processing callback: " << backend::id_to_QString(first_callback.new_entity);

    return read_callback_(first_callback);
}

bool Engine::read_callback_(backend::Callback callback)
{
    // Add one to the number of discovered entities
    sum_entity_number_issue(1);

    bool res = false;

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

    return res;
}

void Engine::new_callback_slot()
{
    process_callback_queue();
}

