#pragma once


#include "../baseDialog.h"
#include <constantValuesSetting_cp9000>

class MTableWidget;
class CDirKeyInputForData;
class QTableWidgetItem;

class CConstValueModifyDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CConstValueModifyDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CConstValueModifyDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

protected slots:
    void tableWidget1Changed(QTableWidgetItem *item);
    void tableWidget2Changed(QTableWidgetItem *item);

private:
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    MTableWidget* createTableWidget(QString objectName, int item);
    //更新设置到界面
    void updateSettings();

private:
    MTableWidget* m_tableWidget1;
    MTableWidget* m_tableWidget2;

    int m_currentRow;

    CDirKeyInputForData* m_dirKeyInputForData;
    CDirKeyInputForData* m_dirKeyInputForHex;

    CConstValuesSetting* m_dev;
    ConstValueSettings m_settings;
    bool        m_bModify;
};