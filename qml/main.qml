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
    title: qsTr("Fast DDS Monitor")

    Panels {
        id: panels
    }

    Controller {
        id: controller
    }

    InitMonitorDialog {
        id: dialogInitMonitor
    }

    DataKindDialog {
        id: dataKindDialog
        onCreateChart: panels.createChart(dataKind)
    }
}
