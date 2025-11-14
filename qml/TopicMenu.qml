// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

import QtQuick 2.15
import QtQuick.Controls 2.15
import Theme 1.0

/*
    Menu containing the possible actions that can be performed on topic entities.
 */
Menu {
    id: topicMenu
    property string domainEntityId: ""
    property string domainId: ""
    property string entityId: ""
    property string currentAlias: ""
    property string entityKind: ""
    property string showGraphButtonName: ""

    MenuItem {
        text: "Change alias"
        onTriggered: changeAlias(menu.domainEntityId, menu.entityId, menu.currentAlias, menu.entityKind)
    }
    MenuItem {
        text: "View problems"
        onTriggered: filterEntityStatusLog(menu.entityId)
    }
    MenuItem {
        text: menu.showGraphButtonName
        onTriggered: openTopicView(menu.domainEntityId, menu.domainId, menu.entityId)
    }
    MenuItem {
        text: "Data type IDL view"
        onTriggered: openIDLView(menu.entityId)
    }
    MenuItem {
        text: "Set alert"
        onTriggered: {
            openAlertDialogWithTopic(menu.domainEntityId, menu.entityId)
        }
    }
    MenuItem {
        text: "Spy topic data"
        onTriggered: openSpyView(menu.domainId, menu.entityId)
    }
}

