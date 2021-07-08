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
    title: "Init Monitor"
    standardButtons: Dialog.Apply | Dialog.Ok | Dialog.Cancel | Dialog.RestoreDefaults
    width: 700

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property int simpleMonitor: -1
    property string discoveryServerMonitor: ""

    onAccepted: {
        if (monitorTab.currentIndex == 0){
            controller.init_monitor(simpleDiscoveryAnswer.value)
        } else {
            initDiscoveryServer(true)
        }
    }

    onApplied: {
        if (monitorTab.currentIndex == 0){
            controller.init_monitor(simpleDiscoveryAnswer.value)
            dialogInitMonitor.open()
        } else {
            initDiscoveryServer(false)
        }
    }

    onReset: {
        discoveryServerGuid.text = "44.53.00.5f.45.50.52.4f.53.49.4d.41"
        discoveryServerLocatorsModel.clear()
        discoveryServerLocatorsModel.append({"transportProtocolIdx": 0, "ip": "", "port": -1})
    }

    Component.onCompleted: {
        standardButton(Dialog.Apply).text = qsTrId("Apply and Continue")
        standardButton(Dialog.Ok).text = qsTrId("Apply and Close")
        discoveryServerLocatorsModel.append({"transportProtocolIdx": 0, "ip": "", "port": -1})
    }

    ListModel {
        id: discoveryServerLocatorsModel
    }

    ColumnLayout {
        anchors.fill: parent
        TabBar {
            id: monitorTab
            Layout.fillWidth: true
            Layout.bottomMargin: 10

            TabButton {
                id: simpleDiscoveryTab
                text: "Simple Discovery"
            }

            TabButton {
                id: discoveryServerTab
                text: "Discovery Server"
            }
        }

        StackLayout {
            id: monitorStack
            currentIndex: monitorTab.currentIndex
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop | Qt.AlignCenter

            ColumnLayout {
                Layout.topMargin: 20
                Layout.fillHeight: true
                Layout.fillWidth: true

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

            ColumnLayout {
                Layout.topMargin: 20
                Layout.fillHeight: true
                Layout.fillWidth: true

                Label {
                    text: 'Set the GUID and the network addresses (locators) of a Discovery Server.'
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Label {
                        id: discoveryServerGuidLabel
                        text: "• Discovery Server GUID: "
                        InfoToolTip {
                            text: 'Discovery Server GUID.'
                        }
                    }
                    TextField {
                        id: discoveryServerGuid
                        implicitWidth: monitorStack.width
                        placeholderText: "44.53.00.5f.45.50.52.4f.53.49.4d.41"
                        text: "44.53.00.5f.45.50.52.4f.53.49.4d.41"
                        selectByMouse: true
                        validator: RegExpValidator {
                            regExp: /^(([0-9a-fA-F][0-9a-fA-F]\.){11})([0-9a-fA-F][0-9a-fA-F])$/
                        }
                        Keys.onReturnPressed: dialogInitMonitor.accept()
                    }
                }
                GridLayout {
                    Layout.fillWidth: true
                    columns: 4
                    columnSpacing: 10

                    Label {
                        id: discoveryServerLocatorLabel
                        Layout.columnSpan: 4
                        text: "• Discovery Server locator(s): "
                        InfoToolTip {

                            text: 'Each row defines a locator\n' +
                                  'for the Discovery Server.'
                        }
                    }
                    Label {
                        id: discoveryServerTransportProtocolLabel
                        text: "Transport Protocol"
                        Layout.preferredWidth: parent.width / 3
                        InfoToolTip {
                            text: 'Transport protocol of the\n' +
                                  'Discovery Server network\n' +
                                  'address.'
                        }
                    }
                    Label {
                        id: discoveryServerIPLabel
                        text: "IP"
                        Layout.preferredWidth: parent.width / 3
                        InfoToolTip {
                            text: 'IP of the Discovery Server\n' +
                                  'network address.\n'
                        }
                    }
                    Label {
                        id: discoveryServerPortLabel
                        text: "Port"
                        Layout.preferredWidth: parent.width / 5
                        InfoToolTip {
                            text: 'Port of the Discovery Server\n' +
                                  'network address.'
                        }
                    }
                    Rectangle {
                        id: discoveryServerRemoveIcon
                        Layout.fillWidth: true
                        color: "Blue"
                    }
                    Rectangle {
                        Layout.preferredWidth: parent.width
                        Layout.columnSpan: parent.columns
                        height: 2
                        color: Theme.grey
                    }

                    Rectangle {
                        id: dsLocatorsRect
                        Layout.columnSpan: 4
                        Layout.fillWidth: true
                        height: 100
                        color: "transparent"

                        ListView {
                            id: discoveryServerLocatorsListView
                            model: discoveryServerLocatorsModel
                            delegate: discoveryServerLocatorsDelegate
                            anchors.fill: parent
                            clip: true
                            spacing: 5

                            ScrollBar.vertical: ScrollBar {
                                id: scrollBar
                                visible: true
                                hoverEnabled: true
                            }

                            onCountChanged: {
                                var newIndex = count - 1
                                positionViewAtEnd()
                                currentIndex = newIndex
                            }
                        }

                        Component {
                            id: discoveryServerLocatorsDelegate

                            Item {
                                width: discoveryServerLocatorsListView.width
                                height: dsLocatorRow.height

                                RowLayout {
                                    id: dsLocatorRow
                                    spacing: 10

                                    ComboBox {
                                        id: discoveryServerTransportProtocol
                                        model: ["UDPv4", "UDPv6", "TCPv4", "TCPv6"]
                                        Layout.preferredWidth: discoveryServerTransportProtocolLabel.width
                                        onActivated: transportProtocolIdx = discoveryServerTransportProtocol.currentIndex
                                        Component.onCompleted: {
                                            discoveryServerTransportProtocol.currentIndex = transportProtocolIdx
                                        }
                                    }
                                    TextField {
                                        id: discoveryServerIP
                                        placeholderText: "127.0.0.1"
                                        selectByMouse: true
                                        Layout.preferredWidth: discoveryServerIPLabel.width
                                        text: (ip < 0) ? "" : ip
                                        validator: RegExpValidator {
                                            regExp: {
                                                if (discoveryServerTransportProtocol.currentText.includes("v4")) {
                                                    return ipv4Regex()
                                                } else if (discoveryServerTransportProtocol.currentText.includes("v6")) {
                                                    return ipv6Regex()
                                                } else {
                                                    return matchAllRegex()
                                                }
                                            }
                                        }
                                        Keys.onReturnPressed: dialogInitMonitor.accept()
                                        onTextEdited: ip = text
                                    }
                                    TextField {
                                        id: discoveryServerPort
                                        placeholderText: "11811"
                                        selectByMouse: true
                                        Layout.preferredWidth: discoveryServerPortLabel.width
                                        text: (port < 0) ? "" : port
                                        validator: IntValidator {
                                            bottom: 0
                                        }
                                        Keys.onReturnPressed: dialogInitMonitor.accept()
                                        onTextEdited: port = parseInt(text)
                                    }

                                    Rectangle {
                                        height: discoveryServerPort.height - discoveryServerPort.height/3
                                        width: discoveryServerPort.height - discoveryServerPort.height/3
                                        radius: discoveryServerPort.height - discoveryServerPort.height/3
                                        Layout.alignment: Qt.AlignCenter
                                        color: Theme.grey
                                        border.width: 2
                                        border.color: "transparent"

                                        IconSVG {
                                            id: iconRemove
                                            name: "cross"
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            size: parent.height/2
                                            color: "white"
                                        }

                                        MouseArea {
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            onClicked: {
                                                discoveryServerLocatorsModel.remove(index)
                                            }
                                            onEntered: {
                                                parent.color = Theme.lightGrey
                                                parent.border.color = Theme.grey
                                                iconRemove.color = "grey"
                                            }
                                            onExited: {
                                                parent.color = Theme.grey
                                                parent.border.color = "transparent"
                                                iconRemove.color = "white"
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Rectangle {
                        Layout.preferredWidth: parent.width
                        Layout.columnSpan: parent.columns
                        height: 2
                        color: Theme.grey
                    }

                    Rectangle {
                        Layout.columnSpan: 2
                        Layout.preferredWidth: 1
                    }

                    Button {
                        text: "Add locator row"
                        Layout.columnSpan: 2
                        Layout.alignment: Qt.AlignLeft
                        Layout.fillWidth: true
                        onClicked: {
                            discoveryServerLocatorsModel.append({"transportProtocolIdx": 0, "ip": "", "port": -1})
                        }
                    }
                }
            }
        }
    }

    MessageDialog {
        id: wrongIP
        title: "Invalid Discovery Server IP"
        icon: StandardIcon.Warning
        standardButtons:  isAccepted ? (StandardButton.Retry | StandardButton.Discard) : StandardButton.Retry
        text: "The inserted Discovery Server IP " + ip + " is not a valid IP."
        property string ip: ""
        property bool isAccepted: true
        onAccepted: {
            dialogInitMonitor.open()
        }
    }

    MessageDialog {
        id: emptyPort
        title: "Invalid Discovery Server Port"
        icon: StandardIcon.Warning
        standardButtons:  isAccepted ? (StandardButton.Retry | StandardButton.Discard) : StandardButton.Retry
        text: "No port has been inserted for the Discovery Server IP " + ip + ". " +
              "Please fill in the ports of all network addresses."
        property string ip: ""
        property bool isAccepted: true
        onAccepted: {
            dialogInitMonitor.open()
        }
    }

    MessageDialog {
        id: wrongGuid
        title: "Invalid Discovery Server GUID"
        icon: StandardIcon.Warning
        standardButtons:  isAccepted ? (StandardButton.Retry | StandardButton.Discard) : StandardButton.Retry
        text: "The inserted Discovery Server GUID is not valid."
        property bool isAccepted: true
        onAccepted: {
            dialogInitMonitor.open()
        }
    }

    /**
     * Returns an regular expression for IPv4 string matching
     */
    function ipv4Regex() {
        var ipv4re = /^(((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3})(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/g
        return ipv4re
    }

    /**
     * Returns an regular expression for IPv6 string matching
     */
    function ipv6Regex() {
        var ipv6re = /(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))/gi;
        return ipv6re
    }

    /**
     * Returns an regular expression that matches any string
     */
    function matchAllRegex() {
        var re = /[\s\S]*/
        return re
    }

    /**
     * Function to parse the input parameter of the initialize monitor dialog for Discovery Server
     */
    function initDiscoveryServer(isAccepted) {
        /////
        // Check that Discovery Server GUID is correct
        if (!discoveryServerGuid.acceptableInput) {
            wrongGuid.isAccepted = isAccepted
            wrongGuid.open()
            return
        }

        /////
        // Build the locators
        var locators = ""

        for (var i = 0; i < discoveryServerLocatorsModel.rowCount(); i++) {
            // Get the trasnport protocol from the ComboBox
            var transportProtocol = ""
            switch (discoveryServerLocatorsModel.get(i).transportProtocolIdx) {
                case 0:
                    transportProtocol = "UDPv4"
                    break
                case 1:
                    transportProtocol = "UDPv6"
                    break
                case 2:
                    transportProtocol = "TCPv4"
                    break
                case 3:
                    transportProtocol = "TCPv6"
                    break
            }

            // Get the IP of locator
            var ip = discoveryServerLocatorsModel.get(i).ip
            var ipRe;
            if (transportProtocol.includes("v4")) {
                ipRe = ipv4Regex()
            } else if (transportProtocol.includes("v6")) {
                ipRe = ipv6Regex()
            } else {
                ipRe = matchAllRegex()
            }
            if (!ip) {
                continue
            } else if (!ipRe.test(ip)) {
                wrongIP.isAccepted = isAccepted
                wrongIP.ip = ip
                wrongIP.open()
                return
            }

            // Get the port of the locator
            var port = discoveryServerLocatorsModel.get(i).port
            if (port < 0) {
                emptyPort.isAccepted = isAccepted
                emptyPort.ip = ip
                emptyPort.open()
                return
            }

            var locator = transportProtocol + ":[" + ip + "]:" + port
            if (i !== (discoveryServerLocatorsModel.rowCount() - 1)) {
                locator = locator.concat(";")
            }
            locators = locators.concat(locator)
        }

        /////
        // Call the controller to initialize a Discovery Server monitor
        if (locator) {
            console.log("Init monitor -> GUID: " + discoveryServerGuid.text + " | Locators: " + locators)
            controller.init_monitor(discoveryServerGuid.text, locators)
        }
    }
}
