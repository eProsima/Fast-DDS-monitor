import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import Controller 1.0

Dialog {
    id: dialogInitMonitor
    modality: Qt.WindowModal
    title: "Init Monitor"
    standardButtons: Dialog.Ok | Dialog.Cancel

    property int simpleMonitor: -1
    property string discoveryServerMonitor: ""

    width: 400
    height: 250

    onAccepted: {
        if (monitorTab.currentIndex == 0){
            controller.init_monitor(simpleMonitor)
        }
        else{
            controller.init_monitor(discoveryServerMonitor)
        }
    }

    TabView {
        id: monitorTab
        height: parent.height
        width: parent.width
        Tab {
            id: simpleDiscoveryTab
            title: "Simple Discovery"

            ColumnLayout {
                Column {
                    spacing: 10

                    Label {
                        text: "DDS Domain <int>"
                        font.bold: true
                    }
                    SpinBox {
                        id: simpleDiscoveryAnswer
                        value: 0
                        maximumValue: 200
                    }
                }
                Button {
                    text: "Apply"
                    Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                    onClicked: {
                        simpleMonitor = simpleDiscoveryAnswer.value;
                    }
                }
            }
        }
        Tab {
            id: discoveryServerTab
            title: "Discovery Server"

            ColumnLayout {
                Column {
                    spacing: 10

                    Label {
                        text: "Discovery Server Locators"
                        font.bold: true
                    }
                    Text {
                        width: parent.width
                        text: 'Add Ip and port from each Discovery Server separated with ; i.e. 127.0.0.1:11811'
                        wrapMode: Text.WordWrap
                    }
                    TextField {
                        id: discoveryServerAnswer
                        width: parent.width
                        placeholderText: "127.0.0.1:11811;127.0.0.1:11812"
                    }
                }
                Button {
                    text: "Apply"
                    Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                    onClicked: {
                        discoveryServerMonitor = discoveryServerAnswer.text;
                    }
                }
            }
        }
    }
}
