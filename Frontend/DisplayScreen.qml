/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : DisplayScreen.qml
* Contents    : Top Display Area (Menu, Title, and Result Screen)
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
//!@brief: Main container for the upper part of the calculator.
//!        Includes the Title Bar and the Numerical Display area.
/*""COMPONENT COMMENT END""**************************************************/
ColumnLayout {
    Layout.fillWidth: true
    spacing: 0

    // --- Required Properties ---

    /*""PROPERTY COMMENT""*******************************************************/
    //!@brief: Reference to C++ Backend for data binding (displayText, expressionText).
    /*""PROPERTY COMMENT END""***************************************************/
    required property var backend

    /*""PROPERTY COMMENT""*******************************************************/
    //!@brief: Reference to Main Window for responsive visibility logic.
    /*""PROPERTY COMMENT END""***************************************************/
    required property var mainWindow

    /*""COMPONENT COMMENT""******************************************************/
    //!@brief: Header Bar containing the Hamburger Menu icon and Mode Title ("Standard").
    /*""COMPONENT COMMENT END""**************************************************/
    RowLayout {
        Layout.preferredHeight: 40
        Layout.fillWidth: true
        Layout.leftMargin: 15
        spacing: 15
        Layout.minimumWidth: 200

        Text {
            text: "☰"
            color: "white"
            font.pixelSize: 18
            font.bold: true
        }
        Text {
            text: "Standard"
            color: "white"
            font.pixelSize: 20
            font.family: "Segoe UI Semibold"
        }
        Item {
            Layout.fillWidth: true
        }
    }

    /*""COMPONENT COMMENT""******************************************************/
    //!@brief: The digital screen area showing the calculation steps and result.
    //!        Responsive: Hides if the window is too small.
    /*""COMPONENT COMMENT END""**************************************************/
    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 160
        color: "transparent"

        visible: mainWindow.width >= 600 || mainWindow.height >= 300

        ColumnLayout {
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            width: parent.width - 30
            spacing: 0

            /*""COMPONENT COMMENT""******************************************************/
            //!@brief: Small top text showing the current equation (e.g., "12 + 5 =").
            /*""COMPONENT COMMENT END""**************************************************/
            Text {
                Layout.fillWidth: true
                text: backend.expressionText
                font.pixelSize: 16
                font.family: "Segoe UI"
                color: "#A0A0A0"
                horizontalAlignment: Text.AlignRight
                elide: Text.ElideRight
                textFormat: Text.RichText
            }

            /*""COMPONENT COMMENT""******************************************************/
            //!@brief: Large bottom text showing the current number or result.
            //!        Auto-scales font size to fit the width.
            /*""COMPONENT COMMENT END""**************************************************/
            Text {
                Layout.fillWidth: true
                text: backend.displayText
                font.family: "Segoe UI Semibold"
                font.pixelSize: 60
                minimumPixelSize: 20
                fontSizeMode: Text.Fit
                color: "white"
                horizontalAlignment: Text.AlignRight
            }
        }
    }
}
