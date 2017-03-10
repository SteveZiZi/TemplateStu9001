#include "cubicleTempHumTrendDialog.h"
#include "common.h"

#include <mComboBox>
#include <mTrendCtrl/BackGround>
#include <mTrendCtrl/Description>
#include <mTrendCtrl/Foreground>
#include <mTrendCtrl/Scale>

#include "debug.h"

using namespace mTrend;


#define DESC_POS_L          200
#define DESC_POS_T          20
#define DESC_OFFSET_X       80


CCubicleTempHumTrendDlg::CCubicleTempHumTrendDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_trend(NULL)
, m_comboBox(NULL)
{
    m_trend = createTrend();
    m_trend->DrawForegound();
    _create_comboBox(m_comboBox, "comboBox_trend", DESC_POS_L+DESC_OFFSET_X*2, DESC_POS_T);
    m_comboBox->setFixedHeight(m_comboBox->size().height()-10);
    m_comboBox->setFixedWidth(DESC_OFFSET_X-10);
    m_comboBox->addItem(CCubicleTempHumTrendDlg::tr("Channel 1"));
    m_comboBox->addItem(CCubicleTempHumTrendDlg::tr("Channel 2"));
    m_comboBox->setFont(QFont(QString::fromLocal8Bit(WFG_FONT_STYLE), WFG_TITLE_FONT_SIZE, QFont::Normal));
}

CCubicleTempHumTrendDlg::~CCubicleTempHumTrendDlg()
{
    STU_DELETE_PTR(m_trend);
    STU_DELETE_PTR(m_comboBox);
}



void CCubicleTempHumTrendDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden())
        this->show();

    if (style == CCubicleTempHumTrendDlg::CONTENT_FOCUE)
        m_comboBox->setFocus();
}


CTrendCtrl* CCubicleTempHumTrendDlg::createTrend()
{
    QRect rect(this->rect());
    CTrendCtrl* trendCtrl = new CTrendCtrl(NULL, NULL, this);
    trendCtrl->setGeometry(rect);

    m_tScaleInfo.fScaleX = 10.0;
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
    pScale->SetTitle(CCubicleTempHumTrendDlg::tr("Time/h"), CCubicleTempHumTrendDlg::tr("Temp/¡æ"));
    pScale->AttachScale(&m_tScaleInfo);
    pScale->setScaleValPos(40, -1);

    int x = DESC_POS_L;
    int y = DESC_POS_T;
    CDescription* pDesc1 = new CDescription(DESCRIPTION_1_ID, pScale);
    pDesc1->SetLabelColor(qRgb(255,255, 0));
    pDesc1->SetDescriptionPos(QPoint(x, y));
    pDesc1->SetDescription(CCubicleTempHumTrendDlg::tr("Channel 1"));

    x += DESC_OFFSET_X;
    CDescription* pDesc2 = new CDescription(DESCRIPTION_2_ID, pDesc1);
    pDesc2->SetLabelColor(qRgb(0,255, 0));
    pDesc2->SetDescriptionPos(QPoint(x, y));
    pDesc2->SetDescription(CCubicleTempHumTrendDlg::tr("Channel 2"));


    CForeground* pForeground = new CForeground(FOREGROUND_ID);

    m_pWave = new waveTrend(TREND_2_ID, pForeground);
    m_pWave->AttachScale(&m_tScaleInfo);
    m_pWave->SetColor(0, qRgb(255,255, 0));
    m_pWave->SetColor(1, qRgb(0,255, 0));

    trendCtrl->SetComponent(pDesc2, m_pWave);
    trendCtrl->Init();

    return trendCtrl;
}

void CCubicleTempHumTrendDlg::updateTrend(int type)
{

}