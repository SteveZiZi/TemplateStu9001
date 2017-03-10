#include "mDataEdit.h"

#include <dirKeyInput>

#include "debug.h"


MDataEdit::MDataEdit(int a, int fieldWidth, int base, QString unit, QWidget* parent)
: MLineEdit(parent)
, m_var(a)
, m_fieldWidth(fieldWidth)
, m_base(base)
, m_unit(unit)
, m_format('g')
, m_precision(-1)
{
    setText(QString("%1%2").arg(a, fieldWidth, base, QChar('0')).arg(unit));
}

MDataEdit::MDataEdit(uint a, int fieldWidth, int base, QString unit, QWidget* parent)
: MLineEdit(parent)
, m_var(a)
, m_fieldWidth(fieldWidth)
, m_base(base)
, m_unit(unit)
, m_format('g')
, m_precision(-1)
{
    setText(QString("%1%2").arg(a, fieldWidth, base, QChar('0')).arg(unit));
}

MDataEdit::MDataEdit(float f, int fieldWidth, char format, int precision, QString unit, QWidget* parent)
: MLineEdit(parent)
, m_var(f)
, m_fieldWidth(fieldWidth)
, m_base(10)
, m_unit(unit)
, m_format(format)
, m_precision(precision)
{
    setText(QString("%1%2").arg(f, fieldWidth, format, precision, QChar('0')).arg(unit));
}


MDataEdit::MDataEdit(double d, int fieldWidth, char format, int precision, QString unit, QWidget* parent)
: MLineEdit(parent)
, m_var(d)
, m_fieldWidth(fieldWidth)
, m_base(10)
, m_unit(unit)
, m_format(format)
, m_precision(precision)
{
    setText(QString("%1%2").arg(d, fieldWidth, format, precision, QChar('0')).arg(unit));
}

MDataEdit::~MDataEdit()
{

}

void MDataEdit::startEdit()
{
    setText(text().remove(m_unit));
    MLineEdit::startEdit();
}


void MDataEdit::endEdit(void)
{
    bool bChanged = false;
    switch (m_var.type())
    {
    case QVariant::Int:
        if (m_var.toInt() != text().toInt()) {
            m_var.setValue(text().toInt());
            bChanged = true;
        }
        setText(QString("%1%2").arg(m_var.toInt(), m_fieldWidth, m_base, QChar('0')).arg(m_unit));
        break;
    case QVariant::UInt:
        if (m_var.toUInt() != text().toUInt()) {
            m_var.setValue(text().toUInt());
            bChanged = true;
        }
        setText(QString("%1%2").arg(m_var.toUInt(), m_fieldWidth, m_base, QChar('0')).arg(m_unit));
        break;
    case QMetaType::Float:
        if (m_var.toFloat() != text().toFloat()) {
            m_var.setValue(text().toFloat());
            bChanged = true;
        }
        setText(QString("%1%2").arg(m_var.toDouble(), m_fieldWidth, m_format, m_precision, QChar('0')).arg(m_unit));
        break;
    case QVariant::Double:
        if (m_var.toDouble() != text().toDouble()) {
            m_var.setValue(text().toDouble());
            bChanged = true;
        }
        setText(QString("%1%2").arg(m_var.toDouble(), m_fieldWidth, m_format, m_precision, QChar('0')).arg(m_unit));
        break;
    default:
        setText(text().append(m_unit));
        break;
    }
    MLineEdit::endEdit();

    if (bChanged) {
        emit dataChanged(m_var);
    }
}


bool MDataEdit::setVar(const QVariant& var)
{
    if (m_var.type() == var.type()) {
        m_var = var;
        switch (m_var.type())
        {
        case QVariant::Int:
            setText(QString("%1%2").arg(m_var.toInt(), m_fieldWidth, m_base, QChar('0')).arg(m_unit));
            break;
        case QVariant::UInt:
            setText(QString("%1%2").arg(m_var.toUInt(), m_fieldWidth, m_base, QChar('0')).arg(m_unit));
            break;
        case QMetaType::Float:
            setText(QString("%1%2").arg(m_var.toFloat(), m_fieldWidth, m_format, m_precision, QChar('0')).arg(m_unit));
            break;
        case QVariant::Double:
            setText(QString("%1%2").arg(m_var.toDouble(), m_fieldWidth, m_format, m_precision, QChar('0')).arg(m_unit));
            break;
        default:
            Q_ASSERT(false);
            break;
        }
        return true; 
    }

    return false;
}