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
import QtCharts 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: legend

    property int itemWidth: legend.width/2
    property int itemHeight: 20

    property int seriesCount: 0
    property variant seriesNames: []
    property variant seriesColors: []

    GridView {
        id: gridView
        anchors.fill: parent
        cellWidth: itemWidth
        cellHeight: itemHeight
        model: seriesCount
        delegate: legendDelegate
        clip: true
    }

    Component {
        id: legendDelegate
        Rectangle {
            id: rect
            implicitWidth: gridView.cellWidth
            implicitHeight: gridView.cellHeight

            property string name: seriesNames[index]
            property color markerColor: seriesColors[index]

            RowLayout {
                spacing: 5
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                Rectangle {
                    id: marker
                    width: 10; height: 10; radius: 10
                    color: markerColor
                }
                Label {
                    id: label
                    text: name
                }
            }
        }
    }

    function addLeyend(name, color) {
        var names = seriesNames;
        names[seriesCount] = name;
        seriesNames = names;

        var colors = seriesColors;
        colors[seriesCount] = color;
        seriesColors = colors;

        seriesCount++;
    }
}
