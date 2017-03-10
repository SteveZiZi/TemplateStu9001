#pragma once


#include "../baseDialog.h"


#include <mTrendCtrl/TrendCommon>
#include <mTrendCtrl/TrendCtrl>
#include <mTrendCtrl/Trend>

class MTableWidget;
class MComboBox;

class CMachineCharactristicTrendDlgPrivate;
class CMachineCharactristicTrendDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    enum {TREND_POINT_NUM = 501};
    typedef mTrend::CTrend<float, float, 4, TREND_POINT_NUM> waveTrend;

    enum ReportStyle {
        SEPARATE_BREAKER,
        CLOSE_BREAKER,
        STORE_ENERGY
    };
    enum UpdateStyle {
        UPDATE_DATA     = 0x01,
        UPDATE_CAPTION  = 0x02
    };
    Q_DECLARE_FLAGS(UpdateStyles, UpdateStyle);


    CMachineCharactristicTrendDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CMachineCharactristicTrendDlg();

    virtual void _ShowContent(int style, quint32 data);
    virtual void _HideContent();
    
public slots:
    /*
     *  @dataType:   取值 MC_DataUpdateFlag 或的关系
     */
    void updateDataBase(int dataType);

protected slots:
    void changeShowType(int);

private:
    void moveToNextWidget() { };
    void moveToPreWidget() { };

    mTrend::CTrendCtrl* createTrend();
    MTableWidget* createTableWidget(QString objectName);
    void updateTableWidget(ReportStyle reportStyle, UpdateStyles updateStyles);

    void updateTrend(int item);

private:
    mTrend::CTrendCtrl* m_trend;
    MComboBox*  m_comboBox;

    mTrend::ScaleInfo   m_tScaleInfo;
    waveTrend          *m_pWave;

    MTableWidget* m_tableWidget;

    int m_showItem;    //0 分闸曲线  1 合闸曲线  2 储能曲线

    CMachineCharactristicTrendDlgPrivate* m_data;
};