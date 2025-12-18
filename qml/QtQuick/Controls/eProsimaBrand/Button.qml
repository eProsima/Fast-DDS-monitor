// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls.impl
import QtQuick.Controls.Universal

import Theme 1.0

T.Button {
    id: tButton

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 8
    verticalPadding: padding - 4
    spacing: 8

    icon.width: 20
    icon.height: 20
    icon.color: Color.transparent(Universal.foreground, enabled ? 1.0 : 0.2)

    property bool useSystemFocusVisuals: true

    contentItem: IconLabel {
        spacing: tButton.spacing
        mirrored: tButton.mirrored
        display: tButton.display

        icon: tButton.icon
        text: tButton.text
        font: tButton.font
        color: Color.transparent(tButton.Universal.foreground, enabled ? 1.0 : 0.2)
    }

    background: Rectangle {
        implicitWidth: 32
        implicitHeight: 32
        radius: 5

        color: tButton.pressed ? Theme.whiteSmoke :
               Theme.lightGrey

        Rectangle {
            width: parent.width
            height: parent.height
            radius: parent.radius
            color: "transparent"
            visible: tButton.hovered
            border.width: 2 // ButtonBorderThemeThickness
            border.color: Theme.grey
        }
    }
}
