#include "harmonicTrendDialog.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>

#include <mTableWidget>
#include <mComboBox>
#include <mTrendCtrl/BackGround>
#include <mTrendCtrl/Description>
#include <mTrendCtrl/Foreground>
#include <mTrendCtrl/Scale>

#include "debug.h"

using namespace mTrend;


#define TREND_L             50
#define TREND_T             50
#define TREND_H             170
#define TREND_W             400

#define TREND_OFFSET_Y     (TREND_H)



CHarmonicTrendDlg::CHarmonicTrendDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_comboBox(NULL)
{
    m_trend[0] = createTrend(0);
    m_trend[0]->DrawForegound();
    m_trend[1] = createTrend(1);
    m_trend[1]->DrawForegound();

    _create_comboBox(m_comboBox, "comboBox_trend", TREND_L+300, 30);
    m_comboBox->setFixedHeight(m_comboBox->size().height()-10);
    m_comboBox->setFixedWidth(100);
    m_comboBox->addItem(CHarmonicTrendDlg::tr("Phase A Trend"));
    m_comboBox->addItem(CHarmonicTrendDlg::tr("Phase B Trend"));
    m_comboBox->addItem(CHarmonicTrendDlg::tr("Phase C Trend"));
    m_comboBox->setFont(QFont(QString::fromLocal8Bit(WFG_FONT_STYLE), WFG_TITLE_FONT_SIZE, QFont::Normal));


}

CHarmonicTrendDlg::~CHarmonicTrendDlg()
{
    STU_DELETE_PTR(m_trend[0]);
    STU_DELETE_PTR(m_trend[1]);
    STU_DELETE_PTR(m_comboBox);
}



void CHarmonicTrendDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden())
        this->show();

    if (style == CHarmonicTrendDlg::CONTENT_FOCUE)
        m_comboBox->setFocus();
}


CTrendCtrl* CHarmonicTrendDlg::createTrend(int item)
{
    QRect rect(TREND_L, TREND_T+((item)?TREND_OFFSET_Y:0), TREND_W, TREND_H);
    CTrendCtrl* trendCtrl = new CTrendCtrl(NULL, NULL, this);
    trendCtrl->setGeometry(rect);

    QString captionY[] = 
    {
        CHarmonicTrendDlg::tr("U/%"),
        CHarmonicTrendDlg::tr("I/%")
    };

    m_tScaleInfo[item].fScaleX = 1;
    m_tScaleInfo[item].gridCountX = 30;
    m_tScaleInfo[item].intervalX = 10;
    m_tScaleInfo[item].divIntervalX = 1;
    m_tScaleInfo[item].fScaleY = 2;
    m_tScaleInfo[item].gridCountY = 40;
    m_tScaleInfo[item].intervalY = 20;
    m_tScaleInfo[item].divIntervalY = 10;
    m_tScaleInfo[item].magin.setMargin(40, 20, 10, 30);
    m_tScaleInfo[item].rectClient = trendCtrl->rect();
    m_tScaleInfo[item].axisDirY = POSITIVE;
    m_tScaleInfo[item].axisDirX = POSITIVE;

    CBackGround* pBackGround = new CBackGround(BACKGROUND_ID);
    CScale* pScale = new CScale(SCALE_ID, pBackGround);
    pScale->SetShowTitle(true, true);
    pScale->SetTitle("", captionY[item]);
    pScale->AttachScale(&m_tScaleInfo[item]);
    pScale->setScaleValPos(40, -1);

    CForeground* pForeground = new CForeground(FOREGROUND_ID);
    m_pWave[item] = new waveTrend(TREND_2_ID, pForeground);
    m_pWave[item]->AttachScale(&m_tScaleInfo[item]);
    m_pWave[item]->SetColor(0, qRgb(255,0, 255));

    trendCtrl->SetComponent(pScale, m_pWave[item]);
    trendCtrl->Init();

    return trendCtrl;
}