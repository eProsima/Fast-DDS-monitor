import QtQuick 2.0

Item {
    // public property
    property bool left_to_right: true // arrow points to the left by default

    // Read only private design properties
    readonly property string arrow_color_: "black"

    height: thickness

    Rectangle {
        id: base_arrow
        anchors.fill: parent
        color: arrow_color_
    }
}
