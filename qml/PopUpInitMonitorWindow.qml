import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import Controller 1.0

Dialog {
    id: dialogInitMonitor
    title: "Init Monitor"
    standardButtons: Dialog.Ok | Dialog.Cancel

    width: 400
    height: 250

    onAccepted: {
        if (monitorTab.currentIndex == 0){
            controller.init_monitor(simpleDiscoveryAnswer.value)
        }
        else{
            controller.init_monitor(discoveryServerAnswer.text)
        }
    }

    TabBar {
        id: monitorTab
        width: parent.width
        TabButton {
            text: "Simple Discovery"
        }
        TabButton {
            text: "Discovery Server"
        }
    }

    StackLayout {
        width: parent.width
        currentIndex: monitorTab.currentIndex
        anchors.fill: parent
        Item {
            Column{
                ColumnLayout {
                    Label {
                        text: "DDS Domain <int>"
                        font.bold: true
                    }
                    SpinBox {
                        id: simpleDiscoveryAnswer
                        from: 0
                        to: 200
                    }
                }
            }
        }

        Item {
            Column{
                ColumnLayout {
                    Label {
                        text: "Discovery Server Locators"
                        font.bold: true
                    }
                    Text {
                        text: "Add Ip and port from each\nDiscovery Server separated with ;\n i.e. '127.0.0.1:11811'"
                    }
                    TextField {
                        id: discoveryServerAnswer
                        placeholderText: "127.0.0.1:11811;127.0.0.1:11812"
                    }
                }
            }
        }
    }
}
