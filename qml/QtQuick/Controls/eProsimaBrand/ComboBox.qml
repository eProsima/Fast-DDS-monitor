// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Window
import QtQuick.Controls.impl
import QtQuick.Templates as T
import QtQuick.Controls.Universal

T.ComboBox {
    id: tComboBox

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             implicitIndicatorHeight + topPadding + bottomPadding)

    leftPadding: padding + (!tComboBox.mirrored || !indicator || !indicator.visible ? 0 : indicator.width + spacing)
    rightPadding: padding + (tComboBox.mirrored || !indicator || !indicator.visible ? 0 : indicator.width + spacing)

    Universal.theme: editable && activeFocus ? Universal.Light : undefined

    delegate: ItemDelegate {
        required property var model
        required property int index

        width: ListView.view.width
        // Make each item have the same height as the ComboBox tComboBox
        implicitHeight: tComboBox.implicitHeight

        text: model[tComboBox.textRole]
        font.weight: tComboBox.currentIndex === index ? Font.DemiBold : Font.Normal
        highlighted: tComboBox.highlightedIndex === index
        hoverEnabled: tComboBox.hoverEnabled

        // Highlight hovered item with theme accent and preserve contrast
        background: Rectangle {
            anchors.fill: parent
            color: tComboBox.highlightedIndex === index ? tComboBox.Universal.accent : "transparent"
            opacity: tComboBox.highlightedIndex === index ? 0.4 : 1.0
        }
    }

    indicator: ColorImage {
        x: tComboBox.mirrored ? tComboBox.padding : tComboBox.width - width - tComboBox.padding
        y: tComboBox.topPadding + (tComboBox.availableHeight - height) / 2
        color: !tComboBox.enabled ? tComboBox.Universal.baseLowColor : tComboBox.Universal.baseMediumHighColor
        source: "qrc:/qt-project.org/imports/QtQuick/Controls/Universal/images/downarrow.png"

        Rectangle {
            z: -1
            width: parent.width
            height: parent.height
            color: tComboBox.activeFocus ? tComboBox.Universal.accent :
                   tComboBox.pressed ? tComboBox.Universal.baseMediumLowColor :
                   tComboBox.hovered ? tComboBox.Universal.baseLowColor : "transparent"
            visible: tComboBox.editable && !tComboBox.contentItem.hovered && (tComboBox.pressed || tComboBox.hovered)
            opacity: tComboBox.activeFocus && !tComboBox.pressed ? 0.4 : 1.0
        }
    }

    contentItem: T.TextField {
        leftPadding: tComboBox.mirrored ? 1 : 12
        rightPadding: tComboBox.mirrored ? 10 : 1
        topPadding: 5 - tComboBox.topPadding
        bottomPadding: 7 - tComboBox.bottomPadding

        text: tComboBox.editable ? tComboBox.editText : tComboBox.displayText

        enabled: tComboBox.editable
        autoScroll: tComboBox.editable
        readOnly: tComboBox.down
        inputMethodHints: tComboBox.inputMethodHints
        validator: tComboBox.validator
        selectByMouse: tComboBox.selectTextByMouse

        color: !tComboBox.enabled ? tComboBox.Universal.chromeDisabledLowColor :
                tComboBox.editable && tComboBox.activeFocus ? tComboBox.Universal.chromeBlackHighColor : tComboBox.Universal.foreground
        selectionColor: tComboBox.Universal.accent
        selectedTextColor: tComboBox.Universal.chromeWhiteColor
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 32

        border.width: tComboBox.flat ? 0 : 2 // ComboBoxBorderThemeThickness
        border.color: !tComboBox.enabled ? tComboBox.Universal.baseLowColor :
                       tComboBox.editable && tComboBox.activeFocus ? tComboBox.Universal.accent :
                       tComboBox.down ? tComboBox.Universal.baseMediumLowColor :
                       tComboBox.hovered ? tComboBox.Universal.baseMediumColor : tComboBox.Universal.baseMediumLowColor
        color: !tComboBox.enabled ? tComboBox.Universal.baseLowColor :
                tComboBox.down ? tComboBox.Universal.listMediumColor :
                tComboBox.flat && tComboBox.hovered ? tComboBox.Universal.listLowColor :
                tComboBox.editable && tComboBox.activeFocus ? tComboBox.Universal.background : tComboBox.Universal.altMediumLowColor
        visible: !tComboBox.flat || tComboBox.pressed || tComboBox.hovered || tComboBox.visualFocus

        Rectangle {
            x: 2
            y: 2
            width: parent.width - 4
            height: parent.height - 4

            visible: tComboBox.visualFocus && !tComboBox.editable
            color: tComboBox.Universal.accent
            opacity: tComboBox.Universal.theme === Universal.Light ? 0.4 : 0.6
        }
    }

    popup: T.Popup {
        width: tComboBox.width
        height: Math.min(contentItem.implicitHeight, tComboBox.Window.height - topMargin - bottomMargin)
        topMargin: 8
        bottomMargin: 8

        Universal.theme: tComboBox.Universal.theme
        Universal.accent: tComboBox.Universal.accent

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: tComboBox.delegateModel
            currentIndex: tComboBox.highlightedIndex
            highlightMoveDuration: 0

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: tComboBox.Universal.chromeMediumLowColor
            border.color: tComboBox.Universal.chromeHighColor
            border.width: 1 // FlyoutBorderThemeThickness
        }
    }
}
