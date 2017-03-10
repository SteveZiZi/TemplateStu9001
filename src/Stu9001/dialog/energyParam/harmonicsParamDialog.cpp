#include "harmonicsParamDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QKeyEvent>

#include <mTableWidget>
#include <mComboBox>
#include <dirKeyInputForData>
#include <MLineEditDelegate>

#include "debug.h"

#define REPORT_POS_L        140
#define REPORT_POS_T        12

#define CAPTION_WIDTH       80
#define CONTENT_WIDTH       80

#define REPORT_ITEM_W      (CAPTION_WIDTH+CONTENT_WIDTH+20)
#define REPORT_ITEM_H       23

#define REPORT_ROWS         (15)



CHarnoicsParamDlg::CHarnoicsParamDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_currentRow(0)
, m_bModify(false)
, m_dev(NULL)
{
    m_dev = CHarmonicParam::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    m_dirKeyInputForData = new CDirKeyInputForData();
    m_dirKeyInputForData->addMaskChar('.');

    label_harmonics = new QLabel(this);
    label_harmonics->setObjectName("label_harmonics");
    label_harmonics->setText(tr("harmonics:"));
    label_harmonics->move(x, y);

    comboBox_harnoics = new MComboBox(this);
    comboBox_harnoics->setObjectName("comboBox_volGrade");
    comboBox_harnoics->move(x+CAPTION_WIDTH, y);
    comboBox_harnoics->addItem(tr("Current"), 0);
    comboBox_harnoics->addItem(tr("Voltage"), 1);
    comboBox_harnoics->setFixedWidth(CONTENT_WIDTH);
    comboBox_harnoics->setFixedHeight(comboBox_harnoics->size().height()-10);

    y += REPORT_ITEM_H+5;
    harnoicsTable1 = createTableWidget("harnoicsTable1", 0);
    harnoicsTable1->move(x, y);

    x += REPORT_ITEM_W;
    harnoicsTable2 = createTableWidget("harnoicsTable2", 1);
    harnoicsTable2->move(x, y);
}

CHarnoicsParamDlg::~CHarnoicsParamDlg()
{
    if (harnoicsTable1) {
        delete dynamic_cast<MLineEditDelegate*>(harnoicsTable1->itemDelegate());
    }
    if (harnoicsTable2) {
        delete dynamic_cast<MLineEditDelegate*>(harnoicsTable2->itemDelegate());
    }

    STU_DELETE_PTR(m_dirKeyInputForData);
}


void CHarnoicsParamDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        m_bModify = false;
        m_dev->harmonicParam(&m_param);
        int type = comboBox_harnoics->currentIndex();
        Q_ASSERT(type >= 0 && type < 2);
        changeTableType(type);
        this->show();

        connect(comboBox_harnoics, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTableType(int)));
        connect(harnoicsTable1, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidget1Changed(QTableWidgetItem *)));
        connect(harnoicsTable2, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidget2Changed(QTableWidgetItem *)));
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE)
        comboBox_harnoics->setFocus();
}

void CHarnoicsParamDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CHarnoicsParamDlg::_LeaveContent data Changed";
        m_dev->setHarmonicParam(m_param);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CHarnoicsParamDlg::_HideContent()
{
    if (!this->isHidden()) {
        disconnect(comboBox_harnoics, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTableType(int)));
        disconnect(harnoicsTable1, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidget1Changed(QTableWidgetItem *)));
        disconnect(harnoicsTable2, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(tableWidget2Changed(QTableWidgetItem *)));
    }

    CBaseDialog::_HideContent();
}


MTableWidget* CHarnoicsParamDlg::createTableWidget(QString objectName, int item)
{
    MTableWidget* tableWidget = new MTableWidget(REPORT_ROWS, 2, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setFixedHeight(16*REPORT_ITEM_H+1);
    tableWidget->setFixedWidth(CAPTION_WIDTH+CONTENT_WIDTH);

    tableWidget->horizontalHeader()->setFixedHeight(REPORT_ITEM_H);
    tableWidget->horizontalHeader()->setHighlightSections(false);
    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(new MGridStyle(QColor(STU_GREEN_LINE), false, true));
    tableWidget->setShowTopBottomLine(false, true);

    MLineEditDelegate* delegate = new MLineEditDelegate(tableWidget);
    delegate->setDirKeyInput(m_dirKeyInputForData);
    tableWidget->setItemDelegate(delegate);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QTableWidgetItem *harmonicHeaderItem = new QTableWidgetItem(tr("Harmonic Cur"));
    tableWidget->setHorizontalHeaderItem(0, harmonicHeaderItem);
    tableWidget->setColumnWidth(0, CAPTION_WIDTH);
    harmonicHeaderItem->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(tr("Allow Value"));
    harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
    tableWidget->setHorizontalHeaderItem(1, harmonicValHeaderItem);
    tableWidget->setColumnWidth(1, CONTENT_WIDTH);

    for (int row = 0; row < REPORT_ROWS; ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setTextAlignment(Qt::AlignCenter);
            if (column == 0) {
                newItem->setText(QString("%1%2").arg(row+2+item*REPORT_ROWS).arg(tr("item")));
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::ItemIsSelectable);
            }
            else {
                newItem->setFlags(newItem->flags()&(~Qt::ItemIsUserCheckable));
            }
            tableWidget->setItem(row, column, newItem);
        }
        tableWidget->setRowHeight(row, REPORT_ITEM_H);
    }

    return tableWidget;
}


