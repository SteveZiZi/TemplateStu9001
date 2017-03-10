#pragma once


#include "baseShowDialog.h"
#include <sampleShowData_cp6000>

class MTableWidget;

class CCP6000SampleShowDlg : public CBaseShowDialog
{
    Q_OBJECT
        
public:
    CCP6000SampleShowDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CCP6000SampleShowDlg();

    //override from CBaseShowDialog
    virtual void updateShowData();

private:
    MTableWidget* createTableWidget(QString objectName);
    void updateTableWidget(const SampleShowData_cp6000& data);

private:
    MTableWidget* m_tableWidget;
    CSampleShowData_cp6000* m_dev;
    SampleShowData_cp6000 m_data;
};