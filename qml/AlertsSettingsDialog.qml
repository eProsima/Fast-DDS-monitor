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

import QtQuick 6.8
import QtQuick.Dialogs 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

import Theme 1.0

Dialog {
    id: alertsSettingsDialog
    modal: false
    title: "Alerts Configuration"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property int pollingTime: 2000 // milliseconds

    signal setAlertsPollingTime(int pollingTime)

    onAccepted: {
        pollingTime = parseInt(pollingTimeField.text)
        setAlertsPollingTime(pollingTime)
    }

    GridLayout {
        columns: 2
        rowSpacing: 20

        Label {
            text: "Polling time (ms): "
            InfoToolTip {
                text: "Alerts timeouts are checked with this periodicity, given in ms."
            }
        }

        TextField {
            id: pollingTimeField
            Layout.fillWidth: true
            text: "2000"
            placeholderText: "<time in ms>"
            selectByMouse: true
            selectionColor: Theme.eProsimaLightBlue
            validator: IntValidator { bottom: 0; top: 999999; }
        }
    }
}
