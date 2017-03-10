#include "plateCastBackDialog_cp9000.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QKeyEvent>

#include <mTableWidget>
#include <MCheckBox>
#include <dirKeyInputForData>
#include <MLineEditDelegate>

#include "debug.h"


#define REPORT_POS_L        120
#define REPORT_POS_T        33

#define CAPTION_WIDTH       125
#define CONTENT_WIDTH       85
#define REPORT_ITEM_H       22

#define REPORT_HEADER_H     20
#define REPORT_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_H      (REPORT_HEADER_H+REPORT_ITEM_H*15+2)


CPlateCastBackDlg::CPlateCastBackDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_bModify(false)
, m_dev(NULL)
{
    m_dev = CPlateCastConfig::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    m_tableWidget = createTableWidget("tableWidget_castback");
    m_tableWidget->move(x, y);

    connect(m_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(changed(QTableWidgetItem*)));
}

CPlateCastBackDlg::~CPlateCastBackDlg()
{
    STU_DELETE_PTR(m_tableWidget);
}

void CPlateCastBackDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        this->show();
        m_bModify = false;
        m_dev->plateConfig(&m_settings);
        updateSettings();
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        m_tableWidget->setFocus();
        m_tableWidget->setCurrentCell(0, 1);
    }
}

void CPlateCastBackDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CPlateCastBackDlg::_LeaveContent data Changed";
        m_dev->setPlateConfig(m_settings);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CPlateCastBackDlg::changed(QTableWidgetItem* item)
{
    qDebug() << "CPlateCastBackDlg::changed" << item->row() ;

    if (item->column() == 1)
    {
        bool sel = (item->checkState() == Qt::Checked) ? true : false;

        if (sel)
            item->setText(CPlateCastBackDlg::tr("cast"));
        else 
            item->setText(CPlateCastBackDlg::tr("back"));

        bool* status = &m_settings.bCurCast[0] + item->row();
        *status = sel;
        m_bModify = true;
    }
}

MTableWidget* CPlateCastBackDlg::createTableWidget(QString objectName)
{
    static QString captionName[] = {
        CPlateCastBackDlg::tr("plate Name"),
        CPlateCastBackDlg::tr("cast back")
    };

    static QString plateName[] = {
        CPlateCastBackDlg::tr("cur first section"),
        CPlateCastBackDlg::tr("cur second section"),
        CPlateCastBackDlg::tr("cur three section"),
        CPlateCastBackDlg::tr("zero sequence first section"),
        CPlateCastBackDlg::tr("zero sequence second section"),
        CPlateCastBackDlg::tr("zero sequence three section"),

        CPlateCastBackDlg::tr("cur ACC section"),
        CPlateCastBackDlg::tr("zero sequence ACC section"),
        CPlateCastBackDlg::tr("cur ANTI time"),
        CPlateCastBackDlg::tr("zero sequence ANTI section"),

        CPlateCastBackDlg::tr("overload warning"),
        CPlateCastBackDlg::tr("overload trip"),

        CPlateCastBackDlg::tr("recloser"),

        CPlateCastBackDlg::tr("low cyle split"),
        CPlateCastBackDlg::tr("low vol split")
    };

    MTableWidget* tableWidget = new MTableWidget(15, 2, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setFixedHeight(REPORT_H);
    tableWidget->setFixedWidth(REPORT_W);

    /*
     *  列表头设置
     */
    QHeaderView* hHeader = new QHeaderView(Qt::Horizontal, tableWidget);
    hHeader->setObjectName("plateCastBack_hHeader");
    hHeader->setFixedHeight(REPORT_HEADER_H);
    hHeader->setHighlightSections(false);
    tableWidget->setHorizontalHeader(hHeader);

    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    for(int i = 0; i < 2; i++) {
        QTableWidgetItem *harmonicValHeaderItem = new QTableWidgetItem(captionName[i]);
        tableWidget->setHorizontalHeaderItem(i, harmonicValHeaderItem);
        harmonicValHeaderItem->setTextAlignment(Qt::AlignCenter);
        if (i == 0) {
            tableWidget->setColumnWidth(0, CAPTION_WIDTH);
        }
        else {
            tableWidget->setColumnWidth(i, CONTENT_WIDTH);
        }
    }
    /*
     *  自定义网格设置
     */
    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(new MGridStyle(QColor(STU_GREEN_LINE), false, true));
    tableWidget->setShowTopBottomLine(true, true);

    /*
     *  输入方式设置
     */
//     MLineEditDelegate* delegate = new MLineEditDelegate(tableWidget);
//     delegate->setDirKeyInput(m_dirKeyInputForData);
//     tableWidget->setItemDelegate(delegate);
//     tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*
     *  选择整行
     */
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);


    /*
     *  添加列表内容
     */
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            if (column == 0) {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                newItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
                newItem->setText(plateName[row]);
                newItem->setTextColor(STU_GREEN_LINE);
                newItem->setFlags(Qt::ItemIsSelectable);
                tableWidget->setItem(row, column, newItem);
            }
            else {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                newItem->setTextAlignment(Qt::AlignCenter);
                tableWidget->setItem(row, column, newItem);
            }
        }
        tableWidget->setRowHeight(row, REPORT_ITEM_H);
    }

    return tableWidget;
}

//更新设置到界面
void CPlateCastBackDlg::updateSettings()
{
    bool* status = &m_settings.bCurCast[0];
    for (int row = 0; row < m_tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem *item = m_tableWidget->item(row, 1);
        if (*status) 
            item->setCheckState(Qt::Checked);
        else 
            item->setCheckState(Qt::Unchecked);

        status++;
    }
}


void CPlateCastBackDlg::moveToNextWidget() 
{

}

void CPlateCastBackDlg::moveToPreWidget() 
{
    moveToNextWidget();
}


void CPlateCastBackDlg::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "CPlateCastBackDlg::keyPressEvent:" << hex << event->key();

    switch(event->key()) 
    {
    case Qt::Key_Escape:
        m_tableWidget->setCurrentCell(-1,-1);
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