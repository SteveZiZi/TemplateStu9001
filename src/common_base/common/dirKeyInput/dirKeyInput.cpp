#include "dirKeyInput.h"

#include "debug.h"

#define toupr(ch) islower(ch) ? toupper(ch) : ch

#define verify_char(ch) ((isxdigit(ch)) || \
                         ('A'>=ch && 'F'<=ch) || \
                         ('a'>=ch && 'f'<=ch) )


CDirKeyInput::CDirKeyInput(qint32 maxTextLength)
: m_maxLength(maxTextLength)
, m_text("0")
, m_pos(0)
, m_base(10)
{

}

CDirKeyInput::~CDirKeyInput()
{

}


QChar CDirKeyInput::add(QChar qch, int n)
{
    char ch = qch.toAscii();
    if (!verify_char(ch)) {
        return qch;
    }

    if (m_base != 16) {
        int data = ch - '0';
        if (data < 0 || data >= m_base) {
            data = 0;
        }
        data += n%m_base;
        data += m_base;
        data = data % m_base;
        return QChar(data + '0');
    }
    else if (m_base == 16) {
        ch = toupr(ch);

        int data = ch - '0';
        if (ch >= 'A' && ch <= 'F') {
            data = ch - 'A' + 10;
        }

        data += n;
        data = data % m_base;

        if (data > 9) {
            ch = data - 10 + 'A';
        }
        else
            ch = data + '0';

        return QChar(ch);
    }

    return qch;
}

QChar CDirKeyInput::minus(QChar qch, int n)
{
    char ch = qch.toAscii();
    if (!verify_char(ch)) {
        return qch;
    }

    if (m_base != 16) {
        int data = ch - '0';
        if (data < 0 || data >= m_base) {
            data = 0;
        }
        data -= n % m_base;
        data += m_base;
        data = data % m_base;
        return QChar(data + '0');
    }
    else if (m_base == 16) {
        ch = toupr(ch);

        int data = ch - '0';
        if (ch >= 'A' && ch <= 'F') {
            data = ch - 'A' + 10;
        }

        data -= n % m_base;
        data += m_base;
        data = data % m_base;

        if (data > 9) {
            ch = data - 10 + 'A';
        }
        else
            ch = data + '0';

        return QChar(ch);
    }

    return qch;
}

void CDirKeyInput::addMaskChar(QChar ch)
{
    if (!isMaskChar(ch))
        maskCharList.append(ch);
}

bool CDirKeyInput::isMaskChar(QChar ch)
{
    for(MASKList::Iterator it = maskCharList.begin(); it != maskCharList.end(); it++)
    {
        if (*it == ch)
            return true;
    }
    return false;
}

void  CDirKeyInput::skipMaskChar(int dir)
{
    if (!isMaskChar(m_text[m_pos])) {
        return ;
    }

    if (dir == -1) {
        if (m_pos != 0) {
            m_pos--;
        }
        else {
            m_text.insert(0, '0');
            
            if (m_text.length() > m_maxLength) {
                m_text.remove(m_maxLength, 1);
            }
        }
    }
    else {
        if (m_pos != m_text.length()-1) {
            m_pos++;
        }
        else {
            if (m_pos < m_maxLength-1) {
                m_text.insert(m_pos, '0');
                m_pos++;
            }
            else {
                m_text.remove(0, 1);
                m_text.insert(m_pos, '0');
            }
        }
    }
    skipMaskChar(dir);
}


bool CDirKeyInput::inputKey(int key)
{
    bool rc = true;
    switch(key)
    {
    case Qt::Key_Left:
        moveLeft();
        break;
    case Qt::Key_Right:
        moveRight();
        break;
    case Qt::Key_Up:
        moveUp();
        break;
    case Qt::Key_Down:
        moveDown();
        break;
    default: 
        rc = false;
    }

    return rc;
}


void  CDirKeyInput::moveLeft()
{
    if (m_text.isEmpty()) {
        m_text = "0";
    }
    else {
        // 跳到上一项
        if ( m_pos == 0 )
        {
            int strlen = m_text.length();
            if (strlen < m_maxLength) {
                m_text.insert(0, '0');
            }
            else {
                m_pos = (strlen<m_maxLength) ? strlen-1 : m_maxLength-1;
            }
        }
        else
        {
            m_pos--;
        }
        skipMaskChar(-1);
    }
}

void  CDirKeyInput::moveRight()
{
    if (m_text.isEmpty()) {
        m_text = "0";
    }
    else {
        // 跳到上一项
        if ( m_pos == m_maxLength-1 )
        {
            m_pos = 0;
        }
        else
        {
            if (m_pos == m_text.length()-1) {
                m_text += '0';
            }
            m_pos++;
        }
        skipMaskChar(1);
    }
}

void  CDirKeyInput::moveUp()
{
    m_text[m_pos] = add(m_text[m_pos]);
}

void  CDirKeyInput::moveDown()
{
    m_text[m_pos] = minus(m_text[m_pos]);
}
