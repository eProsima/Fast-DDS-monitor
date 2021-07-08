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

import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3 as QtDialogs
import QtQml.Models 2.15

Rectangle {
    id: legend
    implicitHeight: itemHeight * gridView.count

    property int itemWidth: legend.width
    property int itemHeight: 20

    signal seriesNameUpdated(int seriesIndex, string newSeriesName)
    signal seriesColorUpdated(int seriesIndex, color newSeriesColor)
    signal seriesHidden(int seriesIndex)
    signal seriesDisplayed(int seriesIndex)
    signal seriesRemoved(int seriesIndex)

    ListModel {
        id: seriesModel
    }

    GridView {
        id: gridView
        anchors.fill: parent
        cellWidth: itemWidth
        cellHeight: itemHeight
        model: seriesModel
        delegate: legendDelegate
        clip: true
    }

    Component {
        id: legendDelegate
        Rectangle {
            id: rect
            implicitWidth: gridView.cellWidth
            implicitHeight: gridView.cellHeight

            RowLayout {
                spacing: 5
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                Rectangle {
                    id: seriesMarker
                    width: 10; height: 10; radius: 10
                    color: seriesColor.toString()

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        onClicked: {
                            colorDialog.open()
                        }
                    }
                }
                Label {
                    id: seriesLabel
                    text: seriesName
                    color: hidden ? "grey" : "black"

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        onClicked: {
                            hidden ? displaySeriesLegend(index) : hideSeriesLegend(index)
                        }
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                propagateComposedEvents: true

                onClicked: {
                    if (mouse.button === Qt.RightButton) {
                        contextMenu.x = mouse.x;
                        contextMenu.y = mouse.y - contextMenu.contentHeight;
                        contextMenu.open()
                    } else {
                        mouse.accepted = false;
                    }
                }
            }

            Menu {
                id: contextMenu
                MenuItem {
                    text: "Remove series"
                    onTriggered: removeSeries(index)
                }
                MenuItem {
                    text: "Rename series"
                    onTriggered: renameSeriesDialog.open()
                }
                MenuItem {
                    text: "Change color"
                    onTriggered: colorDialog.open()
                }
                MenuItem {
                    text: hidden ? "Display series" : "Hide series"
                    onTriggered: hidden ? displaySeriesLegend(index) : hideSeriesLegend(index)
                }
            }

            Dialog {
                id: renameSeriesDialog
                modal: false
                title: "Rename series"
                standardButtons: Dialog.Ok | Dialog.Cancel
                anchors.centerIn: Overlay.overlay

                GridLayout {
                    columns: 2
                    rowSpacing: 20
                    Label {
                        text: "Current series name: "
                    }
                    Label {
                        text: seriesName
                    }
                    Label {
                        text: "New series name: "
                    }
                    TextField {
                        id: newSeriesNameTextField
                        selectByMouse: true
                        maximumLength: 20
                    }
                }

                onAccepted: {
                    if (newSeriesNameTextField.text !== "") {
                        seriesModel.setProperty(index, "seriesName", newSeriesNameTextField.text)
                        seriesNameUpdated(index, newSeriesNameTextField.text);
                    }
                }
            }

            QtDialogs.ColorDialog {
                id: colorDialog
                title: "Please choose a color for the series " + seriesName
                onAccepted: {
                    seriesModel.setProperty(index, "seriesColor", colorDialog.color.toString())
                    seriesModel.setProperty(index, "originalSeriesColor", colorDialog.color.toString())
                    seriesColorUpdated(index, colorDialog.color);
                }
            }
        }

    }

    function addLeyend(name, color) {
        seriesModel.append({
                           "seriesName": name,
                           "seriesColor": color.toString(),
                           "originalSeriesColor": color.toString(),
                           "hidden": false
                           })
    }

    function removeLeyend(seriesIndex) {
        seriesModel.remove(seriesIndex)
    }

    function removeAllLegends() {
        seriesModel.clear()
    }

    function hideSeriesLegend(seriesIndex) {
        seriesModel.setProperty(seriesIndex, "seriesColor", "grey")
        seriesModel.setProperty(seriesIndex, "hidden", true)
        seriesHidden(seriesIndex);
    }

    function hideAllSeries() {
        for (var idx = 0; idx < seriesModel.count; idx++) {
            hideSeriesLegend(idx);
        }
    }

    function displaySeriesLegend(seriesIndex) {
        seriesModel.setProperty(seriesIndex, "seriesColor", seriesModel.get(seriesIndex).originalSeriesColor)
        seriesModel.setProperty(seriesIndex, "hidden", false)
        seriesDisplayed(seriesIndex);
    }

    function displayAllSeries() {
        for (var idx = 0; idx < seriesModel.count; idx++) {
            displaySeriesLegend(idx);
        }
    }

    function removeSeries(seriesIndex) {
        seriesRemoved(seriesIndex);
    }
}
