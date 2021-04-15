import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

Item {
    id: issueView
    visible: true

    TreeView {
        id: issue_tree_view
        anchors.fill: parent
        model: issueModel
        itemDelegate: Item {
            Text {
                anchors.fill: parent
                elide: styleData.elideMode
                text: styleData.value
            }
        }

        TableViewColumn {
            width: parent.width / 2
            role: "name"
            title: "Name"
        }

        TableViewColumn {
            width: parent.width / 2
            role: "value"
            title: "Value"
        }


        Component.onCompleted: rightPanel.expand_all(issue_tree_view, issueModel)

        Connections {
            target: issueModel
            function onUpdatedData() {
                rightPanel.expand_all(issue_tree_view, issueModel)
            }
        }
    }
}