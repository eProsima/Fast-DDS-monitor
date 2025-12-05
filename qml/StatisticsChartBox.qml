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
import QtQuick.Window
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Theme 1.0

Rectangle {
    id: statisticsChartBox

    radius: statisticsChartBox.chartBoxRadius

    property string dataKind
    property string chartTitle
    property int index
    property bool visibility: true
    property bool isDynamic: false
    property variant timeWindow: -1
    property variant updatePeriod: -1
    property int chartboxId: -1
    property variant currentDate: toMsecsSinceEpoch(new Date())
    property bool running: false
    property int maxPoints: 0

    property int chartBoxRadius: 0

    signal fullScreen(int chartBoxIdx)

    Component.onCompleted: {
        if (isDynamic){
            chartboxId = dynamicData.add_chartbox(dataKind, currentDate, timeWindow, maxPoints)
            chartTitle = chartTitle + " [dynamic]"
            dynamicDisplayStatisticsDialog.open()
        } else {
            controlPanel.removeMenu(realTimeMenu);
            chartboxId = historicData.add_chartbox(dataKind)
            chartTitle = chartTitle + " [historic]"
            historicDisplayStatisticsDialog.open();
        }
    }

    Component.onDestruction: {
        if (isDynamic && dynamicData) {
            dynamicData.delete_chartbox(chartboxId)
        } else if (!isDynamic && historicData) {
            historicData.delete_chartbox(chartboxId)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        visible: visibility

        Rectangle {
            id: chartBoxTitle
            Layout.fillWidth: true
            height: 25
            color: Theme.eProsimaDarkBlue
            radius: statisticsChartBox.chartBoxRadius

            Rectangle {
                height: parent.height/2
                width: parent.width
                anchors.bottom: parent.bottom
                color: parent.color
            }

            Label {
                id: statisticsChartBoxLabel
                text: chartTitle
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            RowLayout {
                anchors.right: parent.right
                anchors.rightMargin: parent.height/3
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    height: chartBoxTitle.height * 4/5
                    width: chartBoxTitle.height * 4/5
                    radius: chartBoxTitle.height * 4/5
                    color: "transparent"

                    IconSVG {
                        name: chartsLayout.fullScreen ? "minimize" : "maximize"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "white"
                        size: parent.width * 1/2
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            fullScreen(index)
                        }
                        onEntered: {
                            parent.color = Theme.eProsimaLightBlue
                        }
                        onExited: {
                            parent.color = "transparent"
                        }
                    }
                }

                Rectangle {
                    height: chartBoxTitle.height * 4/5
                    width: chartBoxTitle.height * 4/5
                    radius: chartBoxTitle.height * 4/5
                    color: "transparent"

                    IconSVG {
                        name: "cross"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "white"
                        size: parent.width * 1/2
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            chartsLayout.exitFullScreen()
                            statisticsChartBoxModel.remove(index)
                            statisticsChartBox.destroy()
                        }
                        onEntered: {
                            parent.color = Theme.eProsimaLightBlue
                        }
                        onExited: {
                            parent.color = "transparent"
                        }
                    }
                }
            }

        }

        MenuBar {
            id: controlPanel
            Layout.fillWidth: true
            
            background: Rectangle {
                implicitHeight: 30
                color: "#e5e6e3"  // Original background color
                
                Rectangle {
                    width: parent.width
                    height: 2
                    anchors.bottom: parent.bottom
                    color: "#5c5c5a"  // Bottom border color
                }
            }

            delegate: MenuBarItem {
                id: menuBarItem
                
                implicitWidth: Math.max(contentItem.implicitWidth + leftPadding + rightPadding, 40)
                implicitHeight: 28
                
                padding: 0
                leftPadding: 5
                rightPadding: 5
                
                contentItem: Text {
                    text: menuBarItem.text
                    font: menuBarItem.font
                    opacity: enabled ? 1.0 : 0.3
                    color: "black"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                
                background: Rectangle {
                    opacity: enabled ? 1 : 0.3
                    color: menuBarItem.highlighted ? "#d0d0d0" : "transparent"
                }
            }

            signal addHistoricSeries(
                string dataKind,
                string seriesLabel,
                string sourceEntityId,
                string targetEntityId,
                int bins,
                date startTime,
                bool startTimeDefault,
                date endTime,
                bool endTimeDefault,
                string statisticKind)
            signal addDynamicSeries(
                string seriesLabel,
                string sourceEntityId,
                string targetEntityId,
                string statisticKind,
                bool cumulative,
                int cumulative_interval,
                int maxPoints)
            signal clearChart()
            signal dynamicPause()
            signal dynamicContinue()

            onAddHistoricSeries: function(dataKind, seriesLabel, sourceEntityId, targetEntityId, bins, startTime, startTimeDefault, endTime, endTimeDefault, statisticKind) {
                statisticsChartViewLoader.item.addHistoricSeries(
                                    dataKind,
                                    seriesLabel,
                                    sourceEntityId,
                                    targetEntityId,
                                    bins,
                                    startTime,
                                    startTimeDefault,
                                    endTime,
                                    endTimeDefault,
                                    statisticKind)
            }
            onAddDynamicSeries: function(seriesLabel, sourceEntityId, targetEntityId, statisticKind, cumulative, cumulative_interval, maxPoints) {
                statisticsChartViewLoader.item.addDynamicSeries(
                                    seriesLabel,
                                    sourceEntityId,
                                    targetEntityId,
                                    statisticKind,
                                    cumulative,
                                    cumulative_interval,
                                    maxPoints)
            }
            onClearChart: statisticsChartViewLoader.item.clearChart();
            onDynamicContinue: statisticsChartViewLoader.item.dynamicContinue();
            onDynamicPause: statisticsChartViewLoader.item.dynamicPause();

            Menu {
                title: "Chart"
                Action {
                    text: "Reset zoom"
                    onTriggered: statisticsChartViewLoader.item.resetChartViewZoom()
                }
                Action {
                    text: "Set axes"
                    onTriggered: statisticsChartViewLoader.item.userSetAxes()
                }
                Action {
                    text: "Clear chart"
                    onTriggered: controlPanel.clearChart();
                }
                MenuSeparator { }
                Action {
                    text: "Rename chart box"
                    onTriggered: renameChartBoxDialog.open()
                }
                Action {
                    text: "Close chart box"
                    onTriggered: {
                        statisticsChartBoxModel.remove(index)
                        statisticsChartBox.destroy()
                    }
                }
                Action {
                    // Export whole chartbox to CSV
                    text: "Export to CSV"
                    onTriggered: {

                        // All the labels of the series in order of index of each series
                        var seriesNum = customLegend.getNumberOfSeries()
                        
                        var chartboxIds = []
                        var seriesIds = []
                        var dataKinds = []
                        var chartTitles = []
                        
                        for (var i = 0; i < seriesNum; i++) {
                            chartboxIds.push(chartboxId)
                            seriesIds.push(i)
                            dataKinds.push(dataKind)
                            chartTitles.push(chartTitle)
                        }
                        
                        saveCSV(
                            chartboxIds,
                            seriesIds,
                            dataKinds,
                            chartTitles,
                            customLegend.getAllLabels()
                        )
                    }
                }
                MenuSeparator { }
                Action {
                    text: "Chart Controls"
                    onTriggered: infoDialog.open()
                }
            }

            Menu {
                title: "Series"
                Action {
                    text: "Add series"
                    onTriggered: (isDynamic) ? dynamicDisplayStatisticsDialog.open() : historicDisplayStatisticsDialog.open();
                }

                Action {
                    text: "Hide all series"
                    onTriggered: customLegend.hideAllSeries()
                }
                Action {
                    text: "Display all series"
                    onTriggered: customLegend.displayAllSeries()
                }
            }

            Menu {
                id: realTimeMenu
                title: "Real Time"
                Action {
                    text: running ? "Pause" : "Continue"
                    onTriggered: {
                        running ? statisticsChartViewLoader.item.dynamicPause() : statisticsChartViewLoader.item.dynamicContinue()
                    }
                }
            }
        }

        // Statistics ChartView
        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Loader {
                id: statisticsChartViewLoader
                anchors.fill: parent

                property string dataKind: statisticsChartBox.dataKind
                property variant timeWindow: statisticsChartBox.timeWindow
                property variant currentDate: statisticsChartBox.currentDate
                property variant updatePeriod: statisticsChartBox.updatePeriod
                property variant chartboxId: statisticsChartBox.chartboxId

                source: (isDynamic) ? "DynamicStatisticsChartView.qml" : "HistoricStatisticsChartView.qml"
            }

            Connections {
                target: statisticsChartViewLoader.item
                ignoreUnknownSignals: true
                function onSeriesAdded(series){
                    customLegend.addLeyend(series.name, series.color)
                }
                function onClearedChart(){
                    customLegend.removeAllLegends()
                }
                function onRunningChanged(){
                    running = !running
                }
            }

            // Side Buttons Column
            ColumnLayout {

                id: chartViewIcons

                property int iconSize: 30
                property real innerIconSize: iconSize * 4/5

                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: iconSize/10
                anchors.topMargin: iconSize/10

                width: iconSize

                spacing: iconSize/10

                // Info Button
                Rectangle {

                    height: chartViewIcons.iconSize
                    width: chartViewIcons.iconSize
                    radius: chartViewIcons.iconSize/10

                    color: infoMouseArea.containsMouse ? Theme.lightGrey : "transparent"

                    IconSVG {
                        size: chartViewIcons.innerIconSize
                        name: "help"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "black"
                    }

                    ToolTip {
                        text: "Interactive Chart controls Info"
                        delay: 250
                        visible: infoMouseArea.containsMouse
                        contentItem: Text{
                            color: Theme.whiteSmoke
                            text: "Interactive Chart controls Info"
                        }
                        background: Rectangle {
                            color: Theme.eProsimaLightBlue
                            border.color: Theme.eProsimaLightBlue
                        }
                    }

                    MouseArea {
                        id: infoMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            infoDialog.open()
                        }
                    }
                }

                // Reset Zoom Button
                Rectangle {

                    height: chartViewIcons.iconSize
                    width: chartViewIcons.iconSize
                    radius: chartViewIcons.iconSize/10

                    color: resizeMouseArea.containsMouse ? Theme.lightGrey : "transparent"

                    IconSVG {
                        size: chartViewIcons.innerIconSize
                        name: "resize"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "black"
                    }

                    MouseArea {
                        id: resizeMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            statisticsChartViewLoader.item.resetChartViewZoom()
                        }
                    }

                    ToolTip {
                        text: "Reset Chart Zoom"
                        delay: 250
                        visible: resizeMouseArea.containsMouse
                        contentItem: Text{
                            color: Theme.whiteSmoke
                            text: "Reset Chart Zoom"
                        }
                        background: Rectangle {
                            color: Theme.eProsimaLightBlue
                            border.color: Theme.eProsimaLightBlue
                        }
                    }
                }

                // Set Axes Button
                Rectangle {

                    height: chartViewIcons.iconSize
                    width: chartViewIcons.iconSize
                    radius: chartViewIcons.iconSize/10

                    color: resetMouseArea.containsMouse ? Theme.lightGrey : "transparent"

                    IconSVG {
                        size: chartViewIcons.innerIconSize
                        name: "editaxis"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "black"
                    }

                    MouseArea {
                        id: resetMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            statisticsChartViewLoader.item.userSetAxes()
                        }
                    }

                    ToolTip {
                        text: "Set Axes"
                        delay: 250
                        visible: resetMouseArea.containsMouse
                        contentItem: Text{
                            color: Theme.whiteSmoke
                            text: "Set Axes"
                        }
                        background: Rectangle {
                            color: Theme.eProsimaLightBlue
                            border.color: Theme.eProsimaLightBlue
                        }
                    }
                }

                // Pause/Play Button
                Rectangle {
                    height: chartViewIcons.iconSize
                    width: chartViewIcons.iconSize
                    radius: chartViewIcons.iconSize/10

                    color: playMouseArea.containsMouse ? Theme.lightGrey : "transparent"
                    visible: isDynamic

                    IconSVG {
                        size: chartViewIcons.innerIconSize
                        name: running ? "pause" : "play"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "black"
                    }

                    MouseArea {
                        id: playMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            if (running) {
                                statisticsChartViewLoader.item.dynamicPause()
                            } else {
                                statisticsChartViewLoader.item.dynamicContinue()
                            }
                        }
                    }

                    ToolTip {
                        text: running ? "Disable X axis move" : "Enable X axis move"
                        delay: 250
                        visible: playMouseArea.containsMouse
                        contentItem: Text{
                            color: Theme.whiteSmoke
                            text: running ? "Disable X axis move" : "Enable X axis move"
                        }
                        background: Rectangle {
                            color: Theme.eProsimaLightBlue
                            border.color: Theme.eProsimaLightBlue
                        }
                    }
                }
            }
        }

        CustomLegend {
            id: customLegend
            Layout.fillWidth: true
            Layout.margins: 10
            onSeriesNameUpdated: function(seriesIndex, newSeriesName) {
                statisticsChartViewLoader.item.updateSeriesName(seriesIndex, newSeriesName)
            }
            onSeriesColorUpdated: function(seriesIndex, newSeriesColor) {
                statisticsChartViewLoader.item.updateSeriesColor(seriesIndex, newSeriesColor)
            }
            onSeriesHidden: function(seriesIndex) {
                statisticsChartViewLoader.item.hideSeries(seriesIndex)
            }
            onSeriesDisplayed: function(seriesIndex) {
                statisticsChartViewLoader.item.displaySeries(seriesIndex)
            }
            onSeriesRemoved: function(seriesIndex) {
                statisticsChartViewLoader.item.removeSeries(statisticsChartViewLoader.item.series(seriesIndex))
                removeLegend(seriesIndex)
                if(isDynamic) {
                    dynamicData.delete_series(chartboxId, seriesIndex)
                    statisticsChartViewLoader.item.customRemoveSeries(seriesIndex)
                } else {
                    historicData.delete_series(chartboxId, seriesIndex)
                    statisticsChartViewLoader.item.customRemoveSeries(seriesIndex)
                }
            }
            onSeriesToCSV: function(seriesIndex, seriesLabel) {
                // Export one series as CSV
                saveCSV(
                    [chartboxId],
                    [seriesIndex],
                    [dataKind],
                    [chartTitle],
                    [seriesLabel])
            }
            onSetMaxPoints: function(seriesIndex, maxPoints) {
                // Export one series as CSV
                seriesSetMaxPoints(chartboxId, seriesIndex, maxPoints)
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        radius: statisticsChartBox.chartBoxRadius
        border {
            width: 2
            color: Theme.eProsimaDarkBlue
        }
    }

    Label {
        text: chartTitle
        color: "white"
        visible: !visibility
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    HistoricDisplayStatisticsDialog {
        id: historicDisplayStatisticsDialog
        anchors.centerIn: Overlay.overlay
    }

    DynamicDisplayStatisticsDialog {
        id: dynamicDisplayStatisticsDialog
        anchors.centerIn: Overlay.overlay
    }

    Dialog {
        id: renameChartBoxDialog
        title: "Rename Chart Box"
        standardButtons: Dialog.Ok | Dialog.Cancel
        anchors.centerIn: Overlay.overlay

        GridLayout {
            columns: 2
            rowSpacing: 20
            Label {
                text: "Current chart box name: "
            }
            Label {
                text: chartTitle
            }
            Label {
                text: "New chart box name: "
            }
            TextField {
                id: newChartBoxNameTextField
                selectByMouse: true
                maximumLength: 100
                implicitWidth: textMetrics.width + leftPadding + rightPadding

                Keys.onReturnPressed: renameChartBoxDialog.accept()
            }
        }

        TextMetrics {
            id: textMetrics
            text: "----------------------------------------------------------------------------------------------------"
        }

        onAccepted: {
            if (newChartBoxNameTextField.text !== "") {
                chartTitle = newChartBoxNameTextField.text
            }
        }
    }

    Dialog {
        id: infoDialog
        title: "Chart Interactive Controls"
        standardButtons: Dialog.Ok | Dialog.Help
        anchors.centerIn: Overlay.overlay

        Component.onCompleted: {
            standardButton(Dialog.Ok).text = qsTrId("Got it!")
            standardButton(Dialog.Help).text = qsTrId("Extra Help...")
        }

        onHelpRequested: Qt.openUrlExternally("https://fast-dds-monitor.readthedocs.io/en/latest/rst/user_manual/chart_panel_index.html")

        RowLayout {
            spacing: 20

            Rectangle {
                id: infoChartRect
                width: 400
                height: infoChartRectLayout.height
                color: "transparent"

                GridLayout {
                    id: infoChartRectLayout
                    width: parent.width
                    columns: 2
                    rows: 2
                    rowSpacing: 15

                    Label { text:"Click in chart point:"; font.bold: true}
                    Label { text:"Show point value"}

                    Label { text:"Ctrl + click and drag:"; font.bold: true}
                    Label { text:"Scroll axex"}

                    Label { text:"Ctrl + wheel:"; font.bold: true}
                    Label { text:"Zoom in / out"}

                    Label { text:"Mayus + grab area:"; font.bold: true}
                    Label { text:"Zoom in over the area"}

                    Label { text:"Only available while stopped"; visible: isDynamic}

                }
            }
        }
    }

    function toMsecsSinceEpoch(date) {
        return date.getTime().valueOf();
    }

    function fromMsecsSinceEpoch(milliseconds) {
        return new Date(milliseconds);
    }

    function chartboxSeriesLabels() {
        return customLegend.getAllLabels()
    }
}
