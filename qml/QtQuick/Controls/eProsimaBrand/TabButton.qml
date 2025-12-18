/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Universal
import Theme 1.0

T.TabButton {
    id: tTabButton

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 6 // PivotItemMargin
    spacing: 8

    icon.width: 15
    icon.height: 15
    icon.color: Color.transparent(tTabButton.hovered ? tTabButton.Universal.baseMediumHighColor : tTabButton.Universal.foreground,
                                                    tTabButton.checked || tTabButton.down || tTabButton.hovered ? 1.0 : 0.2)

    background: Rectangle {
        // Underline that matches the content width (text + icon)
        Rectangle {
            id: underline
            visible: tTabButton.checked || tTabButton.down
            color: Theme.eProsimaLightBlue
            height: 2
            anchors.bottom: parent.bottom

            // Use the content's implicit width (natural text+icon size) so the
            // underline doesn't stretch when the tab expands to fill the row.
            // Center the underline on the content's visual center.
            width: tTabButton.contentItem ? tTabButton.contentItem.implicitWidth : 0
            x: tTabButton.contentItem ? (tTabButton.contentItem.x + tTabButton.contentItem.width/2 - width/2) : 0

            Behavior on width { NumberAnimation { duration: 120 } }
            Behavior on x { NumberAnimation { duration: 120 } }
            Behavior on visible { NumberAnimation { duration: 80 } }
        }
    }

    contentItem: IconLabel {
        spacing: tTabButton.spacing
        mirrored: tTabButton.mirrored
        display: tTabButton.display

        icon: tTabButton.icon
        text: tTabButton.text
        font: Theme.font
        color: Color.transparent(tTabButton.hovered ? tTabButton.Universal.baseMediumHighColor : tTabButton.Universal.foreground,
                                 tTabButton.checked || tTabButton.down || tTabButton.hovered ? 1.0 : 0.2)
    }
}
