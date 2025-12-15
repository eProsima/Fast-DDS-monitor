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

import QtQuick 6.8
import QtCharts 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8
import QtQuick.Dialogs 6.8

Rectangle {
    id: legend

    property int maxToShow: 3

    implicitHeight: (gridView.count <= maxToShow) ? itemHeight * gridView.count : itemHeight * maxToShow

    property int itemWidth: legend.width
    property int itemHeight: 20

    signal seriesNameUpdated(int seriesIndex, string newSeriesName)
    signal seriesColorUpdated(int seriesIndex, color newSeriesColor)
    signal seriesHidden(int seriesIndex)
    signal seriesDisplayed(int seriesIndex)
    signal seriesRemoved(int seriesIndex)
    signal seriesToCSV(int seriesIndex, string seriesLabel)
    signal setMaxPoints(int seriesIndex, int currentSize)

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

        onCountChanged: {
            var newIndex = count - 1
            positionViewAtEnd()
            currentIndex = newIndex // force index to be coherent when automatically scroll down
        }

        ScrollBar.vertical: CustomScrollBar {
            id: scrollBar
        }
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
                        hoverEnabled: true
                        onClicked: {
                            colorDialog.selectedColor = seriesColor
                            colorDialog.open()
                        }
                        onEntered: legendDelegateMouseArea.cursorShape = Qt.PointingHandCursor
                        onExited: legendDelegateMouseArea.cursorShape = Qt.ArrowCursor
                    }
                }
                Label {
                    id: seriesLabel
                    text: seriesName
                    color: hidden ? "grey" : "black"

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        hoverEnabled: true
                        onClicked: hidden ? displaySeriesLegend(index) : hideSeriesLegend(index)
                        onEntered: legendDelegateMouseArea.cursorShape = Qt.PointingHandCursor
                        onExited: legendDelegateMouseArea.cursorShape = Qt.ArrowCursor
                    }
                }
            }

            MouseArea {
                id: legendDelegateMouseArea
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                propagateComposedEvents: true

                onClicked: function(mouse) {
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
                    onTriggered: {
                        colorDialog.selectedColor = seriesColor
                        colorDialog.open()
                    }
                }
                MenuItem {
                    text: hidden ? "Display series" : "Hide series"
                    onTriggered: hidden ? displaySeriesLegend(index) : hideSeriesLegend(index)
                }
                MenuItem {
                    text: "Export to CSV"
                    onTriggered: seriesToCSV(index, seriesModel.get(index).seriesName)
                }
                MenuItem {
                    // TODO this should not be shown in historic series
                    text: "Set max data points"
                    onTriggered: setMaxPoints(index, maxPoints)
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
                        maximumLength: 50
                        implicitWidth: textMetrics.width + leftPadding + rightPadding

                        Keys.onReturnPressed: renameSeriesDialog.accept()
                    }
                }

                TextMetrics {
                    id: textMetrics
                    text: "--------------------------------------------------"
                }

                onAccepted: {
                    if (newSeriesNameTextField.text !== "") {
                        seriesModel.setProperty(index, "seriesName", newSeriesNameTextField.text)
                        seriesNameUpdated(index, newSeriesNameTextField.text);
                    }
                }
            }

            ColorDialog {
                id: colorDialog
                title: "Please choose a color for the series " + seriesName
                selectedColor: seriesColor
                onAccepted: {
                    var chosenColor = colorDialog.selectedColor
                    seriesModel.setProperty(index, "seriesColor", chosenColor.toString())
                    seriesModel.setProperty(index, "originalSeriesColor", chosenColor.toString())
                    seriesColorUpdated(index, chosenColor);
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

    function removeLegend(seriesIndex) {
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

    function getLabel(seriesIndex) {
        return seriesModel.get(seriesIndex).seriesName
    }

    function getAllLabels() {
        var labels = []
        for (var idx = 0; idx < seriesModel.count; idx++) {
            labels.push(getLabel(idx))
        }
        return labels
    }

    function getNumberOfSeries() {
        return seriesModel.count
    }
}
