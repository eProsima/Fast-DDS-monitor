#include <QQmlApplicationEngine>
#include <QDateTime>
#include <QtCore/QRandomGenerator>

#include <qqmlcontext.h>

#include <include/statistics/StatisticsData.h>
#include <include/model/physical/HostModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/dds/ParticipantModelItem.h>
#include <include/model/EntityItem.h>
#include <include/model/SubListedListItem.h>
#include <include/model/SubListedListModel.h>
#include <include/backend/SyncBackendConnection.h>
#include <include/backend/Listener.h>
#include <include/Engine.h>
#include <include/model/tree/TreeModel.h>
#include <include/Controller.h>
#include <include/backend/backend_types.h>

#include <chrono>

#include <json.hpp>

using nlohmann::json;

Engine::Engine()
    : enabled_(false)
    , last_entity_clicked_(backend::ID_ALL)
    , callback_process_run_(true)
    , callback_listener_(this)
{
}

QObject* Engine::enable()
{
    // Initialize async backend
    listener_ = new backend::Listener(this);
    backend_connection_.set_listener(listener_);

    // Initialize models
    participants_model_ = new models::SubListedListModel(new models::ParticipantModelItem());
    fill_dds_data();

    physical_model_ = new models::SubListedListModel(new models::HostModelItem());
    fill_physical_data();

    logical_model_ = new models::SubListedListModel(new models::DomainModelItem());
    fill_logical_data();

    info_model_ = new models::TreeModel();
    fill_first_entity_info();

    summary_model_ = new models::TreeModel();
    fill_summary(backend::ID_ALL);

    // Creates a default structure for issue json and fills the tree model with it
    issue_model_ = new models::TreeModel();
    generate_new_issue_info();
    fill_issue();


    source_entity_id_model_ = new models::ListModel(new models::EntityItem());
    fill_available_entity_id_list(backend::EntityKind::HOST, "getDataDialogSourceEntityId");
    destination_entity_id_model_ = new models::ListModel(new models::EntityItem());
    fill_available_entity_id_list(backend::EntityKind::HOST, "getDataDialogDestinationEntityId");

    statisticsData_ = new StatisticsData();
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

    rootContext()->setContextProperty("statisticsData", statisticsData_);
    rootContext()->setContextProperty("controller", controller_);

    // qmlRegisterType<Controller>("Controller", 1, 0, "Controller");

    load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    // Connect Callback Listener
    QObject::connect(
            &callback_listener_,
            &CallbackListener::new_callback_signal,
            &callback_listener_,
            &CallbackListener::new_callback_slot);

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
    add_domain_issue(backend_connection_.get_name(domain_id));

    if (domain_id.is_valid())
    {
        update_domain_data(domain_id);
        last_entity_clicked_ = domain_id;
    }
}

bool Engine::fill_entity_info(backend::EntityId id /*ID_ALL*/)
{
    info_model_->update(backend_connection_.get_info(id));
    return true;
}


bool Engine::fill_summary(backend::EntityId id /*ID_ALL*/)
{
    summary_model_->update(backend_connection_.get_summary(id));
    return true;
}

bool Engine::fill_issue()
{
    issue_model_->update(issue_info_);
    return true;
}

void Engine::generate_new_issue_info()
{
    json info;

    info["Callbacks"] = json::array();
    info["Issues"] = json::array();
    info["Entities"] = json();
    info["Entities"]["Domains"] = json::array();
    info["Entities"]["Entities"] = 0;

    issue_info_ = info;
}

void Engine::sum_entity_number_issue(int n)
{
    issue_info_["Entities"]["Entities"] = issue_info_["Entities"]["Entities"].get<double>() + n;
    fill_issue();
}

void Engine::add_domain_issue(std::string name)
{
    issue_info_["Entities"]["Domains"].emplace_back(name);
    add_issue_callback("Monitor initialized in domain " + name, "Now");
    fill_issue();
}

bool Engine::add_issue_callback(std::string callback, std::string time)
{
    issue_info_["Callbacks"].emplace_back(callback);
    fill_issue();

    static_cast<void>(time);
    return true;
}

bool Engine::fill_first_entity_info()
{
    json info = R"({"No monitors active.":"Start a monitor in a specific domain"})"_json;
    info_model_->update(info);
    return true;
}

