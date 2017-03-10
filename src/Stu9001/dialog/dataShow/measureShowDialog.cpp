#include "measureShowDialog.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>

#include <mTableWidget>

#include "debug.h"

#define REPORT_POS_L        40
#define REPORT_POS_T        30

#define CAPTION_WIDTH       110
#define CONTENT_WIDTH       110
#define REPORT_ITEM_H       24

#define REPORT_W      (CAPTION_WIDTH+CONTENT_WIDTH*3)
#define REPORT_H      (REPORT_ITEM_H + REPORT_ITEM_H*11+2)


CMeasureShowDlg::CMeasureShowDlg(QWidget *parent, Qt::WFlags flags)
: CBaseShowDialog(parent, flags)
, m_dev(NULL)
{
    m_dev = CMeasureShowData::getInstance();

    m_tableWidget = createTableWidget("tableWidget_measureShow");
    m_tableWidget->move(REPORT_POS_L, REPORT_POS_T);
}

CMeasureShowDlg::~CMeasureShowDlg()
{
    STU_DELETE_PTR(m_tableWidget);
}

void CMeasureShowDlg::updateShowData()
{
    Q_ASSERT(m_dev);
    m_dev->GetMeasureShowData(&m_data);
    updateTableWidget(m_data);
}

MTableWidget* CMeasureShowDlg::createTableWidget(QString objectName)
{
    const QString captionName[] = {
        CMeasureShowDlg::tr("phase A"),
        CMeasureShowDlg::tr("phase B"),
        CMeasureShowDlg::tr("phase C")
    };

    const QString measureName[] = {
        CMeasureShowDlg::tr("U(kV)"),
        CMeasureShowDlg::tr("I(A)"),

        CMeasureShowDlg::tr("P(kW)"),
        CMeasureShowDlg::tr("Q(kVAR)"),
        CMeasureShowDlg::tr("S(kVA)"),

        CMeasureShowDlg::tr("PF"),
        CMeasureShowDlg::tr("F(Hz)"),

        CMeasureShowDlg::tr("PS(kW)"),
        CMeasureShowDlg::tr("QS(kVAR)"),
        CMeasureShowDlg::tr("SS(kVA)"),

        CMeasureShowDlg::tr("PFS")
    };


    MTableWidget* tableWidget = new MTableWidget(11, 4, this);
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

    QTableWidgetItem *harmonicHeaderItem = new QTableWidgetItem(tr("Measure Show"));
    tableWidget->setHorizontalHeaderItem(0, harmonicHeaderItem);
    tableWidget->setColumnWidth(0, CAPTION_WIDTH);
    harmonicHeaderItem->setTextAlignment(Qt::AlignCenter);
    for(int i = 0; i < 3; i++) {
        QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(captionName[i]);
        harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(i+1, harmonicValHeaderItem);
        tableWidget->setColumnWidth(i+1, CONTENT_WIDTH);
    }


    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            if (column == 0) {
                newItem->setText(measureName[row]);
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::ItemIsSelectable);
                newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
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


void CMeasureShowDlg::updateTableWidget(const MeasureShowData& data)
{
    //three phase voltage
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        m_tableWidget->item(0, i+1)->setText(QString("%1").arg(data.phaseVol[i], 0, 'f', 2));

    //three phase current
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        m_tableWidget->item(1, i+1)->setText(QString("%1").arg(data.Current[i], 0, 'f', 2));

    //three phase ActivePower
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        m_tableWidget->item(2, i+1)->setText(QString("%1").arg(data.ActivePower[i], 0, 'f', 2));

    //three phase ReactivePower
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        m_tableWidget->item(3, i+1)->setText(QString("%1").arg(data.ReactivePower[i], 0, 'f', 2));

    //three phase ReactivePower
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        m_tableWidget->item(4, i+1)->setText(QString("%1").arg(data.ApparentPower[i], 0, 'f', 2));

    //three phase ReactivePower
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        m_tableWidget->item(5, i+1)->setText(QString("%1").arg(data.PowerFactor[i], 0, 'f', 2));

    //Frequence
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        if (i == 0)
            m_tableWidget->item(6, i+1)->setText(QString("%1").arg(data.Frequence, 0, 'f', 2));
        else
            m_tableWidget->item(6, i+1)->setText("--");

    //ActivePowerS
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        if (i == 0)
            m_tableWidget->item(7, i+1)->setText(QString("%1").arg(data.ActivePowerS, 0, 'f', 2));
        else
            m_tableWidget->item(7, i+1)->setText("--");

    //ReactivePowerS
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        if (i == 0)
            m_tableWidget->item(8, i+1)->setText(QString("%1").arg(data.ReactivePowerS, 0, 'f', 2));
        else
            m_tableWidget->item(8, i+1)->setText("--");

    //ReactivePowerS
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        if (i == 0)
            m_tableWidget->item(9, i+1)->setText(QString("%1").arg(data.ApparentPowerS, 0, 'f', 2));
        else
            m_tableWidget->item(9, i+1)->setText("--");

    //ReactivePowerS
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        if (i == 0)
            m_tableWidget->item(10, i+1)->setText(QString("%1").arg(data.PowerFactorS, 0, 'f', 2));
        else
            m_tableWidget->item(10, i+1)->setText("--");
}