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
import Theme 1.0

ToolBar {
    id: toolBar
    visible: isVisible

    property bool isVisible: true
    property bool isVisibleDispData: false
    property bool isVisibleDispDynData: true
    property bool isVisibleRefresh: true
    property bool isVisibleClearLog: false
    property bool isVisibleClearIssues: false
    property bool isVisibleDashboardLayout: true

    signal lastClickedReset
    signal changeChartboxLayout(int chartsPerRow)

    RowLayout {
        anchors.fill: parent

        MonitorToolBarButton {
            id: dashboardLayout
            iconName: "grid" + chartsPerRow
            tooltipText: "Dashboard Layout"
            visible: isVisibleDashboardLayout

            property int chartsPerRow: 1

            onClicked: {
                if (chartsPerRow === 3) {
                    chartsPerRow = 1
                } else {
                    chartsPerRow++
                }
                changeChartboxLayout(chartsPerRow)
            }
        }

        MonitorToolBarButton {
            id: historicalChart
            iconName: "historicalchart"
            tooltipText: "Display Historical Data"
            visible: isVisibleDispData
            onClicked: dataKindDialog.open()
        }

        MonitorToolBarButton {
            id: dynamicChart
            iconName: "dynamicchart"
            tooltipText: "Display Real-Time Data"
            visible: isVisibleDispDynData
            onClicked: dynamicDataKindDialog.open()
        }

        MonitorToolBarButton {
            id: refresh
            iconName: "refresh"
            tooltipText: "Refresh"
            visible: isVisibleRefresh
            onClicked: {
                controller.refresh_click()
                lastClickedReset()
            }
        }

        MonitorToolBarButton {
            id: clearLog
            iconName: "clearlog"
            tooltipText: "Clear Log"
            visible: isVisibleClearLog
            onClicked: controller.clear_log()
        }

        MonitorToolBarButton {
            id: clearIssues
            iconName: "clearissues"
            tooltipText: "Clear Issues"
            visible: isVisibleClearIssues
            onClicked: controller.clear_issues()
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

    function changeChartboxLayoutIcon(chartsPerRow) {
        dashboardLayout.chartsPerRow = chartsPerRow
    }
}
