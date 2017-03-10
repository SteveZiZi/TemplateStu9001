#include "sampleShowDialog_cp9000.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>

#include <mTableWidget>

#include "debug.h"

#define REPORT_POS_L        40
#define REPORT_POS_T        30

#define CAPTION_WIDTH       145
#define CONTENT_WIDTH       145
#define REPORT_ITEM_H       21

#define REPORT_W      (CAPTION_WIDTH+CONTENT_WIDTH*2)
#define REPORT_H      (REPORT_ITEM_H + REPORT_ITEM_H*16+2)


CCP9000SampleShowDlg::CCP9000SampleShowDlg(QWidget *parent, Qt::WFlags flags)
: CBaseShowDialog(parent, flags)
, m_dev(NULL)
{
    m_dev = CSampleShowData_cp9000::getInstance();

    m_tableWidget = createTableWidget("tableWidget_sampleShow");
    m_tableWidget->move(REPORT_POS_L, REPORT_POS_T);
}

CCP9000SampleShowDlg::~CCP9000SampleShowDlg()
{
    STU_DELETE_PTR(m_tableWidget);
}

void CCP9000SampleShowDlg::updateShowData()
{
    Q_ASSERT(m_dev);
    m_dev->GetSampleShowData(&m_data);
    updateTableWidget(m_data);
}

MTableWidget* CCP9000SampleShowDlg::createTableWidget(QString objectName)
{
    static QString captionName[] = {
        CCP9000SampleShowDlg::tr("sample show"),
        CCP9000SampleShowDlg::tr("measure value"),
        CCP9000SampleShowDlg::tr("angle")
    };

    static QString sampleName[] = {
        CCP9000SampleShowDlg::tr("Ua(kV)"),
        CCP9000SampleShowDlg::tr("Ub(kV)"),
        CCP9000SampleShowDlg::tr("Uc(kV)"),

        CCP9000SampleShowDlg::tr("Ia(A)"),
        CCP9000SampleShowDlg::tr("Ib(A)"),
        CCP9000SampleShowDlg::tr("Ic(A)"),

        CCP9000SampleShowDlg::tr("Uab(kV)"),
        CCP9000SampleShowDlg::tr("Ubc(kV)"),
        CCP9000SampleShowDlg::tr("Uca(kV)"),
        CCP9000SampleShowDlg::tr("Ux(kV)"),

        CCP9000SampleShowDlg::tr("I0(A)"),
        CCP9000SampleShowDlg::tr("I1(A)"),
        CCP9000SampleShowDlg::tr("I2(A)"),

        CCP9000SampleShowDlg::tr("U0(V)"),
        CCP9000SampleShowDlg::tr("U1(V)"),
        CCP9000SampleShowDlg::tr("U2(V)")
    };


    MTableWidget* tableWidget = new MTableWidget(16, 3, this);
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

    for(int i = 0; i < 3; i++) {
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
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            if (column == 0) {
                newItem->setText(sampleName[row]);
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


void CCP9000SampleShowDlg::updateTableWidget(const SampleShowData_cp9000& data)
{
    SampleVal* val = (SampleVal*)(&data);

    for(int row = 0; row < m_tableWidget->rowCount(); row++) 
    {
        m_tableWidget->item(row, 1)->setText(QString("%1").arg(val->fMeasure, 0, 'f', 2));
        m_tableWidget->item(row, 2)->setText(QString("%1").arg(val->fAngle, 0, 'f', 2));
        val++;
    }
}