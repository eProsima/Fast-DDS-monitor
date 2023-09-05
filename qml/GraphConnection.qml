import QtQuick 2.0

Item {
    // public property
    property bool left_to_right: true           // arrow points to the left by default
    property int left_margin: 0
    property string arrow_color: Theme.grey
    property string background_color: "white"

    Rectangle {
        id: background_arrow
        visible: left_margin != 0
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.topMargin: -2; anchors.bottomMargin: -2
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: left_margin
        color: background_color
    }

    Rectangle {
        id: base_arrow
        anchors.fill: parent
        color: arrow_color
    }
}
