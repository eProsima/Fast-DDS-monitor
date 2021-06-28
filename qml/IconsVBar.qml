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
        ListElement {
            icon: ""
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
                color: {
                    if (selected == index) {
                        return "white"
                    } else if (((selected + 1) == index) || ((selected - 1) == index)) {
                        return "transparent"
                    } else {
                        if (ma.containsMouse) {
                            return Theme.lightGrey
                        } else {
                            return "transparent"
                        }
                    }
                }

                Rectangle {
                    anchors.fill: parent
                    visible: (((selected + 1) == index) || ((selected - 1) == index))
                    color: "white"

                    Rectangle {
                        height: parent.height/2
                        width: parent.width
                        anchors.bottom: parent.bottom
                        visible: ((selected + 1) == index)
                        color: (ma.containsMouse) ? Theme.lightGrey : Theme.grey
                    }

                    Rectangle {
                        height: parent.height/2
                        width: parent.width
                        anchors.top: parent.top
                        visible: ((selected - 1) == index)
                        color: (ma.containsMouse) ? Theme.lightGrey : Theme.grey
                    }

                    Rectangle {
                        height: parent.height
                        width: parent.width/2
                        anchors.left: parent.left
                        color: (ma.containsMouse) ? Theme.lightGrey : Theme.grey
                    }

                    Rectangle {
                        anchors.fill: parent
                        radius: 7
                        color: (ma.containsMouse) ? Theme.lightGrey : Theme.grey
                    }
                }

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
                    enabled: (index != (iconsVBarModel.count -1))
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
