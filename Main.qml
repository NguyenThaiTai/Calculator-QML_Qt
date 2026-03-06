/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : Main.qml
* Contents    : Main Application Window Layout
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Calculator
import "Frontend"

Window {
    id: mainWindow
    width: 700; height: 600
    minimumWidth: 400; minimumHeight: 500
    visible: true
    title: "Calculator"
    color: "#1E1E1E"

    /*""COMPONENT COMMENT""******************************************************/
    //!@brief: Backend C++ Instance. Connects UI signals to C++ Logic.
    /*""COMPONENT COMMENT END""**************************************************/
    CalculatorBackend { id: backend }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // --- LEFT COLUMN: Screen + Toolbar + Keypad ---
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            /*""COMPONENT COMMENT""******************************************************/
            //!@brief: Custom Component for displaying results and expressions.
            /*""COMPONENT COMMENT END""**************************************************/
            DisplayScreen {
                backend: backend
                mainWindow: mainWindow
            }

            /*""COMPONENT COMMENT""******************************************************/
            //!@brief: Memory Toolbar (MC, MR, M+, M-, MS).
            //!        Only enabled when memory has data (except MS/M+/M-).
            /*""COMPONENT COMMENT END""**************************************************/
            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 34
                spacing: 0

                component MemToolBtn: Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    enabled: (text === "MC" || text === "MR") ? backend.hasMemory : true
                    background: Rectangle {
                        color: !parent.enabled ? "transparent" : (parent.hovered ? "#383838" : "transparent")
                    }
                    contentItem: Text {
                        text: parent.text
                        color: !parent.enabled ? "#505050" : "#FFFFFF";
                        font.pixelSize: 12
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    onClicked: if (enabled) backend.onMemoryCommand(text)
                }

                MemToolBtn { text: "MC" }
                MemToolBtn { text: "MR" }
                MemToolBtn { text: "M+" }
                MemToolBtn { text: "M-" }
                MemToolBtn { text: "MS" }
            }

            /*""COMPONENT COMMENT""******************************************************/
            //!@brief: Main Keypad Grid containing digits and operators.
            /*""COMPONENT COMMENT END""**************************************************/
            Keypad {
                backend: backend
            }
        }

        /*""COMPONENT COMMENT""******************************************************/
        //!@brief: Right Side Panel for History and Memory lists.
        //!        Collapsible based on window width.
        /*""COMPONENT COMMENT END""**************************************************/
        SidePanel {
            backend: backend
            mainWindow: mainWindow
        }
    }
}
