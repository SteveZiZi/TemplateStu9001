#include "constValueModifyDialog_cp9000.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QKeyEvent>

#include <mTableWidget>
#include <dirKeyInputForData>
#include <MLineEditDelegate>

#include "debug.h"


#define REPORT_POS_L        20
#define REPORT_POS_T        10

#define CAPTION_WIDTH       150
#define CONTENT_WIDTH       100
#define REPORT_ITEM_H       20

#define REPORT_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_H      (REPORT_ITEM_H*20+2)


static int prec1[18] = 
{
    2,2,2, 
    3,3,3, 
    2,2,2, 
    3,3,3, 
    2,
    3,
    2,
    3,
    2,
    2
};
static quint8 prec2[20] = {
    3,
    2,
    2,
    2,
    0,
    0,
    2,
    3,
    2,
    3,
    2,
    2,
    2,
    3,
    2,
    2,
    3,
    3,
    3,
    2
};


CConstValueModifyDlg::CConstValueModifyDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_currentRow(0)
, m_bModify(false)
, m_dev(NULL)
{
    m_dev = CConstValuesSetting::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    m_dirKeyInputForData = new CDirKeyInputForData();
    m_dirKeyInputForData->addMaskChar('.');

    m_dirKeyInputForHex = new CDirKeyInputForData(4);
    m_dirKeyInputForHex->setBase(16);

    m_tableWidget1 = createTableWidget("tableWidget_constValueModify1", 0);
    m_tableWidget1->move(x, y);

    x += REPORT_W+20;
    m_tableWidget2 = createTableWidget("tableWidget_constValueModify2", 1);
    m_tableWidget2->move(x, y);

    connect(m_tableWidget1, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidget1Changed(QTableWidgetItem *)));
    connect(m_tableWidget2, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidget2Changed(QTableWidgetItem *)));
}

CConstValueModifyDlg::~CConstValueModifyDlg()
{
    if (m_tableWidget1) {
        delete dynamic_cast<MLineEditDelegate*>(m_tableWidget1->itemDelegate());
        delete dynamic_cast<MLineEditDelegate*>(m_tableWidget1->itemDelegateForRow(0));
        delete dynamic_cast<MLineEditDelegate*>(m_tableWidget1->itemDelegateForRow(1));
    }
    if (m_tableWidget2) {
        delete dynamic_cast<MLineEditDelegate*>(m_tableWidget2->itemDelegate());
    }
    STU_DELETE_PTR(m_tableWidget1);
    STU_DELETE_PTR(m_tableWidget2);

    STU_DELETE_PTR(m_dirKeyInputForData);
    STU_DELETE_PTR(m_dirKeyInputForHex);
}

void CConstValueModifyDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        this->show();
        m_bModify = false;
        m_dev->constValSettings(&m_settings);
        updateSettings();
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        m_currentRow = 0;
        m_tableWidget1->setFocus();
        m_tableWidget1->setCurrentCell(m_currentRow, 1);
    }
}

void CConstValueModifyDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CConstValueModifyDlg::_LeaveContent data Changed";
        m_dev->setConstValSettings(m_settings);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

