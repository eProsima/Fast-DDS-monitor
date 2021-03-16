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
                                controller.participant_click(id)
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
                    text: guid
                    font.pixelSize: 9
                    leftPadding: 20
                }
                Text {
                    text: domain
                    font.pixelSize: 9
                    leftPadding: 20
                }
                ListView {
                    id: endpointList
                    model: participantModel.subModelFromEntityId(id)
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
                                                controller.endpoint_click(id)
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
                                    text: guid
                                    font.pixelSize: 9
                                    leftPadding: 20
                                }
                                Text {
                                    text: topic
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
