#pragma once


#include "../baseDialog.h"
#include <plateCastBackParam_cp9000>

class MTableWidget;

class QTableWidgetItem;

class CPlateCastBackDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CPlateCastBackDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CPlateCastBackDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();

public slots:
    void changed(QTableWidgetItem* item);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    MTableWidget* createTableWidget(QString objectName);
    //更新设置到界面
    void updateSettings();

private:
    MTableWidget* m_tableWidget;
    CPlateCastConfig* m_dev;
    PlateCastParam m_settings;
    bool        m_bModify;
};