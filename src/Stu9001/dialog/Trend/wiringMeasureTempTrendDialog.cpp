#include "wiringMeasureTempTrendDialog.h"
#include "common.h"

#include <mComboBox>
#include <mTrendCtrl/BackGround>
#include <mTrendCtrl/Description>
#include <mTrendCtrl/Foreground>
#include <mTrendCtrl/Scale>

#include <MeasureTempRecorder>
#include <wiringTempThreshold>

#include <QTimer>

#include "debug.h"

using namespace mTrend;


#define DESC_POS_L          100
#define DESC_POS_T          20
#define DESC_OFFSET_X       75


CWiringMeasureTempTrendDlg::CWiringMeasureTempTrendDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_trend(NULL)
, m_comboBox(NULL)
, m_showItem(0)
{
    m_trend = createTrend();
    _create_comboBox(m_comboBox, "comboBox_trend", DESC_POS_L+DESC_OFFSET_X*4, DESC_POS_T);
    m_comboBox->setFixedHeight(m_comboBox->size().height()-10);
    m_comboBox->setFixedWidth(DESC_OFFSET_X-10);
    m_comboBox->addItem(CWiringMeasureTempTrendDlg::tr("Line In"));
    m_comboBox->addItem(CWiringMeasureTempTrendDlg::tr("Line Out"));
    m_comboBox->setFont(QFont(QString::fromLocal8Bit(WFG_FONT_STYLE), WFG_TITLE_FONT_SIZE, QFont::Normal));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTrend()));
    connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeShowType(int)));
}

CWiringMeasureTempTrendDlg::~CWiringMeasureTempTrendDlg()
{
    STU_DELETE_PTR(m_trend);
    STU_DELETE_PTR(m_comboBox);
}


void CWiringMeasureTempTrendDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        WIRING_TEMP_THRESHOLD tempThreshold;
        CTempHumidityParam::getInstance()->wiringTempThreshold(&tempThreshold);
        float fThreshold = tempThreshold.fContactTemp[0];
        thesholdTrend::WaveData data;
        for(int i = 0; i < WAVE_POINT_NUM; i++) {
            data.xData = (float)i;
            data.yData[0] = fThreshold*m_tScaleInfo.fScaleY;
            m_pThesholdWave->AppendData(data);
        }
        m_trend->Init();

        changeShowType(m_comboBox->currentIndex());
        this->show();
        if (m_timer && !m_timer->isActive())
            m_timer->start(1000);
        connect(CMeasureTempRecorder::recorder(), SIGNAL(dataUpdated(int)), this, SLOT(updateDataBase(int)));
    }

    if (style == CWiringMeasureTempTrendDlg::CONTENT_FOCUE)
        m_comboBox->setFocus();
}

void CWiringMeasureTempTrendDlg::_HideContent()
{
    if (m_timer && !m_timer->isActive())
        m_timer->stop();
    disconnect(CMeasureTempRecorder::recorder(), SIGNAL(dataUpdated(int)), this, SLOT(updateDataBase(int)));
    m_pThesholdWave->RemoveAll();

    CBaseDialog::_HideContent();
}

