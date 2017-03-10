#pragma once

#include "mLineEdit.h"

#include <QVariant>

class MDataEdit : public MLineEdit
{
    Q_OBJECT

public:
    explicit MDataEdit(int a, int fieldWidth = 0, int base = 10, QString unit = "", QWidget* parent = 0);
    explicit MDataEdit(uint a, int fieldWidth = 0, int base = 10, QString unit = "", QWidget* parent=0);
    explicit MDataEdit(float f, int fieldWidth = 0, char format = 'g', int precision = -1, QString unit = "", QWidget* parent=0);
    explicit MDataEdit(double d, int fieldWidth = 0, char format = 'g', int precision = -1, QString unit = "", QWidget* parent=0);
    virtual ~MDataEdit();


    const QVariant* constVar() {return &m_var;}
    const QVariant& constVarPtr() {return m_var;}

    bool setVar(const QVariant& var);

signals:
    void dataChanged(const QVariant& var);

protected:
    //override MLineEdit
    virtual void startEdit(void);
    virtual void endEdit(void);

private:

private:
    QVariant    m_var;
    int         m_fieldWidth;
    int         m_base;
    QString     m_unit;
    char        m_format;
    int         m_precision;
};