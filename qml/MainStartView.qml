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

import QtQuick 6.10
import QtQuick.Layouts 6.10
import QtQuick.Window 6.10
import QtQuick.Controls 6.10
import QtQuick.Effects 6.10

import Theme 1.0

ColumnLayout {
    id: mainStartView
    anchors.fill: parent
    spacing: 0

    Rectangle {
        id: upperRect
        Layout.minimumWidth: parent.width
        Layout.preferredWidth: parent.width
        Layout.maximumWidth: parent.width
        Layout.minimumHeight: parent.height/2
        Layout.preferredHeight: parent.height/2
        Layout.maximumHeight: parent.height/2
        color: "white"

        Image {
            width: parent.width
            height: parent.height/0.9
            fillMode: Image.PreserveAspectFit
            source: "/resources/images/fastdds-monitor-logo.png"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -parent.height/4
        }

        Image {
            width: parent.width/4.5
            height: parent.height/4.5
            fillMode: Image.PreserveAspectFit
            source: "/resources/images/eprosima_logo_horizontal.png"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 20
        }
    }

    Rectangle {
        id: bottomRect
        Layout.minimumWidth: parent.width
        Layout.preferredWidth: parent.width
        Layout.maximumWidth: parent.width
        Layout.fillHeight: true
        color: Theme.eProsimaDarkBlue

        Rectangle {
            width: parent.width/2.5
            height: parent.height/4
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: parent.height/5
            radius: height * 0.2

            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "white"
                }
                GradientStop {
                    position: 0.5
                    color: Theme.lightGrey
                }
                GradientStop {
                    position: 1.0
                    color: Theme.grey
                }
            }

            Rectangle {
                width: parent.width/1.2
                height: parent.height/1.5
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"

                Text {
                    id: initMonitorLabel
                    text: "Start monitoring!"
                    width: parent.width
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font.pointSize: 60
                    color: Theme.eProsimaDarkBlue
                }
            }

            Item {
                anchors.fill: parent;
                
                Rectangle {
                    id: btnShadow
                    antialiasing: true
                    anchors.margins: -2
                    anchors.fill: parent
                    radius: parent.parent.radius
                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: "white"
                        }
                        GradientStop {
                            position: 0.5
                            color: "transparent"
                        }
                        GradientStop {
                            position: 1.0
                            color: "black"
                        }
                    }
                    
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        maskEnabled: true
                        maskSource: mask
                        opacity: 0.65
                    }
                }
                
                Rectangle {
                    id: mask
                    color: "transparent"
                    radius: parent.parent.radius
                    antialiasing: true
                    border.width: 3
                    border.color: "black"
                    anchors.fill: btnShadow
                    visible: false
                }
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor

                onClicked: {
                    mainApplicationView.startMonitoring()
                }
            }
        }

        Rectangle {
            width: parent.width/1.2
            height: parent.height/2.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            color: "transparent"

            Text {
                id: descriptionLabel
                text: "Monitor and view data charts on a vast range of different metrics in order to\noptimize and control data communications with Fast DDS."
                width: parent.width
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                fontSizeMode: Text.Fit
                minimumPixelSize: 2
                font.pointSize: 30
                color: "white"
            }
        }
    }
}
