import QtQuick
import QtQuick.Controls
import Theme 1.0

Item {
    id: spyView
    property var model: userDataModel
    property string domain_id
    property string topic_id
    property string topic_name
    property bool is_active_: false
    readonly property int elements_spacing_: 10

    function start_spy() {
        if (!spyView.is_active_) {
            controller.start_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
            spyView.is_active_ = true
        }
    }

    function stop_spy() {
        if (spyView.is_active_) {
            controller.stop_topic_spy(spyView.domain_id, controller.get_name(spyView.topic_id))
            spyView.is_active_ = false
        }
    }

    function initialize(domainId, topicId, topicName) {
        stop_spy()
        domain_id = domainId
        topic_id = topicId
        topic_name = topicName
        start_spy()
    }

    Column {
        anchors.fill: parent
        spacing: elements_spacing_

        Rectangle {
            width: parent.width
            height: 40
            color: "transparent"

            Text {
                id: rowTitle
                text: (topic_name || "No Topic") + " Data"
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                anchors.leftMargin: elements_spacing_
                anchors.verticalCenter: parent.verticalCenter
            }

            Row {
                id: buttonContainer
                spacing: elements_spacing_
                anchors.right: parent.right
                anchors.rightMargin: elements_spacing_
                anchors.verticalCenter: parent.verticalCenter

                Button {
                    id: pausePlayButton
                    text: spyView.is_active_ ? "Pause" : "Play"
                    enabled: spyView.topic_id !== ""
                    onClicked: {
                        if (spyView.is_active_) {
                            spyView.stop_spy()
                        } else {
                            spyView.start_spy()
                        }
                    }
                }

                Button {
                    id: expandAllButton
                    text: "Expand All"
                    enabled: spyView.topic_id !== ""
                    onClicked: {
                        reusableTree.expandAll()
                    }
                }

                Button {
                    id: collapseAllButton
                    text: "Collapse All"
                    enabled: spyView.topic_id !== ""
                    onClicked: {
                        reusableTree.collapseAll()
                    }
                }

                Button {
                    id: copyButton
                    text: "Copy JSON"
                    enabled: spyView.topic_id !== ""
                    onClicked: {
                        if (spyView.model && spyView.model.copy_json_to_clipboard) {
                            spyView.model.copy_json_to_clipboard()
                        }
                    }
                }
            }
        }

        ReusableTreeView {
            id: reusableTree
            width: parent.width
            height: parent.height - 50
            treeModel: spyView.model
            columnSplitRatio: 0.5
            expandOnUpdate: false
            enableCopySubtree: false
        }
    }
}
