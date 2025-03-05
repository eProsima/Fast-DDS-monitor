import QtQuick 2.0

Item {
    id: graphConnection
    // public property
    property bool left_direction: false                 // defines if the represented connection must draw a left arrow
    property bool right_direction: false                // defines if the represented connection must draw a right arrow
    property int left_margin: 0                         // left margin to be applied
    property string arrow_color: Theme.grey             // connection color
    property string arrow_head_color: "grey"
    property string background_color: "white"           // background color
    property string endpoint_id: ""                     // graph refferred entity id
    property bool hidden_arrow: false                   // associated topic is not visible
    property bool show_fill_gap: true                   // defines if fill_gap component wih base_arrow extension and hidden topic icon  
                                                        // should be displayed or not 

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
    readonly property int hidden_arrow_margin_: 2       // hidden arrow margin
    readonly property int elements_spacing_: 5          // spacing between elements

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
            color: arrow_head_color
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

    Rectangle {
        color: "transparent"
        anchors.verticalCenter: base_arrow.verticalCenter
        anchors.left: base_arrow.right
        height: graphConnection.height - 2* arrow_margin_; width: 7*elements_spacing_

        Rectangle {
            id: fill_gap
            anchors.fill: parent
            color: "white"
            visible: graphConnection.show_fill_gap
            
            Rectangle {
                id: fill_gap_base_arrow
                visible: !graphConnection.hidden_arrow
                anchors.top: parent.top; anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.right: parent.right
                anchors.topMargin: -arrow_margin_; anchors.bottomMargin: -arrow_margin_
                color: arrow_color
            }
            // hidden topic icon
            Rectangle {
                visible: graphConnection.hidden_arrow
                height: graphConnection.height - 2* arrow_margin_; width: 3*graphConnection.height + hidden_arrow_margin_*4
                color: "white"

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.right; anchors.leftMargin: -parent.height/2
                    height: parent.height; width: parent.height
                    radius: parent.height
                    color: "white"
                }

                Rectangle {
                    id: spot_1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left; anchors.leftMargin: hidden_arrow_margin_*2
                    height: graphConnection.height; width: graphConnection.height
                    radius: graphConnection.height
                    color: arrow_color
                }
                Rectangle {
                    id: spot_2
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: spot_1.right; anchors.leftMargin: hidden_arrow_margin_
                    height: graphConnection.height; width: graphConnection.height
                    radius: graphConnection.height
                    color: arrow_color
                }
                Rectangle {
                    id: spot_3
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: spot_2.right; anchors.leftMargin: hidden_arrow_margin_
                    height: graphConnection.height; width: graphConnection.height
                    radius: graphConnection.height
                    color: arrow_color
                }

                Rectangle {
                    id: spot_0
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: spot_1.left; anchors.rightMargin: hidden_arrow_margin_*2-graphConnection.height/2 +1
                    height: graphConnection.height; width: graphConnection.height
                    radius: graphConnection.height
                    color: arrow_color
                }
            }
        }
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
            color: arrow_head_color
            size: arrow_size_ + right_arrow_margin_
        }
    }

    function topid_hidden(entityId, is_hidden)
    {
        if (endpoint_id == entityId && graphConnection.hidden_arrow != is_hidden)
        {
            graphConnection.hidden_arrow = is_hidden
        }
    }
}
