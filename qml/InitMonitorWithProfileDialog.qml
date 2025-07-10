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

import QtQml 2.15
import QtQuick 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.calendar 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as QCC1
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.12
import Theme 1.0

Dialog {
    id: initMonitorWithProfileDialog
    modal: false
    title: "Initialize Monitor with DDS XML Profile"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    Component.onCompleted: {
        standardButton(Dialog.Ok).text = qsTrId("Ok")
        standardButton(Dialog.Cancel).text = qsTrId("Cancel")
    }

    onAboutToShow: {
        xmlProfile.currentIndex = -1
    }

    onAccepted: {
        if (!checkInputs())
            return
        else
            controller.init_monitor_with_profile(xmlProfile.currentText)
    }

    GridLayout{

        columns: 2
        rowSpacing: 20

        Label {
            id: xmlProfileLabel
            text: "DDS Profile: "
            InfoToolTip {
                text: "Select a DDS profile to initialize the monitor.\n" +
                      "You can also upload a new profile using the button below."
            }
        }

        AdaptiveComboBox {
            id: xmlProfile
            textRole: "display"
            valueRole: "display"
            displayText: currentIndex === -1
                            ? ("Please choose a DDS profile ...")
                            : currentText
            model: ParticipantXmlProfiles

            Component.onCompleted: currentIndex = -1
        }

        Button {
            id: uploadXmlButton
            text: "Upload XML Profile Files"
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onClicked: {
                loadXmlProfilesDialog.open()
            }
        }
    }

    MessageDialog {
        id: emptyXmlProfile
        title: "Empty DDS Profile"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Retry | StandardButton.Discard
        text: "The DDS profile field is empty. " +
              "Please choose a profile from the list or upload a new one."
        onAccepted: initMonitorWithProfileDialog.open()
        onDiscard: initMonitorWithProfileDialog.close()
    }

    function checkInputs() {
        if (xmlProfile.currentText == "" || xmlProfile.currentIndex === -1) {
            emptyXmlProfile.open()
            return false
        }

        return true
    }
}
