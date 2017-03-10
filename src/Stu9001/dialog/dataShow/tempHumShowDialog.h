#pragma once


#include "baseShowDialog.h"
#include <tempHumShowData>

class MTableWidget;

class CTempHumShowDlg : public CBaseShowDialog
{
    Q_OBJECT
        
public:
    CTempHumShowDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CTempHumShowDlg();

    //override from CBaseShowDialog
    virtual void updateShowData();

private:
    MTableWidget* createTableWidget(QString objectName, int item);
    void updateContectTemp(const TempShowData& data);
    void updateBusbarTemp(const TempShowData& data);
    void updateCubicleHum(const HumidityData& data);

private:
    MTableWidget* m_tableWidget[3];
    CTempHumShowData* m_dev;
    TempShowData m_contectTemp;
    TempShowData m_busbarTemp;
    HumidityData m_cubicleHum;
};