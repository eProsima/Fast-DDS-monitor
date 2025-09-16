// Copyright 2025 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Theme 1.0

Dialog {
    id: alertKindDialog
    modal: false
    title: "Create new alert"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property var availableAlertKinds: []

    signal createAlert(string alertKind)

    onAccepted: {
        if (!checkInputs())
            return
        createAlert(alertKindComboBox.currentText)
    }

    Component.onCompleted: {
        availableAlertKinds = controller.get_alert_kinds()
    }

    onAboutToShow: {
        alertKindComboBox.currentIndex = -1
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: alertKindLabel
            text: "Alert kind: "
            InfoToolTip {
                text: "Type of alert to be created."
            }
        }
        AdaptiveComboBox {
            id: alertKindComboBox
            displayText: currentIndex === -1
                         ? ("Please choose an alert kind...")
                         : currentText
            model: availableAlertKinds

            Component.onCompleted: currentIndex = -1
        }

    }

    MessageDialog {
        id: emptyAlertKind
        title: "Alert Kind"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The alert kind field is empty. Please choose an alert kind from the list."
        onAccepted: alertKindDialog.open()
        onDiscard: alertKindDialog.close()
    }

    function checkInputs() {
        if (alertKindComboBox.currentIndex === -1) {
            emptyAlertKind.open()
            return false
        }

        return true
    }

}
