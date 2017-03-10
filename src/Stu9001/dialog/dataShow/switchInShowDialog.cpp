#include "switchInShowDialog.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>

#include <mTableWidget>

#include <MCheckBox>

#include "debug.h"

#define REPORT_POS_L        40
#define REPORT_POS_T        30

#define CAPTION_WIDTH       140
#define CONTENT_WIDTH       80
#define REPORT_ITEM_H       22

#define REPORT_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_H      (REPORT_ITEM_H + REPORT_ITEM_H*15+2)


CSwitchInShowDlg::CSwitchInShowDlg(QWidget *parent, Qt::WFlags flags)
: CBaseShowDialog(parent, flags)
, m_dev(NULL)
{
    m_dev = CSwitchInputShowData::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    m_tableWidget1 = createTableWidget("tableWidget_switchInShow1", 0);
    m_tableWidget1->move(x, y);

    x += REPORT_W+20;
    m_tableWidget2 = createTableWidget("tableWidget_switchInShow2", 1);
    m_tableWidget2->move(x, y);
}

CSwitchInShowDlg::~CSwitchInShowDlg()
{
    STU_DELETE_PTR(m_tableWidget1);
    STU_DELETE_PTR(m_tableWidget2);
}

void CSwitchInShowDlg::updateShowData()
{
    Q_ASSERT(m_dev);
    m_dev->GetSwitchInputShowData(&m_data);
    updateTableWidget(m_data);
}

MTableWidget* CSwitchInShowDlg::createTableWidget(QString objectName, int item)
{
    static QString captionName[] = {
        CSwitchInShowDlg::tr("switch in show"),
        CSwitchInShowDlg::tr("status")
    };

    static QString sampleName[][15] = {
        {
            CSwitchInShowDlg::tr("automatic bus transfer locked"), // 闭锁备自投
            CSwitchInShowDlg::tr("service position"),
            CSwitchInShowDlg::tr("testing position"),
            CSwitchInShowDlg::tr("open position"),
            CSwitchInShowDlg::tr("closed position"),
            CSwitchInShowDlg::tr("earthing knife on"),
            CSwitchInShowDlg::tr("earthing knife off"),
            CSwitchInShowDlg::tr("sping energy"),
            CSwitchInShowDlg::tr("remote tele out"),
            CSwitchInShowDlg::tr("remote tele in"),
            CSwitchInShowDlg::tr("contralateral opened"),   //对侧分位
            CSwitchInShowDlg::tr("remote position"),
            CSwitchInShowDlg::tr("fault reset"),
            CSwitchInShowDlg::tr("front door status"),
            CSwitchInShowDlg::tr("back door status")
        },
        {
            CSwitchInShowDlg::tr("electriferous display A"),
            CSwitchInShowDlg::tr("electriferous display B"),
            CSwitchInShowDlg::tr("electriferous display C"),
            CSwitchInShowDlg::tr("light gas"),
            CSwitchInShowDlg::tr("heavy gas"),
            CSwitchInShowDlg::tr("oil over temp"),
            CSwitchInShowDlg::tr("oil highest temp"),
            CSwitchInShowDlg::tr("switch in 1"),
            CSwitchInShowDlg::tr("switch in 2"),
            CSwitchInShowDlg::tr("switch in 3"),
            CSwitchInShowDlg::tr("switch in 4"),
            CSwitchInShowDlg::tr("switch in 5"),
            CSwitchInShowDlg::tr("switch in 6"),
            CSwitchInShowDlg::tr("switch in 7"),
            CSwitchInShowDlg::tr("switch in 8"),
        }
    };


    MTableWidget* tableWidget = new MTableWidget(15, 2, this);
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

    for(int i = 0; i < 2; i++) {
        QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(captionName[i]);
        harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(i, harmonicValHeaderItem);
        if (i == 0) {
            tableWidget->setColumnWidth(0, CAPTION_WIDTH);
        }
        else {
            tableWidget->setColumnWidth(i, CONTENT_WIDTH);
        }
    }

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        tableWidget->setRowHeight(row, REPORT_ITEM_H);

        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setTextAlignment(Qt::AlignCenter);
        newItem->setText(sampleName[item][row]);
        newItem->setTextColor(STU_GREEN_LINE);
        newItem->setFlags(Qt::ItemIsSelectable);
        newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        tableWidget->setItem(row, 0, newItem);

        tableWidget->setItem(row, 1, new QTableWidgetItem());
    }

    return tableWidget;
}


void CSwitchInShowDlg::updateTableWidget(const SwitchInputShowData& data)
{
    bool* status = (bool*)(&data);

    for (int row = 0; row < m_tableWidget1->rowCount(); ++row) {
        m_tableWidget1->item(row, 1)->setCheckState((*status) ? Qt::Checked : Qt::Unchecked);
        status++;
    }

    for (int row = 0; row < m_tableWidget2->rowCount(); ++row) {
        m_tableWidget2->item(row, 1)->setCheckState((*status) ? Qt::Checked : Qt::Unchecked);
        status++;
    }
}
