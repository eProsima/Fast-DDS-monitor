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

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1 as QLP
import QtGraphicalEffects 1.15
import Theme 1.0

Rectangle {
    id: statisticsChartBox
    border {
        width: 2
        color: "#09487e"
    }

    property string chartTitle
    property int index
    property bool visibility: true

    Component.onCompleted: displayStatisticsDialog.open();

    ColumnLayout {

        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 0
        visible: visibility

        Rectangle {
            id: chartBoxTitle
            width: statisticsChartBox.width
            height: statisticsChartBox.height/20 + controlPanel.contentHeight
            color: "#09487e"

            ColumnLayout {
                Layout.alignment: Qt.AlignCenter
                spacing: 0

                Rectangle {
                    id: chartBoxInnerTitle
                    width: statisticsChartBox.width
                    height: statisticsChartBox.height/20
                    color: "#09487e"

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
                            source: "/resources/images/cross.svg"
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            dye: true
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
                    Layout.alignment: Qt.AlignCenter | Qt.AlignBottom
                    implicitWidth: statisticsChartBox.width - (statisticsChartBox.border.width*2)

                    signal addSeries(
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
                    signal clearChart()

                    onAddSeries: statisticsChartView.addSeries(
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
                    onClearChart: statisticsChartView.clearChart();

                    Menu {
                        title: "Chart"
                        Action {
                            text: "Reset zoom"
                            Component.onCompleted: {
                                triggered.connect(statisticsChartView.resetChartViewZoom)
                            }
                        }
                        Action {
                            text: "Clear chart"
                            onTriggered: controlPanel.clearChart();
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
                            onTriggered: displayStatisticsDialog.open();
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
                }
            }
        }

        StatisticsChartView {
            id: statisticsChartView
            Layout.alignment: Qt.AlignCenter
            height: statisticsChartBox.height - 2*chartBoxTitle.height
            width: statisticsChartBox.width - (statisticsChartBox.border.width*2)
            onSeriesAdded: customLegend.addLeyend(series.name, series.color)
            onSeriesRemoved: customLegend.removeLeyend(series.index)
        }

        CustomLegend {
            id: customLegend
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            height: statisticsChartBox.height - chartBoxTitle.height -
                    statisticsChartView.height - statisticsChartBox.border.width
            width: statisticsChartBox.width - (statisticsChartBox.border.width*2)
            onSeriesNameUpdated: statisticsChartView.updateSeriesName(seriesIndex, newSeriesName)
            onSeriesColorUpdated: statisticsChartView.updateSeriesColor(seriesIndex, newSeriesColor)
            onSeriesHidden: statisticsChartView.hideSeries(seriesIndex)
            onSeriesDisplayed: statisticsChartView.displaySeries(seriesIndex)
            onSeriesRemoved: statisticsChartView.removeSeries(statisticsChartView.series(seriesIndex))
        }
    }

    Label {
        text: chartTitle
        color: "white"
        visible: !visibility
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    DisplayStatisticsDialog {
        id: displayStatisticsDialog
    }
}