MTableWidget* CConstValueModifyDlg::createTableWidget(QString objectName, int item)
{
    static QString constValueName[][20] = {
        {
            CConstValueModifyDlg::tr("control word 1"),
            CConstValueModifyDlg::tr("control word 2"),
            CConstValueModifyDlg::tr("primary section cur const value"),
            CConstValueModifyDlg::tr("second section cur const value"),
            CConstValueModifyDlg::tr("three section cur const value"),
            CConstValueModifyDlg::tr("primary section cur const time"),
            CConstValueModifyDlg::tr("second section cur const time"),
            CConstValueModifyDlg::tr("three section cur const time"),
            CConstValueModifyDlg::tr("primary section zero sequence cur const value"),
            CConstValueModifyDlg::tr("second section zero sequence cur const value"),
            CConstValueModifyDlg::tr("three section zero sequence cur const value"),
            CConstValueModifyDlg::tr("primary section zero sequence cur const time"),
            CConstValueModifyDlg::tr("second section zero sequence cur const time"),
            CConstValueModifyDlg::tr("three section zero sequence cur const time"),
            CConstValueModifyDlg::tr("cur ACC const value"),
            CConstValueModifyDlg::tr("cur ACC time"),
            CConstValueModifyDlg::tr("zero sequence cur ACC const value"),
            CConstValueModifyDlg::tr("zero sequence cur ACC time"),
            CConstValueModifyDlg::tr("compound press lock vol"),
            CConstValueModifyDlg::tr("cur Anti Time REF"),
        },
        {
            CConstValueModifyDlg::tr("cur anti time time"),
            CConstValueModifyDlg::tr("zero sequence cur Anti Time REF"),
            CConstValueModifyDlg::tr("zero sequence cur anti time time"),
            CConstValueModifyDlg::tr("overload current"),
            CConstValueModifyDlg::tr("overload warning time"),
            CConstValueModifyDlg::tr("overload trip time"),
            CConstValueModifyDlg::tr("recloser sync check const value"),
            CConstValueModifyDlg::tr("recloser time"),
            CConstValueModifyDlg::tr("low cycle component freq"),
            CConstValueModifyDlg::tr("low cycle component time"),
            CConstValueModifyDlg::tr("low cycle lock voltage"),
            CConstValueModifyDlg::tr("low cycle lock slip"),
            CConstValueModifyDlg::tr("low vol component vol"),
            CConstValueModifyDlg::tr("low vol component time"),
            CConstValueModifyDlg::tr("low vol lock slip"),
            CConstValueModifyDlg::tr("freq diff lock const val"),
            CConstValueModifyDlg::tr("quasi same vol lock"),
            CConstValueModifyDlg::tr("quasi sync ACC lock"),
            CConstValueModifyDlg::tr("closing phase time"),
            CConstValueModifyDlg::tr("phase angle const val")
        }
    };

    const char* unitName[][20] = {
        {
            "", "", 
            "A", "A", "A", "S", "S", "S",
            "A", "A", "A", "S", "S", "S",
            "A", "S", "A", "S", "V", "A"
        },
        {
            "S", "A", "S", "A", "S", "S",
            "°", "S", "Hz", "S", "V", "Hz/S",
            "V", "S", "V/S", "V", "Hz", "Hz/S",
            "S", "°"
        }
    };


    MTableWidget* tableWidget = new MTableWidget(20, 2, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setFixedHeight(REPORT_H);
    tableWidget->setFixedWidth(REPORT_W);

    tableWidget->horizontalHeader()->hide();
    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(new MGridStyle(QColor(STU_GREEN_LINE), false, true));
    tableWidget->setShowTopBottomLine(true, true);

    MLineEditDelegate* delegate = new MLineEditDelegate(tableWidget);
    delegate->setDirKeyInput(m_dirKeyInputForData);
    tableWidget->setItemDelegate(delegate);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    if (item == 0) {
        MLineEditDelegate* delegate = new MLineEditDelegate(tableWidget);
        delegate->setDirKeyInput(m_dirKeyInputForHex);
        tableWidget->setItemDelegateForRow(0, delegate);
        tableWidget->setItemDelegateForRow(1, delegate);
    }


    tableWidget->setColumnWidth(0, CAPTION_WIDTH);
    tableWidget->setColumnWidth(1, CONTENT_WIDTH);

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            if (column == 0) {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
                newItem->setText(constValueName[item][row]);
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::ItemIsSelectable);
                tableWidget->setItem(row, column, newItem);
            }
            else {
                MTableWidgetItem *newItem = new MTableWidgetItem(QString::fromLocal8Bit(unitName[item][row]));
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(newItem->flags()&(~Qt::ItemIsUserCheckable));
                tableWidget->setItem(row, column, newItem);
            }
        }
        tableWidget->setRowHeight(row, REPORT_ITEM_H);
    }

    return tableWidget;
}

//更新设置到界面
void CConstValueModifyDlg::updateSettings()
{
    float* fVal = &m_settings.fCurConstValue[0];
    const SettingsLimit* limit = &m_dev->constValLimit()->tCurConstValue[0];
    MTableWidgetItem *item = NULL;
    for (int row = 0; row < m_tableWidget1->rowCount(); ++row) {
        item = dynamic_cast<MTableWidgetItem*>(m_tableWidget1->item(row, 1));
        Q_ASSERT(item);
        if (row < 2) {
            item->setText(QString("%1").arg(m_settings.nCtrlWord[row], 4, 16, QChar('0')));
        }
        else {
            if (*fVal < limit->min) {
                *fVal = limit->min;
                m_bModify = true;
            }
            else if (*fVal > limit->max) {
                *fVal = limit->max;
                m_bModify = true;
            }
            item->setText(QString("%1").arg(*fVal, 0, 'f', prec1[row-2]));
            fVal++;
            limit++;
        }
    }

    for (int row = 0; row < m_tableWidget2->rowCount(); ++row) {
        item = dynamic_cast<MTableWidgetItem*>(m_tableWidget2->item(row, 1));
        Q_ASSERT(item);
        if (*fVal < limit->min) {
            *fVal = limit->min;
            m_bModify = true;
        }
        else if (*fVal > limit->max) {
            *fVal = limit->max;
            m_bModify = true;
        }
        item->setText(QString("%1").arg(*fVal, 0, 'f', prec2[row]));
        fVal++;
        limit++;
    }
}


