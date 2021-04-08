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
{
}

QObject* Engine::enable()
{
    // Initialize async backend
    listener_ = new backend::Listener();
    backend_connection_.set_listener(listener_);

    // Initialize models
    participantsModel_ = new models::SubListedListModel(new models::ParticipantModelItem());
    fill_dds_data();

    physicalModel_ = new models::SubListedListModel(new models::HostModelItem());
    fill_physical_data();

    logicalModel_ = new models::SubListedListModel(new models::DomainModelItem());
    fill_logical_data();

    infoModel_ = new models::TreeModel();
    fill_entity_info(backend::ID_ALL);

    summaryModel_ = new models::TreeModel();
    fill_summary(backend::ID_ALL);

    entityIdModelFirst_ = new models::ListModel(new models::EntityItem());
    fillAvailableEntityIdList(backend::EntityKind::HOST, "getDataDialogEntityIdModelFirst");
    entityIdModelSecond_ = new models::ListModel(new models::EntityItem());
    fillAvailableEntityIdList(backend::EntityKind::HOST, "getDataDialogEntityIdModelSecond");

    statisticsData_ = new StatisticsData();

    // Initialized qml
    rootContext()->setContextProperty("participantModel", participantsModel_);
    rootContext()->setContextProperty("hostModel", physicalModel_);
    rootContext()->setContextProperty("domainModel",  logicalModel_);

    rootContext()->setContextProperty("qosModel", infoModel_);
    rootContext()->setContextProperty("summaryModel", summaryModel_);

    rootContext()->setContextProperty("entityModelFirst", entityIdModelFirst_);
    rootContext()->setContextProperty("entityModelSecond", entityIdModelSecond_);

    rootContext()->setContextProperty("statisticsData", statisticsData_);

    qmlRegisterType<Controller>("Controller", 1, 0, "Controller");

    load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    // Connect Callback Listener
    QObject::connect(&call_listener, &CallbackListener::new_callback_signal,
                         &call_listener, &CallbackListener::new_callback_slot);

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

        if (participantsModel_)
        {
            delete participantsModel_;
        }

        if (physicalModel_)
        {
            delete physicalModel_;
        }

        if (logicalModel_)
        {
            delete logicalModel_;
        }

        if (infoModel_)
        {
            delete infoModel_;
        }

        if (summaryModel_)
        {
            delete summaryModel_;
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
    if (domain_id.is_valid())
    {
        update_domain_data(domain_id);
        last_entity_clicked_ = domain_id;
    }
}

bool Engine::fill_entity_info(backend::EntityId id /*ID_ALL*/)
{
    infoModel_->update(backend_connection_.get_info(id));
    return true;
}


bool Engine::fill_summary(backend::EntityId id /*ID_ALL*/)
{
    summaryModel_->update(backend_connection_.get_summary(id));
    return true;
}


/// Backend API
bool Engine::fill_physical_data()
{
    return backend::SyncBackendConnection::update_physical_data(physicalModel_);
}

// TODO reimplement these functions so it is not needed to call the whole fill
bool Engine::update_host_data(backend::EntityId id)
{
    static_cast<void>(id);
    physicalModel_->clear();
    return backend::SyncBackendConnection::update_physical_data(physicalModel_);
}
bool Engine::update_user_data(backend::EntityId id)
{
    static_cast<void>(id);
    physicalModel_->clear();
    return backend::SyncBackendConnection::update_physical_data(physicalModel_);
}
bool Engine::update_process_data(backend::EntityId id)
{
    static_cast<void>(id);
    physicalModel_->clear();
    return backend::SyncBackendConnection::update_physical_data(physicalModel_);
}

// LOGICAL PARTITION
bool Engine::fill_logical_data()
{
    return backend::SyncBackendConnection::update_logical_data(logicalModel_);
}

bool Engine::update_domain_data(backend::EntityId id)
{
    static_cast<void>(id);
    logicalModel_->clear();
    return backend::SyncBackendConnection::update_logical_data(logicalModel_);
}

bool Engine::update_topic_data(backend::EntityId id)
{
    static_cast<void>(id);
    logicalModel_->clear();
    return backend::SyncBackendConnection::update_logical_data(logicalModel_);
}

// DDS PARTITION
bool Engine::fill_dds_data()
{
    return backend::SyncBackendConnection::update_dds_data(participantsModel_, last_entity_clicked_);
}

bool Engine::update_reset_dds_data(
        backend::EntityId id /*ID_ALL*/)
{
    participantsModel_->clear();
    return update_dds_data(id);
}

bool Engine::update_dds_data(
        backend::EntityId id /*ID_ALL*/)
{
    return backend::SyncBackendConnection::update_dds_data(participantsModel_, id);
}

// Update the model with a new or updated entity
bool Engine::update_participant_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participantsModel_->clear();
    return backend::SyncBackendConnection::update_dds_data(participantsModel_, last_entity_clicked_);
}

