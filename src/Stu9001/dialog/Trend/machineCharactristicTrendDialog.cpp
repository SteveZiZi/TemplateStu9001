#include "machineCharactristicTrendDialog.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>

#include <mTableWidget>
#include <mComboBox>
#include <mTrendCtrl/BackGround>
#include <mTrendCtrl/Description>
#include <mTrendCtrl/Foreground>
#include <mTrendCtrl/Scale>

#include <MachineCharacterRecorder>

#include "debug.h"

using namespace mTrend;
using namespace Dev_SM;


#define TREND_L             60
#define TREND_T             10
#define TREND_H             210
#define TREND_W             440

#define DESC_POS_L          80
#define DESC_POS_T          0
#define DESC_OFFSET_X       55

#define REPORT_L           (TREND_L)
#define REPORT_T           (TREND_T+TREND_H)
#define REPORT_ROW_H       (23)
#define REPORT_ROW_CNT      7
#define REPORT_HEADER_H     20
#define REPORT_CAPTION_W    160
#define REPORT_CONTENT_W    90
#define REPORT_COLUMN_CNT   4
#define REPORT_H           (REPORT_HEADER_H + REPORT_ROW_H*REPORT_ROW_CNT + 2)
#define REPORT_W           (REPORT_CAPTION_W + REPORT_CONTENT_W*(REPORT_COLUMN_CNT-1))


#define SAMPLE_RATE         5000

struct MC_SeparateBrakeInfo {
    QDateTime time;
    float noSync;
    struct {
        float contactDistance;    //锄头开距
        float wholeRoute;
        float wholeTimes;
        float separateBrakeSpeedAvg;
        float separatingBrakeSpeed;
        float bounceAMP;
    }phase[MAX_PHASE_NUM];
};

struct MC_CloseBrakeInfo {
    QDateTime time;
    float noSync;
    struct {
        float contactOverRoute;    //锄头开距
        float wholeRoute;
        float wholeTimes;
        float closeBrakeSpeedAvg;
        float closingBrakeSpeed;
        float bounceTime;
    }phase[MAX_PHASE_NUM];
};

struct MC_StoreEnergyInfo {
    float time;
};
struct MC_ShiftInfo {
    float pos[500];
};
struct MC_CoilCurrent {
    float cur[500];
};
struct MC_MotorCurrent {
    float cur[500];
};

class CMachineCharactristicTrendDlgPrivate {
public:
    CMachineCharactristicTrendDlgPrivate() 
        : m_bSeparateBrakeDataActive(false)
        , m_bCloseBrakeDataActvie(false)
        , m_bStoreEnergyDataActive(false) 
    {
   
    }
    ~CMachineCharactristicTrendDlgPrivate() {}

    MC_SeparateBrakeInfo    m_separateBrakeInfo;
    MC_ShiftInfo          m_separateBrakeShift[MAX_PHASE_NUM];
    MC_CoilCurrent        m_separateBrakeCoilCur;
    bool m_bSeparateBrakeDataActive;
    
    MC_CloseBrakeInfo       m_closeBrakeInfo;
    MC_ShiftInfo          m_closeBrakeShift[MAX_PHASE_NUM];
    MC_CoilCurrent        m_closeBrakeCoilCur;
    bool m_bCloseBrakeDataActvie;

    MC_StoreEnergyInfo    m_storeEnergyInfo;
    MC_MotorCurrent       m_storeEnergyMotorCur;
    bool m_bStoreEnergyDataActive;

};


static void recordToSeparateBrakeInfo(const MC_SeparateBrakeRecordItem& record, MC_SeparateBrakeInfo& info);
static void recordToSeparateBrakeShift(const MC_SeparateBrakeRecordItem& record, MC_ShiftInfo shift[MAX_PHASE_NUM]);
static void recordToSeparateBrakeCoilCur(const MC_SeparateBrakeRecordItem& record, MC_CoilCurrent& coilCur);

static void recordToCloseBrakeInfo(const MC_CloseBrakeRecordItem& record, MC_CloseBrakeInfo& info);
static void recordToCloseBrakeShift(const MC_CloseBrakeRecordItem& record, MC_ShiftInfo shift[MAX_PHASE_NUM]);
static void recordToCloseBrakeCoilCur(const MC_CloseBrakeRecordItem& record, MC_CoilCurrent& coilCur);

