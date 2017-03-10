#include "mLineEdit.h"
#include <QtGui/QKeyEvent>
#include <dirKeyInput>

#include "debug.h"

MLineEdit::MLineEdit(const QString& text, QWidget* parent/* =0 */, bool trrigleEdit/* = true*/)
: QLineEdit(text, parent)
, m_oldText(text)
, m_dirKeyInput(NULL)
, m_trrigleEdit(trrigleEdit)
, m_isEditMode(false)
{
    if (m_trrigleEdit)
        setReadOnly(true);
}

MLineEdit::MLineEdit(QWidget* parent/* =0 */, bool trrigleEdit/* = true*/)
: QLineEdit(parent)
, m_oldText("")
, m_dirKeyInput(NULL)
, m_trrigleEdit(trrigleEdit)
, m_isEditMode(false)
{
    if (!m_trrigleEdit) {
        qDebug() << "MLineEdit::MLineEdit no trrigle mode";
    }
    if (m_trrigleEdit)
        setReadOnly(true);
}

MLineEdit::~MLineEdit()
{

}

void MLineEdit::setDirKeyInput(CDirKeyInput* dirKeyInput)
{
    m_dirKeyInput = dirKeyInput;
}

void MLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    selectAll();
}

void MLineEdit::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    qDebug() << "MLineEdit::keyPressEvent" << hex << key;

    //必须先按下Enter键才能进入编辑状态
    if (m_trrigleEdit) {
        if (isReadOnly()) {
            if (key == Qt::Key_Enter || key == Qt::Key_Return) {
                m_oldText = text();
                startEdit();
                event->accept();
            }
            else if (key == Qt::Key_Left || key == Qt::Key_Right) {
                event->accept();
            }
            else {
                QLineEdit::keyPressEvent(event);
            }
        }
        else {
            switch(key)
            {
            case Qt::Key_Left:
            case Qt::Key_Right:
            case Qt::Key_Up:
            case Qt::Key_Down:
                if (dirInput(key)) {
                    event->accept();
                }
                break;
            case Qt::Key_Enter:
            case Qt::Key_Return:
                endEdit();
                event->accept();
                break;
            case Qt::Key_Escape:
                cancelEdit();
                event->accept();
                break;
            default:
                QLineEdit::keyPressEvent(event);
                break;
            }
        }
    }
    else {
        switch(key)
        {
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            if (!m_isEditMode) {
                m_oldText = text();
                startEdit();
                m_isEditMode = true;
            }
            if (dirInput(key)) {
                event->accept();
            }
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            m_isEditMode = false;
            endEdit();
            event->ignore();
            break;
        case Qt::Key_Escape:
            m_isEditMode = false;
            cancelEdit();
            event->ignore();
            break;
        default:
            QLineEdit::keyPressEvent(event);
            break;
        }
    }
}

void MLineEdit::startEdit(void)
{
    setReadOnly(false);
    if (m_dirKeyInput) {
        m_dirKeyInput->setPos(0);
        if (text().length() > 0) {
            m_dirKeyInput->setText(text());
        }
        else {
            m_dirKeyInput->setText("0");
            setText("0");
        }
        setSelection(0, 1);
    }
}

void MLineEdit::endEdit(void)
{
    setReadOnly(true);
    selectAll();
    if (m_oldText != text())
        emit accepted(text());
}

void MLineEdit::cancelEdit(void)
{
    setText(m_oldText);
    setReadOnly(true);
    selectAll();
    emit rejected(text());
}


bool MLineEdit::dirInput(int key)
{
    if (m_dirKeyInput && m_dirKeyInput->inputKey(key)) {
        setText(m_dirKeyInput->text());
        int pos = m_dirKeyInput->pos();
        setSelection(pos, 1);
        return true;
    }
    return false;
}
