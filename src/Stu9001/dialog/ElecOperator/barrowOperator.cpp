#include "barrowOperator.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>

#include <QKeyEvent>

#include <mPushButton>
#include <mTableWidget>

#include "debug.h"

#define BTN_POS_L           0
#define BTN_POS_T           0
#define BTN_W               55
#define BTN_H               24
#define BTN_OFFSET_X        20
#define BTN_OFFSET_Y        30

#define REPORT_POS_L        0
#define REPORT_POS_T        130
#define CAPTION_WIDTH       85
#define CONTENT_WIDTH       45
#define REPORT_ROW_H        30
#define REPORT_HEADER_H     24
#define REPORT_W           (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_H           (REPORT_HEADER_H + REPORT_ROW_H * 5 + 2)

CbarrowOperator::CbarrowOperator(QWidget *parent)
: QGroupBox(parent)
, m_item(0)
, m_bAllowOper(false)
{
    createBtn();
    m_tableWidget = createTableWidget("cubicleOperator");

    connect(m_pushButton[0], SIGNAL(clicked()), this, SLOT(teleInClick()));
    connect(m_pushButton[1], SIGNAL(clicked()), this, SLOT(teleOutClick()));
    connect(m_pushButton[2], SIGNAL(clicked()), this, SLOT(stopClick()));
    connect(m_pushButton[3], SIGNAL(clicked()), this, SLOT(resetClick()));
}

CbarrowOperator::~CbarrowOperator()
{
    STU_DELETE_PTR(m_tableWidget);
    for(int i = 0; i < 4; i++) {
        STU_DELETE_PTR(m_pushButton[i]);
    }
}

void CbarrowOperator::createBtn()
{
    static QString captionText[] = {
        QObject::tr("tele in"),
        QObject::tr("tele out"),
        QObject::tr("stop"),
        QObject::tr("reset")
    };
    static QString objectName[] = {
        "operate_teleIn",
        "operate_teleOut",
        "operate_stop",
        "operate_reset"
    };

    int y = BTN_POS_T;
    for(int i = 0; i < 2; i++) {
        int x = BTN_POS_L;
        for(int j = 0; j < 2; j++)
        {
            int item = i*2+j;
            m_pushButton[item] = new MPushButton(this);
            m_pushButton[item]->setText(captionText[item]);
            m_pushButton[item]->setGeometry(x, y, BTN_W, BTN_H);
            m_pushButton[item]->setPriorityDrawStatus(MPushButton::FOCUSED_PRIORITY);
            m_pushButton[item]->setObjectName(objectName[item]);
            x += BTN_OFFSET_X + BTN_W;
        }
        y += BTN_OFFSET_Y + BTN_H;
    }
}

MTableWidget* CbarrowOperator::createTableWidget(QString objectName)
{
    static QString captionName[] = {
        QObject::tr("Fault Show"),
        QObject::tr("status")
    };

    static QString faultName[] = {
        QObject::tr("Input Over Voltage"),
        QObject::tr("Input Under Voltage"),
        QObject::tr("Motor Short circuit"),
        QObject::tr("Motor Over Current"),
        QObject::tr("Motor Stalled")
    };

    MTableWidget* tableWidget = new MTableWidget(5, 2, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setGeometry(REPORT_POS_L, REPORT_POS_T, REPORT_W, REPORT_H);

    QHeaderView* hHeader = new QHeaderView(Qt::Horizontal, tableWidget);
    hHeader->setObjectName("cubicleOpear_hHeader");
    hHeader->setFixedHeight(REPORT_HEADER_H);
    hHeader->setHighlightSections(false);
    tableWidget->setHorizontalHeader(hHeader);

    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(new MGridStyle(QColor(STU_GREEN_LINE), false, true));
    tableWidget->setShowTopBottomLine(false, true);

    for(int i = 0; i < 2; i++) {
        QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(captionName[i]);
        harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(i, harmonicValHeaderItem);
        if (i == 0) 
            tableWidget->setColumnWidth(0, CAPTION_WIDTH);
        else 
            tableWidget->setColumnWidth(i, CONTENT_WIDTH);
    }

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            if (column == 0) {
                newItem->setText(faultName[row]);
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::ItemIsSelectable);
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            else {
                newItem->setCheckState(Qt::Unchecked);
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            tableWidget->setItem(row, column, newItem);
        }
        tableWidget->setRowHeight(row, REPORT_ROW_H);
    }

    return tableWidget;
}

void CbarrowOperator::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    qDebug() << "CbarrowOperator::keyPressEvent:" << hex << event->key();

    switch(key) 
    {
    case Qt::Key_Left:
        if (m_item == 0) 
            m_item = 3;
        else 
            m_item--;
        m_pushButton[m_item]->setFocus();
        break;
    case Qt::Key_Right:
        if (m_item == 3) 
            m_item = 0;
        else 
            m_item++;
        m_pushButton[m_item]->setFocus();
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
        if (m_item < 2) 
            m_item += 2;
        else 
            m_item -= 2;
        m_pushButton[m_item]->setFocus();
        break;
    default:
        event->ignore();
        break;
    }

    if (!event->isAccepted()) {
        QGroupBox::keyPressEvent(event);
    }
}

void CbarrowOperator::focusInEvent(QFocusEvent *event)
{
    m_item = 0;
    m_pushButton[m_item]->setFocus();
}


void CbarrowOperator::teleInClick(void)
{
    emit tele_in();
}

void CbarrowOperator::teleOutClick(void)
{
    emit tele_out();
}

void CbarrowOperator::stopClick(void)
{
    emit stop();
}

void CbarrowOperator::resetClick(void)
{
    emit reset();
}


void CbarrowOperator::allowOperate(bool allow)
{
    m_bAllowOper = allow;
    //emit repaint();
    qDebug() << "CbarrowOperator::allowOperate no object";
}