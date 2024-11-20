import QtQuick 2.15
import QtQuick.Controls 2.15
import Theme 1.0

/*
    Menu containing the possible actions that can be performed on any DDS, physical and logical entity.
 */


Menu {
    id: entitiesMenu
    property string domainEntityId: ""
    property string entityId: ""
    property string currentAlias: ""
    property string entityKind: ""
    property string showGraphButtonName: ""  

    signal changeAlias(string domainEntityId, string entityId, string currentAlias, string entityKind)
    signal filterEntityStatusLog(string entityId)
    signal openTopicView(string domainEntityId, string domainId, string topicId)
    
    //////////////////
    // Menu options //
    //////////////////

    Component {
        id: changeAlias
        
        MenuItem {
            text: "Change alias"
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onEntered: parent.highlighted = true
                onExited: parent.highlighted = false
                onPressed: {
                    entitiesMenu.changeAlias(entitiesMenu.domainEntityId, entitiesMenu.entityId, entitiesMenu.currentAlias, entitiesMenu.entityKind)
                    entitiesMenu.close()
                }
            }
            Component.onCompleted: highlighted = false
        }
    }

    Component {
        id: viewProblems

        MenuItem {
            text: "View Problems"
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onEntered: parent.highlighted = true
                onExited: parent.highlighted = false
                onPressed: {
                    entitiesMenu.filterEntityStatusLog(entitiesMenu.entityId)
                    entitiesMenu.close()
                }
            }
            Component.onCompleted: highlighted = false
        }
    }

    Component {
        id: showGraph

        MenuItem {
            text: entitiesMenu.showGraphButtonName
            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onEntered: parent.highlighted = true
                onExited: parent.highlighted = false
                onPressed: {
                    let domain = controller.get_name(entitiesMenu.domainEntityId)
                    let topicId = controller.get_endpoint_topic_id(entityId)
                    entitiesMenu.openTopicView(entitiesMenu.domainEntityId, domain, topicId)
                    entitiesMenu.close()
                }
            }
            Component.onCompleted: highlighted = false
        }
    }

    // Print menu options depending on the entity kind
    ListModel {
        id: entityModel
    }
    
    Repeater {
        model: entityModel
        delegate: Loader {
            sourceComponent: available ? option : null
        }    
    }

    // Update model if some property change implies graphic changes in UI
    onEntityKindChanged: updateEntityModel()
    onShowGraphButtonNameChanged: updateEntityModel()

    function updateEntityModel() {
        entityModel.clear()
        entityModel.append({"available": entitiesMenu.entityKind === "DataWriter" || entitiesMenu.entityKind === "DataReader", "option": showGraph})
        entityModel.append({"available": true, "option": changeAlias})
        entityModel.append({"available": true, "option": viewProblems})
    }
}
