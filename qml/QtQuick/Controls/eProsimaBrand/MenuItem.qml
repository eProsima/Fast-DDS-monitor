// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick 6.8
import QtQuick.Templates 6.8 as T
import QtQuick.Controls.impl 6.8
import QtQuick.Controls.Universal 6.8

T.MenuItem {
    id: tMenuItem

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             implicitIndicatorHeight + topPadding + bottomPadding)

    padding: 12
    topPadding: padding - 1
    bottomPadding: padding + 1
    spacing: 12

    icon.width: 20
    icon.height: 20
    icon.color: !enabled ? Universal.baseLowColor : Universal.baseHighColor

    contentItem: IconLabel {
        readonly property real arrowPadding: tMenuItem.subMenu && tMenuItem.arrow ? tMenuItem.arrow.width + tMenuItem.spacing : 0
        readonly property real indicatorPadding: tMenuItem.checkable && tMenuItem.indicator ? tMenuItem.indicator.width + tMenuItem.spacing : 0
        leftPadding: !tMenuItem.mirrored ? indicatorPadding : arrowPadding
        rightPadding: tMenuItem.mirrored ? indicatorPadding : arrowPadding

        spacing: tMenuItem.spacing
        mirrored: tMenuItem.mirrored
        display: tMenuItem.display
        alignment: Qt.AlignLeft

        icon: tMenuItem.icon
        text: tMenuItem.text
        font: tMenuItem.font
        color: !tMenuItem.enabled ? tMenuItem.Universal.baseLowColor : tMenuItem.Universal.baseHighColor
    }

    arrow: ColorImage {
        x: tMenuItem.mirrored ? tMenuItem.leftPadding : tMenuItem.width - width - tMenuItem.rightPadding
        y: tMenuItem.topPadding + (tMenuItem.availableHeight - height) / 2

        visible: tMenuItem.subMenu
        mirror: tMenuItem.mirrored
        color: !enabled ? tMenuItem.Universal.baseLowColor : tMenuItem.Universal.baseHighColor
        source: "qrc:/qt-project.org/imports/QtQuick/Controls/Universal/images/rightarrow.png"
    }

    indicator: ColorImage {
        x: tMenuItem.text ? (tMenuItem.mirrored ? tMenuItem.width - width - tMenuItem.rightPadding : tMenuItem.leftPadding) : tMenuItem.leftPadding + (tMenuItem.availableWidth - width) / 2
        y: tMenuItem.topPadding + (tMenuItem.availableHeight - height) / 2

        visible: tMenuItem.checked
        color: !tMenuItem.enabled ? tMenuItem.Universal.baseLowColor : tMenuItem.down ? tMenuItem.Universal.baseHighColor : tMenuItem.Universal.baseMediumHighColor
        source: !tMenuItem.checkable ? "" : "qrc:/qt-project.org/imports/QtQuick/Controls/Universal/images/checkmark.png"
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 40

        color: !tMenuItem.enabled ? tMenuItem.Universal.baseLowColor :
                tMenuItem.down ? tMenuItem.Universal.listMediumColor :
                tMenuItem.highlighted ? tMenuItem.Universal.listLowColor : tMenuItem.Universal.altMediumLowColor

        Rectangle {
            x: 1; y: 1
            width: parent.width - 2
            height: parent.height - 2

            visible: tMenuItem.visualFocus
            color: tMenuItem.Universal.accent
            opacity: tMenuItem.Universal.theme === Universal.Light ? 0.4 : 0.6
        }
    }
}
