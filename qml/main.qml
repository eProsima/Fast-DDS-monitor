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

    Rectangle {
        anchors.fill: parent

        LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(parent.width, parent.height)
            source: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: Theme.eProsimaLightBlue }
                GradientStop { position: 1.0; color: Theme.eProsimaDarkBlue }
            }
        }

        RowLayout {
            width: parent.width * 2/3
            height: parent.height * 2/3
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 50

            ColumnLayout {

                Layout.fillHeight: true
                Layout.preferredWidth: parent.width/2

                Image {
                    Layout.minimumWidth: parent.width
                    Layout.preferredWidth: parent.width
                    Layout.maximumWidth: parent.width
                    Layout.minimumHeight: parent.width/2
                    Layout.preferredHeight: parent.width/2
                    Layout.maximumHeight: parent.width/2
                    fillMode: Image.PreserveAspectFit
                    source: "/resources/images/fastdds-monitor-logo.png"
                    Layout.alignment: Qt.AlignVCenter
                }

                Image {
                    Layout.minimumWidth: parent.width
                    Layout.preferredWidth: parent.width
                    Layout.maximumWidth: parent.width
                    Layout.minimumHeight: parent.width/2
                    Layout.preferredHeight: parent.width/2
                    Layout.maximumHeight: parent.width/2
                    fillMode: Image.PreserveAspectFit
                    source: "/resources/images/eprosima_logo_vertical_original.png"
                    Layout.alignment: Qt.AlignVCenter
                }
            }

            Rectangle {
                Layout.minimumWidth: parent.width/2
                Layout.preferredWidth: parent.width/2
                Layout.maximumWidth: parent.width/2
                Layout.minimumHeight: parent.width/10
                Layout.preferredHeight: parent.width/10
                Layout.maximumHeight: parent.width/10
                radius: height * 0.65
                color: Theme.whiteSmoke

                Text {
                    id: initMonitorLabel
                    text: "Init Monitor"
                    width: parent.width
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font.pointSize: 60
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        mainApplicationView.visible = true
                        mainStartView.visible = false
                    }
                }

                Item {
                    anchors.fill: parent;

                    Rectangle {
                        id: btnShadow
                        antialiasing: true
                        anchors.margins: -3
                        anchors.fill: parent
                        radius: (width / 2)
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
                        radius: (width / 2)
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
            }
        }
    }

    MainApplicationView {
        id: mainApplicationView
        visible: false
    }
}
