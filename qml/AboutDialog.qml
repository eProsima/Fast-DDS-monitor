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

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: aboutDialog
    modal: false
    title: "About Fast DDS Monitor"
    standardButtons: Dialog.Close

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    RowLayout {
        spacing: 20

        Image {
            id: fastddsMonitorLogo
            source: "/resources/images/fastdds-monitor-logo.png"
            sourceSize.width: 200
            sourceSize.height: 200
            Layout.alignment: Qt.AlignTop
        }

        Rectangle {
            id: aboutPropertiesRect
            width: 400
            height: aboutPropertiesLayout.height
            color: "transparent"

            ColumnLayout {
                id: aboutPropertiesLayout
                width: parent.width
                spacing: 20

                ColumnLayout {
                    Label { text:"Version: " + controller.fastdds_monitor_version() }
                    Label { text:"Commit: " + controller.git_commit() }
                    Label { text:"Date: " + controller.build_date() }
                    Label { text:"eProsima Fast DDS: " + controller.fastdds_version() }
                    Label { text:"eProsima Fast DDS Statistics Backend: " + controller.fastdds_statistics_backend_version() }
                    Label { text:"Qt: " + controller.qt_version() }
                    Label { text:"OS: " + controller.system_info() }
                }

                Label {
                    width: aboutPropertiesRect.width
                    Layout.preferredWidth: aboutPropertiesRect.width
                    text: "Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima). All Rights Reserved. " +
                          "Licensed under the GNU General Public License version 3 (GPLv3), published by the " +
                          "Free Software Foundation."
                    wrapMode: Text.WordWrap
                }
            }
        }



    }
}
