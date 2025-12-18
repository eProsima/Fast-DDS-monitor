// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Universal
import Theme 1.0

T.MenuBar {
    id: tMenuBar

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    delegate: CustomMenuBarItem { }

    contentItem: Row {
        spacing: tMenuBar.spacing
        Repeater {
            model: tMenuBar.contentModel
        }
    }

    background: Rectangle {
        implicitHeight: 20
        color: tMenuBar.Universal.chromeMediumColor

        Rectangle {
            color: tMenuBar.Universal.baseMediumColor
            width: parent.width
            height: 2
            anchors.bottom: parent.bottom
        }
    }
}
