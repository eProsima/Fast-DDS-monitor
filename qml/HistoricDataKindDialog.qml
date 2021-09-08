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

import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Dialog {
    id: dataKindDialog
    modal: false
    title: "Display new statistics data"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property var availableDataKinds: []

    signal createChart(string dataKind)

    onAccepted: createChart(dataKindComboBox.currentText)

    Component.onCompleted: {
        availableDataKinds = controller.get_data_kinds()
    }

    onAboutToShow: {
        dataKindComboBox.currentIndex = -1
    }

    RowLayout {

        Label {
            id: dataKindLabel
            text: "Data kind: "
            InfoToolTip {
                text: "Data type to be plotted."
            }
        }
        AdaptiveComboBox {
            id: dataKindComboBox
            displayText: currentIndex === -1
                         ? ("Please choose a data kind...")
                         : currentText
            model: availableDataKinds

            Component.onCompleted: currentIndex = -1
        }
    }
}


