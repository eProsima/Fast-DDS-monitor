import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Item {
    id: logicalView

    ListView {
        id: domainList
        model: domainModel
        delegate: listdelegate
        anchors.fill: parent
    }

    Component {
        id: listdelegate

        Item {
            id: domainItem
            width: 300
            height: domainListColumn.childrenRect.height
            property var item_id: id

            Column {
                id: domainListColumn
                anchors.left: parent.left
                anchors.right: parent.right
                RowLayout {
                    Rectangle {
                        color: "grey"
                        width: 10
                        height: 10

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(topicList.height === topicList.collapseHeightFlag) {
                                    topicList.height = 0;
                                }
                                else
                                    topicList.height = topicList.collapseHeightFlag;
                            }
                        }
                    }
                    Text {
                        text: name
                        leftPadding: 5
                    }
                }
                Text {
                    text: id
                    font.pixelSize: 9
                    leftPadding: 20
                }
                ListView {
                    id: topicList
                    model: domainModel.subModelFromEntityId(id)
                    property int collapseHeightFlag: childrenRect.height
                    leftMargin: 20
                    delegate: Component {
                        Item {
                            width: parent.width
                            height: topicListColumn.childrenRect.height

                            Column {
                                id: topicListColumn
                                anchors.left: parent.left
                                anchors.right: parent.right
                                RowLayout {
                                    Rectangle {
                                        color: "grey"
                                        width: 10
                                        height: 10
                                    }
                                    Text {
                                        text: name
                                        leftPadding: 5
                                    }
                                }
                                Text {
                                    text: id
                                    font.pixelSize: 9
                                    leftPadding: 20
                                }
                                Text {
                                    text: type
                                    font.pixelSize: 9
                                    leftPadding: 20
                                }
                            }
                        }
                    }
                    contentHeight: contentItem.childrenRect.height
                    height: 0
                    anchors.left: parent.left
                    anchors.right: parent.right
                    clip: true
                }
            }
        }
    }
}
