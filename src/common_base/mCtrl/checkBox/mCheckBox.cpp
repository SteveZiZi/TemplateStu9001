#include "mCheckBox.h"

#include <QtGui/QKeyEvent>

#include "debug.h"

MCheckBox::MCheckBox(QWidget* parent/* =0 */)
: QCheckBox(parent)
{
}

MCheckBox::MCheckBox(const QString &text, QWidget *parent)
: QCheckBox(text, parent)
{

}

MCheckBox::~MCheckBox()
{

}

void MCheckBox::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MCheckBox::keyPressEvent" << hex << event->key();

    switch(event->key()) 
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        setChecked(checkState() == Qt::Unchecked);
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        event->ignore();
        break;
    default:
        QCheckBox::keyPressEvent(event);
        break;
    }
}
