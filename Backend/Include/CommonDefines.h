/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : CommonDefines.h
* Contents    : Common Definitions & Constants (Enums, SQL, Config)
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

#include <QString>

/*""ENUM COMMENT""***********************************************************/
//!@brief: Enumeration for Calculator Commands to handle Input Logic
/*""ENUM COMMENT END""*******************************************************/
enum class CalcCmd {
    Digit,                                          // 0-9 and decimal point
    Operator,                                       // +, -, *, /
    Equals,                                         // = (Calculate result)
    CE,                                             // Clear Entry (Current number)
    C,                                              // Clear All (Reset state)
    Backspace,                                      // ⌫ (Remove last digit)
    Negate,                                         // +/- (Invert sign)
    Recip,                                          // 1/x (Reciprocal)
    Sqr,                                            // x² (Square)
    Sqrt,                                           // √ (Square Root)
    Percent,                                        // % (Percentage)
    Unknown                                         // Error / Undefined
};

/*""NAMESPACE COMMENT""******************************************************/
//!@brief: Database connection settings and file paths
/*""NAMESPACE COMMENT END""**************************************************/
namespace DBConfig {
    const QString CONN_NAME = "CalcConnection";     // Unique Connection Name
    const QString DRIVER    = "QSQLITE";            // SQLite Driver
    const QString FOLDER    = "/Database";          // Folder Name
    const QString FILENAME  = "/calchistory.db";    // Database File Name
}

/*""NAMESPACE COMMENT""******************************************************/
//!@brief: Display formatting settings (Precision, Format type)
/*""NAMESPACE COMMENT END""**************************************************/
namespace DisplayConfig {
    const int PRECISION = 10;                       // Max decimal places
    const char FORMAT   = 'f';                      // Floating point format
}

/*""NAMESPACE COMMENT""******************************************************/
//!@brief: SQL Queries for History and Memory tables
/*""NAMESPACE COMMENT END""**************************************************/
namespace SQL {
    const QString INIT_TABLE_LOG  = "CREATE TABLE IF NOT EXISTS Log (expr TEXT, res TEXT)";
    const QString INIT_TABLE_MEM  = "CREATE TABLE IF NOT EXISTS Memory (val TEXT)";

    const QString GET_HISTORY     = "SELECT expr, res FROM Log ORDER BY rowid DESC LIMIT 20";
    const QString CLEAR_HISTORY   = "DELETE FROM Log";
    const QString ADD_HISTORY     = "INSERT INTO Log (expr, res) VALUES (?, ?)";

    const QString GET_MEMORY      = "SELECT val FROM Memory ORDER BY rowid DESC";
    const QString CLEAR_MEMORY    = "DELETE FROM Memory";
    const QString ADD_MEMORY      = "INSERT INTO Memory (val) VALUES (?)";

    const QString UPDATE_MEM_AT   = "UPDATE Memory SET val = ? WHERE rowid = (SELECT rowid FROM Memory ORDER BY rowid DESC LIMIT 1 OFFSET %1)";
    const QString UPDATE_MEM_LAST = "UPDATE Memory SET val = ? WHERE rowid = (SELECT MAX(rowid) FROM Memory)";

    const QString DELETE_MEM_AT   = "DELETE FROM Memory WHERE rowid = (SELECT rowid FROM Memory ORDER BY rowid DESC LIMIT 1 OFFSET %1)";
}

#endif
