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
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Dialog {
    id: dialogInitMonitor
    modal: false
    title: "Init Monitor"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property int simpleMonitor: -1
    property string discoveryServerMonitor: ""

    onAccepted: {
        if (monitorTab.currentIndex == 0){
            controller.init_monitor(simpleDiscoveryAnswer.value)
        }
        else{
            controller.init_monitor(discoveryServerAnswer.text)
        }
    }

    ColumnLayout {
        TabBar {
            id: monitorTab
            width: parent.width
            TabButton {
                id: simpleDiscoveryTab
                text: "Simple Discovery"
            }
            TabButton {
                id: discoveryServerTab
                text: "Discovery Server"
            }
        }

        StackLayout {
            id: monitorStack
            currentIndex: monitorTab.currentIndex
            width: parent.width
            Layout.alignment: Qt.AlignTop | Qt.AlignCenter
            Layout.fillHeight: true

            ColumnLayout {
                Layout.topMargin: 50

                Label {
                    text: "DDS Domain: "
                }
                SpinBox {
                    id: simpleDiscoveryAnswer
                    editable: true
                    value: 0
                    from: 0
                    to: 999
                    Layout.alignment: Qt.AlignTop
                    Keys.onReturnPressed: dialogInitMonitor.accept()
                }
            }

            ColumnLayout {
                Layout.topMargin: 20
                Column {
                    spacing: 10

                    Label {
                        text: "Discovery Server Locators"
                        font.bold: true
                    }
                    Label {
                        text: 'Add Ip and port from each Discovery Server separated with ; i.e. 127.0.0.1:11811'
                        width: monitorStack.width
                        wrapMode: Text.WordWrap
                    }
                    TextField {
                        id: discoveryServerAnswer
                        width: parent.width
                        placeholderText: "127.0.0.1:11811;127.0.0.1:11812"
                        Keys.onReturnPressed: dialogInitMonitor.accept()
                    }
                }
            }
        }
    }
}
