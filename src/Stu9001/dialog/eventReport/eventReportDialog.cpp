#include "eventReportDialog.h"
#include "common.h"
#include "reportFilter.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QKeyEvent>
#include <QTimer>

#include <mTableWidget>

#include "debug.h"


#define FILTER_POS_L        0
#define FILTER_POS_T        0
#define FILTER_POS_W        STU_P_BODY1_W
#define FILTER_POS_H        48

#define REPORT_POS_L        0
#define REPORT_POS_T       (FILTER_POS_T+FILTER_POS_H)
#define REPORT_W            STU_P_BODY1_W+16
#define REPORT_H           (STU_P_BODY1_H-REPORT_POS_T+2)
#define REPORT_HEADER_H     24
#define REPORT_ROW_H        25
#define REPORT_COLUMN_CNT   5
#define REPORT_ROWS      14

#define ITEM_COLUMN_W       40
#define TIME_COLUMN_W       120
#define CAPTION_COLUMN_W    220
#define TYPE_COLUMN_W       75
#define FAULT_COLUMN_W      94



CEventReportDlg::CEventReportDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_eventNo(0)
{
    m_filter = new CReportFilter(this);
    m_filter->setGeometry(FILTER_POS_L, FILTER_POS_T, FILTER_POS_W, FILTER_POS_H);

    m_tableWidget = createTableWidget("tableWidget_eventReport");

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(detectNewEvent()));
}

CEventReportDlg::~CEventReportDlg()
{
    STU_DELETE_PTR(m_filter);
    STU_DELETE_PTR(m_tableWidget);
}

void CEventReportDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        showNewestEvent();
        this->show();
    }

    if (!m_timer->isActive())
        m_timer->start(500);

    if (style == CAbstractMenuContent::CONTENT_FOCUE)
        m_filter->setFocus();
}

void CEventReportDlg::_HideContent()
{
    if (this->isVisible()) {
        this->hide();
    }
    if (m_timer->isActive())
        m_timer->stop();
}

MTableWidget* CEventReportDlg::createTableWidget(QString objectName)
{
    static QString captionName[] = {
        CEventReportDlg::tr("Item"),
        CEventReportDlg::tr("Event Time"),
        CEventReportDlg::tr("Event Name"),
        CEventReportDlg::tr("Event Type"),
        CEventReportDlg::tr("Fault Record")
    };
    static int columnWidth[] = {
        ITEM_COLUMN_W,
        TIME_COLUMN_W,
        CAPTION_COLUMN_W,
        TYPE_COLUMN_W,
        FAULT_COLUMN_W,
    };

    MTableWidget* tableWidget = new MTableWidget(REPORT_ROWS, REPORT_COLUMN_CNT, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setGeometry(REPORT_POS_L, REPORT_POS_T, REPORT_W, REPORT_H);

    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setAlternatingRowColors(true);

    QHeaderView* hHeader = new QHeaderView(Qt::Horizontal, tableWidget);
    hHeader->setObjectName("eventReport_hHeader");
    hHeader->setFixedHeight(REPORT_HEADER_H);
    hHeader->setHighlightSections(false);
    tableWidget->setHorizontalHeader(hHeader);

    for(int i = 0; i < REPORT_COLUMN_CNT; i++) {
        QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(captionName[i]);
        harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(i, harmonicValHeaderItem);
        tableWidget->setColumnWidth(i, columnWidth[i]);
    }

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            if (column == 2) {
                newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
            }
            else {
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

            tableWidget->setItem(row, column, newItem);
        }
        tableWidget->setRowHeight(row, REPORT_ROW_H);
    }

    return tableWidget;
}

void CEventReportDlg::showNewestEvent()
{
    //m_tableWidget->setCurrentCell(m_tableWidget->rowCount()-1, 0);
}


