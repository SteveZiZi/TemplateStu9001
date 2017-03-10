#pragma once


#include "../baseDialog.h"
class QTimer;

class CBaseShowDialog : public CBaseDialog
{
    Q_OBJECT
        
public:
    CBaseShowDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~CBaseShowDialog();

    // override from CAbstractMenuContent
    virtual void _ShowContent(int style, quint32 data);
    virtual void _HideContent();

public slots:
    virtual void updateShowData() {}

protected:
    virtual void moveToNextWidget() { };
    virtual void moveToPreWidget() { };

protected:
    QTimer* m_timer;
};