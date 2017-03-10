#pragma once


#include "../baseDialog.h"


#include <mTrendCtrl/TrendCommon>
#include <mTrendCtrl/TrendCtrl>
#include <mTrendCtrl/Trend>

class MComboBox;


class CCubicleTempHumTrendDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    typedef mTrend::CTrend<float, float, 3, 240> waveTrend;
    typedef mTrend::CTrend<float, float, 1, 240> thesholdTrend;

    CCubicleTempHumTrendDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CCubicleTempHumTrendDlg();

    //override DObserver
    //virtual void Update(DObserveSubject*, DWORD arg);

    //void loadHistoryData();
    //void CoordConv(waveTrend::WaveData& waveData, tm_t& tm, WiringTempData_t& data);

    virtual void _ShowContent(int style, quint32 data);

public slots:
    /*
     *  @type ȡֵ
     *   0: ����������
     *   1�����һ�����ݱ�����
     *  -1���б����
     */
    void updateTrend(int type);

private:
    void moveToNextWidget() { };
    void moveToPreWidget() { };

    mTrend::CTrendCtrl* createTrend();

private:
    mTrend::CTrendCtrl* m_trend;
    MComboBox*  m_comboBox;

    mTrend::ScaleInfo   m_tScaleInfo;
    waveTrend          *m_pWave;
};