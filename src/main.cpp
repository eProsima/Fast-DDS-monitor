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

#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick/QQuickView>

#include <fastdds-monitor/Engine.h>

int main(
        int argc,
        char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif // if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resources/images/eprosima_logo.ico"));

    /******************************************************************************************************************
    * Application engine                                                                                             *
    ******************************************************************************************************************/

    Engine engine;
    QObject* topLevel = engine.enable();

    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel); \
    if ( !window )
    {
        qWarning("Error: Your root item has to be a Window."); \
        return -1;
    }
    window->show();

    return app.exec();
}
