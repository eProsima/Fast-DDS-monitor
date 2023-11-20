import QtQuick 2.0

Item {
    // public property
    property bool left_direction: false                 // defines if the represented connection must draw a left arrow
    property bool right_direction: false                // defines if the represented connection must draw a right arrow
    property int left_margin: 0                         // left margin to be applied
    property string arrow_color: Theme.grey             // connection color
    property string background_color: "white"           // background color

    // readonly private design properties
    readonly property int arrow_margin_: -3             // margins for background
    readonly property int arrow_size_: 18               // arrow size
    readonly property int main_left_margin_: 10         // left arrow margin size
    readonly property int main_right_margin_: 15        // right arrow margin size
    readonly property int left_arrow_background_: 15    // left arrow background size
    readonly property int left_arrow_background_icon_size_offset_: 8
    readonly property int left_arrow_background_margin_: -4
    readonly property int left_arrow_margin_: -5        // left arrow margin
    readonly property int right_arrow_margin_: -2       // right arrow margin

    // background to make connection overlap nicely with previous topics (looks like connection goes OVER the topic)
    Rectangle {
        id: background_arrow
        visible: left_margin != 0
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.topMargin: arrow_margin_; anchors.bottomMargin: arrow_margin_
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: left_margin; anchors.rightMargin: left_margin
        color: "white"
    }

    // background to make connection overlap nicely left panel
    Rectangle {
        id: left_background
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.topMargin: arrow_margin_; anchors.bottomMargin: arrow_margin_
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: parent.height /2
        anchors.rightMargin: left_direction ? left_margin: left_margin != 0 ? parent.height : parent.height/2
        color: "white"
    }



    // left arrow if visible
    Item {
        id: left_arrow_background
        visible: left_direction
        height: arrow_size_ + left_arrow_background_
        width: arrow_size_
        clip: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left; anchors.leftMargin: left_arrow_background_margin_

        IconSVG {
            anchors.left: parent.left
            anchors.top: parent.top
            name: "left_arrow"
            color: "white"
            size: arrow_size_ + left_arrow_background_icon_size_offset_
        }

        IconSVG {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            name: "left_arrow"
            color: "white"
            size: arrow_size_ + left_arrow_background_icon_size_offset_
        }
    }


    Item {
        id: left_arrow
        visible: left_direction
        height: arrow_size_
        width: arrow_size_
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left; anchors.leftMargin: left_arrow_margin_

        IconSVG {
            name: "left_arrow"
            color: "grey"
            size: arrow_size_
        }
    }

    // main connection
    Rectangle {
        id: base_arrow
        anchors.top: parent.top; anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: left_direction ? main_left_margin_ : 0
        anchors.rightMargin: right_direction ? main_right_margin_ : 0
        color: arrow_color
    }

    // right arrow if visible
    Item {
        id: right_arrow
        visible: right_direction
        height: arrow_size_ + right_arrow_margin_
        width: arrow_size_ + right_arrow_margin_
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right; anchors.rightMargin: parent.height /2

        IconSVG {
            name: "right_arrow"
            color: "grey"
            size: arrow_size_ + right_arrow_margin_
        }
    }
}
