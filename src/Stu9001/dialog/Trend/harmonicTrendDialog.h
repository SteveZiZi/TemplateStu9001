#pragma once


#include "../baseDialog.h"


#include <mTrendCtrl/TrendCommon>
#include <mTrendCtrl/TrendCtrl>
#include <mTrendCtrl/Trend>

class MTableWidget;
class MComboBox;


class CHarmonicTrendDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    typedef mTrend::CTrend<float, float, 3, 240> waveTrend;
    typedef mTrend::CTrend<float, float, 1, 240> thesholdTrend;

    CHarmonicTrendDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CHarmonicTrendDlg();

    //override DObserver
    //virtual void Update(DObserveSubject*, DWORD arg);

    //void loadHistoryData();
    //void CoordConv(waveTrend::WaveData& waveData, tm_t& tm, WiringTempData_t& data);

    virtual void _ShowContent(int style, quint32 data);

private:
    void moveToNextWidget() { };
    void moveToPreWidget() { };

    mTrend::CTrendCtrl* createTrend(int item);

private:
    mTrend::CTrendCtrl* m_trend[2];
    mTrend::ScaleInfo   m_tScaleInfo[2];
    MComboBox*  m_comboBox;

    waveTrend          *m_pWave[2];
};