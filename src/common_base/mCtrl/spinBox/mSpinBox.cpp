#include "mSpinBox.h"

#include <QtGui/QKeyEvent>

#include "debug.h"

MSpinBox::MSpinBox(QWidget* parent/* =0 */)
: QSpinBox(parent)
{
}

MSpinBox::~MSpinBox()
{

}


void MSpinBox::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MSpinBox::keyPressEvent" << hex << event->key();

//     switch(event->key()) 
//     {
//     case Qt::Key_Enter:
//     case Qt::Key_Return:
//         setChecked(checkState() == Qt::Unchecked);
//         break;
//     default:
//         QSpinBox::keyPressEvent(event);
//         break;
//     }
    QSpinBox::keyPressEvent(event);
}
