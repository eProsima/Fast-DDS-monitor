#include <QQmlApplicationEngine>
#include <qqmlcontext.h>

#include <include/model/physical/HostModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/dds/ParticipantModelItem.h>

#include <include/model/SubListedListItem.h>
#include <include/model/SubListedListModel.h>

#include <include/backend/SyncBackendConnection.h>
#include <include/Engine.h>

#include <include/model/tree/TreeModel.h>

#include <include/Controller.h>

#include <json.hpp>

using nlohmann::json;

Engine::Engine()
{
    participantsModel = new models::SubListedListModel(new models::ParticipantModelItem());
    fill_dds_data(participantsModel);

    physicalModel = new models::SubListedListModel(new models::HostModelItem());
    fill_physical_data(physicalModel);

    logicalModel = new models::SubListedListModel(new models::DomainModelItem());
    fill_logical_data(logicalModel);

    qosModel = new models::TreeModel(backend_connection.get_qos(ALL_ID_BACKEND));
}

QObject* Engine::enable()
{
    rootContext()->setContextProperty("participantModel", participantsModel);
    rootContext()->setContextProperty("hostModel", physicalModel);
    rootContext()->setContextProperty("domainModel",  logicalModel);

    rootContext()->setContextProperty("qosModel", qosModel);

    qmlRegisterType<Controller>("com.myself", 1, 0, "Controller");

    load(QUrl(QLatin1String("qrc:/main.qml")));

    return rootObjects().value(0);
}

void Engine::init_monitor(int domain)
{
    backend_connection.init_monitor(domain);
}

void Engine::init_monitor(QString locators)
{
    backend_connection.init_monitor(locators);
}

bool Engine::fill_dds_qos(backend::EntityId id /*ALL_ID_BACKEND*/)
{
    // TODO implement update
    qosModel->update(backend_connection.get_qos(id));
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
        models::ListModel* dds_model,
        backend::EntityId id /*ALL_ID_BACKEND*/)
{
    dds_model->clear();
    return backend::SyncBackendConnection::update_dds_data(dds_model, id);
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
