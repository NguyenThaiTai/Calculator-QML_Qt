/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : CalculatorButton.qml
* Contents    : Custom Button Component for Calculator Keypad
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

/*""COMPONENT COMMENT""******************************************************/
//!@brief: A reusable button component that sends commands to the C++ backend.
//!        Supports custom display text, hover effects and different color themes (Number vs Operator).
/*""COMPONENT COMMENT END""**************************************************/
Button {
    id: btn
    Layout.fillWidth: true
    Layout.fillHeight: true

    /*""PROPERTY COMMENT""*******************************************************/
    //!@brief: Optional display symbol (e.g., "÷") different from the logical command (e.g., "/").
    /*""PROPERTY COMMENT END""***************************************************/
    property string displayKey: ""

    /*""PROPERTY COMMENT""*******************************************************/
    //!@brief: Reference to the C++ Backend object to invoke commands.
    /*""PROPERTY COMMENT END""***************************************************/
    required property var backend

    // --- Internal Logic & Styling ---

    // Check button type to apply correct color theme
    property bool isEquals: text === "="
    property bool isNum: ["0","1","2","3","4","5","6","7","8","9",".",","].includes(text)

    // Color Palette (Local constants)
    readonly property color cBtnNum: "#2D2D2D"
    readonly property color cBtnOp: "#252525"
    readonly property color cBtnEquals: "#005A9E"
    readonly property color cHover: "#383838"
    readonly property color cPressed: "#191919"
    readonly property color cTextWhite: "#FFFFFF"

    /*""COMPONENT COMMENT""******************************************************/
    //!@brief: Custom Background implementation.
    //!        Handles state changes (Pressed, Hovered, Normal) and Type changes (Equals, Number, Operator).
    /*""COMPONENT COMMENT END""**************************************************/
    background: Rectangle {
        radius: 4
        color: {
            if (btn.down) return isEquals ? "#004578" : cPressed
            if (btn.hovered) {
                if (isEquals) return "#006CC1"
                return cHover
            }
            return isEquals ? cBtnEquals : (isNum ? cBtnNum : cBtnOp)
        }
    }

    /*""COMPONENT COMMENT""******************************************************/
    //!@brief: Custom Text Content.
    //!        Prioritizes 'displayKey' if set, otherwise uses 'text'.
    /*""COMPONENT COMMENT END""**************************************************/
    contentItem: Text {
        text: (btn.displayKey !== "") ? btn.displayKey : btn.text
        font.pixelSize: 22
        font.family: "Segoe UI"
        font.italic: btn.displayKey !== "" // Italic style for math symbols
        textFormat: Text.RichText
        color: cTextWhite
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    /*""SIGNAL COMMENT""*********************************************************/
    //!@brief: On Click, send the logical 'text' (not displayKey) to Backend.
    /*""SIGNAL COMMENT END""*****************************************************/
    onClicked: backend.onCommand(text)
}
