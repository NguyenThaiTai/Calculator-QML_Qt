/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : SidePanel.qml
* Contents    : Side Panel for History and Memory Lists
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

/*""COMPONENT COMMENT""******************************************************/
//!@brief: Side Drawer Component.
//!        Displays History and Memory lists. Visibility is responsive to window width.
/*""COMPONENT COMMENT END""**************************************************/
Rectangle {
    Layout.preferredWidth: 320
    Layout.fillHeight: true
    color: "#1E1E1E"

    /*""PROPERTY COMMENT""*******************************************************/
    //!@brief: Reference to C++ Backend for data models (historyList, memoryList).
    /*""PROPERTY COMMENT END""***************************************************/
    required property var backend

    /*""PROPERTY COMMENT""*******************************************************/
    //!@brief: Reference to Main Window for responsive layout logic.
    /*""PROPERTY COMMENT END""***************************************************/
    required property var mainWindow

    visible: mainWindow.width >= 550 // Auto-hide if window is too narrow

    // --- Internal State & Style ---
    property int currentTab: 0 // 0: History, 1: Memory
    readonly property color cTextWhite: "#FFFFFF"
    readonly property color cTextGray: "#A0A0A0"
    readonly property color cHover: "#383838"

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        /*""COMPONENT COMMENT""******************************************************/
        //!@brief: Tab Navigation Bar (History | Memory).
        //!        Includes clickable text and an underline indicator.
        /*""COMPONENT COMMENT END""**************************************************/
        RowLayout {
            Layout.preferredHeight: 50
            Layout.fillWidth: true
            spacing: 20
            Layout.leftMargin: 20

            component TabText: Text {
                property int tabIndex: 0
                text: tabIndex === 0 ? "History" : "Memory"
                color: currentTab === tabIndex ? cTextWhite : cTextGray
                font.bold: currentTab === tabIndex
                font.pixelSize: 16
                font.family: "Segoe UI"
                MouseArea {
                    anchors.fill: parent
                    onClicked: currentTab = parent.tabIndex
                }

                // Active Tab Indicator (Blue line)
                Rectangle {
                    width: parent.width
                    height: 3
                    color: "#005A9E"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -8
                    visible: currentTab === parent.tabIndex
                    radius: 2
                }
            }
            TabText { tabIndex: 0 }
            TabText { tabIndex: 1 }
        }

        /*""COMPONENT COMMENT""******************************************************/
        //!@brief: Main Content Area. Uses StackLayout to switch between views.
        /*""COMPONENT COMMENT END""**************************************************/
        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: currentTab

            // --- VIEW 1: HISTORY LIST ---
            Item {
                // Empty State Message
                Text {
                    text: "There's no history yet."
                    color: cTextWhite
                    visible: backend.historyList.length === 0
                    font.family: "Segoe UI"
                    font.bold: true
                    font.pixelSize: 14
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                ListView {
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        bottom: btnClearHistory.top
                        margins: 15;
                        bottomMargin: 10
                    }
                    clip: true
                    spacing: 20
                    model: backend.historyList
                    delegate: Column {
                        width: parent.width
                        spacing: 2
                        Text {
                            text: modelData.split("=")[0] + " ="
                            color: cTextGray
                            font.pixelSize: 14
                            width: parent.width
                            horizontalAlignment: Text.AlignRight
                            textFormat: Text.RichText
                        }

                        Text {
                            text: modelData.split("=")[1]
                            color: cTextWhite
                            font.pixelSize: 22
                            font.bold: true
                            width: parent.width
                            horizontalAlignment: Text.AlignRight
                        }
                    }
                }

                // Trash Button (Clear History)
                Button {
                    id: btnClearHistory
                    visible: backend.historyList.length > 0
                    background: null
                    contentItem: Text {
                        text: "🗑"
                        color: "white"
                        font.pixelSize: 20
                    }
                    anchors {
                        bottom: parent.bottom
                        right: parent.right
                        margins: 10
                    }
                    onClicked: backend.clearHistory()
                }
            }

            // --- VIEW 2: MEMORY LIST ---
            Item {
                // Empty State Message
                Text {
                    text: "There's nothing saved in memory."
                    color: cTextWhite
                    visible: backend.memoryList.length === 0
                    font.family: "Segoe UI"
                    font.bold: true
                    font.pixelSize: 14
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                ListView {
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        bottom: btnClearMemory.top
                        margins: 15
                        bottomMargin: 10
                    }
                    clip: true
                    spacing: 10
                    model: backend.memoryList
                    delegate: Item {
                        width: parent.width
                        height: 80

                        // Hover Effect Background
                        Rectangle {
                            anchors.fill: parent
                            color: mouseArea.containsMouse ? cHover : "transparent"
                            radius: 4
                        }
                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                        }

                        // Memory Value
                        Text {
                            text: modelData
                            color: cTextWhite
                            font.pixelSize: 24
                            font.bold: true
                            font.family: "Segoe UI"
                            anchors {
                                top: parent.top
                                right: parent.right
                                topMargin: 10
                                rightMargin: 15
                            }
                        }

                        // Mini Controls (MC, M+, M-) - Visible on Hover
                        Row {
                            visible: mouseArea.containsMouse
                            anchors {
                                right: parent.right
                                bottom: parent.bottom
                                margins: 8
                            }
                            spacing: 15

                            component MiniMemBtn: Text {
                                property string btnText
                                property var btnAction
                                text: btnText
                                color: maBtn.containsMouse ? cTextWhite : cTextGray
                                font.pixelSize: 13
                                font.bold: true
                                font.family: "Segoe UI"
                                MouseArea {
                                    id: maBtn;
                                    anchors.fill: parent
                                    anchors.margins: -8
                                    hoverEnabled: true
                                    onClicked: parent.btnAction()
                                }
                            }
                            MiniMemBtn { btnText: "MC"; btnAction: () => backend.clearMemoryIndex(index) }
                            MiniMemBtn { btnText: "M+"; btnAction: () => backend.memoryAddAt(index) }
                            MiniMemBtn { btnText: "M-"; btnAction: () => backend.memorySubAt(index) }
                        }
                    }
                }

                // Trash Button (Clear All Memory)
                Button {
                    id: btnClearMemory
                    visible: backend.memoryList.length > 0
                    background: null
                    contentItem: Text {
                        text: "🗑"
                        color: "white"
                        font.pixelSize: 20
                    }
                    anchors {
                        bottom: parent.bottom
                        right: parent.right
                        margins: 10
                    }
                    onClicked: backend.onMemoryCommand("MC")
                }
            }
        }
    }
}
