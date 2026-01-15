pragma Singleton

import QtQuick

QtObject {
    readonly property color eProsimaDarkBlue: "#09487e"
    readonly property color eProsimaLightBlue: "#0895cd"
    readonly property color eProsimaGreen: "#88ce28"
    readonly property color eProsimaRed: "#ff0d0c"
    readonly property color eProsimaYellow: "#ffc001"

    readonly property color darkBlueProxy: "#a7d3f9"
    readonly property color lightBlueProxy: "#b8e9fc"
    readonly property color greenProxy: "#e1f4c8"
    readonly property color redProxy: "#ffc2c2"
    readonly property color yellowProxy: "#ffefbf"
    readonly property color whiteProxy: "#fcfcfc"

    readonly property color grey: "#808080"
    readonly property color midGrey: "#585858"
    readonly property color lightGrey: "#d3d3d3"
    readonly property color darkGrey: "#3e3e3e"
    readonly property color x11Grey: "#BEBEBE"
    readonly property color whiteSmoke: "#f5f5f5"

    // readonly property int smallSize: 10
    // readonly property int largeSize: 16

    property font font
    font.bold: false
    font.underline: false
    font.pointSize: 11
}