void CEventReportDlg::addNewEvent(EventReportItem_t& eventItem)
{
    int eventNo = eventItem.item;
    bool bActionEvent = false;
    if (eventItem.style == CEventReportDlg::tr("Action Event")) {
        bActionEvent = true;
    }

    m_tableWidget->insertRow(0);
    for (int column = 0; column < m_tableWidget->columnCount(); ++column) {
        QTableWidgetItem *newItem = new QTableWidgetItem();
        if (column == 2) {
            newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        }
        else {
            newItem->setTextAlignment(Qt::AlignCenter);
        }
        newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        if (bActionEvent) {
            newItem->setTextColor(qRgb(0xff, 0x00, 0x00));
        }

        m_tableWidget->setItem(0, column, newItem);
    }
    m_tableWidget->setRowHeight(0, REPORT_ROW_H);

    if (eventNo < REPORT_ROWS) {
        m_tableWidget->removeRow(m_tableWidget->rowCount()-1);
    }

    m_tableWidget->item(0, 0)->setText(QString("%1").arg(eventNo+1));
    m_tableWidget->item(0, 1)->setText(eventItem.time);
    m_tableWidget->item(0, 2)->setText(eventItem.caption);
    m_tableWidget->item(0, 3)->setText(eventItem.style);
    if (eventItem.hasRecord) {
        m_tableWidget->item(0, 4)->setText("Y");
    }
    else {
        m_tableWidget->item(0, 4)->setText("N");
    }

    showNewestEvent();
}

void CEventReportDlg::keyPressEvent(QKeyEvent *event)
{
    QWidget* currentFocusWidget = focusWidget();

    qDebug() << "CEventReportDlg::keyPressEvent:" << hex << event->key();

    switch(event->key()) 
    {
    case Qt::Key_Escape:
        if (currentFocusWidget == m_tableWidget) {
            m_tableWidget->setCurrentCell(-1, 4);
            moveToNextWidget();
        }
        else {
            event->ignore();
        }
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
        if (currentFocusWidget != m_tableWidget) {
            moveToNextWidget();
        }
        break;
    default:
        event->ignore();
        break;
    }

    if (!event->isAccepted()) {
        CBaseDialog::keyPressEvent(event);
    }
}

void CEventReportDlg::moveToNextWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_tableWidget) {
        m_filter->setFocus();
    }
    else {
        m_tableWidget->setFocus();
        m_tableWidget->setCurrentCell(0, 4);
    }
}

void CEventReportDlg::moveToPreWidget()
{
    moveToNextWidget();
}


void CEventReportDlg::detectNewEvent()
{

}



