import QtQuick 2.12
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: window
    visible: true
    width: 1600
    height: 900
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
}
