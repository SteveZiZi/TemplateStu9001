#pragma once


#include "../baseDialog.h"

class QLabel;
class QLineEdit;

class CSimulationViewsDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CSimulationViewsDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CSimulationViewsDlg();


    virtual void _ShowContent(int style, quint32 data);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //override from CBaseDialog
    virtual void moveToNextWidget() { };
    virtual void moveToPreWidget() { };

private:
};