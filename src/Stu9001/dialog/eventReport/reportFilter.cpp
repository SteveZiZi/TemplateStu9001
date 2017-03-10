#include "reportFilter.h"
#include "common.h"

#include <QtGui/QLabel>
#include <QtGui/QDateEdit>

#include <QKeyEvent>

#include <MCheckBox>
#include <mTableWidget>
#include <mComboBox>
#include <mDataEdit>
#include <mDateTimeEdit>

#include "debug.h"

#define SUB_CTRL_POS_L      4
#define SUB_CTRL_POS_T      10
#define SUB_CTRL_POS_H      30

#define TIME_LABEL_L        (SUB_CTRL_POS_L)
#define TIME_LABEL_T        (SUB_CTRL_POS_T+5)
#define TIME_LABEL_W        (40)
#define TIME_LABEL_H        (SUB_CTRL_POS_H)

#define START_DATE_EDIT_L   (TIME_LABEL_L + TIME_LABEL_W)
#define START_DATE_EDIT_T   (SUB_CTRL_POS_T+4)
#define START_DATE_EDIT_W    105
#define START_DATE_EDIT_H   (22)

#define END_DATE_EDIT_L     (START_DATE_EDIT_L + START_DATE_EDIT_W + 10)
#define END_DATE_EDIT_T     (START_DATE_EDIT_T)
#define END_DATE_EDIT_W     (START_DATE_EDIT_W)
#define END_DATE_EDIT_H     (22)

#define WARNING_CHECKBOX_L  (END_DATE_EDIT_L + END_DATE_EDIT_W + 20)
#define WARNING_CHECKBOX_T  (SUB_CTRL_POS_T)
#define WARNING_CHECKBOX_W  (55)
#define WARNING_CHECKBOX_H  (SUB_CTRL_POS_H)

#define WARNING_EDIT_L      (WARNING_CHECKBOX_L + WARNING_CHECKBOX_W)
#define WARNING_EDIT_T      (SUB_CTRL_POS_T)
#define WARNING_EDIT_W      (70)
#define WARNING_EDIT_H      (SUB_CTRL_POS_H)

#define ACTION_CHECKBOX_L  (WARNING_EDIT_L + WARNING_EDIT_W + 10)
#define ACTION_CHECKBOX_T  (WARNING_CHECKBOX_T)
#define ACTION_CHECKBOX_W  (WARNING_CHECKBOX_W)
#define ACTION_CHECKBOX_H  (WARNING_CHECKBOX_H)

#define ACTION_EDIT_L      (ACTION_CHECKBOX_L + ACTION_CHECKBOX_W)
#define ACTION_EDIT_T      (WARNING_EDIT_T)
#define ACTION_EDIT_W      (WARNING_EDIT_W)
#define ACTION_EDIT_H      (WARNING_EDIT_H)



CReportFilter::CReportFilter(QWidget *parent)
: QGroupBox(parent)
{
    createFilter();

    connect(date_start, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(changedStartDateTime(const QDateTime &)));
    connect(date_end, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(changedEndDateTime(const QDateTime &)));
}

CReportFilter::~CReportFilter()
{
    destoryFilter();
}


void CReportFilter::createFilter()
{
    _create_label(label_time, CReportFilter::tr("time"), TIME_LABEL_L, TIME_LABEL_T);
    label_time->setObjectName("label_time");

    date_start = new MDateTimeEdit(QDateTime::currentDateTime(), MDateTimeEdit::SHOW_MONTH, MDateTimeEdit::SHOW_MINUTE, this);
    date_start->setObjectName("date_start");
    date_start->setGeometry(START_DATE_EDIT_L, START_DATE_EDIT_T, START_DATE_EDIT_W, START_DATE_EDIT_H);

    date_end = new MDateTimeEdit(QDateTime::currentDateTime(), MDateTimeEdit::SHOW_MONTH, MDateTimeEdit::SHOW_MINUTE, this);
    date_end->setObjectName("date_end");
    date_end->setGeometry(END_DATE_EDIT_L, END_DATE_EDIT_T, END_DATE_EDIT_W, END_DATE_EDIT_H);

    checkBox_warning = new MCheckBox(CReportFilter::tr("warning"), this);
    checkBox_warning->setObjectName("checkBox_warning");
    checkBox_warning->setGeometry(WARNING_CHECKBOX_L, WARNING_CHECKBOX_T, WARNING_CHECKBOX_W, WARNING_CHECKBOX_H);

    lineEdit_warningCnt = new MDataEdit((int)9999, 0, 10, CReportFilter::tr("count"), this);
    lineEdit_warningCnt->setObjectName("lineEdit_warningCnt");
    lineEdit_warningCnt->setGeometry(WARNING_EDIT_L, WARNING_EDIT_T, WARNING_EDIT_W, WARNING_EDIT_H);
    lineEdit_warningCnt->setFocusPolicy(Qt::NoFocus);

    checkBox_action = new MCheckBox(CReportFilter::tr("action"), this);
    checkBox_action->setObjectName("checkBox_action");
    checkBox_action->setGeometry(ACTION_CHECKBOX_L, ACTION_CHECKBOX_T, ACTION_CHECKBOX_W, ACTION_CHECKBOX_H);

    lineEdit_actionCnt = new MDataEdit((int)9999, 0, 10, CReportFilter::tr("count"), this);
    lineEdit_actionCnt->setObjectName("lineEdit_actionCnt");
    lineEdit_actionCnt->setGeometry(ACTION_EDIT_L, ACTION_EDIT_T, ACTION_EDIT_W, ACTION_EDIT_H);
    lineEdit_actionCnt->setFocusPolicy(Qt::NoFocus);
}

void CReportFilter::destoryFilter()
{
    STU_DELETE_PTR(label_time);
    STU_DELETE_PTR(date_start);
    STU_DELETE_PTR(date_end);
    STU_DELETE_PTR(checkBox_warning);
    STU_DELETE_PTR(lineEdit_warningCnt);
    STU_DELETE_PTR(checkBox_action);
    STU_DELETE_PTR(lineEdit_actionCnt);
}


void CReportFilter::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "CReportFilter::keyPressEvent" << hex << event->key();

    switch(event->key())
    {
    case Qt::Key_Left:
        focusNextPrevChild(false);
        break;
    case Qt::Key_Right:
        focusNextPrevChild(true);
        break;
    default:
        event->ignore();
        break;
    }
}


bool CReportFilter::focusNextPrevChild(bool next)
{
    QWidget* focus = focusWidget();

    if (next) {
        if (focus == checkBox_action) {
            date_start->setFocus();
        }
        else {
            QGroupBox::focusNextPrevChild(next);
        }
    }
    else {
        if (focus == date_start) {
            checkBox_action->setFocus();
        }
        else {
            QGroupBox::focusNextPrevChild(next);
        }
    }
    return true;
}


void CReportFilter::changedStartDateTime(const QDateTime &dateTime)
{
    emit dateTimeChanged(0, dateTime);
}

void CReportFilter::changedEndDateTime(const QDateTime &dateTime)
{
    emit dateTimeChanged(1, dateTime);
}