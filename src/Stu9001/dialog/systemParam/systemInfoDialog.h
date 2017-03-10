#pragma once


#include "../baseDialog.h"

class QLabel;
class MComboBox;

class CSystemInfoDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CSystemInfoDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CSystemInfoDlg();


    virtual void _ShowContent(int style, quint32 data);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //override fro CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

private:

private:
    QLabel *label_lan;
    MComboBox *comboBox_lan;

    QLabel *label_machine;
    QLabel *label_machineName;

    QLabel *label_version;
    QLabel *label_versionString;

    QLabel *label_serialNo;
    QLabel *label_serialNoString;
};