#include "mComboBox.h"

#include <QtGui/QKeyEvent>

#include "debug.h"


MComboBox::MComboBox(QWidget* parent/* =0 */)
: QComboBox(parent)
, m_bShowPopup(false)
{
}

MComboBox::~MComboBox()
{

}


void MComboBox::focusInEvent(QFocusEvent *event)
{
    if (m_bShowPopup) {
        hidePopup();
        m_bShowPopup = false;
    }
    QComboBox::focusInEvent(event);
}

void MComboBox::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MComboBox::keyPressEvent" << hex << event->key();

    switch(event->key()) 
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        showPopup();
        m_bShowPopup = true;
        event->accept();
        break;
    case Qt::Key_Escape:
        if (m_bShowPopup) {
            hidePopup();
            m_bShowPopup = false;
            event->accept();
        }
        else {
            event->ignore();
        }
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
        event->ignore();
        break;
    case Qt::Key_Plus:
        setCurrentIndex((currentIndex()+1)%count());
        event->accept();
        break;
    case Qt::Key_Minus:
        if (currentIndex() == 0) {
            setCurrentIndex(count()-1);
        }
        else {
            setCurrentIndex((currentIndex()-1)%count());
        }
        event->accept();
        break;
    default:
        QComboBox::keyPressEvent(event);
        break;
    }
}
