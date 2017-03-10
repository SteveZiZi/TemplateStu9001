#include "timeSettingDialog.h"
#include "common.h"

#include <QPainter>
#include <QtGui/QLabel>

#include <QTimer>
#include <mDateTimeEdit>
#include <stu_utility>
#include "debug.h"

#define REPORT_POS_L        180
#define REPORT_POS_T        150

#define CAPTION_WIDTH       50
#define CONTENT_WIDTH       60

#define REPORT_ITEM_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_ITEM_H       40



CTimeSettingDlg::CTimeSettingDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    _create_label(label_time, tr("time:"), x, y);

    m_dateTimeEdit = new MDateTimeEdit(this);
    m_dateTimeEdit->setObjectName("systemTimeEdit");
    m_dateTimeEdit->setGeometry(x+CAPTION_WIDTH, y, 158, 25);
    connect(m_dateTimeEdit, SIGNAL(startEdit()), this, SLOT(enterEditMode()));
    connect(m_dateTimeEdit, SIGNAL(cancelEdit()), this, SLOT(cancelEditMode()));
    connect(m_dateTimeEdit, SIGNAL(finishEdit(const QDateTime &)), this, SLOT(finishEditTime(const QDateTime &)));

    m_tickTimer = new QTimer(this);
    connect(m_tickTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
}

CTimeSettingDlg::~CTimeSettingDlg()
{
    if (m_tickTimer && m_tickTimer->isActive()) {
        m_tickTimer->stop();
    }
}



void CTimeSettingDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        updateTime();
        this->show();
        m_tickTimer->start(500);
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
		m_dateTimeEdit->setFocus();
        m_dateTimeEdit->selectAll();
    }
}

void CTimeSettingDlg::_HideContent()
{
    if (m_tickTimer && m_tickTimer->isActive()) {
        m_tickTimer->stop();
    }

    CBaseDialog::_HideContent();
}

void CTimeSettingDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
	const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
	painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());
	painter.setPen(oldPen);
}

void CTimeSettingDlg::moveToNextWidget()
{

}

void CTimeSettingDlg::moveToPreWidget()
{

}


void CTimeSettingDlg::updateTime(void)
{
    QDateTime dateTime;
    stu_getSystemTime(&dateTime);
    m_dateTimeEdit->setDateTime(dateTime);
}


void CTimeSettingDlg::enterEditMode(void)
{
    m_tickTimer->stop();
}

void CTimeSettingDlg::cancelEditMode(void)
{
    m_tickTimer->start(500);
}

void CTimeSettingDlg::finishEditTime(const QDateTime &dateTime)
{
    stu_setSystemTime(&dateTime);
    m_tickTimer->start(500);
}
