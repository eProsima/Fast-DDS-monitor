import QtQuick 2.7
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Theme 1.0

MenuBar {
    id: monitorMenuBar

    signal toolBarHidden
    signal initMonitorButtonHidden
    signal dispDataButtonHidden
    signal dispDynDataButtonHidden
    signal refreshButtonHidden
    signal clearLogButtonHidden
    signal clearIssuesButtonHidden
    signal dashboardLayoutButtonHidden
    signal changeChartboxLayout(int chartsPerRow)
    signal saveAllCSV()
    signal explorerDDSEntitiesChanged(bool status)
    signal explorerPhysicalChanged(bool status)
    signal explorerLogicalChanged(bool status)
    signal explorerEntityInfoChanged(bool status)
    signal ros2DemanglingChange(bool newValue)

    signal leftSidebarHidden

    property bool inactive_visible: controller.inactive_visible()
    property bool metatraffic_visible: controller.metatraffic_visible()
    property bool ros2DemanglingActive: controller.ros2_demangling_active()

    AdaptiveMenu {
        title: qsTr("&File")
        Action {
            text: qsTr("Initialize DDS &Monitor")
            onTriggered: dialogInitMonitor.open()
        }
        Action {
            text: qsTr("Initialize Discovery Server Monitor")
            onTriggered: dialogDSInitMonitor.open()
        }
        Action {
            text: qsTr("Initialize DDS Monitor with Profile")
            onTriggered: initMonitorWithProfileDialog.open()
        }
        MenuSeparator { }
        Action {
            text: qsTr("Export Charts to &CSV")
            onTriggered: saveAllCSV()
        }
        MenuSeparator { }
        Action {
            text: qsTr("Dump")
            onTriggered: dumpDialog.open()
        }
        Action {
            text: qsTr("Dump and clear")
            onTriggered: dumpDialogClear.open()
        }
        MenuSeparator { }
        Action {
            text: qsTr("&Quit")
            onTriggered: Qt.quit()
        }
    }
    AdaptiveMenu {
        id: editMenu
        title: qsTr("&Edit")
        Action {
            text: qsTr("&Display Historical Data")
            onTriggered: dataKindDialog.open()
        }
        Action {
            text: qsTr("Display Real-&Time Data")
            onTriggered: dynamicDataKindDialog.open()
        }
        MenuSeparator { }
        Action {
            text: qsTr("Delete inactive entities")
            onTriggered: {
                controller.clear_entities()
            }
        }
        Action {
            text: qsTr("Delete statistics data")
            onTriggered: {
                controller.clear_statistics_data()
            }
        }
        Action {
            text: qsTr("Scheduler Configuration")
            onTriggered: {
                scheduleClear.open()
            }
        }
        MenuSeparator { }
        Action {
            id: editMenuRefresh
            text: qsTr("&Refresh")
            onTriggered: {
                controller.refresh_click()
            }
        }
        Action {
            text: qsTr("Clear &Log")
            onTriggered: {
                controller.clear_log()
            }
        }
        Action {
            text: qsTr("Clear &Issues")
            onTriggered: {
                controller.clear_issues()
            }
        }
    }
    AdaptiveMenu {
        title: qsTr("&View")
        implicitWidth: 250
        Action {
            text: inactive_visible ? "Hide Inactive Entities" : "Show Inactive Entities"
            onTriggered: {
                inactive_visible = !inactive_visible
                controller.change_inactive_visible()
            }
        }
        Action {
            text: metatraffic_visible ? "Hide Metatraffic" : "Show Metatraffic"
            onTriggered: {
                metatraffic_visible = !metatraffic_visible
                controller.change_metatraffic_visible()
            }
        }
        Action {
            text: ros2DemanglingActive ? "Revert ROS 2 Demangling" : "Perform ROS 2 Demangling"
            onTriggered: {
                ros2DemanglingActive = !ros2DemanglingActive
                controller.change_ros2_demangling()
                ros2DemanglingChange(ros2DemanglingActive);
            }
        }
        MenuSeparator { }
        AdaptiveMenu {
            id: dashboardLayout
            title: qsTr("&Dashboard Layout")
            Action {
                id: dashboardLayoutLarge
                text: "Large"
                checkable: true
                checked: false
                onTriggered: {
                    if (!checked) {
                        checked = true
                    } else {
                        dashboardLayoutMedium.checked = false
                        dashboardLayoutSmall.checked = false
                    }

                    changeChartboxLayout(1)
                }
            }
            Action {
                id: dashboardLayoutMedium
                text: "Medium"
                checkable: true
                checked: true
                onTriggered: {
                    if (!checked) {
                        checked = true
                    } else {
                        dashboardLayoutLarge.checked = false
                        dashboardLayoutSmall.checked = false
                    }

                    changeChartboxLayout(2)
                }
            }
            Action {
                id: dashboardLayoutSmall
                text: "Small"
                checkable: true
                checked: false
                onTriggered: {
                    if (!checked) {
                        checked = true
                    } else {
                        dashboardLayoutLarge.checked = false
                        dashboardLayoutMedium.checked = false
                    }

                    changeChartboxLayout(3)
                }
            }

            delegate: MenuItem {
                id: menuItem
                property string iconName: menuItem.text == "Large" ? "grid1" :
                                          menuItem.text == "Medium" ? "grid2" : "grid3"

                indicator: Item {
                    x: contentItem.x + contentItem.leftPadding / 3
                    y: contentItem.y + contentItem.height / 2
                    Rectangle {
                        width: 20
                        height: 20
                        anchors.centerIn: parent
                        visible: menuItem.checkable
                        IconSVG {
                            id: participantIcon
                            name: menuItem.iconName
                            size: parent.width
                            anchors.centerIn: parent
                            visible: menuItem.checkable
                            color: menuItem.checked ? "eProsimaLightBlue" : "black"
                        }
                    }
                }

                contentItem: Text {
                    id: contentItem
                    leftPadding: 35
                    text: menuItem.text
                    opacity: enabled ? 1.0 : 0.3
                    color: menuItem.checked ? Theme.eProsimaLightBlue : "black"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
            }
        }
        MenuSeparator { }
        Action {
            text: (toolBar.isVisible) ? "Hide Shorcuts Toolbar" : "Show Shorcuts Toolbar"
            onTriggered: toolBarHidden()
        }
        Action {
            text: qsTr("Customize Shorcuts Toolbar")
            onTriggered: customizeShorcutsToolbarDialog.open()
        }
        MenuSeparator { }
        Action {
            text: (panels.showLeftSidebar) ? "Hide Left sidebar" : "Show Left Sidebar"
            onTriggered: leftSidebarHidden()
        }
        AdaptiveMenu {
            id: contextMenu
            title: qsTr("Customize Left Sidebar")

            Action {
                id: contextMenuDDSEntities
                text: "DDS Entities"
                checkable: true
                checked: true
                onTriggered: explorerDDSEntitiesChanged(checked)
            }
            Action {
                id: contextMenuPhysical
                text: "Physical"
                checkable: true
                onTriggered: explorerPhysicalChanged(checked)
            }
            Action {
                id: contextMenuLogical
                text: "Logical"
                checkable: true
                onTriggered: explorerLogicalChanged(checked)
            }
            Action {
                id: contextMenuEntityInfo
                text: "Entity Info"
                checkable: true
                checked: true
                onTriggered: explorerEntityInfoChanged(checked)
            }
        }
    }

    AdaptiveMenu {
        title: qsTr("&Help")
        Action {
            text: qsTr("&Documentation")
            onTriggered: Qt.openUrlExternally("https://fast-dds-monitor.readthedocs.io/en/latest/")
        }
        Action {
            text: qsTr("&Release Notes")
            onTriggered: Qt.openUrlExternally("https://github.com/eProsima/Fast-DDS-monitor/releases")
        }
        MenuSeparator { }
        Action {
            text: qsTr("Join Us on &Twitter")
            onTriggered: Qt.openUrlExternally("https://twitter.com/EProsima")
        }
        Action {
            text: qsTr("Search &Feature Requests")
            onTriggered: Qt.openUrlExternally("https://github.com/eProsima/Fast-DDS-monitor/issues")
        }
        Action {
            text: qsTr("Report &Issue")
            onTriggered: Qt.openUrlExternally("https://github.com/eProsima/Fast-DDS-monitor/issues/new")
        }
        MenuSeparator { }
        Action {
            text: qsTr("&About")
            onTriggered: aboutDialog.open()
        }
    }

    Dialog {
        id: customizeShorcutsToolbarDialog
        title: "Customize Shortcuts Toolbar"
        anchors.centerIn: Overlay.overlay
        standardButtons: DialogButtonBox.Close

        GridLayout {
            columns: 2

            CheckBox {
                id: dashboardLayoutCheckBox
                checked: true
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: dashboardLayoutButtonHidden()
            }
            Label {
                text: "Dashboard Layout"
            }
            CheckBox {
                id: displayNewDataCheckBox
                checked: false
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: dispDataButtonHidden()
            }
            Label {
                text: "Display Historical Data"
            }
            CheckBox {
                id: displayDynamicDataCheckBox
                checked: true
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: dispDynDataButtonHidden()
            }
            Label {
                text: "Display Real-Time Data"
            }
            CheckBox {
                id: refreshCheckBox
                checked: true
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: refreshButtonHidden()
            }
            Label {
                text: "Refresh"
            }
            CheckBox {
                id: clearLogCheckBox
                checked: false
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: clearLogButtonHidden()
            }
            Label {
                text: "Clear Log"
            }
            CheckBox {
                id: clearIssuesCheckBox
                checked: false
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: clearIssuesButtonHidden()
            }
            Label {
                text: "Clear Issues"
            }
        }
    }

    function changeChartboxLayoutViewMenu(chartsPerRow) {
        switch (chartsPerRow) {
            case 1:
                dashboardLayoutLarge.trigger()
                break
            case 2:
                dashboardLayoutMedium.trigger()
                break
            case 3:
                dashboardLayoutSmall.trigger()
                break
            default:
                break
        }
    }

    function changeExplorerDDSEntities(status) {
        contextMenuDDSEntities.checked = status
    }

    function changeExplorerPhysical(status) {
        contextMenuPhysical.checked = status
    }

    function changeExplorerLogical(status) {
        contextMenuLogical.checked = status
    }

    function changeExplorerEntityInfo(status) {
        contextMenuEntityInfo.checked = status
    }
}
