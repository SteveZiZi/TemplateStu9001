#include "cubicleViews.h"
#include "common.h"

#include "debug.h"


#define LAMP_WIDTH          32
#define LAMP_HEIGHT         34
//Lamp
#define LAMP1_LEFT          161
#define LAMP1_TOP           1
#define LAMP2_LEFT          9
#define LAMP2_TOP           356

//FAN
#define FAN_WIDTH           31
#define FAN_HEIGHT          30
#define FAN1_LEFT           118
#define FAN1_TOP            59
#define FAN2_LEFT           FAN1_LEFT
#define FAN2_TOP            330

//Heater
#define HEATER_WIDTH        31
#define HEATER_HEIGHT       19
#define HEATER1_LEFT        FAN1_LEFT
#define HEATER1_TOP         FAN1_TOP+FAN_WIDTH+4
#define HEATER2_LEFT        FAN2_LEFT
#define HEATER2_TOP         FAN2_TOP+FAN_WIDTH+4

//Earthing Knif
#define EARTHING_KNIF_WIDTH             39
#define EARTHING_KNIF_HEIGHT            45
#define EARTHING_KNIF_LEFT              65
#define EARTHING_KNIF_TOP               246


//Barrow
#define BARROW_WIDTH            132
#define BARROW_HEIGHT           101
#define BARROW_LEFT             105
#define BARROW_TOP              171


CCubicleViews::CCubicleViews(QWidget *parent)
: QGroupBox(parent)
{
    m_fan[0] = createFan(FAN1_LEFT, FAN1_TOP, FAN_WIDTH, FAN_HEIGHT);
    m_fan[1] = createFan(FAN2_LEFT, FAN2_TOP, FAN_WIDTH, FAN_HEIGHT);

    m_lamp[0] = createLamp(LAMP1_LEFT, LAMP1_TOP, LAMP_WIDTH, LAMP_HEIGHT);
    m_lamp[1] = createLamp(LAMP2_LEFT, LAMP2_TOP, LAMP_WIDTH, LAMP_HEIGHT);

    m_heater[0] = createHeater(HEATER1_LEFT, HEATER1_TOP, HEATER_WIDTH, HEATER_HEIGHT);
    m_heater[1] = createHeater(HEATER2_LEFT, HEATER2_TOP, HEATER_WIDTH, HEATER_HEIGHT);

    m_barrow = createBarrow(BARROW_LEFT, BARROW_TOP, BARROW_WIDTH, BARROW_HEIGHT);
    m_earthKnife = createEarthKnife(EARTHING_KNIF_LEFT, EARTHING_KNIF_TOP, EARTHING_KNIF_WIDTH, EARTHING_KNIF_HEIGHT);

    m_bFanOn[0] = false;
    m_bFanOn[1] = false;
}

CCubicleViews::~CCubicleViews()
{
    STU_DELETE_PTR(m_fan[0]);
    STU_DELETE_PTR(m_fan[1]);

    STU_DELETE_PTR(m_lamp[0]);
    STU_DELETE_PTR(m_lamp[1]);

    STU_DELETE_PTR(m_heater[0]);
    STU_DELETE_PTR(m_heater[1]);

    STU_DELETE_PTR(m_barrow);
    STU_DELETE_PTR(m_earthKnife);
}

void CCubicleViews::setVisible(bool visible)
{
    QGroupBox::setVisible(visible);

    if (visible) {
        operate_fun(0, m_bFanOn[0]);
        operate_fun(1, m_bFanOn[1]);
    }
    else {
        m_bFanOn[0] = m_fan[0]->isPlay();
        m_bFanOn[1] = m_fan[1]->isPlay();
        m_fan[0]->stopPlay();
        m_fan[1]->stopPlay();
    }
}

void CCubicleViews::setBarrowInitStatus(CMachine::STATE_ENUM status)
{
    m_barrow->SetState(m_barrow->GetState(status));
}

void CCubicleViews::setEarthKnifeInitStatus(CMachine::STATE_ENUM status)
{
    m_earthKnife->SetState(m_earthKnife->GetState(status));
}


CMachine* CCubicleViews::createBarrow(int x, int y, int w, int h)
{
    CMachine* machine = new CMachine(this);
    machine->setGeometry(x, y, w, h);

    for(int i = 1; i <= 23; i++) {
        machine->insertImage(QString(":/images/images/elecOperator/Breaker/%1.png").arg(i));
    }

    return machine;
}

CMachine* CCubicleViews::createEarthKnife(int x, int y, int w, int h)
{
    CMachine* machine = new CMachine(this);
    machine->setGeometry(x, y, w, h);

    for(int i = 1; i <= 9; i++) {
        machine->insertImage(QString(":/images/images/elecOperator/EarthingKnife/%1.png").arg(i));
    }

    return machine;
}

CImageShow* CCubicleViews::createLamp(int x, int y, int w, int h)
{
    CImageShow* imageShow = new CImageShow(this);
    imageShow->setGeometry(x, y, w, h);

    imageShow->insertImage(":/images/images/elecOperator/Lamp/off.png");
    imageShow->insertImage(":/images/images/elecOperator/Lamp/on.png");

    return imageShow;
}

CImageShow* CCubicleViews::createFan(int x, int y, int w, int h)
{
    CImageShow* imageShow = new CImageShow(this);
    imageShow->setGeometry(x, y, w, h);

    for(int i = 1; i <= 6; i++) {
        imageShow->insertImage(QString(":/images/images/elecOperator/Fan/%1.png").arg(i));
    }

    return imageShow;
}

CImageShow* CCubicleViews::createHeater(int x, int y, int w, int h)
{
    CImageShow* imageShow = new CImageShow(this);
    imageShow->setGeometry(x, y, w, h);

    imageShow->insertImage(":/images/images/elecOperator/Heater/unHeating.png");
    imageShow->insertImage(":/images/images/elecOperator/Heater/heating.png");

    return imageShow;
}

