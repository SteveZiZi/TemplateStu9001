#include "dirKeyInputForData.h"

#include "debug.h"

CDirKeyInputForData::CDirKeyInputForData(qint32 maxTextLength)
: CDirKeyInput(maxTextLength)
{

}

CDirKeyInputForData::~CDirKeyInputForData()
{

}

void  CDirKeyInputForData::moveLeft()
{
    if (m_text.isEmpty()) {
        m_text = "0";
    }
    else {
        if ( m_pos == 0 )
        {
            int strlen = m_text.length();
            if (strlen < m_maxLength) {
                m_text.insert(0, '0');
            }
            else {
                if (m_text[strlen-1] == '0') {
                    m_text.remove(strlen-1, 1);
                    m_text.insert(0, '0');
                }
                else {
                    m_pos = (strlen<m_maxLength) ? strlen-1 : m_maxLength-1;
                }
            }
        }
        else
        {
            m_pos--;
        }
        skipMaskChar(-1);
    }
}

void  CDirKeyInputForData::moveRight()
{
    if (m_text.isEmpty()) {
        m_text = "0";
    }
    else {
        // 跳到上一项
        if ( m_pos == m_maxLength-1 )
        {
            if (m_text[0] == '0') {
                m_text.remove(0, 1);
                m_text.insert(m_maxLength-1, '0');
            }
            else {
                m_pos = 0;
            }
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
