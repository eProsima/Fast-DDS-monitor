import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Rectangle {
    id: entityList
    Layout.fillHeight: true
    Layout.fillWidth: true

    ListView {
        id: participantList
        model: participantModel
        clip: true
        leftMargin: 5
        bottomMargin: 5
        width: parent.width
        height: parent.height
        delegate: participantListDelegate

        ScrollBar.vertical: ScrollBar { }
    }

    Component {
        id: participantListDelegate

        Item {
            id: participantItem
            width: participantList.width - participantList.leftMargin
            height: participantListColumn.childrenRect.height
            property var item_id: id

            Column {
                id: participantListColumn

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
                                if(endpointList.height === endpointList.collapseHeightFlag) {
                                    endpointList.height = 0;
                                } else {
                                    endpointList.height = endpointList.collapseHeightFlag;
                                }
                            }
                            onDoubleClicked: {
                                controller.participant_click(id)
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
                    text: guid
                    font.pixelSize: 9
                    leftPadding: 20
                }
                Label {
                    text: domain
                    font.pixelSize: 9
                    leftPadding: 20
                }
                ListView {
                    id: endpointList
                    model: participantModel.subModelFromEntityId(id)
                    property int collapseHeightFlag: childrenRect.height
                    leftMargin: 20
                    width: participantList.width - participantList.leftMargin
                    height: 0
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    delegate: endpointListDelegate
                }

                Component {
                    id: endpointListDelegate

                    Item {
                        height: endpointListColumn.childrenRect.height

                        ListView.onAdd: {
                            if(endpointList.height != 0) {
                                endpointList.height = endpointList.collapseHeightFlag;
                            }
                        }

                        Column {
                            id: endpointListColumn

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
                                            if(locatorList.height === locatorList.collapseHeightFlag) {
                                                locatorList.height = 0;
                                                endpointList.height =
                                                        endpointList.height - locatorList.collapseHeightFlag;
                                            } else {
                                                locatorList.height = locatorList.collapseHeightFlag;
                                                endpointList.height = endpointList.height + locatorList.height;
                                            }
                                        }
                                        onDoubleClicked: {
                                            controller.endpoint_click(id)
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
                                text: guid
                                font.pixelSize: 9
                                leftPadding: 20
                            }
                            Label {
                                text: topic
                                font.pixelSize: 9
                                leftPadding: 20
                            }
                            ListView {
                                id: locatorList
                                model: participantModel.subModelFromEntityId(
                                           participantItem.item_id).subModelFromEntityId(id)
                                property int collapseHeightFlag: childrenRect.height
                                leftMargin: 20
                                contentHeight: contentItem.childrenRect.height
                                width: participantList.width - participantList.leftMargin
                                height: 0
                                clip: true
                                delegate: locatorListDelegate
                            }

                            Component {
                                id: locatorListDelegate

                                Item {
                                    width: parent.width
                                    height: locatorListColumn.childrenRect.height

                                    ListView.onAdd: {
                                        if(locatorList.height != 0) {
                                            locatorList.height = locatorList.collapseHeightFlag;
                                            endpointList.height = endpointList.height + locatorList.height;
                                        }
                                    }

                                    Column {
                                        id: locatorListColumn
                                        anchors.left: parent.left
                                        anchors.right: parent.right
                                        RowLayout {
                                            Rectangle {
                                                color: "blue"
                                                width: 5; height: 5; radius: 5
                                            }
                                            Label {
                                                text: name
                                                leftPadding: 5

                                                MouseArea {
                                                    anchors.fill: parent
                                                    onDoubleClicked: {
                                                        controller.locator_click(id)
                                                    }
                                                }
                                            }
                                        }
                                        Label {
                                            text: id
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
        }
    }
}