void CHarnoicsParamDlg::changeTableType(int type)
{
    Q_ASSERT(type >= 0 && type < 2);

    changeTableCaption(type);
    updateSettings(type);
}

void CHarnoicsParamDlg::changeTableCaption(int type)
{
    Q_ASSERT(type >= 0 && type < 2);

    if (type == 0) {
        harnoicsTable1->horizontalHeaderItem(0)->setText(tr("Harmonic Cur"));
        harnoicsTable2->horizontalHeaderItem(0)->setText(tr("Harmonic Cur"));
    }
    else {
        harnoicsTable1->horizontalHeaderItem(0)->setText(tr("Harmonic Vol"));
        harnoicsTable2->horizontalHeaderItem(0)->setText(tr("Harmonic Vol"));
    }
}

//更新设置到界面
void CHarnoicsParamDlg::updateSettings(int type)
{
    Q_ASSERT(type >= 0 && type < 2);
    float* harmonicVal = NULL;
    if (type == 0) 
        harmonicVal = m_param.cur;
    else 
        harmonicVal = m_param.vol;

    QTableWidgetItem* item = NULL;
    for (int row = 0; row < REPORT_ROWS; ++row) {
        item = harnoicsTable1->item(row, 1);
        item->setText(QString("%1").arg(harmonicVal[row+2], 0, 'f', 2));

        item = harnoicsTable2->item(row, 1);
        item->setText(QString("%1").arg(harmonicVal[row+2+REPORT_ROWS], 0, 'f', 2));
    }
}

void CHarnoicsParamDlg::tableWidgetChanged(int order, QTableWidgetItem* item)
{
    qDebug() << "CHarnoicsParamDlg::tableWidgetChanged" 
             << "order:" << order
             << " row:" << item->row() 
             << " column:" << item->column() 
             << "text" << item->text();

    Q_ASSERT(order >= 0 && order < 2);
    int index = item->row();
    Q_ASSERT(index < REPORT_ROWS);
    int type = comboBox_harnoics->currentIndex();
    Q_ASSERT(type >= 0 && type < 2);
    float* harmonicVal = NULL;
    if (type == 0) 
        harmonicVal = &m_param.cur[index + 2 + order*REPORT_ROWS];
    else 
        harmonicVal = &m_param.vol[index + 2 + order*REPORT_ROWS];

    bool ok = false;
    float val = item->text().toDouble(&ok);
    if (ok) {
        if (qAbs(val-*harmonicVal) >= 0.0001) {
            *harmonicVal = val;
            m_bModify = true;
        }
    }
    else {
        MTableWidgetItem *mItem = dynamic_cast<MTableWidgetItem*>(item);
        mItem->setText(QString("%1").arg(*harmonicVal, 0, 'f', 2));
    }
}

void CHarnoicsParamDlg::tableWidget1Changed(QTableWidgetItem *item)
{
    tableWidgetChanged(0, item);
}

void CHarnoicsParamDlg::tableWidget2Changed(QTableWidgetItem *item)
{
    tableWidgetChanged(1, item);
}

void CHarnoicsParamDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    painter.setPen(oldPen);
}


void CHarnoicsParamDlg::moveToNextWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == comboBox_harnoics) {
        harnoicsTable1->setFocus(Qt::TabFocusReason);
        harnoicsTable1->setCurrentCell(m_currentRow, 1);
    }
    else if (currentFocusWidget == harnoicsTable1) {
        harnoicsTable2->setFocus(Qt::TabFocusReason);
        harnoicsTable2->setCurrentCell(m_currentRow, 1);
        harnoicsTable1->setCurrentCell(-1,-1);
    }
    else {
        harnoicsTable1->setFocus(Qt::TabFocusReason);
        harnoicsTable1->setCurrentCell(m_currentRow, 1);
        harnoicsTable2->setCurrentCell(-1,-1);
    }
}

void CHarnoicsParamDlg::moveToPreWidget() 
{
    moveToNextWidget();
}


void CHarnoicsParamDlg::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QWidget* currentFocusWidget = focusWidget();

    qDebug() << "CHarnoicsParamDlg::keyPressEvent:" << hex << event->key();

    switch(key) 
    {
    case Qt::Key_Escape:
        if (currentFocusWidget != comboBox_harnoics) {
            comboBox_harnoics->setFocus();
            dynamic_cast<MTableWidget*>(currentFocusWidget)->setCurrentCell(-1, -1);
            m_currentRow = -1;
        }
        else {
            event->ignore();
        }
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
        if (currentFocusWidget != comboBox_harnoics) {
            m_currentRow = dynamic_cast<MTableWidget*>(currentFocusWidget)->currentRow();
            moveToNextWidget();
        }
        else {
            event->ignore();
        }
        break;
    case Qt::Key_Up:
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