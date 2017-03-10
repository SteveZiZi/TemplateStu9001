#pragma once


#include "baseShowDialog.h"
#include <MeasureShowData>

class MTableWidget;

class CMeasureShowDlg : public CBaseShowDialog
{
    Q_OBJECT
        
public:
    CMeasureShowDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CMeasureShowDlg();

    //override from CBaseShowDialog
    virtual void updateShowData();

private:
    MTableWidget* createTableWidget(QString objectName);
    void updateTableWidget(const MeasureShowData& data);

private:
    MTableWidget* m_tableWidget;
    CMeasureShowData* m_dev;
    MeasureShowData m_data;
};