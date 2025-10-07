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

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQml.Models
import Theme 1.0

/*
    Object to create the sidebar for shortcuts to DDS entity lists and information, alerts,
    monitor status and issues. The accesses are arranged in a list containing the icons of each drop-down.
    Each item in the list displays its corresponding display sidebar.
 */

Rectangle {
    id: iconsVBar
    color: Theme.grey

    signal iconClicked(int icon)

    property int selected: 0

    // List of sidebar icons
    ListModel {
        id: iconsVBarModel
        ListElement {
            icon: "explorer"
        }
        ListElement {
            icon: "alert"
        }
        ListElement {
            icon: "status"
        }
        ListElement {
            icon: "issues"
        }
        ListElement {
            icon: ""
        }
    }

    // List view of the icons list
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

                // Selected icon view effect
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
                    name: icon
                    size: parent.width - 15
                    color: (selected == index) ? "grey" :
                           ma.containsMouse ? "grey" : "white"
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

    // Function to update the currently displayed sidebar.
    function updateSelectedSubPanel(panelIdx, show) {
        if (show) {
            selected = panelIdx
        } else {
            selected = -1
        }
    }
}
