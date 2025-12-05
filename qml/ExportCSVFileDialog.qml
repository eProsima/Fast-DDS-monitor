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

import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

FileDialog {
    id: csvDialog
    title: qsTr("Export charts to CSV file")
    fileMode: FileDialog.SaveFile
    defaultSuffix: "csv"
    nameFilters: [ "CSV files (*.csv)", "All files (*)" ]

    property var chartboxIds: []
    property var seriesIds: []
    property var dataKinds: []
    property var chartboxNames: []
    property var labelNames: []

    onAccepted: {
        controller.save_csv(
            csvDialog.selectedFile,
            chartboxIds,
            seriesIds,
            dataKinds,
            chartboxNames,
            labelNames)
    }
}
