#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick/QQuickView>

#include <include/model/SubListedListModel.h>
#include <include/model/logical/ParticipantModelItem.h>
#include <include/model/logical/EndpointModelItem.h>
#include <include/model/logical/TopicModelItem.h>
#include <include/model/physical/HostModelItem.h>
#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    /******************************************************************************************************************
     * Logical view static data                                                                                       *
     ******************************************************************************************************************/

    models::ListModel* participantsModel = new models::SubListedListModel(new ParticipantModelItem());

    participantsModel->appendRow(new ParticipantModelItem(
             "00.00.00.00.00.00.00.00.00.00.00.01|00.00.00.00",
             "DomainParticipant_1"));
    participantsModel->appendRow(new ParticipantModelItem(
             "00.00.00.00.00.00.00.00.00.00.00.02|00.00.00.00",
             "DomainParticipant_2"));
    participantsModel->appendRow(new ParticipantModelItem(
             "00.00.00.00.00.00.00.00.00.00.00.03|00.00.00.00",
             "DomainParticipant_3"));

    static_cast<ParticipantModelItem*>(
            participantsModel->find("00.00.00.00.00.00.00.00.00.00.00.01|00.00.00.00")
        )->submodel()->appendRow(new EndpointModelItem(
                                     "00.00.00.00.00.00.00.00.00.00.00.01|00.00.00.01",
                                     "DataWriter"));

    static_cast<ParticipantModelItem*>(
            participantsModel->find("00.00.00.00.00.00.00.00.00.00.00.03|00.00.00.00")
        )->submodel()->appendRow(new EndpointModelItem(
                                     "00.00.00.00.00.00.00.00.00.00.00.03|00.00.00.01",
                                     "DataWriter"));

    static_cast<EndpointModelItem*>(
            static_cast<ParticipantModelItem*>(
                participantsModel->find("00.00.00.00.00.00.00.00.00.00.00.01|00.00.00.00")
                    )->submodel()->find("00.00.00.00.00.00.00.00.00.00.00.01|00.00.00.01")
                        )->submodel()->appendRow(new TopicModelItem(
                            "Topic_1",
                            "HelloWord",
                            "HelloWorldType"));

    /******************************************************************************************************************
     * Physical view static data                                                                                      *
     ******************************************************************************************************************/

    models::ListModel* hostsModel = new models::SubListedListModel(new HostModelItem());

    hostsModel->appendRow(new HostModelItem("Host_1"));
    hostsModel->appendRow(new HostModelItem("Host_2"));
    hostsModel->appendRow(new HostModelItem("Host_3"));
    hostsModel->appendRow(new HostModelItem("Host_4"));

    static_cast<HostModelItem*>(hostsModel->find("Host_2"))->submodel(
        )->appendRow(new UserModelItem("UserId_1", "username_1"));

    static_cast<HostModelItem*>(hostsModel->find("Host_3"))->submodel(
        )->appendRow(new UserModelItem("UserId_2", "username_2"));

    static_cast<UserModelItem*>(static_cast<HostModelItem*>(hostsModel->find("Host_3"))->submodel(
        )->find("UserId_2")
            )->submodel()->appendRow(new ProcessModelItem("ProcessId", "ProcessExec", "ProcessPID"));


    /******************************************************************************************************************
     * Application engine                                                                                             *
     ******************************************************************************************************************/

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("participantModel", participantsModel);
    engine.rootContext()->setContextProperty("hostModel", hostsModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    QObject *topLevel = engine.rootObjects().value(0);
        QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel); \
        if ( !window ) {
            qWarning("Error: Your root item has to be a Window."); \
            return -1;
        }
        window->show();

    return app.exec();
}
