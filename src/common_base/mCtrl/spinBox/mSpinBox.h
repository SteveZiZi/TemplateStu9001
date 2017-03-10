#pragma once

#include <QtGui/QSpinBox>


class MSpinBox : public QSpinBox
{
public:
    explicit MSpinBox(QWidget* parent = 0);
    virtual ~MSpinBox();

protected:
    virtual void keyPressEvent(QKeyEvent *);
};