CTrendCtrl* CWiringMeasureTempTrendDlg::createTrend()
{
    QRect rect(this->rect());
    CTrendCtrl* trendCtrl = new CTrendCtrl(NULL, NULL, this);
    trendCtrl->setGeometry(rect);

    m_tScaleInfo.fScaleX = 20.0;
    m_tScaleInfo.gridCountX = 24;
    m_tScaleInfo.intervalX = 3;
    m_tScaleInfo.divIntervalX = 1;
    m_tScaleInfo.fScaleY = 10.0;
    m_tScaleInfo.gridCountY = 100;
    m_tScaleInfo.intervalY = 10;
    m_tScaleInfo.divIntervalY = 2;
    m_tScaleInfo.magin.setMargin(40, 40, 60, 30);
    m_tScaleInfo.rectClient = rect;
    m_tScaleInfo.axisDirY = POSITIVE;
    m_tScaleInfo.axisDirX = POSITIVE;

    CBackGround* pBackGround = new CBackGround(BACKGROUND_ID);

    CScale* pScale = new CScale(SCALE_ID, pBackGround);
    pScale->SetShowTitle(true, true);
    pScale->SetTitle(CWiringMeasureTempTrendDlg::tr("Time/h"), CWiringMeasureTempTrendDlg::tr("Temp/℃"));
    pScale->AttachScale(&m_tScaleInfo);
    pScale->setScaleValPos(40, -1);

    int x = DESC_POS_L;
    int y = DESC_POS_T;
    CDescription* pDesc1 = new CDescription(DESCRIPTION_1_ID, pScale);
    pDesc1->SetLabelColor(qRgb(255,255, 0));
    pDesc1->SetDescriptionPos(QPoint(x, y));
    pDesc1->SetDescription(CWiringMeasureTempTrendDlg::tr("Phase A"));

    x += DESC_OFFSET_X;
    CDescription* pDesc2 = new CDescription(DESCRIPTION_2_ID, pDesc1);
    pDesc2->SetLabelColor(qRgb(0,255, 0));
    pDesc2->SetDescriptionPos(QPoint(x, y));
    pDesc2->SetDescription(CWiringMeasureTempTrendDlg::tr("Phase B"));

    x += DESC_OFFSET_X;
    CDescription* pDesc3 = new CDescription(DESCRIPTION_3_ID, pDesc2);
    pDesc3->SetLabelColor(qRgb(255,0, 0));
    pDesc3->SetDescriptionPos(QPoint(x, y));
    pDesc3->SetDescription(CWiringMeasureTempTrendDlg::tr("Phase C"));

    x += DESC_OFFSET_X;
    CDescription* pDesc4 = new CDescription(DESCRIPTION_4_ID, pDesc3);
    pDesc4->SetLabelColor(qRgb(0,0, 255));
    pDesc4->SetDescriptionPos(QPoint(x, y));
    pDesc4->SetDescription(CWiringMeasureTempTrendDlg::tr("Warning"));

    m_pThesholdWave = new thesholdTrend(TREND_1_ID, pDesc4);
    m_pThesholdWave->AttachScale(&m_tScaleInfo);
    m_pThesholdWave->SetColor(0, qRgb(0, 0, 255));

    CForeground* pForeground = new CForeground(FOREGROUND_ID);

    m_pWave = new waveTrend(TREND_2_ID, pForeground);
    m_pWave->AttachScale(&m_tScaleInfo);
    m_pWave->SetColor(0, qRgb(255,255, 0));
    m_pWave->SetColor(1, qRgb(0,255, 0));
    m_pWave->SetColor(2, qRgb(255, 0, 0));

    trendCtrl->SetComponent(m_pThesholdWave, m_pWave);

    return trendCtrl;
}

/*
 *  @type 取值
 *   0: 加入新数据
 *   1：最后一个数据被更新
 *  -1：列别被清空
 */
void CWiringMeasureTempTrendDlg::updateDataBase(int type)
{
    static int dataPos = 0;
    CMeasureTempRecorder* recorder = CMeasureTempRecorder::recorder();
    if (type == -1) {
        dataPos = 0;
        m_pWave->RemoveAll();
    }
    else if (type == 1) {
        if (dataPos!=0)
            dataPos--;
    }

    TempReordInfo tempInfo;    
    waveTrend::WaveData data;
    while (recorder->recordInfo(dataPos, &tempInfo)) {
        recordInfoToWaveData(tempInfo, &data);
        if (m_pWave->DataCount() != 0)
        {
            const waveTrend::WaveData& endData = *m_pWave->endData();
            if (data.xData == endData.xData) {
                for(int i = 0 ; i < MAX_PHASE_NUM; i++)
                    data.yData[i] = (data.yData[i] + endData.yData[i])/2;
                m_pWave->ReplaceData(m_pWave->DataCount()-1, data);
            }
            else {
                m_pWave->AppendData(data);
            }
        }
        else {
            m_pWave->AppendData(data);
        }
        dataPos++;
    }

    qDebug() << "dataPos" << dataPos;
}

void CWiringMeasureTempTrendDlg::changeShowType(int item)
{
    Q_ASSERT(item >= 0 && item < 2);
    m_showItem = item;
    updateDataBase(-1);
    updateTrend();
}


void CWiringMeasureTempTrendDlg::recordInfoToWaveData(const TempReordInfo& record, waveTrend::WaveData* data)
{
    Q_ASSERT(data);

    int zeroSec = QDateTime(QDateTime::currentDateTime().date(), QTime(0, 0, 0)).utcOffset();

    data->xData = (record.time - zeroSec) / (3600/m_tScaleInfo.fScaleX);

    for(int i = 0; i < MAX_PHASE_NUM; i++)
        data->yData[i] = Dev_SM::CWiringTempConv::realTemp(record.temp.contact.temp[i][m_showItem])*10;
}