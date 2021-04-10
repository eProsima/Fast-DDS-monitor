import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Rectangle {
    id: logicalView

    ListView {
        id: domainList
        model: domainModel
        clip: true
        leftMargin: 5
        bottomMargin: 5
        width: parent.width
        height: parent.height
        delegate: domainListDelegate
    }

    Component {
        id: domainListDelegate

        Item {
            id: domainItem
            width: domainList.width - domainList.leftMargin
            height: domainListColumn.childrenRect.height
            property var item_id: id

            Column {
                id: domainListColumn

                RowLayout {
                    Rectangle {
                        color: "grey"
                        width: 5; height: 5; radius: 5
                    }
                    Label {
                        text: name
                        leftPadding: 5

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(topicList.height === topicList.collapseHeightFlag) {
                                    topicList.height = 0;
                                }
                                else {
                                    topicList.height = topicList.collapseHeightFlag;
                                }
                            }
                            onDoubleClicked: {
                                controller.domain_click(id)
                            }
                        }
                    }
                }
                Label {
                    text: id
                    font.pixelSize: 9
                    leftPadding: 20
                }
                ListView {
                    id: topicList
                    model: domainModel.subModelFromEntityId(id)
                    property int collapseHeightFlag: childrenRect.height
                    leftMargin: 20
                    width: domainList.width - domainList.leftMargin
                    height: 0
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AlwaysOn
                    }
                    delegate: topicListDelegate
                }

                Component {
                    id: topicListDelegate

                    Item {
                        height: topicListColumn.childrenRect.height

                        Column {
                            id: topicListColumn

                            RowLayout {
                                Rectangle {
                                    color: "grey"
                                    width: 5; height: 5; radius: 5
                                }
                                Label {
                                    text: name
                                    leftPadding: 5

                                    MouseArea {
                                        anchors.fill: parent
                                        onDoubleClicked: {
                                            controller.topic_click(id)
                                        }
                                    }
                                }
                            }
                            Label {
                                text: id
                                font.pixelSize: 9
                                leftPadding: 20
                            }
                            Label {
                                text: type
                                font.pixelSize: 9
                                leftPadding: 20
                            }
                        }
                    }
                }
            }
        }
    }
}
