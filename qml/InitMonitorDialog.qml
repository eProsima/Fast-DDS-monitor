import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import Controller 1.0

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
                    value: 0
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
