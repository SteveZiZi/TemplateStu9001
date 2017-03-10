#include "machineCharactristicParamDialog.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QtGui/QPainter>
#include <QtGui/QKeyEvent>

#include <mTableWidget>
#include <dirKeyInputForData>
#include <MLineEditDelegate>

#include "debug.h"

#define REPORT_POS_L        60
#define REPORT_POS_T        30

#define CAPTION_WIDTH       180
#define CONTENT_WIDTH       100
#define UNIT_WIDTH          60

#define REPORT_ITEM_H       25

#define REPORT_ROWS         13
#define REPORT_COLUMNS      4
#define REPORT_W      (CAPTION_WIDTH + CONTENT_WIDTH*2 + UNIT_WIDTH)
#define REPORT_H      (REPORT_ITEM_H + REPORT_ITEM_H*REPORT_ROWS+2)



CMachineCharactristicParamDlg::CMachineCharactristicParamDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    m_dev = CMachineCharacterParam::getInstance();

    m_dirKeyInputForData = new CDirKeyInputForData();
    m_dirKeyInputForData->addMaskChar('.');

    m_tableWidget = createTableWidget("MachineCharacterParam");
    m_tableWidget->move(REPORT_POS_L, REPORT_POS_T);
}

CMachineCharactristicParamDlg::~CMachineCharactristicParamDlg()
{
    if (m_tableWidget) {
        delete dynamic_cast<MLineEditDelegate*>(m_tableWidget->itemDelegate());
    }

    STU_DELETE_PTR(m_dirKeyInputForData);
}


void CMachineCharactristicParamDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        m_bModify = false;
        m_dev->machineCharacterSettings(&m_settings);
        updateSettings();
        this->show();
        connect(m_tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidgetChanged(QTableWidgetItem *)));
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        m_tableWidget->setFocus();
        m_tableWidget->setCurrentCell(0, 1);
    }
}

void CMachineCharactristicParamDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CMachineCharactristicParamDlg::_LeaveContent data Changed";
        m_dev->setMachineCharacterSettings(m_settings);
        m_bModify = false;
    }

    m_tableWidget->setCurrentCell(-1, -1);

    CBaseDialog::_LeaveContent();
}

void CMachineCharactristicParamDlg::_HideContent()
{
    if (!this->isHidden()) {
        disconnect(m_tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidgetChanged(QTableWidgetItem *)));
    }

    CBaseDialog::_HideContent();
}

MTableWidget* CMachineCharactristicParamDlg::createTableWidget(QString objectName)
{
    const QString captionName[REPORT_COLUMNS] = {
        CMachineCharactristicParamDlg::tr("Parameter Name"),
        CMachineCharactristicParamDlg::tr("Calibration Value"),
        CMachineCharactristicParamDlg::tr("Offset Range"),
        CMachineCharactristicParamDlg::tr("Unit")
    };

    QString parameterName[REPORT_ROWS] = {
        CMachineCharactristicParamDlg::tr("contact distance"),
        CMachineCharactristicParamDlg::tr("separate brake route"),
        CMachineCharactristicParamDlg::tr("separate brake time"),
        CMachineCharactristicParamDlg::tr("separate brake speed avg"),
        CMachineCharactristicParamDlg::tr("spearate brake bounce AMP"),
        CMachineCharactristicParamDlg::tr("separate brake async cycle time"),

        CMachineCharactristicParamDlg::tr("contact over route"),
        CMachineCharactristicParamDlg::tr("close brake route"),
        CMachineCharactristicParamDlg::tr("close brake time"),
        CMachineCharactristicParamDlg::tr("close brake speed avg"),
        CMachineCharactristicParamDlg::tr("close brake bounce time"),
        CMachineCharactristicParamDlg::tr("close brake async cycle time"),

        CMachineCharactristicParamDlg::tr("store time")
    };
    char* unitName[REPORT_ROWS] = {
        "mm", "mm", "ms", "m/s", "mm", "ms",
        "mm", "mm", "ms", "m/s", "ms", "ms",
        "s"
    };

    MTableWidget* tableWidget = new MTableWidget(REPORT_ROWS, 4, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setFixedHeight(REPORT_H);
    tableWidget->setFixedWidth(REPORT_W);

    QHeaderView* hHeader = new QHeaderView(Qt::Horizontal, tableWidget);
    hHeader->setObjectName("machineCharacter_hHeader");
    hHeader->setFixedHeight(REPORT_ITEM_H);
    hHeader->setHighlightSections(false);
    tableWidget->setHorizontalHeader(hHeader);

    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(new MGridStyle(QColor(STU_GREEN_LINE), false, true));
    tableWidget->setShowTopBottomLine(false, true);
    tableWidget->setAlternatingRowColors(true);

    MLineEditDelegate* delegate = new MLineEditDelegate(tableWidget);
    delegate->setDirKeyInput(m_dirKeyInputForData);
    tableWidget->setItemDelegate(delegate);

    for(int i = 0; i < REPORT_COLUMNS; i++) {
        QTableWidgetItem *headerItem = new QTableWidgetItem(captionName[i]);
        headerItem->setTextAlignment(Qt::AlignCenter);
        if(i==0) {
            tableWidget->setColumnWidth(i, CAPTION_WIDTH);
        }
        else if (i == REPORT_COLUMNS-1) {
            tableWidget->setColumnWidth(i, UNIT_WIDTH);
        }
        else {
            tableWidget->setColumnWidth(i, CONTENT_WIDTH);
        }
        tableWidget->setHorizontalHeaderItem(i, headerItem);
    }

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            if (column == 0) {
                newItem->setText(parameterName[row]);
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::NoItemFlags);
                newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
            }
            else if (column == REPORT_COLUMNS-1) {
                newItem->setText(unitName[row]);
                newItem->setFlags(Qt::NoItemFlags);
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            else {
                newItem->setFlags(newItem->flags()&(~Qt::ItemIsUserCheckable));
                newItem->setTextAlignment(Qt::AlignCenter);
            }
            tableWidget->setItem(row, column, newItem);
        }
        tableWidget->setRowHeight(row, REPORT_ITEM_H);
    }

    return tableWidget;
}

void CMachineCharactristicParamDlg::updateSettings(void)
{
    MC_Setting* setting = (MC_Setting*)(&m_settings);
    QTableWidgetItem* item = NULL;
    for (int row = 0; row < REPORT_ROWS; ++row) {
        item = m_tableWidget->item(row, 1);
        item->setText(QString("%1").arg(setting[row].fCalibrationVal, 0, 'f', 2));
        item = m_tableWidget->item(row, 2);
        item->setText(QString("%1").arg(setting[row].fOffsetRange, 0, 'f', 2));
    }
}

void CMachineCharactristicParamDlg::tableWidgetChanged(QTableWidgetItem* item)
{
    int row = item->row();
    Q_ASSERT(row < REPORT_ROWS);
    int colunm = item->column();
    Q_ASSERT(colunm == 1 || colunm == 2);

    float* fSetting = (float*)((MC_Setting*)(&m_settings)+row) + colunm-1;
    bool ok = false;
    float val = item->text().toDouble(&ok);
    if (ok) {
        if (qAbs(val-*fSetting) >= 0.0001) {
            *fSetting = val;
            m_bModify = true;
        }
    }
    else {
        MTableWidgetItem *mItem = dynamic_cast<MTableWidgetItem*>(item);
        mItem->setText(QString("%1").arg(*fSetting, 0, 'f', 2));
    }
}