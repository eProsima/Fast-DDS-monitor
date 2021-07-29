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
import QtQuick.Dialogs 1.2

MessageDialog {
    id: errorDialog
    title: "Error"
    icon: StandardIcon.Warning
    text: "Error message has not been set"
    standardButtons: StandardButton.Cancel | StandardButton.Retry
    property int errorType // Dependeing on this value it would behave differently in Accept
    onAccepted: {
        if (errorType == 1) {           // INIT_MONITOR
            dialogInitMonitor.open()
        } else if (errorType == 2) {    // INIT_DS_MONITOR
            dialogDSInitMonitor.open()
        }
    }
}
