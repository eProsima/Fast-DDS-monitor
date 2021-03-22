import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Item {
    id: logicalViewEntityList

    ListView {
        id: hostList
        model: hostModel
        delegate: listdelegate
        anchors.fill: parent
    }

    Component {
        id: listdelegate

        Item {
            id: hostItem
            width: 300
            height: hostListColumn.childrenRect.height
            property var item_id: id

            Column {
                id: hostListColumn
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
                                if(userList.height === userList.collapseHeightFlag) {
                                    userList.height = 0;
                                }
                                else{
                                    userList.height = userList.collapseHeightFlag;
                                }
                            }
                        }
                    }
                    Text {
                        text: name
                        leftPadding: 5
                    }
                    Rectangle {
                        color: "red"
                        width: 10
                        height: 10

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                controller.host_click(id)
                            }
                        }
                    }
                }
                Text {
                    text: id
                    font.pixelSize: 9
                    leftPadding: 20
                }
                ListView {
                    id: userList
                    model: hostModel.subModelFromEntityId(id)
                    property int collapseHeightFlag: childrenRect.height
                    leftMargin: 20
                    delegate: Component {
                        Item {
                            width: parent.width
                            height: userListColumn.childrenRect.height

                            Column {
                                id: userListColumn
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
                                                if(processList.height === processList.collapseHeightFlag) {
                                                    processList.height = 0;
                                                    userList.height =
                                                            userList.height - processList.collapseHeightFlag;
                                                }
                                                else
                                                {
                                                    processList.height = processList.collapseHeightFlag;
                                                    userList.height = userList.height + processList.height;
                                                }
                                            }
                                        }
                                    }
                                    Text {
                                        text: name
                                        leftPadding: 5
                                    }
                                    Rectangle {
                                        color: "red"
                                        width: 10
                                        height: 10

                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                controller.host_click(id)
                                            }
                                        }
                                    }
                                }
                                Text {
                                    text: id
                                    font.pixelSize: 9
                                    leftPadding: 20
                                }
                                ListView {
                                    id: processList
                                    model: hostModel.subModelFromEntityId(
                                               hostItem.item_id).subModelFromEntityId(id)
                                    property int collapseHeightFlag: childrenRect.height
                                    leftMargin: 20
                                    delegate: Component {
                                        Item {
                                            width: parent.width
                                            height: processListColumn.childrenRect.height

                                            Column {
                                                id: processListColumn
                                                anchors.left: parent.left
                                                anchors.right: parent.right
                                                RowLayout {
                                                    Rectangle {
                                                        color: "blue"
                                                        width: 10
                                                        height: 10
                                                    }
                                                    Text {
                                                        text: name
                                                        leftPadding: 5
                                                    }
                                                    Rectangle {
                                                        color: "red"
                                                        width: 10
                                                        height: 10

                                                        MouseArea {
                                                            anchors.fill: parent
                                                            onClicked: {
                                                                controller.host_click(id)
                                                            }
                                                        }
                                                    }
                                                }
                                                Text {
                                                    text: id
                                                    font.pixelSize: 9
                                                    leftPadding: 20
                                                }
                                                Text {
                                                    text: processPID
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
