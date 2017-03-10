#include "wireTypesParamDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QKeyEvent>

#include <mTableWidget>
#include <mPushButton>

#include "debug.h"

#define REPORT_POS_L        140
#define REPORT_POS_T        2

#define CONTENT_WIDTH       320

#define REPORT_ITEM_W      (CONTENT_WIDTH)
#define REPORT_ITEM_H       140



CWireTypesParamDlg::CWireTypesParamDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_bModify(false)
, m_dev(NULL)
{
    m_dev = CWireTypeSettings::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    tableWidget = createTableWidget("tableWidget_wireTypes");
    tableWidget->move(x, y);
}

CWireTypesParamDlg::~CWireTypesParamDlg()
{
    STU_DELETE_PTR(tableWidget);
}


void CWireTypesParamDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        m_bModify = false;
        m_dev->wireTypeSettings(&m_wireType);
        updateSettings();
        this->show();
        // Add connect
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        tableWidget->setCurrentCell(0, 0);
        tableWidget->cellWidget(0, 0)->setFocus();
    }
}

void CWireTypesParamDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CWireTypesParamDlg::_LeaveContent data Changed";
        m_dev->setWireTypeSettings(m_wireType);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CWireTypesParamDlg::_HideContent()
{
    if (!this->isHidden()) {
        // add disconnect
    }

    CBaseDialog::_HideContent();
}


QTableWidget* CWireTypesParamDlg::createTableWidget(QString objectName)
{
    QString imagePath[] = {
        ":/wireTypes/three_phase_four_line_1.png",
        ":/wireTypes/three_phase_three_line.png",
        ":/wireTypes/three_phase_four_line_2.png",
    };
    QTableWidget* tableWidget = new QTableWidget(3, 1, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setFixedHeight(3*REPORT_ITEM_H);
    tableWidget->setFixedWidth(REPORT_ITEM_W);

    tableWidget->horizontalHeader()->hide();
    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setShowGrid(false);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    tableWidget->setColumnWidth(0, REPORT_ITEM_W);
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        tableWidget->setCellWidget(row, 0, new MPushButton());
        MPushButton* pngBtn = dynamic_cast<MPushButton*>(tableWidget->cellWidget(row,0));
        pngBtn->setObjectName(QString("wireTypes"));
        pngBtn->setStyleSheet(QString("background-image: url(%1);").arg(imagePath[row]));
        pngBtn->setPriorityDrawStatus(MPushButton::FOCUSED_PRIORITY);
        tableWidget->setRowHeight(row, REPORT_ITEM_H);
    }

    return tableWidget;
}

//更新设置到界面
void CWireTypesParamDlg::updateSettings()
{
    for(int row = 0; row < tableWidget->rowCount(); row++) {
        MPushButton* pngBtn = dynamic_cast<MPushButton*>(tableWidget->cellWidget(row, 0));
        Q_ASSERT(pngBtn);
        if (row == m_wireType) {
            pngBtn->SetPressMode(true);
        }
    }
}

void CWireTypesParamDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    painter.setPen(oldPen);
}

void CWireTypesParamDlg::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    qDebug() << "CWireTypesParamDlg::keyPressEvent:" << hex << event->key();

    switch(key) 
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        for(int row = 0; row < tableWidget->rowCount(); row++) {
            MPushButton* pngBtn = dynamic_cast<MPushButton*>(tableWidget->cellWidget(row, 0));
            Q_ASSERT(pngBtn);
            if (row != tableWidget->currentRow()) {
                pngBtn->SetPressMode(false);
            }
            else {
                m_wireType = (WIRE_LINK_STYLE_ENUM)row;
                m_bModify = true;
                pngBtn->SetPressMode(true);
            }
        }
        event->accept();
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        event->accept();
        break;
    default:
        event->ignore();
        break;
    }

    if (!event->isAccepted()) {
        CBaseDialog::keyPressEvent(event);
    }
}

void CWireTypesParamDlg::moveToNextWidget() 
{

}

void CWireTypesParamDlg::moveToPreWidget() 
{

}