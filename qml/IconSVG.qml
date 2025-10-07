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

Image {
    id: image
    smooth: true
    visible: true
    source: buildFileName()

    property string name: ""
    property string color: "black"
    property int size: 12
    property real scalingFactor: 1
    sourceSize.width: size * scalingFactor
    sourceSize.height: size * scalingFactor

    function buildFileName() {
        return name ? ("/resources/images/icons/" + name + "_" + color + ".svg") : ""
    }
}
