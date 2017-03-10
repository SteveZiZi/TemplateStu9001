#pragma once


#include "baseShowDialog.h"
#include <SwitchInShowData>

class MTableWidget;

class CSwitchInShowDlg : public CBaseShowDialog
{
    Q_OBJECT
        
public:
    CSwitchInShowDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CSwitchInShowDlg();

    //override from CBaseShowDialog
    virtual void updateShowData();

private:
    MTableWidget* createTableWidget(QString objectName, int item);
    void updateTableWidget(const SwitchInputShowData& data);

private:
    MTableWidget* m_tableWidget1;
    MTableWidget* m_tableWidget2;
    CSwitchInputShowData* m_dev;
    SwitchInputShowData m_data;
};