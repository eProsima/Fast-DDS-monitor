import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQml.Models 2.11

Item {
    id: qos_view
    visible: true

    TreeView {
        id: qos_tree_view
        anchors.fill: parent
        model: qosModel
        selectionMode: SelectionMode.SingleSelection
        selection: ItemSelectionModel {
            id: item_selection_model
            model: qosModel
        }
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

        Component.onCompleted: rightPanel.expand_all(qos_tree_view, qosModel)

        Connections {
            target: qosModel
            function onUpdatedData() {
                rightPanel.expand_all(qos_tree_view, qosModel)
            }
        }
    }
}
