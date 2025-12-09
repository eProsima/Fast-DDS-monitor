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

import QtQuick 6.10
import QtQuick.Layouts 6.10
import QtQuick.Dialogs 6.10
import QtQuick.Controls 6.10
import Theme 1.0

Dialog {
    id: seriesSetMaxPointsDialog
    modal: true
    title: "Change max number of data points in series"
    standardButtons: Dialog.Ok | Dialog.Cancel

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property var chartboxId: -1
    property var seriesId: -1
    property var currentSize: 0

    RowLayout {
        Label {
            id: maxPointsLabel
            text: qsTr("Maximum data points")
            InfoToolTip {
                text: "To avoid memory exhaustation\n" +
                        "set a maximum number of points.\n" +
                        "When maximum number reached, old\n" +
                        "points would be deleted when new\n" +
                        "are printed [0 for no maximum]."
            }
        }
        SpinBox {
            id: maxPoints
            editable: true
            from: 0
            to: 999999
            value: currentSize
        }
    }

    onAccepted: {
        controller.change_max_points(
            chartboxId,
            seriesId,
            maxPoints.value)
    }
}
