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
            width: 300
            height: hostListColumn.childrenRect.height

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
                                else
                                    userList.height = userList.collapseHeightFlag;
                            }
                        }
                    }
                    Text {
                        text: hostId
                        leftPadding: 5
                    }
                }
                ListView {
                    id: userList
                    model: hostModel.subModelFromEntityId(hostId)
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
                                        text: username
                                        leftPadding: 5
                                    }
                                }
                                Text {
                                    text: userId
                                    font.pixelSize: 9
                                    leftPadding: 20
                                }
                                ListView {
                                    id: processList
                                    model: hostModel.subModelFromEntityId(
                                               hostId).subModelFromEntityId(userId)
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
                                                        color: "grey"
                                                        width: 10
                                                        height: 10
                                                    }
                                                    Text {
                                                        text: processId
                                                        leftPadding: 5
                                                    }
                                                }
                                                Text {
                                                    text: processExec
                                                    leftPadding: 20
                                                }
                                                Text {
                                                    text: processPID
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
