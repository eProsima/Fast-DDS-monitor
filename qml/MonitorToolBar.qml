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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

ToolBar {
    id: toolBar
    visible: isVisible

    property bool isVisible: true
    property bool isVisibleInitMonitor: true
    property bool isVisibleDispData: true
    property bool isVisibleDispDynData: true
    property bool isVisibleRefresh: true
    property bool isVisibleClearLog: false
    property bool isVisibleClearIssues: false

    signal lastClickedReset

    RowLayout {
        anchors.fill: parent
        ToolButton {
            text: "Init new monitor"
            visible: isVisibleInitMonitor
            onClicked: {
                dialogInitMonitor.open()
            }
        }

        ToolButton {
            text: "Display historical data"
            visible: isVisibleDispData
            onClicked: {
                dataKindDialog.open()
            }
        }

        ToolButton {
            text: "Display real-time data"
            visible: isVisibleDispDynData
            onClicked: {
                dynamicDataKindDialog.open()
            }
        }

        ToolButton {
            text: "Refresh"
            visible: isVisibleRefresh
            onClicked: {
                controller.refresh_click()
                lastClickedReset()
            }
        }

        ToolButton {
            text: "Clear log"
            visible: isVisibleClearLog
            onClicked: {
                controller.clear_log()
            }
        }

        ToolButton {
            text: "Clear issues"
            visible: isVisibleClearIssues
            onClicked: {
                controller.clear_issues()
            }
        }

        Item {
            Layout.fillWidth: true
        }
    }

    Shortcut {
        sequence: "Ctrl+R"
        context: Qt.ApplicationShortcut
        onActivated: controller.refresh_click()
    }
}
