import QtQuick 2.12
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import Controller 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1200
    height: 675
    title: qsTr("Hello World")

    TabView {
        anchors.fill: parent

        Tab {
            title: "Panels"
            Panels {}
        }

        Tab {
            title: "Testing"
            Testing {}
        }
    }

    Controller {
        id: controller
    }

    InitMonitorDialog {
        id: dialogInitMonitor
    }

    DisplayStatisticsDialog {
        id: displayStatisticsDialog
    }
}
