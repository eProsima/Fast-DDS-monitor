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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Theme 1.0

ToolBar {
    id: toolBar
    visible: isVisible

    property bool isVisible: false
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
        spacing: 10

        Item {
            width: 1
        }

        MonitorToolBarButton {
            id: dashboardLayout
            iconName: "grid" + chartsPerRow
            tooltipText: "Dashboard Layout"
            visible: isVisibleDashboardLayout

            property int chartsPerRow: 2

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
            tooltipText: "Refresh (Ctrl+R)"
            visible: isVisibleRefresh
            onClicked: {
                controller.refresh_click()
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
        onActivated: {
            controller.refresh_click()
            lastClickedReset()
        }
    }

    function changeChartboxLayoutIcon(chartsPerRow) {
        dashboardLayout.chartsPerRow = chartsPerRow
    }
}
