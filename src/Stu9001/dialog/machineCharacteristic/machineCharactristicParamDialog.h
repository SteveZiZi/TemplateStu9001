#pragma once


#include "../baseDialog.h"
#include <machineCharacteristicParam>

class QLabel;
class CDirKeyInputForData;
class MTableWidget;
class QTableWidgetItem;

class CMachineCharactristicParamDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CMachineCharactristicParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CMachineCharactristicParamDlg();

    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

protected slots:
    void tableWidgetChanged(QTableWidgetItem *item);

private:
    //override from CBaseDialog
    virtual void moveToNextWidget() {}
    virtual void moveToPreWidget() {}

    MTableWidget* createTableWidget(QString objectName);
    //更新设置到界面
    void updateSettings(void);


private:
    MTableWidget* m_tableWidget;
    CDirKeyInputForData* m_dirKeyInputForData;

    CMachineCharacterParam* m_dev;
    MachineCharacterSettings m_settings;
    bool        m_bModify;
};