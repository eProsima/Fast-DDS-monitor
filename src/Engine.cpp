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

#include <chrono>

#include <json.hpp>

using nlohmann::json;

Engine::Engine()
    : enabled_(false)
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
    fill_physical_data(physicalModel_);

    logicalModel_ = new models::SubListedListModel(new models::DomainModelItem());
    fill_logical_data(logicalModel_);

    infoModel_ = new models::TreeModel();
    fill_dds_info(ALL_ID_BACKEND);

    summaryModel_ = new models::TreeModel();
    fill_summary(ALL_ID_BACKEND);

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
    backend_connection_.init_monitor(domain);
}

void Engine::init_monitor(QString locators)
{
    backend_connection_.init_monitor(locators);
}

bool Engine::fill_dds_info(backend::EntityId id /*ALL_ID_BACKEND*/)
{
    // TODO implement update
    infoModel_->update(backend_connection_.get_info(id));
    return false;
}


bool Engine::fill_summary(backend::EntityId id /*ALL_ID_BACKEND*/)
{
    // TODO implement update
    summaryModel_->update(backend_connection_.get_summary(id));
    return false;
}


/// Backend API
bool Engine::fill_physical_data(models::ListModel* physical_model)
{
    return backend::SyncBackendConnection::update_physical_data(physical_model);
}

// TODO reimplement these functions so it is not needed to call the whole fill
bool Engine::update_host_data(models::ListModel* physical_model, backend::EntityId id)
{
    static_cast<void>(id);
    return backend::SyncBackendConnection::update_physical_data(physical_model);
}
bool Engine::update_user_data(models::ListModel* physical_model, backend::EntityId id)
{
    static_cast<void>(id);
    return backend::SyncBackendConnection::update_physical_data(physical_model);
}
bool Engine::update_process_data(models::ListModel* physical_model, backend::EntityId id)
{
    static_cast<void>(id);
    return backend::SyncBackendConnection::update_physical_data(physical_model);
}

// LOGICAL PARTITION
bool Engine::fill_logical_data(models::ListModel* logical_model)
{
    return backend::SyncBackendConnection::update_logical_data(logical_model);
}

bool Engine::update_domain_data(models::ListModel* logical_model, backend::EntityId id)
{
    static_cast<void>(id);
    return backend::SyncBackendConnection::update_logical_data(logical_model);
}

bool Engine::update_topic_data(models::ListModel* logical_model, backend::EntityId id)
{
    static_cast<void>(id);
    return backend::SyncBackendConnection::update_logical_data(logical_model);
}

bool Engine::fill_dds_data(
        backend::EntityId id /*ALL_ID_BACKEND*/)
{
    participantsModel_->clear();
    return backend::SyncBackendConnection::update_dds_data(participantsModel_, id);
}

// Update the model with a new or updated entity
bool Engine::update_participant_data(models::ListModel* dds_model, backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    return backend::SyncBackendConnection::update_dds_data(dds_model, ALL_ID_BACKEND);
}

bool Engine::update_endpoint_data(models::ListModel* dds_model, backend::EntityId id)
{
    // TODO update only the entity that has changed
    static_cast<void>(id);
    return backend::SyncBackendConnection::update_dds_data(dds_model, ALL_ID_BACKEND);
}

bool Engine::on_dds_entity_clicked(backend::EntityId id)
{
    bool res = fill_dds_info(id);
    return fill_summary(id) or res;
}

bool Engine::on_entity_clicked(backend::EntityId id)
{
    bool res = fill_dds_data(id);
    res = fill_dds_info(id) or res;
    return fill_summary(id) or res;
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
}
