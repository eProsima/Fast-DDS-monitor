import QtQuick 2.7
import QtQuick.Controls 2.15

MenuBar {
    id: monitorMenuBar

    Menu {
        title: qsTr("File")
        Action {
            text: qsTr("Quit")
            onTriggered: Qt.quit()
        }
    }
    Menu {
        title: qsTr("Edit")
        Action {
            text: qsTr("Init New Monitor")
            onTriggered: dialogInitMonitor.open()
        }
        Action {
            text: qsTr("Display New Data")
            onTriggered: dataKindDialog.open()
        }
    }
    Menu {
        title: qsTr("Help")
        Action {
            text: qsTr("Documentation")
        }
        Action {
            text: qsTr("Release Notes")
        }
        MenuSeparator { }
        Action {
            text: qsTr("Join Us on Twitter")
            onTriggered: Qt.openUrlExternally("https://twitter.com/EProsima")
        }
        Action {
            text: qsTr("Search Feature Requests")
            onTriggered: Qt.openUrlExternally("https://github.com/eProsima/Fast-DDS-monitor/issues")
        }
        Action {
            text: qsTr("Report Issue")
            onTriggered: Qt.openUrlExternally("https://github.com/eProsima/Fast-DDS-monitor/issues/new")
        }
        MenuSeparator { }
        Action {
            text: qsTr("About")
        }
    }

    delegate: MenuBarItem {
        id: menuBarItem

        contentItem: Text {
            text: menuBarItem.text
            font: menuBarItem.font
            opacity: enabled ? 1.0 : 0.3
            color: menuBarItem.highlighted ? "#ffffff" : "black"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 20
            implicitHeight: 20
            opacity: enabled ? 1 : 0.3
            color: menuBarItem.highlighted ? "grey" : "transparent"
        }
    }

    background: Rectangle {
        implicitWidth: 20
        implicitHeight: 20
        color: "#ffffff"

        Rectangle {
            color: "grey"
            width: parent.width
            height: 3
            anchors.bottom: parent.bottom
        }
    }
}
