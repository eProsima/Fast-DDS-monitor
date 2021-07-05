import QtQuick 2.15
import QtQuick.Controls 2.15
import Theme 1.0

/*
    Menu containing the possible actions that can be performed on any DDS, physical and logical entity.
 */
Menu {
    id: entitiesMenu
    property string entityId: ""
    property string currentAlias: ""
    property string entityKind: ""

    MenuItem {
        text: "Change alias"
        onTriggered: changeAlias(menu.entityId, menu.currentAlias, menu.entityKind)
    }
}
