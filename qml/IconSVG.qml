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
import QtGraphicalEffects 1.15

Image {
    id: image
    smooth: true
    visible: true
    property color color: "transparent"
    property bool dye: false
    property int size: 12
    property real scalingFactor: 1
    sourceSize.width: size * scalingFactor
    sourceSize.height: size * scalingFactor

    ColorOverlay {
        id: overlay
        anchors.fill: parent
        source: parent
        color: parent.color
        visible: dye ? true : false
    }
}


