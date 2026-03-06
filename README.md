# Qt QML Calculator

A modern, cross-platform Calculator application developed using **Qt 6**, **QML**, and **C++**. 
This application features standard arithmetic operations, a persistent history log, and memory functions, all powered by a local SQLite database.

## Features

* **Standard Calculations**: Basic arithmetic (+, -, ×, ÷) plus advanced operators (Square Root, Square, Reciprocal, Percentage).
* **Persistent History**: Calculation history is saved automatically to a local SQLite database and persists between sessions.
* **Memory Functions**: Full support for Memory Store (MS), Recall (MR), Clear (MC), Add (M+), and Subtract (M-).
* **Responsive UI**: The interface adapts to window resizing. The History/Memory side panel automatically collapses on smaller screens.
* **MVVM Architecture**: Clean separation of concerns with QML for the UI (View) and C++ for logic (ViewModel/Model).

## Tech Stack

* **Framework**: Qt 6.8 (Quick & Quick Controls 2).
* **Language**: C++17 (Backend) & QML (Frontend).
* **Build System**: CMake (Minimum version 3.16).
* **Database**: SQLite (via `QtSql` module).

## Project Structure

*The project is organized into clear backend and frontend layers:

```
Calculator/
├── Backend/
│   ├── Include/               # Header files (.h)
│   │   ├── CalculatorBackend.h
│   │   ├── CommonDefines.h
│   │   └── DatabaseManager.h
│   └── Source/                # Source files (.cpp)
│       ├── CalculatorBackend.cpp
│       └── DatabaseManager.cpp
├── Frontend/                  # QML UI Components
│   ├── CalculatorButton.qml   # Custom button component
│   ├── DisplayScreen.qml      # Top display area
│   ├── Keypad.qml             # Button grid layout
│   └── SidePanel.qml          # History & Memory drawer
├── CMakeLists.txt             # Build configuration
├── main.cpp                   # Application entry point
└── Main.qml                   # Main window layout
```

## Database Info

*The application automatically creates a local database file named calchistory.db inside a /Database folder relative to the executable path.

*Table Log: Stores calculation history (Expression, Result).

*Table Memory: Stores memory values.

## Author

*Developer: Nguyễn Thái Tài

*Role: C/C++ Software Developer

*Copyright: (C) 2026. All rights reserved.