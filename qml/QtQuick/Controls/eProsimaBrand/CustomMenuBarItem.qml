// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick 6.8
import QtQuick.Templates 6.8 as T
import QtQuick.Controls 6.8
import QtQuick.Controls.impl 6.8
import QtQuick.Controls.Universal 6.8
import Theme 1.0

T.MenuBarItem {
    id: tMenuBarItem

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             implicitIndicatorHeight + topPadding + bottomPadding)

    padding: 12
    topPadding: 5
    bottomPadding: 6
    spacing: 12

    icon.width: 10
    icon.height: 10
    icon.color: !enabled ? Universal.baseLowColor : Universal.baseHighColor

    contentItem: IconLabel {
        spacing: tMenuBarItem.spacing
        mirrored: tMenuBarItem.mirrored
        display: tMenuBarItem.display
        alignment: Qt.AlignLeft

        icon: tMenuBarItem.icon
        text: tMenuBarItem.text
        font: tMenuBarItem.font
        color: !tMenuBarItem.enabled ? tMenuBarItem.Universal.baseLowColor : tMenuBarItem.Universal.baseHighColor
    }

    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 20

        color: !tMenuBarItem.enabled ? tMenuBarItem.Universal.baseLowColor :
                tMenuBarItem.down ? tMenuBarItem.Universal.listMediumColor :
                tMenuBarItem.highlighted ? tMenuBarItem.Universal.listLowColor : "transparent"

        Rectangle {
            x: 1; y: 1
            width: parent.width - 2
            height: parent.height - 2

            visible: tMenuBarItem.visualFocus
            color: tMenuBarItem.Universal.accent
            opacity: tMenuBarItem.Universal.theme === Universal.Light ? 0.4 : 0.6
        }
    }
}
