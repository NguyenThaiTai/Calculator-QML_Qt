/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : DatabaseManager.cpp
* Contents    : CDatabaseManager Class Implementation
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

#include "DatabaseManager.h"

/*""FUNC COMMENT""***********************************************************/
//!@brief: Constructor for CDatabaseManager. Automatically initializes the database.
//!@param[in]: parent (The parent QObject, default is nullptr)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
CDatabaseManager::CDatabaseManager(QObject *parent) : QObject(parent) {
    init();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Destructor. Closes the database connection if it is open.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
CDatabaseManager::~CDatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

// Static instance initialization
CDatabaseManager* CDatabaseManager::instance = nullptr;

/*""FUNC COMMENT""***********************************************************/
//!@brief: Static method to retrieve the singleton instance. Creates it if not exists.
//!@param[in]: None
//!@param[out]: None
//!@return: Pointer to the static CDatabaseManager instance
/*""FUNC COMMENT END""*******************************************************/
CDatabaseManager* CDatabaseManager::GetInstance() {
    if(instance == nullptr)
    {
        instance = new CDatabaseManager();
    }
    return instance;
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Initializes the SQLite database connection, creates folder/file and tables if needed.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::init() {
    if (QSqlDatabase::contains(DBConfig::CONN_NAME)) {
        m_db = QSqlDatabase::database(DBConfig::CONN_NAME);
    } else {
        m_db = QSqlDatabase::addDatabase(DBConfig::DRIVER, DBConfig::CONN_NAME);

        QString appPath = QCoreApplication::applicationDirPath();
        QString dbFolderPath = appPath + DBConfig::FOLDER;

        QDir dir(dbFolderPath);
        if (!dir.exists()) dir.mkpath(".");

        m_db.setDatabaseName(dbFolderPath + DBConfig::FILENAME);
    }

    if (!m_db.isOpen() && !m_db.open()) {
        qDebug() << "DB Error:" << m_db.lastError().text();
        return;
    }

    QSqlQuery q(m_db);
    q.exec(SQL::INIT_TABLE_LOG);
    q.exec(SQL::INIT_TABLE_MEM);
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Adds a new calculation record to the History table (Log).
//!@param[in]: expr (The expression string)
//!@param[in]: res (The result string)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::addHistory(const QString &expr, const QString &res) {
    QSqlQuery q(m_db);
    q.prepare(SQL::ADD_HISTORY);
    q.addBindValue(expr);
    q.addBindValue(res);
    q.exec();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Clears all records from the History table.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::clearHistory() {
    QSqlQuery q(m_db);
    q.exec(SQL::CLEAR_HISTORY);
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Fetches the latest history records formatted as "Expression = Result".
//!@param[in]: None
//!@param[out]: None
//!@return: A QStringList containing the formatted history strings
/*""FUNC COMMENT END""*******************************************************/
QStringList CDatabaseManager::fetchHistory() {
    QStringList list;
    QSqlQuery q(m_db);
    q.prepare(SQL::GET_HISTORY);
    q.exec();
    while(q.next()) {
        list.append(q.value(0).toString() + " = " + q.value(1).toString());
    }
    return list;
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Adds a new value to the Memory table.
//!@param[in]: val (The value to store)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::addMemory(const QString &val) {
    QSqlQuery q(m_db);
    q.prepare(SQL::ADD_MEMORY);
    q.addBindValue(val);
    q.exec();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Updates the most recently added memory value (Last row).
//!@param[in]: val (The new value)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::updateMemoryLast(const QString &val) {
    QSqlQuery q(m_db);
    q.prepare(SQL::UPDATE_MEM_LAST);
    q.addBindValue(val);
    q.exec();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Updates a specific memory value at a given index offset.
//!@param[in]: index (The row index to update)
//!@param[in]: val (The new value)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::updateMemoryAt(int index, const QString &val) {
    QSqlQuery q(m_db);
    q.prepare(SQL::UPDATE_MEM_AT.arg(index));
    q.addBindValue(val);
    q.exec();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Deletes a specific memory record at a given index offset.
//!@param[in]: index (The row index to delete)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::deleteMemoryAt(int index) {
    QSqlQuery q(m_db);
    q.prepare(SQL::DELETE_MEM_AT.arg(index));
    q.exec();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Clears all records from the Memory table.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CDatabaseManager::clearMemory() {
    QSqlQuery q(m_db);
    q.exec(SQL::CLEAR_MEMORY);
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Fetches all memory records from the database.
//!@param[in]: None
//!@param[out]: None
//!@return: A QStringList containing the memory values
/*""FUNC COMMENT END""*******************************************************/
QStringList CDatabaseManager::fetchMemory() {
    QStringList list;
    QSqlQuery q(m_db);
    q.prepare(SQL::GET_MEMORY);
    q.exec();
    while(q.next()) {
        list.append(q.value(0).toString());
    }
    return list;
}
