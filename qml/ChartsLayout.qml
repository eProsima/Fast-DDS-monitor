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

Rectangle {
    id: chartsLayout
    Layout.fillWidth: true
    Layout.fillHeight: true

    property int boxesPerRow: 1
    property int actualBoxesPerRow: Math.min(boxesPerRow, (gridView.count === 0) ? 1 : gridView.count)
    property int chartBoxWidth: gridViewWidth / actualBoxesPerRow
    property int chartBoxHeight: Math.min(chartBoxWidth, height / actualBoxesPerRow)
    property int gridViewWidth: width < 1 ? 0 : width - 1

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
            pressAndHoldTimer.start();
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

        onWheel: {
            if (wheel.angleDelta.y > 0) {
                scrollBar.decrease()
            } else {
                scrollBar.increase()
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
            cacheBuffer: chartBoxHeight * 100

            property int firstIndexDrag: -1

            Item {
                id: container
                anchors.fill: parent
            }

            ScrollBar.vertical: ScrollBar {
                id: scrollBar
                visible: true
                hoverEnabled: true
            }
        }

        Component {
            id: widgetdelegate

            Item {
                width: gridView.cellWidth
                height: gridView.cellHeight

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

    function createHistoricChart(dataKind){
        statisticsChartBoxModel.append({
                                           "dataKind": dataKind,
                                           "chartTitle": dataKind,
                                           "timeFrame": -1,
                                           "timeUpdate": -1,
                                           "dynamic": false
                                       })
    }

    function createDynamicChart(dataKind, timeWindowSeconds, updatePeriod){
        statisticsChartBoxModel.append({
                                           "dataKind": dataKind,
                                           "chartTitle": dataKind,
                                           "timeFrame": timeWindowSeconds,
                                           "timeUpdate": updatePeriod,
                                           "dynamic": true
                                       })
    }

    function calculateGridViewWidth(){
        mouseArea.width = (chartBoxWidth - 10) * actualBoxesPerRow
    }
}