static void recordToStoreEnergyInfo(const MC_StoreEnergyRecordItem& record, MC_StoreEnergyInfo& info);
static void recordToStoreEnergyMotorCur(const MC_StoreEnergyRecordItem& record, MC_MotorCurrent& motorCur);

static void recordDataToWaveData(const MC_ShiftInfo shift[MAX_PHASE_NUM],
                                 const MC_CoilCurrent& coilCur,
                                 const mTrend::ScaleInfo& tScaleInfo,
                                 CMachineCharactristicTrendDlg::waveTrend* trendData);


CMachineCharactristicTrendDlg::CMachineCharactristicTrendDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_trend(NULL)
, m_comboBox(NULL)
, m_tableWidget(NULL)
, m_data(new CMachineCharactristicTrendDlgPrivate())
{
    m_trend = createTrend();
    m_trend->DrawForegound();
    _create_comboBox(m_comboBox, "comboBox_trend", TREND_L+DESC_POS_L+DESC_OFFSET_X*4+10, TREND_T+DESC_POS_T);
    m_comboBox->setFixedHeight(m_comboBox->size().height()-10);
    m_comboBox->setFixedWidth(DESC_OFFSET_X+40);
    m_comboBox->addItem(CMachineCharactristicTrendDlg::tr("separate brake trend"));
    m_comboBox->addItem(CMachineCharactristicTrendDlg::tr("close brake trend"));
    //m_comboBox->addItem(CMachineCharactristicTrendDlg::tr("store energy trend"));
    m_comboBox->setFont(QFont(QString::fromLocal8Bit(WFG_FONT_STYLE), WFG_TITLE_FONT_SIZE, QFont::Normal));

    m_tableWidget = createTableWidget("machineCharactristicTrend");

    connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeShowType(int)));
}

CMachineCharactristicTrendDlg::~CMachineCharactristicTrendDlg()
{
    STU_DELETE_PTR(m_trend);
    STU_DELETE_PTR(m_data);
}


void CMachineCharactristicTrendDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        changeShowType(m_comboBox->currentIndex());
        this->show();
        connect(CMachineCharacterRecorder::recorder(), SIGNAL(dataUpdated(int)), this, SLOT(updateDataBase(int)));
    }

    if (style == CMachineCharactristicTrendDlg::CONTENT_FOCUE)
        m_comboBox->setFocus();
}

void CMachineCharactristicTrendDlg::_HideContent()
{
    disconnect(CMachineCharacterRecorder::recorder(), SIGNAL(dataUpdated(int)), this, SLOT(updateDataBase(int)));

    CBaseDialog::_HideContent();
}


