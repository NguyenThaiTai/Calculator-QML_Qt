/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : calculatorbackend.h
* Contents    : CCalculatorBackend Class Definition
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/

#ifndef CALCULATORBACKEND_H
#define CALCULATORBACKEND_H

#include <QObject>
#include <QStandardPaths>
#include <QDebug>
#include <cmath>
#include "CommonDefines.h"
#include "DatabaseManager.h"

/*""CLASS COMMENT""**********************************************************/
//!@brief: Backend controller class for the Calculator.
//!        Handles arithmetic logic, maintains state and interfaces with the DatabaseManager.
/*""CLASS COMMENT END""******************************************************/
class CCalculatorBackend : public QObject
{
    Q_OBJECT
    //!@brief: Property for the main display text (the large number).
    Q_PROPERTY(QString displayText READ displayText NOTIFY displayTextChanged)

    //!@brief: Property for the expression text (the small formula above).
    Q_PROPERTY(QString expressionText READ expressionText NOTIFY expressionTextChanged)

    //!@brief: Property for the history list model.
    Q_PROPERTY(QStringList historyList READ historyList NOTIFY historyListChanged)

    //!@brief: Property for the memory list model.
    Q_PROPERTY(QStringList memoryList READ memoryList NOTIFY memoryListChanged)

    //!@brief: Property to check if memory contains any items (used for UI visibility).
    Q_PROPERTY(bool hasMemory READ hasMemory NOTIFY memoryListChanged)

private:
    void updateHistory();
    void updateMemory();
    void calculate();
    QString formatNumber(double value);
    CalcCmd mapCommand(const QString &input);

    QString m_displayText = "0";
    QString m_expressionText = "";
    QStringList m_historyList;
    QStringList m_memoryList;
    QString m_op = "";
    double m_firstNum = 0;
    bool m_newNumber = true;
    QString m_cachedOp = "";
    double m_cachedSecondNum = 0;
    QString m_tempStepString = "";

public:
    CCalculatorBackend(QObject *parent = nullptr);

    /*""FUNC COMMENT""***********************************************************/
    //!@brief: Processes input commands (digits, operators, special keys).
    //!@param[in]: input (The button text or command string)
    //!@param[out]: None
    //!@return: None
    /*""FUNC COMMENT END""*******************************************************/
    Q_INVOKABLE void onCommand(const QString &input);

    /*""FUNC COMMENT""***********************************************************/
    //!@brief: Processes memory-related commands (MS, MR, MC, M+, M-).
    //!@param[in]: cmd (The memory command string)
    //!@param[out]: None
    //!@return: None
    /*""FUNC COMMENT END""*******************************************************/
    Q_INVOKABLE void onMemoryCommand(const QString &cmd);

    /*""FUNC COMMENT""***********************************************************/
    //!@brief: Clears the entire history log.
    //!@param[in]: None
    //!@param[out]: None
    //!@return: None
    /*""FUNC COMMENT END""*******************************************************/
    Q_INVOKABLE void clearHistory();

    /*""FUNC COMMENT""***********************************************************/
    //!@brief: Clears a specific memory item by index.
    //!@param[in]: index (Index in the memory list)
    //!@param[out]: None
    //!@return: None
    /*""FUNC COMMENT END""*******************************************************/
    Q_INVOKABLE void clearMemoryIndex(int index);

    /*""FUNC COMMENT""***********************************************************/
    //!@brief: Adds current value to memory at a specific index.
    //!@param[in]: index (Index in the memory list)
    //!@param[out]: None
    //!@return: None
    /*""FUNC COMMENT END""*******************************************************/
    Q_INVOKABLE void memoryAddAt(int index);

    /*""FUNC COMMENT""***********************************************************/
    //!@brief: Subtracts current value from memory at a specific index.
    //!@param[in]: index (Index in the memory list)
    //!@param[out]: None
    //!@return: None
    /*""FUNC COMMENT END""*******************************************************/
    Q_INVOKABLE void memorySubAt(int index);

    //!@brief: Getter for the displayText property (Main screen value).
    QString displayText() const { return m_displayText; }

    //!@brief: Getter for the expressionText property (Small equation string).
    QString expressionText() const { return m_expressionText; }

    //!@brief: Getter for the historyList property.
    QStringList historyList() const { return m_historyList; }

    //!@brief: Getter for the memoryList property.
    QStringList memoryList() const { return m_memoryList; }

    //!@brief: Helper to check if memory is not empty.
    bool hasMemory() const { return !m_memoryList.isEmpty(); }

signals:
    void displayTextChanged();
    void expressionTextChanged();
    void historyListChanged();
    void memoryListChanged();
};

#endif
