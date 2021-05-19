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

import QtQuick 2.15
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import Theme 1.0

ApplicationWindow {
    id: mainStartView
    visible: true
    width: 1600
    height: 900
    title: qsTr("Fast DDS Monitor")

    ColumnLayout {
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
                width: parent.width/1.2
                height: parent.height/1.2
                fillMode: Image.PreserveAspectFit
                source: "/resources/images/fastdds-monitor-logo.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
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
                    }
                    Rectangle {
                        id: mask
                        color: "transparent"
                        radius: parent.parent.radius
                        antialiasing: true
                        border.width: 3
                        border.color: "black"
                        anchors.fill: btnShadow
                    }
                    OpacityMask {
                        opacity: 0.65
                        anchors.fill: btnShadow
                        source: ShaderEffectSource {
                            sourceItem: btnShadow
                            hideSource: true
                        }
                        maskSource: ShaderEffectSource {
                            sourceItem: mask
                            hideSource: true
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        mainApplicationView.visible = true
                        mainStartView.visible = false
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

    MainApplicationView {
        id: mainApplicationView
        visible: false
    }
}