CTrendCtrl* CMachineCharactristicTrendDlg::createTrend()
{
    QRect rect(TREND_L, TREND_T, TREND_W, TREND_H);
    CTrendCtrl* trendCtrl = new CTrendCtrl(NULL, NULL, this);
    trendCtrl->setGeometry(rect);

    m_tScaleInfo.fScaleX = 0.01;
    m_tScaleInfo.gridCountX = 8000;
    m_tScaleInfo.intervalX = 2000;
    m_tScaleInfo.divIntervalX = 500;
    m_tScaleInfo.fScaleY = 0.01;
    m_tScaleInfo.gridCountY = 2500;
    m_tScaleInfo.intervalY = 500;
    m_tScaleInfo.divIntervalY = 500;
    m_tScaleInfo.magin.setMargin(50, 40, 100, 30);
    m_tScaleInfo.rectClient = trendCtrl->rect();
    m_tScaleInfo.axisDirY = POSITIVE;
    m_tScaleInfo.axisDirX = POSITIVE;

    CBackGround* pBackGround = new CBackGround(BACKGROUND_ID);

    CScale* pScale = new CScale(SCALE_ID, pBackGround);
    pScale->SetShowTitle(true, true);
    pScale->SetTitle(CMachineCharactristicTrendDlg::tr("0.01ms/Time"), CMachineCharactristicTrendDlg::tr("0.01mm/Route"));
    pScale->AttachScale(&m_tScaleInfo);
    pScale->setScaleValPos(40, -1);

    int x = DESC_POS_L;
    int y = DESC_POS_T;
    CDescription* pDesc1 = new CDescription(DESCRIPTION_1_ID, pScale);
    pDesc1->SetLabelColor(qRgb(255,255, 0));
    pDesc1->SetDescriptionPos(QPoint(x, y));
    pDesc1->SetDescription(CMachineCharactristicTrendDlg::tr("Phase A"));

    x += DESC_OFFSET_X;
    CDescription* pDesc2 = new CDescription(DESCRIPTION_2_ID, pDesc1);
    pDesc2->SetLabelColor(qRgb(0,255, 0));
    pDesc2->SetDescriptionPos(QPoint(x, y));
    pDesc2->SetDescription(CMachineCharactristicTrendDlg::tr("Phase B"));

    x += DESC_OFFSET_X;
    CDescription* pDesc3 = new CDescription(DESCRIPTION_3_ID, pDesc2);
    pDesc3->SetLabelColor(qRgb(255,0, 0));
    pDesc3->SetDescriptionPos(QPoint(x, y));
    pDesc3->SetDescription(CMachineCharactristicTrendDlg::tr("Phase C"));

    x += DESC_OFFSET_X;
    CDescription* pDesc4 = new CDescription(DESCRIPTION_4_ID, pDesc3);
    pDesc4->SetLabelColor(qRgb(0,0, 255));
    pDesc4->SetDescriptionPos(QPoint(x, y));
    pDesc4->SetDescription(CMachineCharactristicTrendDlg::tr("Current"));


    CForeground* pForeground = new CForeground(FOREGROUND_ID);
    m_pWave = new waveTrend(TREND_2_ID, pForeground);
    m_pWave->AttachScale(&m_tScaleInfo);
    m_pWave->SetColor(0, qRgb(255,255, 0));
    m_pWave->SetColor(1, qRgb(0,255, 0));
    m_pWave->SetColor(2, qRgb(255, 0, 0));
    m_pWave->SetColor(3, qRgb(0, 0, 255));

    trendCtrl->SetComponent(pDesc4, m_pWave);
    trendCtrl->Init();

    return trendCtrl;
}

void CMachineCharactristicTrendDlg::updateTrend(int item)
{
    if (item == SEPARATE_BREAKER) {
        if (m_data->m_bSeparateBrakeDataActive)
            recordDataToWaveData(m_data->m_separateBrakeShift, m_data->m_separateBrakeCoilCur, m_tScaleInfo, m_pWave);
        else
            m_pWave->RemoveAll();
    }
    else if (item == CLOSE_BREAKER) {
        if (m_data->m_bCloseBrakeDataActvie)
            recordDataToWaveData(m_data->m_closeBrakeShift, m_data->m_closeBrakeCoilCur, m_tScaleInfo, m_pWave);
        else
            m_pWave->RemoveAll();

    }
    else if (item == STORE_ENERGY) {

    }
    else {
        return;
    }

    m_trend->ResetForgnd();
    m_trend->DrawForegound();
    m_trend->repaint();
}

MTableWidget* CMachineCharactristicTrendDlg::createTableWidget(QString objectName)
{
    static QString captionName[] = {
        CMachineCharactristicTrendDlg::tr("Parameter Name"),
        CMachineCharactristicTrendDlg::tr("A"),
        CMachineCharactristicTrendDlg::tr("B"),
        CMachineCharactristicTrendDlg::tr("C")
    };


    MTableWidget* tableWidget = new MTableWidget(REPORT_ROW_CNT, REPORT_COLUMN_CNT, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setGeometry(REPORT_L, REPORT_T, REPORT_W, REPORT_H);

    QHeaderView* hHeader = new QHeaderView(Qt::Horizontal, tableWidget);
    hHeader->setObjectName("dataShow_hHeader");
    hHeader->setFixedHeight(REPORT_HEADER_H);
    hHeader->setHighlightSections(false);
    tableWidget->setHorizontalHeader(hHeader);

    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(new MGridStyle(QColor(STU_GREEN_LINE), false, true));
    tableWidget->setShowTopBottomLine(false, true);

    for(int i = 0; i < REPORT_COLUMN_CNT; i++) {
        QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(captionName[i]);
        tableWidget->setHorizontalHeaderItem(i, harmonicValHeaderItem);
        if (i != 0) {
            tableWidget->setColumnWidth(i, REPORT_CONTENT_W);
            harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        }
        else {
            tableWidget->setColumnWidth(0, REPORT_CAPTION_W);
            harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        }
    }


    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            if (column == 0) {
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::ItemIsSelectable);
                newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
            }
            else {
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            tableWidget->setItem(row, column, newItem);
        }
        tableWidget->setRowHeight(row, REPORT_ROW_H);
    }

    return tableWidget;
}


