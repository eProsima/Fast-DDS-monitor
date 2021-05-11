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
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12
import Theme 1.0

SplitView {
    id: leftPanels
    orientation: Qt.Vertical

    signal leftSidebarHidden

    property int viewsCount: 0
    property variant views: []
    property variant comboBoxIdx: []

    Component.onCompleted: addView("ddsEntities")


    Repeater {
        id: repeater
        model: viewsCount

        delegate: ColumnLayout {
            SplitView.preferredHeight: parent.height / 4
            SplitView.minimumHeight: settingsViewTabBar.height
            Layout.fillWidth: true

            visible: true

            property int comboBoxIndex: comboBoxIdx[index]


            RowLayout {
                spacing: 0

                ComboBox {
                    id: settingsViewTabBar
                    model: ["DDS Entities", "Physical", "Logical"]
                    Layout.fillWidth: true
                    currentIndex: comboBoxIndex
                    property int modelIdx: index
                    onActivated: {
                        comboBoxIdx[modelIdx] = currentIndex
                    }
                }

                Button {
                    id: addSplitView
                    text: qsTr("+")
                    width: parent.width/10

                    onClicked: {
                        contextMenu.x = x
                        contextMenu.y = y + addSplitView.height
                        contextMenu.open()
                    }
                }

                Button {
                    id: closeSplitView
                    text: qsTr("<")
                    width: parent.width/10

                    onClicked: {
                        if (index == 0) {
                            leftSidebarHidden()
                        } else {
                            removeView(index)
                        }

                    }
                }

            }

            Menu {
                id: contextMenu
                MenuItem {
                    text: "Physical"
                    onTriggered: {
                        addView("physical")
                    }
                }
                MenuItem {
                    text: "Logical"
                    onTriggered: {
                        addView("logical")
                    }
                }
            }


            StackLayout {
                currentIndex: settingsViewTabBar.currentIndex
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true

                EntityList {
                    id: entityList
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                }

                PhysicalView {
                    id: physicalView
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                }

                LogicalView {
                    id: logicalView
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                }

            }

        }

    }

    function addView(viewKind) {
        views[viewsCount] = viewKind
        comboBoxIdx[viewsCount] = (viewKind === "ddsEntities") ? 0 :
                          (viewKind === "physical") ? 1 :
                          (viewKind === "logical") ? 2 : 0
        viewsCount++
    }

    function removeView(idx) {
        views.splice(idx, 1)
        comboBoxIdx.splice(idx, 1)
        viewsCount--
    }
}
