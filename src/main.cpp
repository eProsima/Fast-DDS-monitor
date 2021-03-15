#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick/QQuickView>

#include <iostream>

#include <include/model/SubListedListModel.h>
#include <include/Engine.h>

#include <include/backend/SyncBackendConnection.h>

#include <include/model/tree/TreeModel.h>

#include <json.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    /******************************************************************************************************************
     * Application engine                                                                                             *
     ******************************************************************************************************************/

    Engine engine;
    engine.enable();

    QObject *topLevel = engine.rootObjects().value(0);

    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel); \
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window."); \
        return -1;
    }
    window->show();

    return app.exec();
}