void CMachineCharactristicTrendDlg::updateTableWidget(ReportStyle reportStyle, UpdateStyles updateStyles)
{
    Q_ASSERT(m_tableWidget);

    static QString measureName[][REPORT_ROW_CNT] = {
        {
            CMachineCharactristicTrendDlg::tr("contact distance"),
            CMachineCharactristicTrendDlg::tr("separate brake route"),
            CMachineCharactristicTrendDlg::tr("separate brake time"),
            CMachineCharactristicTrendDlg::tr("separate brake bounce AMP"),
            CMachineCharactristicTrendDlg::tr("separate brake speed avg"),
            CMachineCharactristicTrendDlg::tr("separating brake speed"),
            CMachineCharactristicTrendDlg::tr("separate brake async cycle time")
        },
        {
            CMachineCharactristicTrendDlg::tr("contact over route"),
            CMachineCharactristicTrendDlg::tr("close brake route"),
            CMachineCharactristicTrendDlg::tr("close brake time"),
            CMachineCharactristicTrendDlg::tr("close brake bounce Time"),
            CMachineCharactristicTrendDlg::tr("close brake speed avg"),
            CMachineCharactristicTrendDlg::tr("closing brake speed"),
            CMachineCharactristicTrendDlg::tr("close brake async cycle time")
        }
    };

    if (updateStyles&UPDATE_CAPTION) {
        for (int row = 0; row < m_tableWidget->rowCount(); ++row) {
            m_tableWidget->item(row, 0)->setText(measureName[reportStyle][row]);
        }
    }
    if (updateStyles&UPDATE_DATA) {
        switch(reportStyle) {
        case SEPARATE_BREAKER:
            {
                for(int column = 1; column < m_tableWidget->columnCount(); ++column) {
                    float* data = (float*)(&m_data->m_separateBrakeInfo.phase[column-1]);
                    for (int row = 0; row < m_tableWidget->rowCount()-1; ++row) {
                        if (m_data->m_bSeparateBrakeDataActive)
                            m_tableWidget->item(row, column)->setText(QString("%1").arg(data[row], 0, 'g', 2, QChar('0')));
                        else
                            m_tableWidget->item(row, column)->setText("--");
                    }
                }
                if (m_data->m_bSeparateBrakeDataActive) {
                    QString text(QString("%1").arg(m_data->m_separateBrakeInfo.noSync, 0, 'g', 2, QChar('0')));
                    m_tableWidget->item(m_tableWidget->rowCount()-1, 1)->setText(text);
                }
                else {
                    m_tableWidget->item(m_tableWidget->rowCount()-1, 1)->setText("--");
                }
                m_tableWidget->item(m_tableWidget->rowCount()-1, 2)->setText("--");
                m_tableWidget->item(m_tableWidget->rowCount()-1, 3)->setText("--");
            }
            break;
        case CLOSE_BREAKER:
            {
                for(int column = 1; column < m_tableWidget->columnCount(); ++column) {
                    float* data = (float*)(&m_data->m_closeBrakeInfo.phase[column-1]);
                    for (int row = 0; row < m_tableWidget->rowCount()-1; ++row) {
                        if (m_data->m_bCloseBrakeDataActvie)
                            m_tableWidget->item(row, column)->setText(QString("%1").arg(data[row], 0, 'g', 2, QChar('0')));
                        else
                            m_tableWidget->item(row, column)->setText("--");
                    }
                }
                if (m_data->m_bCloseBrakeDataActvie) {
                    QString text(QString("%1").arg(m_data->m_closeBrakeInfo.noSync, 0, 'g', 2, QChar('0')));
                    m_tableWidget->item(m_tableWidget->rowCount()-1, 1)->setText(text);
                }
                else {
                    m_tableWidget->item(m_tableWidget->rowCount()-1, 1)->setText("--");
                }
                m_tableWidget->item(m_tableWidget->rowCount()-1, 2)->setText("--");
                m_tableWidget->item(m_tableWidget->rowCount()-1, 3)->setText("--");
            }
            break;
        case STORE_ENERGY:
            break;
        default:
            break;
        }

    }
}

