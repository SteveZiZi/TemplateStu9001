#pragma once

#include <QtGui/QCheckBox>


class MCheckBox : public QCheckBox
{
public:
    explicit MCheckBox(QWidget* parent = 0);
    explicit MCheckBox(const QString &text, QWidget *parent=0);
    virtual ~MCheckBox();

protected:
    virtual void keyPressEvent(QKeyEvent *);
};