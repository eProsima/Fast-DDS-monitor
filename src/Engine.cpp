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

#include <json.hpp>

using nlohmann::json;

Engine::Engine()
{
    participantsModel = new models::SubListedListModel(new models::ParticipantModelItem());
    backend_connection.fill_dds_data(participantsModel);

    physicalModel = new models::SubListedListModel(new models::HostModelItem());
    backend_connection.fill_physical_data(physicalModel);

    logicalModel = new models::SubListedListModel(new models::DomainModelItem());
    backend_connection.fill_logical_data(logicalModel);

    json qos = R"({
        "DurabilityQosPolicy": "TRANSIENT_LOCAL_DURABILITY_QOS",
        "DeadlineQosPolicy": "5ms",
        "LivelinessQosPolicy": {
            "kind": "AUTOMATIC_LIVELINES_QOS",
            "lease_duration": "c_TimeInfinite",
            "announcement_period": "c_TimeInfinite"
        }
    })"_json;

    qosModel = new models::TreeModel(qos);
}

void Engine::enable()
{
    rootContext()->setContextProperty("participantModel", participantsModel);
    rootContext()->setContextProperty("hostModel", physicalModel);
    rootContext()->setContextProperty("domainModel", logicalModel);

    rootContext()->setContextProperty("qosModel", qosModel);

    load(QUrl(QLatin1String("qrc:/main.qml")));
}
