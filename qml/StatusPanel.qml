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

import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12
import Theme 1.0

/*
    Sidebar containing the Status and the Log views.
 */
ColumnLayout {
    id: statusPanel
    spacing: 0

    Rectangle {
        Layout.fillWidth: true
        height: 20
        color: Theme.grey

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            spacing: 0
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            Label {
                text: "Monitor Status"
                Layout.preferredWidth: parent.width - parent.height
                color: Theme.whiteSmoke
            }
        }
    }

    ColumnLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 0

        TabBar {
            id: logViewTabBar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Status")
            }
            TabButton {
                text: qsTr("Log")
            }
        }

        StackLayout {
            currentIndex: logViewTabBar.currentIndex
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true

            StatusView {
                id: statusView
            }

            LogView {
                id: logView
            }
        }
    }
}
