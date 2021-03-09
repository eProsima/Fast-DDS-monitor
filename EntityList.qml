import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Item {
    id: logicalViewEntityList

    ListView {
        id: participantList
        model: participantModel
        delegate: listdelegate
        anchors.fill: parent
    }

    Component {
        id: listdelegate

        Item {
            width: 300
            height: participantListColumn.childrenRect.height

            Column {
                id: participantListColumn
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
                                if(endpointList.height === endpointList.collapseHeightFlag) {
                                    endpointList.height = 0;
                                }
                                else
                                    endpointList.height = endpointList.collapseHeightFlag;
                            }
                        }
                    }
                    Text {
                        text: participantName
                        leftPadding: 5
                    }
                }
                Text {
                    text: participantGuid
                    font.pixelSize: 9
                    leftPadding: 20
                }
                ListView {
                    id: endpointList
                    model: participantModel.subModelFromEntityId(participantGuid)
                    property int collapseHeightFlag: childrenRect.height
                    leftMargin: 20
                    delegate: Component {
                        Item {
                            width: parent.width
                            height: endpointListColumn.childrenRect.height

                            Column {
                                id: endpointListColumn
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
                                                    endpointList.height = endpointList.height - topicList.collapseHeightFlag;
                                                }
                                                else
                                                {
                                                    topicList.height = topicList.collapseHeightFlag;
                                                    endpointList.height = endpointList.height + topicList.height;
                                                }
                                            }
                                        }
                                    }
                                    Text {
                                        text: endpointType
                                        leftPadding: 5
                                    }
                                }
                                Text {
                                    text: endpointGuid
                                    font.pixelSize: 9
                                    leftPadding: 20
                                }
                                ListView {
                                    id: topicList
                                    model: participantModel.subModelFromEntityId(
                                               participantGuid).subModelFromEntityId(endpointGuid)
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
                                                        text: topicName
                                                        leftPadding: 5
                                                    }
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
