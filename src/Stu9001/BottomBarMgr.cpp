#include "BottomBarMgr.h"
#include "common.h"
#include <QtGui>

#include <stu_utility>
#include "debug.h"

#define TIME_P_L    480
#define TIME_P_T    0


CBottomBarMgr::CBottomBarMgr(QWidget* parent)
: QGroupBox(parent)
{
    label_time = new QLabel(this);
    label_time->setGeometry(TIME_P_L, TIME_P_T, STU_P_BOTTOM_W-TIME_P_L, STU_P_BOTTOM_H);
    label_time->setObjectName("systemTime");

    timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    label_warning = new QLabel(this);
    label_warning->setGeometry(10, TIME_P_T, TIME_P_L-10, STU_P_BOTTOM_H);
    label_warning->setObjectName("warning");
    label_warning->setText("warning");
}

CBottomBarMgr::~CBottomBarMgr()
{
    if (timer && timer->isActive()) {
        timer->stop();
    }
}

#include <dataLevelMisc>
void CBottomBarMgr::updateTime()
{
    if (label_time) {
        QDateTime dateTime;
        stu_getSystemTime(&dateTime);
        label_time->setText(dateTime.toString(Qt::LocalDate));
    }

    static bool rc = false;

    if (rc) {
        label_warning->setStyleSheet("QLabel{color:yellow}");
    }
    else {
        label_warning->setStyleSheet("QLabel{color:red}");
    }

    rc = !rc;
}


void CBottomBarMgr::warning(const QString& text, int splashCnt, int splashInterval)
{
    
}