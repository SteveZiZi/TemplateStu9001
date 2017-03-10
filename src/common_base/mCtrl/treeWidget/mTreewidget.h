#pragma once

#include <QtGui/QTreeWidget>

/****************************************************************************
**
** file: mTreeWidget.h
**
** description:
**     Custom QTreeWidget's Grid Line.
**
** change logs:
**      2015/11/21:   yangyuchao   create file
**
****************************************************************************/

class MTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    MTreeWidget(QWidget *parent = 0);
    virtual ~MTreeWidget();

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void focusInEvent(QFocusEvent *event);


private:
    bool m_editMode;

};
