import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.2
import com.myself 1.0

Dialog {
    id: dialogInitMonitor
    title: "Init Monitor"
    standardButtons: Dialog.Ok | Dialog.Cancel

    property int domain

    onAccepted: {
        console.log(domain)
        console.log(monitorTab.getTab(0).tab1_value)

        if (monitorTab.currentIndex == 0)
            controller.init_monitor(-1)
        else
            controller.init_monitor("127:1")
        // TODO get value from simpleDiscoveryAnswer and discoveryServerAnswer
    }
//    ColumnLayout {
//        SpinBox {
//            id: simpleDiscoveryAnswer_2
//            minimumValue: 0
//            maximumValue: 200
//            // property var item_value: value
//        }
//    }

    TabView {
        id: monitorTab
        Tab {
            id: monitorSimpleDiscoveryTab
            title: "Simple Discovery"

            property var tab1_value: simpleDiscoveryAnswer.value

            ColumnLayout {
                id: simpleDiscovery
                Label {
                    text: "DDS Domain <int>"
                    font.bold: true
                }
                SpinBox {
                    id: simpleDiscoveryAnswer
                    minimumValue: 0
                    maximumValue: 200
                    onEditingFinished: {dialogInitMonitor.domain = simpleDiscoveryAnswer.value}
                    // property var item_value: value
                }
            }
        }

        Tab {
            title: "Discovery Server"
            ColumnLayout {
                id: discoveryServer
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