void CConstValueModifyDlg::tableWidget1Changed(QTableWidgetItem *item)
{
    qDebug() << "CConstValueModifyDlg::tableWidget1Changed" 
             << " row:" << item->row() 
             << " column:" << item->column() 
             << "text" << item->text();

    int index = item->row();
    if (index >= 2) {
        float* settings = &m_settings.fCurConstValue[0] + (index-2);
        bool ok = false;
        float val = item->text().toDouble(&ok);
        if (ok) {
            if (qAbs(val-*settings) >= 0.0001) {
                const SettingsLimit* limit = &m_dev->constValLimit()->tCurConstValue[0] + (index-2);
                if (val > limit->max || val < limit->min) {
                    MTableWidgetItem *mItem = dynamic_cast<MTableWidgetItem*>(item);
                    mItem->setText(QString("%1").arg(*settings, 0, 'f', prec1[index-2]));
                }
                else {
                    *settings = val;
                    m_bModify = true;
                }
            }
        }
        else {
            MTableWidgetItem *mItem = dynamic_cast<MTableWidgetItem*>(item);
            mItem->setText(QString("%1").arg(*settings, 0, 'f', prec1[index-2]));
            return ;
        }
    }
    else if (index >= 0) {
        quint16 val = item->text().toUInt();
        if (val != m_settings.nCtrlWord[index]) {
            m_settings.nCtrlWord[index] = val;
            m_bModify = true;
        }
    }
}

void CConstValueModifyDlg::tableWidget2Changed(QTableWidgetItem *item)
{
    qDebug() << "CConstValueModifyDlg::tableWidget2Changed" 
             << " row:" << item->row() 
             << " column:" << item->column() 
             << "text" << item->text();

    int index = item->row();
    float* settings = &m_settings.fCurAntiTime + index;
    bool ok = false;
    float val = item->text().toDouble(&ok);
    if (ok) {
        if (qAbs(val-*settings) >= 0.0001) {
            const SettingsLimit* limit = &m_dev->constValLimit()->tCurAntiTime + index;
            if (val > limit->max || val < limit->min) {
                MTableWidgetItem *mItem = dynamic_cast<MTableWidgetItem*>(item);
                mItem->setText(QString("%1").arg(*settings, 0, 'f', prec2[index]));
            }
            else {
                *settings = val;
                m_bModify = true;
            }
        }
    }
    else {
        MTableWidgetItem *mItem = dynamic_cast<MTableWidgetItem*>(item);
        mItem->setText(QString("%1").arg(*settings, 0, 'f', prec2[index]));
        return ;
    }
}

void CConstValueModifyDlg::moveToNextWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_tableWidget1) {
        m_tableWidget2->setFocus(Qt::TabFocusReason);
        m_tableWidget2->setCurrentCell(m_currentRow, 1);
        m_tableWidget1->setCurrentCell(-1,-1);
    }
    else {
        m_tableWidget1->setFocus(Qt::TabFocusReason);
        m_tableWidget1->setCurrentCell(m_currentRow, 1);
        m_tableWidget2->setCurrentCell(-1,-1);
    }
}

void CConstValueModifyDlg::moveToPreWidget() 
{
    moveToNextWidget();
}


void CConstValueModifyDlg::keyPressEvent(QKeyEvent *event)
{
    MTableWidget* focusWidget = dynamic_cast<MTableWidget*>(this->focusWidget());
    qDebug() << "CConstValueModifyDlg::keyPressEvent:" << hex << event->key();

    switch(event->key()) 
    {
    case Qt::Key_Escape:
        focusWidget->setCurrentCell(-1,-1);
        event->ignore();
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
        m_currentRow = focusWidget->currentRow();
        moveToNextWidget();
        event->ignore();
        break;
    case Qt::Key_Up:
        m_currentRow = focusWidget->rowCount()-1;
        event->ignore();
        break;
    case Qt::Key_Down:
        m_currentRow = 0;
        event->ignore();
        break;
    default:
        event->ignore();
        break;
    }

    if (!event->isAccepted()) {
        CBaseDialog::keyPressEvent(event);
    }
}
