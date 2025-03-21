// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick/QQuickView>

#include <fastdds_monitor/Engine.h>
#include <fastdds_monitor/io/ClipboardHandler.h>

int main(
        int argc,
        char* argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resources/images/eprosima_logo.ico"));
    app.setOrganizationName("eProsima");
    app.setOrganizationDomain("eprosima.com");
    app.setApplicationName("Fast DDS Monitor");

    /******************************************************************************************************************
    * Application engine                                                                                             *
    ******************************************************************************************************************/

    Engine engine;

    qmlRegisterType<ClipboardHandler>("Clipboard", 1, 0, "ClipboardHandler");

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
