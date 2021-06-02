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
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Dialog {
    id: aboutDialog
    modal: false
    title: "About Fast DDS Monitor"
    standardButtons: Dialog.Close

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    RowLayout {
        spacing: 20

        Image {
            id: fastddsMonitorLogo
            source: "/resources/images/fastdds-monitor-logo.png"
            sourceSize.width: 200
            sourceSize.height: 200
            Layout.alignment: Qt.AlignTop
        }

        Rectangle {
            id: aboutPropertiesRect
            width: 400
            height: aboutPropertiesLayout.height
            color: "transparent"

            ColumnLayout {
                id: aboutPropertiesLayout
                width: parent.width
                spacing: 20

                ColumnLayout {
                    Label { text:"Version: " + "0.0.0" }
                    Label { text:"Commit: " + ""}
                    Label { text:"Date: " + "" }
                    Label { text:"eProsima Fast DDS: " + controller.fastdds_version() }
                    Label { text:"eProsima Fast DDS Statistics Backend: " + controller.fastdds_statistics_backend_version() }
                    Label { text:"Qt: " + "5.15.2" }
                    Label { text:"OS: " + "" }
                }

                Label {
                    width: aboutPropertiesRect.width
                    Layout.preferredWidth: aboutPropertiesRect.width
                    text: "Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima). All Rights Reserved. " +
                          "Licensed under the Apache License, Version 2.0."
                    wrapMode: Text.WordWrap
                }

            }
        }



    }
}
