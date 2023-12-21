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

    MenuItem {
        text: "Change alias"
        onTriggered: changeAlias(menu.domainEntityId, menu.entityId, menu.currentAlias, menu.entityKind)
    }
    MenuItem {
        text: "View Problems"
        onTriggered: filterEntityStatusLog(menu.entityId)
    }
}