/// Backend API
bool Engine::fill_physical_data()
{
    return backend::SyncBackendConnection::update_physical_data(physical_model_);
}

// TODO reimplement these functions so it is not needed to call the whole fill
bool Engine::update_host_data(backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend::SyncBackendConnection::update_physical_data(physical_model_);
}
bool Engine::update_user_data(backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend::SyncBackendConnection::update_physical_data(physical_model_);
}
bool Engine::update_process_data(backend::EntityId id)
{
    static_cast<void>(id);
    physical_model_->clear();
    return backend::SyncBackendConnection::update_physical_data(physical_model_);
}

// LOGICAL PARTITION
bool Engine::fill_logical_data()
{
    return backend::SyncBackendConnection::update_logical_data(logical_model_);
}

bool Engine::update_domain_data(backend::EntityId id)
{
    static_cast<void>(id);
    logical_model_->clear();
    return backend::SyncBackendConnection::update_logical_data(logical_model_);
}

bool Engine::update_topic_data(backend::EntityId id)
{
    static_cast<void>(id);
    logical_model_->clear();
    return backend::SyncBackendConnection::update_logical_data(logical_model_);
}

// DDS PARTITION
bool Engine::fill_dds_data()
{
    return backend::SyncBackendConnection::update_dds_data(participants_model_, last_entity_clicked_);
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
    return backend::SyncBackendConnection::update_dds_data(participants_model_, id);
}

// Update the model with a new or updated entity
bool Engine::update_participant_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend::SyncBackendConnection::update_dds_data(participants_model_, last_entity_clicked_);
}

bool Engine::update_endpoint_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend::SyncBackendConnection::update_dds_data(participants_model_, last_entity_clicked_);
}

bool Engine::update_locator_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participants_model_->clear();
    return backend::SyncBackendConnection::update_dds_data(participants_model_, last_entity_clicked_);
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
        res = fill_entity_info(id) or res;
        res = fill_summary(id) or res;
        break;
    }

    return res;
}

bool Engine::fill_available_entity_id_list(backend::EntityKind entity_kind, QString entity_model_id)
{
    return on_selected_entity_kind(entity_kind, entity_model_id);
}

bool Engine::on_selected_entity_kind(backend::EntityKind entity_kind, QString entity_model_id)
{
    if (entity_model_id == "getDataDialogSourceEntityId")
    {
        source_entity_id_model_->clear();
        return backend::SyncBackendConnection::update_get_data_dialog_entity_id(source_entity_id_model_, entity_kind);
    }
    else if (entity_model_id == "getDataDialogDestinationEntityId")
    {
        destination_entity_id_model_->clear();
        return backend::SyncBackendConnection::update_get_data_dialog_entity_id(destination_entity_id_model_, entity_kind);
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

    std::vector<backend::StatisticsData> statistic_data = backend::SyncBackendConnection::get_data(
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
    std::cout << "REFRESH" << std::endl;
    // TODO this should be changed from erase all models and re draw them
    process_callback_queue();
}

void Engine::process_callback_queue()
{
    // It iterates while run_ is activate and the queue has elements
    while (callback_process_run_.load() && !callback_queue_.empty())
    {
        process_callback_();
    }
}

bool Engine::are_callbacks_to_process_()
{
    QMutexLocker ml(&callback_queue_mutex_);
    return callback_queue_.empty();
}

bool Engine::add_callback(backend::Callback callback)
{
    QMutexLocker ml(&callback_queue_mutex_);
    callback_queue_.append(callback);
    // callback_process_cv_.wakeOne();

    // Add callback to issue model
    add_issue_callback("New entity " + backend_connection_.get_name(callback.new_entity) + " discovered", "Now");

    // Emit signal to specify there are new data
    callback_listener_.new_callback();

    return true;
}

bool Engine::process_callback_()
{
    backend::Callback first_callback;

    {
        QMutexLocker ml(&callback_queue_mutex_);
        first_callback = callback_queue_.front();
        callback_queue_.pop_front();
    }

    std::cout << "Callback: " << first_callback.new_entity << std::endl;

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
        return fill_physical_data();

    case backend::EntityKind::DOMAIN:
    case backend::EntityKind::TOPIC:
        return fill_logical_data();

    default:
        // DDS Model entities
        // TODO this is only needed when new entity is related with the last_clicked entity
        return fill_dds_data();
    }

    return res;
}


