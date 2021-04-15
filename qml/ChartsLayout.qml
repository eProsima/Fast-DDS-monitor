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

Rectangle {
    id: chartsLayout
    Layout.fillWidth: true
    Layout.fillHeight: true

    ListModel {
        id: statisticsChartBoxModel
    }

    MouseArea {
        id: coords
        anchors.fill: parent
        enabled: true
        onPressAndHold: {
            gridView.firstIndexDrag = gridView.indexAt(mouseX, mouseY + gridView.contentY)
        }
        onReleased: {
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

        GridView {
            id: gridView
            anchors.fill: parent
            cellWidth: 500
            cellHeight: 500
            interactive: false
            model: statisticsChartBoxModel
            delegate: widgetdelegate

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
                property int indexOfThisDelegate: index
                width: gridView.cellWidth; height: gridView.cellHeight
                StatisticsChartBox {
                    id: statisticsChartBox
                    chartTitle: dataKind
                    index: model.index
                    state: "inactive"
                    anchors.centerIn: parent
                    width: gridView.cellWidth - 10; height: gridView.cellHeight - 10
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
                            color: "#09487e"
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
                            x: coords.mouseX - statisticsChartBox.width/2
                        }
                        PropertyChanges {
                            target: statisticsChartBox
                            y: coords.mouseY - statisticsChartBox.height/10
                        }
                    }
                ]
            }
        }
    }

    function createChart(dataKind){
        statisticsChartBoxModel.append({"dataKind": dataKind})
    }
}

