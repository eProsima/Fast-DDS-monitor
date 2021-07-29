// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
import QtQuick.Layouts 1.3

/*
    Dialog to set a new alias name for an Entity.
    It has a maximum lenght of 50 characters and calculate the TextField width by a string of that size.
 */

Dialog {
    id: aliasDialog
    modal: false
    title: "Add new alias"
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: Overlay.overlay

    property var entityId: ""
    property var currentAlias: ""
    property var entityKind: ""
    property int maximumNameLength: 50

    GridLayout {
        columns: 2
        rowSpacing: 20
        Label {
            text: "Current entity alias: "
        }
        Label {
            text: currentAlias
            font.italic: true
        }
        Label {
            text: "New entity alias: "
        }
        TextField {
            id: newSeriesNameTextField
            selectByMouse: true
            maximumLength: maximumNameLength
            implicitWidth: textMetrics.width + leftPadding + rightPadding

            Keys.onReturnPressed: aliasDialog.accept()
        }
    }

    TextMetrics {
        id: textMetrics
        text: "--------------------------------------------------"
    }

    onAccepted: {
        if (newSeriesNameTextField.text !== "") {
            if (newSeriesNameTextField.text == "imgonnabelucky") {
                controller.set_alias(entityId, "( ͡° ͜ʖ ͡°)", entityKind)
            } else {
                controller.set_alias(entityId, newSeriesNameTextField.text, entityKind)
            }
        }
    }
}
