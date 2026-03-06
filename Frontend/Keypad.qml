/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : Keypad.qml
* Contents    : Main Keypad Layout (Digits & Operators Grid)
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

import QtQuick
import QtQuick.Layouts

/*""COMPONENT COMMENT""******************************************************/
//!@brief: A Grid Layout containing all calculator buttons (digits & operators).
//!        Arranged in a standard 4-column layout with uniform cell sizes.
/*""COMPONENT COMMENT END""**************************************************/
GridLayout {
    Layout.fillWidth: true;
    Layout.fillHeight: true
    Layout.margins: 4
    columns: 4
    rowSpacing: 2;
    columnSpacing: 2
    uniformCellWidths: true;
    uniformCellHeights: true

    /*""PROPERTY COMMENT""*******************************************************/
    //!@brief: Reference to the C++ Backend. Passed down to child CalculatorButton elements.
    /*""PROPERTY COMMENT END""***************************************************/
    required property var backend

    // --- Row 1 ---
    CalculatorButton { text: "%"; backend: parent.backend }
    CalculatorButton { text: "CE"; backend: parent.backend }
    CalculatorButton { text: "C"; backend: parent.backend }
    CalculatorButton { text: "⌫"; backend: parent.backend; font.family: "Segoe UI Symbol" }

    // --- Row 2 ---
    CalculatorButton { text: "recip"; displayKey: "¹/𝑥"; backend: parent.backend }
    CalculatorButton { text: "sqr";   displayKey: "𝑥²"; backend: parent.backend }
    CalculatorButton { text: "sqrt";  displayKey: "²√𝑥"; backend: parent.backend }
    CalculatorButton { text: "/";     displayKey: "÷"; backend: parent.backend }

    // --- Row 3 ---
    CalculatorButton { text: "7"; backend: parent.backend }
    CalculatorButton { text: "8"; backend: parent.backend }
    CalculatorButton { text: "9"; backend: parent.backend }
    CalculatorButton { text: "*"; displayKey: "×"; backend: parent.backend }

    // --- Row 4 ---
    CalculatorButton { text: "4"; backend: parent.backend }
    CalculatorButton { text: "5"; backend: parent.backend }
    CalculatorButton { text: "6"; backend: parent.backend }
    CalculatorButton { text: "-"; displayKey: "−"; backend: parent.backend }

    // --- Row 5 ---
    CalculatorButton { text: "1"; backend: parent.backend }
    CalculatorButton { text: "2"; backend: parent.backend }
    CalculatorButton { text: "3"; backend: parent.backend }
    CalculatorButton { text: "+"; backend: parent.backend }

    // --- Row 6 ---
    CalculatorButton { text: "+/-"; backend: parent.backend }
    CalculatorButton { text: "0"; backend: parent.backend }
    CalculatorButton { text: "."; backend: parent.backend }
    CalculatorButton { text: "="; backend: parent.backend }
}
