#pragma once


#include <QtGui/QDialog>
#include <AbstractMenu>


class CBaseDialog : public QDialog, public CAbstractMenuContent
{
    Q_OBJECT
        
public:
    CBaseDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~CBaseDialog();

    //
    // override from CAbstractMenuContent
    //
    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

    virtual bool dirKeyDown(int key);

protected:
    virtual void moveToNextWidget() = 0;
    virtual void moveToPreWidget() = 0;

protected:
    virtual void keyPressEvent(QKeyEvent *event);

};