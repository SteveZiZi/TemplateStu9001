#include "tempHumShowDialog.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>

#include <mTableWidget>

#include "debug.h"

#define REPORT_POS_L        40
#define REPORT_POS_T        30

#define CAPTION_WIDTH       115
#define CONTENT_WIDTH       80
#define REPORT_ITEM_H       24

#define REPORT_W      (CAPTION_WIDTH+CONTENT_WIDTH*4)
#define REPORT_H      (REPORT_ITEM_H + REPORT_ITEM_H*2+2)


CTempHumShowDlg::CTempHumShowDlg(QWidget *parent, Qt::WFlags flags)
: CBaseShowDialog(parent, flags)
, m_dev(NULL)
{
    m_dev = CTempHumShowData::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    for(int i = 0; i < 3; i++) {
        m_tableWidget[i] = createTableWidget(QString("tableWidget_tempHumShow%1").arg(i), i);
        m_tableWidget[i]->move(x, y);
        y += REPORT_H + 25;
    }
}

CTempHumShowDlg::~CTempHumShowDlg()
{
    for(int i = 0; i < 3; i++) {
        STU_DELETE_PTR(m_tableWidget[i]);
    }
}

void CTempHumShowDlg::updateShowData()
{
    Q_ASSERT(m_dev);
    m_dev->GetBusbarTemp(&m_busbarTemp);
    updateBusbarTemp(m_busbarTemp);

    m_dev->GetContectTemp(&m_contectTemp);
    updateContectTemp(m_contectTemp);

    m_dev->GetCubicleHum(&m_cubicleHum);
    updateCubicleHum(m_cubicleHum);
}

MTableWidget* CTempHumShowDlg::createTableWidget(QString objectName, int item)
{
    static QString captionName[][5] = {
        {
            CTempHumShowDlg::tr("contact measure point"),
            CTempHumShowDlg::tr("phase A(t)"),
            CTempHumShowDlg::tr("phase B(t)"),
            CTempHumShowDlg::tr("phase C(t)"),
            CTempHumShowDlg::tr("warning threshold")
        },
        {
            CTempHumShowDlg::tr("busbar measure point"),
            CTempHumShowDlg::tr("phase A(t)"),
            CTempHumShowDlg::tr("phase B(t)"),
            CTempHumShowDlg::tr("phase C(t)"),
            CTempHumShowDlg::tr("warning threshold")
        },
        {
            CTempHumShowDlg::tr("cubcile temp hum"),
            CTempHumShowDlg::tr("temp(t)"),
            CTempHumShowDlg::tr("hum(t)"),
        }
    };

    static QString contentName[][2] = {
        {
            CTempHumShowDlg::tr("line In"),
            CTempHumShowDlg::tr("line Out")
        },
        {
            CTempHumShowDlg::tr("line In"),
            CTempHumShowDlg::tr("line Out")
        },
        {
            CTempHumShowDlg::tr("channel 1"),
            CTempHumShowDlg::tr("channel 2")
        }
    };

    int row_cnt = 2;
    int column_cnt = 5;
    int content_width = CONTENT_WIDTH;
    if (item == 2) {
        column_cnt = 3;
        content_width = CONTENT_WIDTH*2;
    }

    MTableWidget* tableWidget = new MTableWidget(row_cnt, column_cnt, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setFixedHeight(REPORT_H);
    tableWidget->setFixedWidth(REPORT_W);

    QHeaderView* hHeader = new QHeaderView(Qt::Horizontal, tableWidget);
    hHeader->setObjectName("dataShow_hHeader");
    hHeader->setFixedHeight(REPORT_ITEM_H);
    hHeader->setHighlightSections(false);
    tableWidget->setHorizontalHeader(hHeader);

    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(new MGridStyle(QColor(STU_GREEN_LINE), false, true));
    tableWidget->setShowTopBottomLine(false, true);

    for(int i = 0; i < column_cnt; i++) {
        QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(captionName[item][i]);
        harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(i, harmonicValHeaderItem);
        if (i == 0) {
            tableWidget->setColumnWidth(0, CAPTION_WIDTH);
        }
        else {
            tableWidget->setColumnWidth(i, content_width);
        }
    }

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setTextAlignment(Qt::AlignCenter);
            if (column == 0) {
                newItem->setText(contentName[item][row]);
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::ItemIsSelectable);
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            else {
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            tableWidget->setItem(row, column, newItem);
        }
        tableWidget->setRowHeight(row, REPORT_ITEM_H);
    }

    return tableWidget;
}



void CTempHumShowDlg::updateContectTemp(const TempShowData& data)
{
    for(int row = 0; row < 2; row++) {
        for(int col = 0; col < 3; col++) {
            m_tableWidget[0]->item(row, col+1)->setText(QString("%1").arg(data.fTemp[row][col], 0, 'f', 2));
        }
        m_tableWidget[0]->item(row, 4)->setText(QString("%1").arg(data.fThreshold, 0, 'f', 2));
    }
}

void CTempHumShowDlg::updateBusbarTemp(const TempShowData& data)
{
    for(int row = 0; row < 2; row++) {
        for(int col = 0; col < 3; col++) {
            m_tableWidget[1]->item(row, col+1)->setText(QString("%1").arg(data.fTemp[row][col], 0, 'f', 2));
        }
        m_tableWidget[1]->item(row, 4)->setText(QString("%1").arg(data.fThreshold, 0, 'f', 2));
    }
}

void CTempHumShowDlg::updateCubicleHum(const HumidityData& data)
{
    for(int row = 0; row < 2; row++) {
        m_tableWidget[2]->item(row, 1)->setText(QString("%1").arg(data.fTemp[row], 0, 'f', 2));
        m_tableWidget[2]->item(row, 2)->setText(QString("%1").arg(data.fTumidity[row], 0, 'f', 1));
    }
}
