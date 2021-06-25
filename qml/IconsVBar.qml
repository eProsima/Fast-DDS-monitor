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
    id: iconsVBar
    color: Theme.grey

    signal iconClicked(int icon)

    property int selected: 0

    ListModel {
        id: iconsVBarModel
        ListElement {
            icon: "/resources/images/explorer.svg"
        }
        ListElement {
            icon: "/resources/images/status.svg"
        }
        ListElement {
            icon: "/resources/images/issues.svg"
        }
    }

    ListView {
        id: iconsVBarListView
        anchors.fill: parent
        model: iconsVBarModel
        delegate: iconsVBarViewDelegate
        clip: true
    }

    Component {
        id: iconsVBarViewDelegate
        Item {
            width: iconsVBarListView.width
            height: width

            Rectangle {
                anchors.fill: parent
                height: parent.width
                color: (selected == index) ? "white" :
                       ma.containsMouse ? Theme.lightGrey : Theme.grey

                IconSVG {
                    id: explorerIcon
                    source: icon
                    size: parent.width - 15
                    dye: true
                    color: (selected == index) ? Theme.grey :
                           ma.containsMouse ? Theme.grey : "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                }

                MouseArea {
                    id: ma
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: iconClicked(index)
                }

                Rectangle {
                    visible: (selected == index) ? true : false
                    color: Theme.eProsimaLightBlue
                    height: parent.height
                    width: 3
                    anchors.left: parent.left
                }
            }
        }
    }

    function updateSelectedSubPanel(panelIdx, show) {
        if (show) {
            selected = panelIdx
        } else {
            selected = -1
        }
    }
}
