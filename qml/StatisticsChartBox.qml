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
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15
import Theme 1.0

Rectangle {
    id: statisticsChartBox

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

    Component.onCompleted: {
        if (isDynamic){
            chartboxId = dynamicData.add_chartbox(dataKind, currentDate, timeWindow, updatePeriod)
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

            Label {
                id: statisticsChartBoxLabel
                text: chartTitle
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                height: parent.height - parent.height/3
                width: parent.height - parent.height/3
                radius: parent.height - parent.height/3
                anchors.right: parent.right
                anchors.rightMargin: parent.height/3
                anchors.verticalCenter: parent.verticalCenter
                color: "transparent"

                IconSVG {
                    name: "cross"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
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

        MenuBar {
            id: controlPanel
            Layout.fillWidth: true

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
                string statisticKind)
            signal clearChart()
            signal dynamicPause()
            signal dynamicContinue()

            onAddHistoricSeries: statisticsChartViewLoader.item.addHistoricSeries(
                                    dataKind,
                                    seriesLabel,
                                    sourceEntityId,
                                    targetEntityId,
                                    bins,
                                    startTime,
                                    startTimeDefault,
                                    endTime,
                                    endTimeDefault,
                                    statisticKind);
            onAddDynamicSeries: statisticsChartViewLoader.item.addDynamicSeries(
                                    seriesLabel,
                                    sourceEntityId,
                                    targetEntityId,
                                    statisticKind);
            onClearChart: statisticsChartViewLoader.item.clearChart();
            onDynamicContinue: statisticsChartViewLoader.item.dynamicContinue();
            onDynamicPause: statisticsChartViewLoader.item.dynamicPause();

            Menu {
                title: "Chart"
                Action {
                    text: "Reset zoom"
                    Component.onCompleted: {
                        triggered.connect(statisticsChartViewLoader.item.resetChartViewZoom)
                    }
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

            Rectangle {
                property int size: 30

                height: size
                width: size
                radius: size/10

                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: size/4
                anchors.topMargin: size/4

                color: playMouseArea.containsMouse ? Theme.lightGrey : "transparent"
                visible: isDynamic

                IconSVG {
                    size: parent.size*3/4
                    name: running ? "pause" : "play"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: running ? "eProsimaLightBlue" : "green"
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
            }
        }

        CustomLegend {
            id: customLegend
            Layout.fillWidth: true
            Layout.margins: 10
            onSeriesNameUpdated: statisticsChartViewLoader.item.updateSeriesName(seriesIndex, newSeriesName)
            onSeriesColorUpdated: statisticsChartViewLoader.item.updateSeriesColor(seriesIndex, newSeriesColor)
            onSeriesHidden: statisticsChartViewLoader.item.hideSeries(seriesIndex)
            onSeriesDisplayed: statisticsChartViewLoader.item.displaySeries(seriesIndex)
            onSeriesRemoved: {
                    statisticsChartViewLoader.item.removeSeries(statisticsChartViewLoader.item.series(seriesIndex))
                    removeLeyend(seriesIndex)
                    if(isDynamic) {
                        dynamicData.delete_series(chartboxId, seriesIndex)
                        statisticsChartViewLoader.item.customRemoveSeries(seriesIndex)
                    } else {
                        historicData.delete_series(chartboxId, seriesIndex)
                        statisticsChartViewLoader.item.customRemoveSeries(seriesIndex)
                    }

            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
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

    function toMsecsSinceEpoch(date) {
        return date.getTime().valueOf();
    }
}
