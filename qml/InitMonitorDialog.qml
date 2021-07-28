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

import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import Theme 1.0

Dialog {
    id: dialogInitMonitor
    modal: false
    title: "Initialize Monitor"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    onAccepted: {
        controller.init_monitor(simpleDiscoveryAnswer.value)
    }

    RowLayout {

        Label {
            text: "DDS Domain: "
        }
        SpinBox {
            id: simpleDiscoveryAnswer
            editable: true
            value: 0
            from: 0
            to: 999
            Layout.alignment: Qt.AlignTop
            Keys.onReturnPressed: dialogInitMonitor.accept()
        }
    }
}
