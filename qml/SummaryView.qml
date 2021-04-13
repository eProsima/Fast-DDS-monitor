import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQml.Models 2.11


Item {
    id: summary_view
    visible: true

    TreeView {
        id: summary_tree_view
        anchors.fill: parent
        model: summaryModel
        selectionMode: SelectionMode.SingleSelection
        selection: ItemSelectionModel {
            id: item_selection_model
            model: summaryModel
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

        Component.onCompleted: rightPanel.expand_all(summary_tree_view, summaryModel)

        Connections {
            target: summaryModel
            function onUpdatedData() {
                rightPanel.expand_all(summary_tree_view, summaryModel)
            }
        }
    }
}