bool Engine::update_endpoint_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participantsModel_->clear();
    return backend::SyncBackendConnection::update_dds_data(participantsModel_, last_entity_clicked_);
}

bool Engine::update_locator_data(backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    participantsModel_->clear();
    return backend::SyncBackendConnection::update_dds_data(participantsModel_, last_entity_clicked_);
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

bool Engine::fillAvailableEntityIdList(backend::EntityKind entityKind, QString entityModelId)
{
    return onSelectedEntityKind(entityKind, entityModelId);
}

bool Engine::onSelectedEntityKind(backend::EntityKind entityKind, QString entityModelId)
{
    if (entityModelId == "getDataDialogEntityIdModelFirst")
    {
        entityIdModelFirst_->clear();
        return backend::SyncBackendConnection::updateGetDataDialogEntityId(entityIdModelFirst_, entityKind);
    }
    else if (entityModelId == "getDataDialogEntityIdModelSecond")
    {
        entityIdModelSecond_->clear();
        return backend::SyncBackendConnection::updateGetDataDialogEntityId(entityIdModelSecond_, entityKind);
    }
    else
    {
        return false;
    }
}

bool Engine::onAddStatisticsDataSeries(
        backend::DataKind dataKind,
        backend::EntityId sourceEntityId,
        backend::EntityId targetEntityId,
        quint16 bins,
        quint64 startTime,
        bool startTimeDefault,
        quint64 endTime,
        bool endTimeDefault,
        backend::StatisticKind statisticKind)
{
    backend::Timestamp timeFrom =
            startTimeDefault ? backend::Timestamp() : backend::Timestamp(std::chrono::milliseconds(startTime));
    backend::Timestamp timeTo =
            endTimeDefault ? std::chrono::system_clock::now() : backend::Timestamp(std::chrono::milliseconds(endTime));

    std::vector<backend::StatisticsData> statisticData = backend::SyncBackendConnection::get_data(
                dataKind,
                sourceEntityId,
                targetEntityId,
                bins,
                timeFrom,
                timeTo,
                statisticKind);

    QVector<QPointF> points;
    points.reserve(statisticData.size());
    qreal maxValue = 0;
    qreal minValue = 0;

    for (backend::StatisticsData data : statisticData)
    {
        points.append(QPointF(
                    std::chrono::duration_cast<std::chrono::milliseconds>(data.first.time_since_epoch()).count(),
                    data.second));
        maxValue = (data.second > maxValue) ? data.second : maxValue;
        minValue = (data.second < minValue) ? data.second : maxValue;
    }

    // Remove previous data
    statisticsData_->clear();
    statisticsData_->appendData(points);

    QDateTime startDate;
    startDate.setMSecsSinceEpoch(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    statisticData.front().first.time_since_epoch()).count());
    QDateTime endDate;
    endDate.setMSecsSinceEpoch(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    statisticData.back().first.time_since_epoch()).count());

    statisticsData_->setAxisYMax(maxValue);
    statisticsData_->setAxisYMin(minValue);
    statisticsData_->setAxisXMax(endDate.toMSecsSinceEpoch());
    statisticsData_->setAxisXMin(startDate.toMSecsSinceEpoch());

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
    callback_process_cv_.wakeOne();

    // Emit signal to specify there are new data
    call_listener.new_callback();

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