void CEventReportDlg::recordConv(int eventNo, const EventRecordItem& report, EventReportItem_t& eventItem)
{

    static QString diChangedCaption[] = {
        QString::fromLocal8Bit("分闸位置"),
        QString::fromLocal8Bit("合闸位置"),
        QString::fromLocal8Bit("工作位置"),
        QString::fromLocal8Bit("试验位置"),
        QString::fromLocal8Bit("地刀分位"),
        QString::fromLocal8Bit("地刀合位"),
        QString::fromLocal8Bit("弹簧储能"),
        QString::fromLocal8Bit("远方位置"),
        QString::fromLocal8Bit("对侧分位"),
        QString::fromLocal8Bit("闭锁备自投"),
        QString::fromLocal8Bit("本体轻瓦斯"),
        QString::fromLocal8Bit("本体重瓦斯"),
        QString::fromLocal8Bit("油温过高"),
        QString::fromLocal8Bit("油温超高"),
        QString::fromLocal8Bit("备用"),
        QString::fromLocal8Bit("备用")
    };

    static QString selfCheckCaption[20] = {
        QString::fromLocal8Bit("A/D故障"),
        QString::fromLocal8Bit("定值错误"),
        QString::fromLocal8Bit("时钟错误"),
        QString::fromLocal8Bit("J1出口断线"),
        QString::fromLocal8Bit("J2出口断线"),
        QString::fromLocal8Bit("J3出口断线"),
        QString::fromLocal8Bit("J4出口断线"),
        QString::fromLocal8Bit("J5出口断线"),
        QString::fromLocal8Bit("J6出口断线"),
        QString::fromLocal8Bit("J7出口断线"),
        QString::fromLocal8Bit("J8出口断线"),
        QString::fromLocal8Bit("出口光耦短路"),
        QString::fromLocal8Bit("EEPROM错误"),
        QString::fromLocal8Bit("参数错误"),
        QString::fromLocal8Bit("CRC错误"),
        QString::fromLocal8Bit("装置异常需要检修")
    };

    eventItem.item = eventNo;
    eventItem.time = QString("%1-%2 %3:%4:%5").arg(BCDtoASCII(report.eventTime.month), 2, 10, QChar('0'))
                                              .arg(BCDtoASCII(report.eventTime.day), 2, 10, QChar('0'))
                                              .arg(BCDtoASCII(report.eventTime.hour), 2, 10, QChar('0'))
                                              .arg(BCDtoASCII(report.eventTime.minute), 2, 10, QChar('0'))
                                              .arg(BCDtoASCII(report.eventTime.second), 2, 10, QChar('0'));
    if (report.eventStyle <= ET_DI_CHANGED) {
        eventItem.style = CEventReportDlg::tr("DI Changed Event");
        if (report.eventStyle < sizeof(diChangedCaption)/sizeof(diChangedCaption[0])) 
            eventItem.caption = diChangedCaption[report.eventStyle-1];
        else 
            eventItem.caption = QString::fromLocal8Bit("备用");

        if (report.diStatus) {
            eventItem.caption += "  0->1";
        }
        else {
            eventItem.caption += "  1->0";
        }
    }
    else if (report.eventStyle > ET_ACTION_EVENT) {
        eventItem.style = CEventReportDlg::tr("Self Check Info Event");
        if (report.eventStyle-60 < sizeof(selfCheckCaption)/sizeof(selfCheckCaption[0]))
            eventItem.caption = selfCheckCaption[report.eventStyle-1];
        else 
            eventItem.caption = QString::fromLocal8Bit("备用");
    }
    else {
        eventItem.style = CEventReportDlg::tr("Action Event");
        switch (report.eventStyle) {
        case 25:
            eventItem.caption = QString::fromLocal8Bit("电流速断 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 26:
            eventItem.caption = QString::fromLocal8Bit("限时速断 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 27:
            eventItem.caption = QString::fromLocal8Bit("过电流 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 28:
            eventItem.caption = QString::fromLocal8Bit("低频减载 Fd=%1Hz").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 29:
            eventItem.caption = QString::fromLocal8Bit("二段后加速 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 30:
            eventItem.caption = QString::fromLocal8Bit("重合闸");
            break;
        case 31:
            eventItem.caption = QString::fromLocal8Bit("低频解列 Fd=%1Hz").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 32:
            eventItem.caption = QString::fromLocal8Bit("控制回路断线");
            break;
        case 33:
            eventItem.caption = QString::fromLocal8Bit("三段后加速 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 34:
            eventItem.caption = QString::fromLocal8Bit("PT断线");
            break;
        case 35:
            eventItem.caption = QString::fromLocal8Bit("小电流接地 3I0=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 36:
            eventItem.caption = QString::fromLocal8Bit("低压解列 Ul=%1V").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 37:
            eventItem.caption = QString::fromLocal8Bit("过负荷 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 38:
            eventItem.caption = QString::fromLocal8Bit("负序过流 I2=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 39:
            eventItem.caption = QString::fromLocal8Bit("零序过流 3I0=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 40:
            eventItem.caption = QString::fromLocal8Bit("过电压 Um=%1V").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 41:
            eventItem.caption = QString::fromLocal8Bit("低电压 Ul=%1V").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 42:
            eventItem.caption = QString::fromLocal8Bit("失电压 Ul=%1V").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 43:
            eventItem.caption = QString::fromLocal8Bit("负序过压 U2=%1V").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 44:
            eventItem.caption = QString::fromLocal8Bit("零序过压 3U0=%1V").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 45:
            eventItem.caption = QString::fromLocal8Bit("复合电压过流 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 46:
            eventItem.caption = QString::fromLocal8Bit("备自投合对侧");
            break;
        case 47:
            eventItem.caption = QString::fromLocal8Bit("过热 Ieq=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 48:
            eventItem.caption = QString::fromLocal8Bit("逆功率 P=-%1W").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 49:
            eventItem.caption = QString::fromLocal8Bit("启动时间过长 Im=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 50:
            eventItem.caption = QString::fromLocal8Bit("Ix过流 Ix=%1A").arg(report.fActionValue, 0, 'f', 2, QChar('0'));
            break;
        case 51:
            eventItem.caption = QString::fromLocal8Bit("本体轻瓦斯");
            break;
        case 52:
            eventItem.caption = QString::fromLocal8Bit("本体重瓦斯");
            break;
        case 53:
            eventItem.caption = QString::fromLocal8Bit("油温过高");
            break;
        case 54:
            eventItem.caption = QString::fromLocal8Bit("油温超高");
            break;
        case 55:
            eventItem.caption = QString::fromLocal8Bit("备自投跳本侧");
            break;
        case 56:
            eventItem.caption = QString::fromLocal8Bit("CT断线");
            break;
        default:
            eventItem.caption = QString::fromLocal8Bit("备用");
            break;
        }
    }

    eventItem.hasRecord = report.bRecord;
}
