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
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Rectangle {
    id: statisticsChartBox
    border {
        width: 2
        color: "#09487e"
    }

    property string chartTitle
    property int index
    property bool visibility: true

    ColumnLayout {

        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 0
        visible: visibility

        Rectangle {
            id: chartBoxTitle
            width: statisticsChartBox.width
            height: 3 * statisticsChartBox.height/20
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
                }

                Rectangle {
                    Layout.alignment: Qt.AlignCenter
                    color: "#697d91"
                    width: statisticsChartBox.width - (statisticsChartBox.border.width*2)
                    height: statisticsChartBox.height/10

                    RowLayout {
                        id: controlPanel
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 8

                        signal addSeries(
                            string dataKind,
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
                                         sourceEntityId,
                                         targetEntityId,
                                         bins,
                                         startTime,
                                         startTimeDefault,
                                         endTime,
                                         endTimeDefault,
                                         statisticKind);
                        onClearChart: statisticsChartView.clearChart();

                        Button {
                            text: "Add series"
                            onClicked: {
                                displayStatisticsDialog.open();
                            }
                        }

                        Button {
                            text: "Clear chart"
                            onClicked: controlPanel.clearChart();
                        }

                        Button {
                            text: "Remove chart"
                            onClicked: {
                                statisticsChartBoxModel.remove(index)
                                statisticsChartBox.destroy()
                            }
                        }
                    }
                }
            }
        }



        StatisticsChartView {
            id: statisticsChartView
            Layout.fillWidth: true
            Layout.preferredHeight: statisticsChartBox.height - (3*statisticsChartBox.height/20)
            Layout.alignment: Qt.AlignTop | Qt.AlignCenter
        }

        DisplayStatisticsDialog {
            id: displayStatisticsDialog
        }
    }

    Label {
        text: chartTitle
        color: "white"
        visible: !visibility
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
