#pragma once

#include <QtGui/QComboBox>


class MComboBox : public QComboBox
{
public:
    explicit MComboBox(QWidget* parent = 0);
    virtual ~MComboBox();

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void focusInEvent(QFocusEvent *);

private:
    bool m_bShowPopup;
};