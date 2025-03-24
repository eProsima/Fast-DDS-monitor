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

import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.15
import Theme 1.0

Dialog {
    id: dialogInitMonitor

    readonly property int layout_vertical_spacing_: 10 // vertical spacing between the components in a row
    readonly property int layout_horizontal_spacing_: 15 // horizontal spacing between rows
    readonly property int item_height_: 40 // Height of header item and each item of
                                           // advanced options submenu (title + options)
    readonly property int dialog_width_: 300 // Width of the dialog

    modal: true

    header: Item {
        width: parent.width
        height: item_height_
        Rectangle {
            color: "transparent"
            width: parent.width
            height: parent.height
            Text {
                topPadding: 5
                text: "Initialize Monitor"
                font.pointSize: 15
                anchors.centerIn: parent
            }
        }
    }

    footer: DialogButtonBox {
        id: dialogButtons
        standardButtons: Dialog.Ok | Dialog.Cancel
    }

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: dialog_width_

    onAccepted: {
        let advancedOptions = {}
        if (easyModeOptionCheckBox.checked) {
            advancedOptions["easy_mode_ip"] = easyModeOptionTextInput.text
        }
        controller.init_monitor(simpleDiscoveryAnswer.value, advancedOptions)
    }

    contentItem: ColumnLayout {
        spacing: layout_horizontal_spacing_

        Row {
            spacing: dialogInitMonitor.layout_vertical_spacing_

            Label {
                text: "DDS Domain: "
                anchors.verticalCenter: parent.verticalCenter
            }

            SpinBox {
                id: simpleDiscoveryAnswer
                anchors.verticalCenter: parent.verticalCenter
                editable: true
                value: 0
                from: 0
                to: 232
                Layout.alignment: Qt.AlignTop
                Keys.onReturnPressed: {
                    // Prevent accepting the dialog if OK button is disabled
                    if (dialogButtons.standardButton(Dialog.Ok).enabled) {
                        dialogInitMonitor.accept()
                    }
                }
            }
        }

        Rectangle {

            id: advancedOptionsSubmenu
            color: "transparent"

            property bool isExpanded: false
            readonly property int item_height_: dialogInitMonitor.item_height_
            readonly property int collapsed_options_box_height_: item_height_
            readonly property int options_box_body_height_: item_height_
            readonly property int expanded_options_box_height_: collapsed_options_box_height_ + options_box_body_height_

            Layout.fillWidth: true
            Layout.preferredHeight: isExpanded
                ? expanded_options_box_height_ + 20
                : collapsed_options_box_height_ + 20

            Column {
                anchors.fill: parent
                spacing: layout_horizontal_spacing_
                RowLayout {
                    width: parent.width

                    Rectangle {
                        Layout.fillWidth: true
                        height: 2
                        color: Theme.lightGrey
                    }

                    Rectangle {
                        width: 175
                        height: 30
                        radius: 15
                        color: advancedOptionsMouseArea.containsMouse ? Theme.grey : "transparent"
                        Row {
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: dialogInitMonitor.layout_vertical_spacing_
                            leftPadding: 10

                            IconSVG {
                            anchors.verticalCenter: parent.verticalCenter
                            name: advancedOptionsSubmenu.isExpanded ? "cross" : "plus"
                            size: 12
                            color: advancedOptionsMouseArea.containsMouse ? "white" : "grey"
                            }

                            Label {
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Advanced options"
                                color: advancedOptionsMouseArea.containsMouse ? "white" : "grey"
                            }
                        }

                        MouseArea {
                            id: advancedOptionsMouseArea
                            width: parent.width
                            height: parent.height
                            hoverEnabled: true
                            onClicked: {
                                advancedOptionsSubmenu.isExpanded = !advancedOptionsSubmenu.isExpanded
                            }
                        }
                    }
                }

                Column {
                    width: parent.width
                    visible: advancedOptionsSubmenu.isExpanded
                    height: advancedOptionsSubmenu.isExpanded ? advancedOptionsSubmenu.item_height_ : 0
                    spacing: dialogInitMonitor.layout_horizontal_spacing_

                    Row {
                        id: easyModeOption
                        spacing: dialogInitMonitor.layout_vertical_spacing_
                        CheckBox {
                            id: easyModeOptionCheckBox
                            text: "Easy Mode"
                            checked: false

                            indicator: Rectangle {
                                implicitWidth: 16
                                implicitHeight: 16
                                anchors.verticalCenter: parent.verticalCenter
                                border.color: Theme.grey
                                border.width: 2
                                Rectangle {
                                    visible: easyModeOptionCheckBox.checked
                                    color: Theme.eProsimaLightBlue
                                    radius: 1
                                    anchors.margins: 3
                                    anchors.fill: parent
                                }
                            }

                            onCheckedChanged: {
                                if (!checked)
                                {
                                    dialogButtons.standardButton(Dialog.Ok).enabled = true
                                }
                                else
                                {
                                    easyModeOptionTextInput.validateInputTest()
                                }
                            }
                        }

                        TextField {
                            id: easyModeOptionTextInput
                            enabled: easyModeOptionCheckBox.checked
                            selectByMouse: true
                            placeholderText: "IPv4 Address"
                            width: 130
                            height: 5/6*advancedOptionsSubmenu.item_height_
                            anchors.verticalCenter: parent.verticalCenter

                            validator: RegExpValidator {
                                regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))$/
                            }

                            background: Rectangle {
                                color: !easyModeOptionCheckBox.checked ? "#a0a0a0" : Theme.whiteSmoke
                                border.color: !easyModeOptionCheckBox.checked ? Theme.grey :
                                    easyModeOptionTextInput.acceptableInput ? "lightgreen" : "salmon"
                            }

                            onTextChanged: {
                                validateInputTest()
                            }

                            function validateInputTest() {
                                if (acceptableInput) {
                                    dialogButtons.standardButton(Dialog.Ok).enabled = true
                                } else {
                                    dialogButtons.standardButton(Dialog.Ok).enabled = false
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
