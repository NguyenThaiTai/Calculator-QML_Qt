cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add Sqlite
find_package(Qt6 REQUIRED COMPONENTS Quick Sql QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appCalculator
    main.cpp
)

target_include_directories(appCalculator PRIVATE Backend/Include)

qt_add_qml_module(appCalculator
    URI Calculator
    VERSION 1.0
    QML_FILES
        Main.qml
        Frontend/CalculatorButton.qml
        Frontend/DisplayScreen.qml
        Frontend/Keypad.qml
        Frontend/SidePanel.qml
    SOURCES
        # Header Files
        Backend/Include/CommonDefines.h
        Backend/Include/CalculatorBackend.h
        Backend/Include/DatabaseManager.h

        # Source Files
        Backend/Source/calculatorbackend.cpp
        Backend/Source/DatabaseManager.cpp
)

target_link_libraries(appCalculator
    PRIVATE Qt6::Quick Qt6::Sql Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appCalculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
