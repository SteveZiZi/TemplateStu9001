#pragma once


#include "baseShowDialog.h"
#include <SampleShowData_cp9000>

class MTableWidget;

class CCP9000SampleShowDlg : public CBaseShowDialog
{
    Q_OBJECT
        
public:
    CCP9000SampleShowDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CCP9000SampleShowDlg();

    //override from CBaseShowDialog
    virtual void updateShowData();

private:
    MTableWidget* createTableWidget(QString objectName);
    void updateTableWidget(const SampleShowData_cp9000& data);

private:
    MTableWidget* m_tableWidget;
    CSampleShowData_cp9000* m_dev;
    SampleShowData_cp9000 m_data;
};