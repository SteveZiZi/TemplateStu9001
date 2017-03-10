#pragma once

#include <qglobal.h>
#include <QList>
#include <QString>

class CDirKeyInput
{
public:
    CDirKeyInput(qint32 maxTextLength = 6);
    virtual ~CDirKeyInput();


    const QString& text() {return m_text;}
    void setText(const QString& text) {m_text = text;}

    int pos() {return m_pos;}
    void setPos(int pos) {if(pos<m_maxLength) m_pos = pos;}

    int base() {return m_base;}
    void setBase(int base) {m_base = base;}

    void addMaskChar(QChar ch);
    bool isMaskChar(QChar ch);

    void setMaxTextLength(qint32 maxLength) {m_maxLength = maxLength;}
    qint32 maxTextLength() const {return m_maxLength;}

    virtual bool inputKey(int key);

    virtual QChar add(QChar ch, int n = 1); 
    virtual QChar minus(QChar ch, int n = 1); 

protected:
    virtual void  moveLeft();
    virtual void  moveRight();
    virtual void  moveUp();
    virtual void  moveDown();

    void skipMaskChar(int dir);

protected:
    typedef QList<QChar> MASKList;
    QString m_text;
    qint32  m_maxLength;
    MASKList maskCharList;
    int m_pos;
    int m_base;

};