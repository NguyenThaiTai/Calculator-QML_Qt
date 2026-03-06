/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : DatabaseManager.h
* Contents    : CDatabaseManager Class Definition
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

#include "CommonDefines.h"

/*""CLASS COMMENT""**********************************************************/
//!@brief: Singleton class responsible for SQLite database operations.
//!        Handles connections, queries for History and Memory tables.
/*""CLASS COMMENT END""******************************************************/
class CDatabaseManager : public QObject
{
    Q_OBJECT
public:
    static CDatabaseManager *GetInstance();

    void addHistory(const QString &expr, const QString &res);
    void clearHistory();
    QStringList fetchHistory();

    void addMemory(const QString &val);
    void updateMemoryLast(const QString &val);
    void updateMemoryAt(int index, const QString &val);
    void deleteMemoryAt(int index);
    void clearMemory();
    QStringList fetchMemory();

private:
    CDatabaseManager(QObject *parent = nullptr);
    ~CDatabaseManager();
    void init();

    static CDatabaseManager *instance;
    QSqlDatabase m_db;
};

#endif
