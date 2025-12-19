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

import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8
import QtQml.Models 6.8
import Theme 1.0

Rectangle {
    id: chartsLayout

    property int boxesPerRow: 2
    property int actualBoxesPerRow: Math.min(fullScreen ? 1 : boxesPerRow, (gridView.count === 0) ? 1 : gridView.count)
    property int chartBoxWidth: fullScreen ? (gridViewWidth / actualBoxesPerRow)
                                           : (gridViewWidth / actualBoxesPerRow) - (20 - 5 * actualBoxesPerRow)
    property int chartBoxHeight: Math.min(chartBoxWidth, height / actualBoxesPerRow)
    property int gridViewWidth: width < 1 ? 0 : width - 1

    property bool fullScreen: false

    ListModel {
        id: statisticsChartBoxModel
    }

    MouseArea {
        id: mouseArea
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: gridViewWidth
        enabled: true

        property int pressAndHoldDuration: 200
        signal customPressAndHold()

        onPressed: {
            if (!fullScreen) {
                pressAndHoldTimer.start();
            }
        }

        onCustomPressAndHold: {
            gridView.firstIndexDrag = gridView.indexAt(mouseX, mouseY + gridView.contentY)
        }

        onReleased: {
            pressAndHoldTimer.stop();
            if (gridView.firstIndexDrag != -1)
                statisticsChartBoxModel.move(
                            gridView.firstIndexDrag, gridView.indexAt(mouseX, mouseY + gridView.contentY), 1)
            gridView.firstIndexDrag = -1
        }

        onWheel: function(wheel) {
            if (!fullScreen) {
                if (wheel.angleDelta.y > 0) {
                    gridViewScrollBar.decrease()
                } else {
                    gridViewScrollBar.increase()
                }
            }
        }

        Timer {
            id:  pressAndHoldTimer
            interval: parent.pressAndHoldDuration
            running: false
            repeat: false
            onTriggered: {
                parent.customPressAndHold();
            }
        }

        GridView {
            id: gridView
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            cellWidth: chartBoxWidth
            cellHeight: chartBoxHeight
            interactive: false
            model: statisticsChartBoxModel
            delegate: widgetdelegate
            cacheBuffer: ((chartBoxHeight * 100) < 0) ? 250 : (chartBoxHeight * 100)

            property int firstIndexDrag: -1

            Item {
                id: container
                anchors.fill: parent
            }

            ScrollBar.vertical: ScrollBar {
                id: gridViewScrollBar
                visible: !fullScreen
                policy: ScrollBar.AlwaysOn
                hoverEnabled: true

                contentItem: Item {
                    implicitWidth: 8

                    Rectangle {
                        anchors.fill: parent
                        anchors.topMargin: 1
                        anchors.rightMargin: 2
                        anchors.leftMargin: 2
                        radius: width / 2
                        color: gridViewScrollBar.pressed ? Theme.eProsimaLightBlue : Theme.lightGrey
                    }
                }

                background: Item {
                    implicitWidth: 12

                    Rectangle {
                        anchors.fill: parent
                        color: gridViewScrollBar.pressed ? Theme.lightGrey : Theme.grey
                    }
                }

                Rectangle {
                    anchors.top: parent.top
                    height: 1
                    width: parent.width
                    color: gridViewScrollBar.pressed ? Theme.lightGrey : Theme.grey
                }
            }

            onCountChanged: {
                var newIndex = count - 1
                positionViewAtEnd()
                currentIndex = newIndex
            }
        }

        Component {
            id: widgetdelegate

            Item {
                width: gridView.cellWidth
                height: gridView.cellHeight

                property var statisticsChartBoxItem: statisticsChartBox

                StatisticsChartBox {
                    id: statisticsChartBox
                    chartTitle: model.dataKind
                    dataKind: model.dataKind
                    isDynamic: (dynamic) ? true : false
                    timeWindow: timeFrame
                    updatePeriod: timeUpdate
                    index: model.index
                    state: "inactive"
                    anchors.centerIn: parent
                    width: gridView.cellWidth - 10
                    height: gridView.cellHeight - 10
                    smooth: true
                    maxPoints: model.maxPoints

                    onFullScreen: function(chartBoxIdx) { chartBoxFullScreen(chartBoxIdx) }

                    states: [
                        State {
                            name: "inactive";
                            when: (gridView.firstIndexDrag == -1) || (gridView.firstIndexDrag === model.index)
                            PropertyChanges {
                                target: statisticsChartBox
                                rotation: 0
                            }
                        }
                    ]
                }
                states: [
                    State {
                        name: "inDrag"
                        when: model.index === gridView.firstIndexDrag
                        PropertyChanges {
                            target: statisticsChartBox
                            parent: container
                        }
                        PropertyChanges {
                            target: statisticsChartBox
                            anchors.centerIn: undefined
                        }
                        PropertyChanges {
                            target: statisticsChartBox
                            visibility: false
                        }
                        PropertyChanges{
                            target: statisticsChartBox
                            color: Theme.eProsimaDarkBlue
                        }
                        PropertyChanges {
                            target: statisticsChartBox
                            width: (gridView.cellWidth - 10) / 2
                        }
                        PropertyChanges {
                            target: statisticsChartBox;
                            height: (gridView.cellHeight - 10) / 2
                        }
                        PropertyChanges {
                            target: statisticsChartBox
                            x: {
                                var x = mouseArea.mouseX - statisticsChartBox.width/2
                                if (x < 0) {
                                    return 0
                                } else if ((x + statisticsChartBox.width) > mouseArea.width) {
                                    return mouseArea.width - statisticsChartBox.width
                                } else {
                                    return x
                                }
                            }
                        }
                        PropertyChanges {
                            target: statisticsChartBox
                            y: mouseArea.mouseY - statisticsChartBox.height/10
                        }
                    }
                ]
            }
        }
    }

    Rectangle {
        id: emptyScreen
        width: parent.width / 1.5
        height: parent.height / 1.5
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        visible: statisticsChartBoxModel.count == 0

        ColumnLayout{
            anchors.fill: parent

            Rectangle {
                Layout.preferredWidth: emptyScreen.width * 3/5
                Layout.preferredHeight: emptyScreen.height * 3/5
                Layout.alignment: Qt.AlignCenter
                color: "transparent"

                Image {
                    id: emptyScreenImage
                    source: "/resources/images/graphs.svg"
                    sourceSize.width: parent.width - 5
                    sourceSize.height: parent.height - 5
                    anchors.centerIn: parent
                    opacity: 0.9
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: emptyScreen.height * 0.5/5
                Layout.alignment: Qt.AlignCenter
                color: "transparent"

                Text {
                    id: emptyScreenLabel
                    width: parent.width
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font.pointSize: 20
                    font.bold: true
                    color: Theme.x11Grey
                    text: mainApplicationView.monitors == 0 ? "Oops... no initialized monitors yet"
                                                            : "Oops... no data charts to display"
                }
            }

            Rectangle {
                id: emptyScreenButton
                Layout.preferredWidth: emptyScreen.width * 2/5
                Layout.preferredHeight: emptyScreen.height * 0.5/5
                Layout.alignment: Qt.AlignCenter
                radius: height
                color: Theme.x11Grey
                border.color: Theme.grey
                border.width: emptyScreenButtonMouseArea.containsMouse ? 3 : 0

                Text {
                    font.bold: emptyScreenButtonMouseArea.containsMouse
                    font.pointSize: 15
                    color: Theme.whiteSmoke
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: mainApplicationView.monitors == 0 ? "Initilialize monitor"
                                                            : "Create new chart"
                }

                MouseArea {
                    id: emptyScreenButtonMouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true

                    onClicked: {
                        if (mainApplicationView.monitors == 0) {
                            dialogInitMonitor.open()
                        } else {
                            dynamicDataKindDialog.open()
                        }
                    }
                }
            }
        }
    }

    ExportCSVFileDialog {
        id: csvDialog
    }

    function createHistoricChart(dataKind){
        exitFullScreen()
        statisticsChartBoxModel.append({
                                           "dataKind": dataKind,
                                           "chartTitle": dataKind,
                                           "timeFrame": -1,
                                           "timeUpdate": -1,
                                           "maxPoints": -1,
                                           "dynamic": false
                                       })
    }

    function createDynamicChart(dataKind, timeWindowSeconds, updatePeriod, maxPoints){
        exitFullScreen()
        statisticsChartBoxModel.append({
                                           "dataKind": dataKind,
                                           "chartTitle": dataKind,
                                           "timeFrame": timeWindowSeconds,
                                           "timeUpdate": updatePeriod,
                                           "maxPoints": maxPoints,
                                           "dynamic": true
                                       })
    }

    function calculateGridViewWidth(){
        mouseArea.width = (chartBoxWidth - 10) * actualBoxesPerRow
    }

    function saveCSV(
            chartboxIds,
            seriesIds,
            dataKinds,
            chartboxNames,
            labelNames)
    {
        csvDialog.chartboxIds = chartboxIds
        csvDialog.seriesIds = seriesIds
        csvDialog.dataKinds = dataKinds
        csvDialog.chartboxNames = chartboxNames
        csvDialog.labelNames = labelNames
        csvDialog.open()
    }

    function seriesSetMaxPoints(
            chartboxId,
            seriesId,
            currentSize)
    {
        seriesSetMaxPointsDialog.chartboxId = chartboxId
        seriesSetMaxPointsDialog.seriesId = seriesId
        seriesSetMaxPointsDialog.currentSize = currentSize
        seriesSetMaxPointsDialog.open()
    }

    function saveAllCSV() {
        var chartboxIds = []
        var seriesIds = []
        var dataKinds = []
        var chartboxNames = []
        var labelNames = []

        // For each Chartbox get its data and fill vectors to export each series
        for (var idx = 0; idx < gridView.count; idx++) {
            var chartboxItem = gridView.itemAtIndex(idx).statisticsChartBoxItem
            var seriesLabels = chartboxItem.chartboxSeriesLabels()
            var seriesNum = seriesLabels.length

            chartboxIds     = chartboxIds.concat(Array(seriesNum).fill(chartboxItem.chartboxId)) // not idx
            seriesIds       = seriesIds.concat([...Array(seriesNum).keys()])
            dataKinds       = dataKinds.concat(Array(seriesNum).fill(chartboxItem.dataKind))
            chartboxNames   = chartboxNames.concat(Array(seriesNum).fill(chartboxItem.chartTitle))
            labelNames      = labelNames.concat(seriesLabels)
        }

        saveCSV(
            chartboxIds,
            seriesIds,
            dataKinds,
            chartboxNames,
            labelNames)
    }

    function chartBoxFullScreen(chartBoxIdx) {
        if (!fullScreen) {
            for (var i = 0; i < gridView.count; i++) {
                gridView.itemAtIndex(i).visible = (i === chartBoxIdx)
            }
            fullScreen = true
        } else {
            exitFullScreen()
        }
        gridView.currentIndex = chartBoxIdx
    }

    function exitFullScreen() {
        fullScreen = false;
        for (var i = 0; i < gridView.count; i++) {
            gridView.itemAtIndex(i).visible = true
        }
        gridView.positionViewAtBeginning()
        gridView.currentIndex = 0
    }
}
