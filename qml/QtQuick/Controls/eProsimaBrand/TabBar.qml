// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick 6.8
import QtQuick.Templates 6.8 as T
import QtQuick.Controls.Universal 6.8

import Theme 1.0

T.TabBar {
    id: tTabBar

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight)

    contentItem: ListView {
        model: tTabBar.contentModel
        currentIndex: tTabBar.currentIndex

        spacing: tTabBar.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: ListView.SnapToItem

        highlightMoveDuration: 100
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: 48
        preferredHighlightEnd: width - 48
    }

    background: Rectangle {
        anchors.fill: parent
        color: tTabBar.Universal.background
    }
}