void CMachineCharactristicTrendDlg::updateDataBase(int dataType)
{
    qDebug() << "CMachineCharactristicTrendDlg::updateDataBase dataType:0x" << hex << dataType;
    if (dataType&(1<<SEPARATE_BREAKER)) {
        MC_SeparateBrakeRecordItem record;
        if (CMachineCharacterRecorder::recorder()->lastestSeparateBrakeRecord(&record)) {
            m_data->m_bSeparateBrakeDataActive = true;
            recordToSeparateBrakeInfo(record, m_data->m_separateBrakeInfo);
            recordToSeparateBrakeShift(record, m_data->m_separateBrakeShift);
            recordToSeparateBrakeCoilCur(record, m_data->m_separateBrakeCoilCur);
        }
    }
    else if (dataType&(1<<CLOSE_BREAKER)) {
        MC_CloseBrakeRecordItem record;
        if (CMachineCharacterRecorder::recorder()->lastestCloseBrakeRecord(&record)) {
            m_data->m_bCloseBrakeDataActvie = true;
            recordToCloseBrakeInfo(record, m_data->m_closeBrakeInfo);
            recordToCloseBrakeShift(record, m_data->m_closeBrakeShift);
            recordToCloseBrakeCoilCur(record, m_data->m_closeBrakeCoilCur);
        }
    }
    else if (dataType&(1<<STORE_ENERGY)) {
        MC_StoreEnergyRecordItem record;
        if (CMachineCharacterRecorder::recorder()->lastestStoreEnergyRecord(&record)) {
            m_data->m_bStoreEnergyDataActive = true;
            recordToStoreEnergyInfo(record, m_data->m_storeEnergyInfo);
            recordToStoreEnergyMotorCur(record, m_data->m_storeEnergyMotorCur);
        }
    }

    changeShowType(m_showItem);
}

void CMachineCharactristicTrendDlg::changeShowType(int item)
{
    Q_ASSERT(item >= 0 && item <= 2);
    m_showItem = item;
    updateTrend(item);
    if (item < 2)
        updateTableWidget(ReportStyle(item), UpdateStyles(UPDATE_DATA|UPDATE_CAPTION));
}




static void recordToSeparateBrakeInfo(const MC_SeparateBrakeRecordItem& record, MC_SeparateBrakeInfo& info)
{
    info.noSync = CMachineCharacterConv::realNoSync(record.info.noSync);
    for(int i = PHASE_A; i < MAX_PHASE_NUM; i++) {
        info.phase[i].contactDistance = CMachineCharacterConv::realContactDistance(record.info.phase[i].contactDistance);
        info.phase[i].wholeRoute = CMachineCharacterConv::realWholeRoute(record.info.phase[i].wholeRoute);
        info.phase[i].wholeTimes = CMachineCharacterConv::realWholeTimes(record.info.phase[i].wholeTimes);
        info.phase[i].separateBrakeSpeedAvg = CMachineCharacterConv::realAvgSpeed(record.info.phase[i].separateBrakeSpeedAvg);
        info.phase[i].separatingBrakeSpeed = CMachineCharacterConv::realAvgSpeed(record.info.phase[i].separatingBrakeSpeed);
        info.phase[i].bounceAMP = CMachineCharacterConv::realBounceAMP(record.info.phase[i].bounceAMP);
    }
    devTime_t::realTime(record.info.time, &info.time);
}

static void recordToSeparateBrakeShift(const MC_SeparateBrakeRecordItem& record, MC_ShiftInfo shift[MAX_PHASE_NUM])
{
    for(int i = PHASE_A; i < MAX_PHASE_NUM; i++) {
        for(int j = 0; j < 500; j++) {
            shift[i].pos[j] = CMachineCharacterConv::realShift(record.shift[i].pos[j]);
        }
    }
}

