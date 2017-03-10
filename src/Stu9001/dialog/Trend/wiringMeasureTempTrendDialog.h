#pragma once


#include "../baseDialog.h"


#include <mTrendCtrl/TrendCommon>
#include <mTrendCtrl/TrendCtrl>
#include <mTrendCtrl/Trend>

class MComboBox;
class QTimer;

struct TempReordInfo;


class CWiringMeasureTempTrendDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    enum {WAVE_POINT_NUM = 480};
    typedef mTrend::CTrend<float, float, 3, WAVE_POINT_NUM> waveTrend;
    typedef mTrend::CTrend<float, float, 1, WAVE_POINT_NUM> thesholdTrend;

    CWiringMeasureTempTrendDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CWiringMeasureTempTrendDlg();

    virtual void _ShowContent(int style, quint32 data);
    virtual void _HideContent();

public slots:
    /*
     *  @type ȡֵ
     *   0: ����������
     *   1�����һ�����ݱ�����
     *  -1�����ݿⱻ���
     */
    void updateDataBase(int type);

protected slots:
    void updateTrend() {
        m_trend->ResetForgnd();
        m_trend->DrawForegound();
        m_trend->repaint();
    }
    void changeShowType(int);


private:
    void moveToNextWidget() { };
    void moveToPreWidget() { };

    mTrend::CTrendCtrl* createTrend();

    void recordInfoToWaveData(const TempReordInfo& record, waveTrend::WaveData* data);

private:
    mTrend::CTrendCtrl* m_trend;
    MComboBox*  m_comboBox;

    mTrend::ScaleInfo   m_tScaleInfo;
    waveTrend          *m_pWave;
    thesholdTrend      *m_pThesholdWave;

    int m_showItem;    //0 ����  1 ����

    QTimer* m_timer;
};