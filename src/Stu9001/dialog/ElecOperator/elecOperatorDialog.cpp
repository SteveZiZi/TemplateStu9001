#include "elecOperatorDialog.h"
#include "common.h"

#include <mComboBox>

#include "cubicleViews.h"
#include "cubicleOperator.h"
#include "barrowOperator.h"
#include "earthKnifeOperator.h"

#include "debug.h"

#define REPORT_POS_L        60
#define REPORT_POS_T        60

#define REPORT_W            170
#define REPORT_H            360

#define IMAGE_W             251
#define IMAGE_H             418
#define IMAGE_POS_L        (STU_P_BODY1_W - IMAGE_W - 2)
#define IMAGE_POS_T        (STU_P_BODY1_H - IMAGE_H - 3)



CElecOperatorDlg::CElecOperatorDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_cubicleViews(NULL)
, m_cubicleOperator(NULL)
, m_barrowOperator(NULL)
, m_earthKnifeOperator(NULL)
, m_item(-1)
, m_cubicleOperatorTimer(NULL)
{
    m_dev = CElecOperatorData::getInstance();

    m_cubicleViews = new CCubicleViews(this);
    m_cubicleViews->setObjectName("cubicleViews");
    m_cubicleViews->setGeometry(IMAGE_POS_L, IMAGE_POS_T, IMAGE_W, IMAGE_H);
    m_cubicleViews->setBarrowInitStatus(CMachine::STATE_OPEN);
    m_cubicleViews->setEarthKnifeInitStatus(CMachine::STATE_OPEN);

    m_cubicleOperator = new CCubicleOperator(this);
    m_cubicleOperator->setObjectName("cubicleOperator");
    m_cubicleOperator->setGeometry(REPORT_POS_L, REPORT_POS_T, REPORT_W, REPORT_H);
    m_cubicleOperator->hide(); 

    m_barrowOperator = new CbarrowOperator(this);
    m_barrowOperator->setObjectName("barrowOperator");
    m_barrowOperator->setGeometry(REPORT_POS_L, REPORT_POS_T, REPORT_W, REPORT_H);
    m_barrowOperator->hide();

    m_earthKnifeOperator = new CEarthKnifeOperator(this);
    m_earthKnifeOperator->setObjectName("earthKnifeOperator");
    m_earthKnifeOperator->setGeometry(REPORT_POS_L, REPORT_POS_T, REPORT_W, REPORT_H);
    m_earthKnifeOperator->hide();

    connect(m_cubicleOperator, SIGNAL(modeChanged(bool)), this, SLOT(changeOperatorMode(bool)));
    connect(m_cubicleOperator, SIGNAL(fanStatusChanged(int, bool)), this, SLOT(changeFanStatus(int, bool)));
    connect(m_cubicleOperator, SIGNAL(lampStatusChanged(int, bool)), this, SLOT(changeLampStatus(int, bool)));
    connect(m_cubicleOperator, SIGNAL(heaterStatusChanged(int, bool)), this, SLOT(changeHeaterStatus(int, bool)));
    connect(m_cubicleOperator, SIGNAL(gateStatusChanged(bool)), this, SLOT(changeGateStatus(bool)));

    connect(m_cubicleOperator, SIGNAL(fanStatusChanged(int, bool)), m_cubicleViews, SLOT(operate_fun(int, bool)));
    connect(m_cubicleOperator, SIGNAL(lampStatusChanged(int, bool)), m_cubicleViews, SLOT(operate_lamp(int, bool)));
    connect(m_cubicleOperator, SIGNAL(heaterStatusChanged(int, bool)), m_cubicleViews, SLOT(operate_heater(int, bool)));


    connect(m_barrowOperator, SIGNAL(tele_in()), m_cubicleViews, SLOT(barrow_close()));
    connect(m_barrowOperator, SIGNAL(tele_out()), m_cubicleViews, SLOT(barrow_open()));
    connect(m_barrowOperator, SIGNAL(stop()), m_cubicleViews, SLOT(barrow_stop()));

    connect(m_barrowOperator, SIGNAL(tele_in()), this, SLOT(barrowTeleIn()));
    connect(m_barrowOperator, SIGNAL(tele_out()), this, SLOT(barrowTeleOut()));
    connect(m_barrowOperator, SIGNAL(stop()), this, SLOT(barrowStop()));
    connect(m_barrowOperator, SIGNAL(reset()), this, SLOT(barrowReset()));


    connect(m_earthKnifeOperator, SIGNAL(tele_in()), m_cubicleViews, SLOT(earthKnife_close()));
    connect(m_earthKnifeOperator, SIGNAL(tele_out()), m_cubicleViews, SLOT(earthKnife_open()));
    connect(m_earthKnifeOperator, SIGNAL(stop()), m_cubicleViews, SLOT(earthKnife_stop()));

    connect(m_earthKnifeOperator, SIGNAL(tele_in()), this, SLOT(earthKnifeTeleIn()));
    connect(m_earthKnifeOperator, SIGNAL(tele_out()), this, SLOT(earthKnifeTeleOut()));
    connect(m_earthKnifeOperator, SIGNAL(stop()), this, SLOT(earthKnifeStop()));
    connect(m_earthKnifeOperator, SIGNAL(reset()), this, SLOT(earthKnifeReset()));
}

CElecOperatorDlg::~CElecOperatorDlg()
{
    STU_DELETE_PTR(m_cubicleViews);
    STU_DELETE_PTR(m_cubicleOperator);
    STU_DELETE_PTR(m_barrowOperator);
    STU_DELETE_PTR(m_earthKnifeOperator);
}

void CElecOperatorDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        updateOperateMode();
        updateCubicleStatus();
        m_cubicleViews->show();
        this->show();
    }

    m_item = data;
    if (m_item == 0) {
        m_cubicleOperator->show();
        if (style == CAbstractMenuContent::CONTENT_FOCUE) 
            m_cubicleOperator->setFocus();
    }
    else if (m_item == 1) {
        m_barrowOperator->show();
        if (style == CAbstractMenuContent::CONTENT_FOCUE)
            m_barrowOperator->setFocus();
    }
    else if (m_item == 2) {
        m_earthKnifeOperator->show();
        if (style == CAbstractMenuContent::CONTENT_FOCUE)
            m_earthKnifeOperator->setFocus();
    }
}


void CElecOperatorDlg::_HideContent()
{
    if (m_item != -1) {
        if (m_item == 0)
            m_cubicleOperator->hide();
        else if (m_item == 1) 
            m_barrowOperator->hide();
        else if (m_item == 2) 
            m_earthKnifeOperator->hide();
        m_item = -1;
        m_cubicleViews->hide();
    }

    endDetectCubicle();

    CBaseDialog::_HideContent();
}

void CElecOperatorDlg::updateOperateMode()
{
    Q_ASSERT(m_dev);
    m_dev->GetCubicleOperateMode(&m_operateMode);
    m_cubicleOperator->comboBox(0)->setCurrentIndex(m_operateMode.bAutoOperator);
    if (m_operateMode.bAutoOperator) {
        startDetectCubicle();
    }
}

void CElecOperatorDlg::updateCubicleStatus()
{
    Q_ASSERT(m_dev);
    m_dev->GetCubicleStatus(&m_cubicleStatus);

    bool* val = (bool*)&m_cubicleStatus;
    for(int row = 1; row < CCubicleOperator::ROWS; row++) {
        m_cubicleOperator->comboBox(row)->setCurrentIndex(*val);
        val++;
    }
}

void CElecOperatorDlg::updateBarrowStatus()
{

}

void CElecOperatorDlg::updateEarthKnifeStatus()
{

}



void CElecOperatorDlg::changeOperatorMode(bool bAutoMode)
{
    if (m_operateMode.bAutoOperator != bAutoMode) {
        m_operateMode.bAutoOperator = bAutoMode;
        m_dev->SetCubicleOperateMode(m_operateMode);
        if (m_operateMode.bAutoOperator) {
            startDetectCubicle();
        }
        else {
            endDetectCubicle();
        }
    }
}

void CElecOperatorDlg::changeFanStatus(int item, bool start)
{
    if (m_cubicleStatus.bFanStart[item] != start) {
        m_cubicleStatus.bFanStart[item] = start;
        m_dev->SetCubicleStatus(m_cubicleStatus);
    }
}

void CElecOperatorDlg::changeLampStatus(int item, bool start)
{
    if (m_cubicleStatus.bLampOn != start) {
        m_cubicleStatus.bLampOn = start;
        m_dev->SetCubicleStatus(m_cubicleStatus);
    }
}

void CElecOperatorDlg::changeHeaterStatus(int item, bool start)
{
    if (m_cubicleStatus.bHeaterStart[item] != start) {
        m_cubicleStatus.bHeaterStart[item] = start;
        m_dev->SetCubicleStatus(m_cubicleStatus);
    }
}

void CElecOperatorDlg::changeGateStatus(bool start)
{
    if (m_cubicleStatus.bGateLock == start) {
        m_cubicleStatus.bGateLock = !start;
        m_dev->SetCubicleStatus(m_cubicleStatus);
    }
}


void CElecOperatorDlg::barrowTeleIn()
{
    qDebug() << "CElecOperatorDlg::barrowTeleIn";
}

void CElecOperatorDlg::barrowTeleOut()
{
    qDebug() << "CElecOperatorDlg::barrowTeleOut";
}

void CElecOperatorDlg::barrowStop()
{
    qDebug() << "CElecOperatorDlg::barrowStop";
}

void CElecOperatorDlg::barrowReset()
{
    qDebug() << "CElecOperatorDlg::barrowReset";
}


void CElecOperatorDlg::earthKnifeTeleIn()
{
    qDebug() << "CElecOperatorDlg::earthKnifeTeleIn";
}

void CElecOperatorDlg::earthKnifeTeleOut()
{
    qDebug() << "CElecOperatorDlg::earthKnifeTeleOut";
}

void CElecOperatorDlg::earthKnifeStop()
{
    qDebug() << "CElecOperatorDlg::earthKnifeStop";
}

void CElecOperatorDlg::earthKnifeReset()
{
    qDebug() << "CElecOperatorDlg::earthKnifeReset";
}

void CElecOperatorDlg::startDetectCubicle()
{
    if (!m_cubicleOperatorTimer) {
        m_cubicleOperatorTimer = new QTimer(this);
    }

    if (!m_cubicleOperatorTimer->isActive()) {
        connect(m_cubicleOperatorTimer, SIGNAL(timeout()), this, SLOT(detectCubicleStatus()));
        m_cubicleOperatorTimer->start(500);
    }
}

void CElecOperatorDlg::endDetectCubicle()
{
    if (m_cubicleOperatorTimer) {
        if (m_cubicleOperatorTimer->isActive()) {
            m_cubicleOperatorTimer->stop();
            disconnect(m_cubicleOperatorTimer, SIGNAL(timeout()), this, SLOT(detectCubicleStatus()));
        }
        m_cubicleOperatorTimer->deleteLater();
        m_cubicleOperatorTimer = NULL;
    }
}

void CElecOperatorDlg::detectCubicleStatus()
{
    updateCubicleStatus();
}