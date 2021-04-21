import QtQuick 2.0
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Image {
    id: root
    smooth: true

    property alias color: colorOverlay.color
    property int size: 12
    property real scalingFactor: 1

    sourceSize.width: size * scalingFactor
    sourceSize.height: size * scalingFactor

    ColorOverlay {
        id: colorOverlay
        anchors.fill: root
        source: root
        color: "#000000"
    }
}
