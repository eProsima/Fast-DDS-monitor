// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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