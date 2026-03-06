/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : main.cpp
* Contents    : Application Entry Point (Main Function)
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "Backend/Include/CalculatorBackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Basic");
    qmlRegisterType<CCalculatorBackend>("Calculator", 1, 0, "CalculatorBackend");
    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );

    engine.loadFromModule("Calculator", "Main");

    return app.exec();
}
