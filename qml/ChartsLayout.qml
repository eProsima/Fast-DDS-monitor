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
        onPressAndHold: {
            gridView.firstIndexDrag = gridView.indexAt(mouseX, mouseY)
        }
        onReleased: {
            if (gridView.firstIndexDrag != -1)
                statisticsChartBoxModel.move(gridView.firstIndexDrag, gridView.indexAt(mouseX, mouseY), 1)
            gridView.firstIndexDrag = -1
        }

        Component {
            id: widgetdelegate
            Item {
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

        GridView {
            property int firstIndexDrag: -1

            id: gridView
            x: 0; y: 0
            interactive: false

            anchors.fill: parent
            cellWidth: 500; cellHeight: 500;

            model: statisticsChartBoxModel
            delegate: widgetdelegate

            Item {
                id: container
                anchors.fill: parent
            }
        }
    }
    function createChart(dataKind){
        statisticsChartBoxModel.append({"dataKind": dataKind})
    }
}