static void recordToSeparateBrakeCoilCur(const MC_SeparateBrakeRecordItem& record, MC_CoilCurrent& coilCur)
{
    for(int j = 0; j < 500; j++) {
        coilCur.cur[j] = CMachineCharacterConv::realCur(record.cur.cur[j]);
    }
}

static void recordToCloseBrakeInfo(const MC_CloseBrakeRecordItem& record, MC_CloseBrakeInfo& info)
{
    info.noSync = CMachineCharacterConv::realNoSync(record.info.noSync);
    for(int i = PHASE_A; i < MAX_PHASE_NUM; i++) {
        info.phase[i].contactOverRoute = CMachineCharacterConv::realContactOverRoute(record.info.phase[i].contactOverRoute);
        info.phase[i].wholeRoute = CMachineCharacterConv::realWholeRoute(record.info.phase[i].wholeRoute);
        info.phase[i].wholeTimes = CMachineCharacterConv::realWholeTimes(record.info.phase[i].wholeTimes);
        info.phase[i].closeBrakeSpeedAvg = CMachineCharacterConv::realAvgSpeed(record.info.phase[i].closeBrakeSpeedAvg);
        info.phase[i].closingBrakeSpeed = CMachineCharacterConv::realAvgSpeed(record.info.phase[i].closingBrakeSpeed);
        info.phase[i].bounceTime = CMachineCharacterConv::realBounceTime(record.info.phase[i].bounceTime);
    }
    devTime_t::realTime(record.info.time, &info.time);
}

static void recordToCloseBrakeShift(const MC_CloseBrakeRecordItem& record, MC_ShiftInfo shift[MAX_PHASE_NUM])
{
    for(int i = PHASE_A; i < MAX_PHASE_NUM; i++) {
        for(int j = 0; j < 500; j++) {
            shift[i].pos[j] = CMachineCharacterConv::realShift(record.shift[i].pos[j]);
        }
    }
}

static void recordToCloseBrakeCoilCur(const MC_CloseBrakeRecordItem& record, MC_CoilCurrent& coilCur)
{
    for(int j = 0; j < 500; j++) {
        coilCur.cur[j] = CMachineCharacterConv::realCur(record.cur.cur[j]);
    }
}

static void recordToStoreEnergyInfo(const MC_StoreEnergyRecordItem& record, MC_StoreEnergyInfo& info)
{
    info.time = CMachineCharacterConv::realStoreEnergyTime(record.info.time);
}

static void recordToStoreEnergyMotorCur(const MC_StoreEnergyRecordItem& record, MC_MotorCurrent& motorCur)
{
    for(int j = 0; j < 500; j++) {
        motorCur.cur[j] = CMachineCharacterConv::realCur(record.cur.cur[j]);
    }
}



static void recordDataToWaveData(const MC_ShiftInfo shift[MAX_PHASE_NUM],
                                 const MC_CoilCurrent& coilCur,
                                 const mTrend::ScaleInfo& tScaleInfo,
                                 CMachineCharactristicTrendDlg::waveTrend* trendData)
{
    trendData->RemoveAll();
    CMachineCharactristicTrendDlg::waveTrend::WaveData data;
    int xPointMax = tScaleInfo.gridCountX * tScaleInfo.fScaleX * SAMPLE_RATE/1000;
    int xLoop = qMin<int>(xPointMax, 500);
    for(int i = 0 ; i < xLoop; i++) {
        data.xData = (float)(i*1000.0/SAMPLE_RATE);
#if 1
        data.yData[0] = (float)(shift[PHASE_A].pos[i]);
        data.yData[1] = (float)(shift[PHASE_B].pos[i]);
        data.yData[2] = (float)(shift[PHASE_C].pos[i]);
        data.yData[3] = (float)(coilCur.cur[i]*25/80*tScaleInfo.fScaleY);
#else
        data.yData[0] = (float)(0.05*i);
        data.yData[1] = (float)(0.04*i);
        data.yData[2] = (float)(0.03*i);
        data.yData[3] = (float)(4000*25/80*tScaleInfo.fScaleY);
#endif
        trendData->AppendData(data);
    }
    if (xPointMax > 500) {
        data.xData = tScaleInfo.gridCountX-1;
        trendData->AppendData(data);
    }
}
