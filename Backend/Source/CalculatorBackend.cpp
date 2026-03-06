/*""FILE COMMENT""***********************************************************
* System Name : Calculator Application
* File Name   : calculatorbackend.cpp
* Contents    : CCalculatorBackend Class Implementation
* Author      : Nguyen Thai Tai
* Model       : N/A
*****************************************************************************
* Copyright, (C) 2026. All rights reserved.
*****************************************************************************
*""FILE COMMENT END""*******************************************************/
#include "calculatorbackend.h"
#include <QDir>
#include <QCoreApplication>

/*""FUNC COMMENT""***********************************************************/
//!@brief: Constructor for CCalculatorBackend. Initializes database history and memory.
//!@param[in]: parent (The parent QObject, default is nullptr)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
CCalculatorBackend::CCalculatorBackend(QObject *parent) : QObject(parent) {
    updateHistory();
    updateMemory();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Formats a double value to a string with a fixed precision, removing trailing zeros.
//!@param[in]: value (The double value to format)
//!@param[out]: None
//!@return: A formatted QString representing the number
/*""FUNC COMMENT END""*******************************************************/
QString CCalculatorBackend::formatNumber(double value) {
    QString s = QString::number(value, DisplayConfig::FORMAT, DisplayConfig::PRECISION);
    while (s.contains('.') && s.endsWith('0')) {
        s.chop(1);
    }
    if (s.endsWith('.')) {
        s.chop(1);
    }
    return s;
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Helper function to check if a string is a mathematical operator.
//!@param[in]: s (The string to check)
//!@param[out]: None
//!@return: True if the string is an operator, False otherwise
/*""FUNC COMMENT END""*******************************************************/
bool isOperator(const QString &s) {
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "×" || s == "÷" || s == "−");
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Fetches the latest calculation history from the database and emits the change signal.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::updateHistory() {
    m_historyList = CDatabaseManager::GetInstance()->fetchHistory();
    emit historyListChanged();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Fetches the latest memory list from the database and emits the change signal.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::updateMemory() {
    m_memoryList = CDatabaseManager::GetInstance()->fetchMemory();
    emit memoryListChanged();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Handles memory-specific commands (MS, MC, MR, M+, M-).
//!@param[in]: cmd (The command string)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::onMemoryCommand(const QString &cmd) {
    double currentVal = m_displayText.toDouble();
    CDatabaseManager *db = CDatabaseManager::GetInstance();

    if (cmd == "MS") {
        db->addMemory(formatNumber(currentVal));
        updateMemory();
        m_newNumber = true;
    }
    else if (cmd == "MC") {
        db->clearMemory();
        updateMemory();
    }
    else if (cmd == "MR") {
        if (!m_memoryList.isEmpty()) {
            m_displayText = m_memoryList.first();
            emit displayTextChanged();
            m_newNumber = true;
        }
    }
    else if (cmd == "M+" || cmd == "M-") {
        if (m_memoryList.isEmpty()) {
            db->addMemory(formatNumber(currentVal));
        } else {
            double topVal = m_memoryList.first().toDouble();
            if (cmd == "M+") topVal += currentVal;
            else topVal -= currentVal;
            db->updateMemoryLast(formatNumber(topVal));
        }
        updateMemory();
        m_newNumber = true;
    }
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Deletes a specific memory entry at the given index.
//!@param[in]: index (The index of the memory item to delete)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::clearMemoryIndex(int index) {
    if (index >= 0 && index < m_memoryList.size()) {
        CDatabaseManager::GetInstance()->deleteMemoryAt(index);
        updateMemory();
    }
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Maps a string input to the internal CalcCmd enum.
//!@param[in]: input (The string representation of the command)
//!@param[out]: None
//!@return: The corresponding CalcCmd enum value
/*""FUNC COMMENT END""*******************************************************/
CalcCmd CCalculatorBackend::mapCommand(const QString &input) {
    static const QHash<QString, CalcCmd> map {
        {"CE", CalcCmd::CE},
        {"C", CalcCmd::C},
        {"⌫", CalcCmd::Backspace},
        {"+/-", CalcCmd::Negate},
        {"recip", CalcCmd::Recip},
        {"sqr", CalcCmd::Sqr},
        {"sqrt", CalcCmd::Sqrt},
        {"%", CalcCmd::Percent},
        {"=", CalcCmd::Equals}
    };

    if (map.contains(input))
        return map.value(input);
    else if (QString("+-*/").contains(input))
        return CalcCmd::Operator;

    return CalcCmd::Digit;
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Main handler for calculator commands/inputs. Dispatches logic based on command type.
//!@param[in]: input (The input string from the UI)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::onCommand(const QString &input) {
    switch (mapCommand(input)) {
    case CalcCmd::CE:
        m_displayText = "0";
        m_tempStepString = "";
        m_newNumber = true;
        break;

    case CalcCmd::C:
        m_displayText = "0";
        m_firstNum = 0;
        m_op = "";
        m_newNumber = true;
        m_expressionText = "";
        m_cachedOp = "";
        m_cachedSecondNum = 0;
        m_tempStepString = "";
        emit expressionTextChanged();
        break;

    case CalcCmd::Backspace:
        if (!m_newNumber && m_displayText.length() > 0) {
            m_displayText.chop(1);
            if (m_displayText.isEmpty() || m_displayText == "-")
                m_displayText = "0";
            m_tempStepString = "";
        }
        break;

    case CalcCmd::Negate:
    {
        double val = m_displayText.toDouble();
        m_displayText = formatNumber(val * -1);
        m_tempStepString = "";
        break;
    }

    case CalcCmd::Recip:
    {
        double val = m_displayText.toDouble();
        if (val == 0) {
            m_displayText = "Cannot divide by zero";
            m_tempStepString = "";
        } else {
            QString curStr = m_tempStepString.isEmpty() ? formatNumber(val) : m_tempStepString;
            m_tempStepString = "1/(" + curStr + ")";
            m_displayText = formatNumber(1.0 / val);

            if (!m_op.isEmpty())
                m_expressionText = formatNumber(m_firstNum) + " " + m_op + " " + m_tempStepString;
            else
                m_expressionText = m_tempStepString;

            emit expressionTextChanged();
        }
        m_newNumber = true;
        break;
    }

    case CalcCmd::Sqr:
    {
        double val = m_displayText.toDouble();
        QString curStr = m_tempStepString.isEmpty() ? formatNumber(val) : m_tempStepString;
        m_tempStepString = "sqr(" + curStr + ")";
        m_displayText = formatNumber(val * val);

        if (!m_op.isEmpty())
            m_expressionText = formatNumber(m_firstNum) + " " + m_op + " " + m_tempStepString;
        else
            m_expressionText = m_tempStepString;

        emit expressionTextChanged();
        m_newNumber = true;
        break;
    }

    case CalcCmd::Sqrt:
    {
        double val = m_displayText.toDouble();
        if (val < 0) {
            m_displayText = "Invalid Input";
            m_tempStepString = "";
        } else {
            QString curStr = m_tempStepString.isEmpty() ? formatNumber(val) : m_tempStepString;
            m_tempStepString = "√(" + curStr + ")";
            m_displayText = formatNumber(std::sqrt(val));

            if (!m_op.isEmpty())
                m_expressionText = formatNumber(m_firstNum) + " " + m_op + " " + m_tempStepString;
            else
                m_expressionText = m_tempStepString;
            emit expressionTextChanged();
        }
        m_newNumber = true;
        break;
    }

    case CalcCmd::Percent:
    {
        double currentVal = m_displayText.toDouble();
        if (!m_op.isEmpty()) {
            double percentVal = m_firstNum * (currentVal / 100.0);
            m_displayText = formatNumber(percentVal);
            m_tempStepString = formatNumber(percentVal);
        } else {
            m_displayText = formatNumber(currentVal / 100.0);
            m_tempStepString = m_displayText;
        }
        m_newNumber = true;
        break;
    }

    case CalcCmd::Equals:
    {
        if (!m_op.isEmpty()) {
            m_cachedOp = m_op;
            m_cachedSecondNum = m_displayText.toDouble();
            calculate();
            m_op = "";
        }
        else if (!m_cachedOp.isEmpty()) {
            m_op = m_cachedOp;
            m_firstNum = m_displayText.toDouble();
            m_displayText = formatNumber(m_cachedSecondNum);
            m_tempStepString = "";
            calculate();
            m_op = "";
        }
        else if (!m_tempStepString.isEmpty()) {
            QString expr = m_tempStepString;
            QString res = m_displayText;
            CDatabaseManager::GetInstance()->addHistory(expr, res);
            updateHistory();
            m_expressionText = m_tempStepString + " =";
            emit expressionTextChanged();
            m_tempStepString = "";
        }
        m_newNumber = true;
        break;
    }

    case CalcCmd::Operator:
    {
        m_cachedOp = "";
        m_cachedSecondNum = 0;
        m_firstNum = m_displayText.toDouble();
        m_op = input;
        m_newNumber = true;
        m_tempStepString = "";
        QString displayOp = m_op;

        if (m_op == "*")
            displayOp = "×";
        if (m_op == "/")
            displayOp = "÷";
        if (m_op == "-")
            displayOp = "−";

        m_expressionText = formatNumber(m_firstNum) + " " + displayOp;
        emit expressionTextChanged();
        break;
    }

    case CalcCmd::Digit:
    default:
        if (m_newNumber) {
            if (m_expressionText.contains("=")) {
                m_expressionText = "";
                emit expressionTextChanged();
            }
            m_displayText = input;
            m_newNumber = false;
            m_tempStepString = "";
        } else {
            if (input == "." && m_displayText.contains("."))
                return;
            if (m_displayText == "0" && input != ".")
                m_displayText = input;
            else
                m_displayText += input;
        }
        break;
    }

    emit displayTextChanged();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Performs calculations based on the stored operator and operands. Saves result to DB.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::calculate() {
    double secondNum = m_displayText.toDouble();
    double res = 0;

    if (m_op == "+")
        res = m_firstNum + secondNum;
    else if (m_op == "-")
        res = m_firstNum - secondNum;
    else if (m_op == "*")
        res = m_firstNum * secondNum;
    else if (m_op == "/") {
        if (secondNum == 0) {
            m_displayText = "Err";
            return;
        }
        res = m_firstNum / secondNum;
    }

    QString displayOp = m_op;
    if (m_op == "*")
        displayOp = "×";
    else if (m_op == "/")
        displayOp = "÷";
    else if (m_op == "-")
        displayOp = "−";

    QString secondStr = m_tempStepString.isEmpty() ? formatNumber(secondNum) : m_tempStepString;
    QString expr = formatNumber(m_firstNum) + " " + displayOp + " " + secondStr;

    m_expressionText = formatNumber(m_firstNum) + " " + displayOp + " " + secondStr + " =";
    emit expressionTextChanged();

    m_displayText = formatNumber(res);

    CDatabaseManager::GetInstance()->addHistory(expr, m_displayText);
    updateHistory();

    m_tempStepString = "";
    emit displayTextChanged();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Clears the entire calculation history from the database.
//!@param[in]: None
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::clearHistory() {
    CDatabaseManager::GetInstance()->clearHistory();
    updateHistory();
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Adds the current display value to the memory value at a specific index.
//!@param[in]: index (The index of the memory item to update)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::memoryAddAt(int index) {
    if (index < 0 || index >= m_memoryList.size()) return;

    double currentVal = m_displayText.toDouble();
    double memVal = m_memoryList[index].toDouble();
    memVal += currentVal;

    CDatabaseManager::GetInstance()->updateMemoryAt(index, formatNumber(memVal));

    updateMemory();
    m_newNumber = true;
}

/*""FUNC COMMENT""***********************************************************/
//!@brief: Subtracts the current display value from the memory value at a specific index.
//!@param[in]: index (The index of the memory item to update)
//!@param[out]: None
//!@return: None
/*""FUNC COMMENT END""*******************************************************/
void CCalculatorBackend::memorySubAt(int index) {
    if (index < 0 || index >= m_memoryList.size()) return;

    double currentVal = m_displayText.toDouble();
    double memVal = m_memoryList[index].toDouble();
    memVal -= currentVal;

    CDatabaseManager::GetInstance()->updateMemoryAt(index, formatNumber(memVal));

    updateMemory();
    m_newNumber = true;
}
