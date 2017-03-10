#pragma once


#include "../baseDialog.h"

class QLabel;
class MIPAddrEdit;
class CDirKeyInput;

class CNetworkSettingDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CNetworkSettingDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CNetworkSettingDlg();


    //override fro CBaseDialog
    virtual void _ShowContent(int style, quint32 data);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //override fro CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

private:
    QLabel *label_net1;
    QLabel *label_ipAddr1;
    MIPAddrEdit *lineEdit_ipAddr1;
    QLabel *label_defaultGatewaye1;
    MIPAddrEdit *lineEdit_defaultGatewaye1;

    QLabel *label_net2;
    QLabel *label_ipAddr2;
    MIPAddrEdit *lineEdit_ipAddr2;
    QLabel *label_defaultGatewaye2;
    MIPAddrEdit *lineEdit_defaultGatewaye2;

    CDirKeyInput* m_dirKeyInput;
};