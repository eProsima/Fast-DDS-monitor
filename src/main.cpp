#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick/QQuickView>

#include <iostream>

#include <include/Engine.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    /******************************************************************************************************************
     * Application engine                                                                                             *
     ******************************************************************************************************************/

    QObject *topLevel = Engine::get_instance()->enable();

    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel); \
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window."); \
        return -1;
    }
    window->show();

    return app.exec();
}
