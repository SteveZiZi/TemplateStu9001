#include "wiringIdSerialDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QKeyEvent>

#include <mTableWidget>
#include <dirKeyInputForData>
#include <IDSerialEditDelegate>

#include "debug.h"

#define REPORT_POS_L        130
#define REPORT_POS_T        20

#define CAPTION_WIDTH       140
#define CONTENT_WIDTH       60
#define REPORT_ITEM_H       30

#define REPORT_W           (CAPTION_WIDTH+CONTENT_WIDTH*4)
#define REPORT_H           (REPORT_ITEM_H*CWiringIdSerialDlg::REPORT_ROWS+1)


CWiringIdSerialDlg::CWiringIdSerialDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_dirKeyInput(NULL)
{
    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    m_dirKeyInput = new CDirKeyInput(2);
    m_dirKeyInput->setBase(16);

    tableWidget_contact = createTableWidget("contact_idSerial", 0);
    tableWidget_contact->move(x, y);

    y += REPORT_ITEM_H; //跳过分割线

    y += REPORT_H;
    tableWidget_busbar = createTableWidget("busbar_idSerial", 1);
    tableWidget_busbar->move(x, y);
}

CWiringIdSerialDlg::~CWiringIdSerialDlg()
{
    if (tableWidget_contact) {
        delete dynamic_cast<MLineEditDelegate*>(tableWidget_contact->itemDelegate());
    }
    if (tableWidget_busbar) {
        delete dynamic_cast<MLineEditDelegate*>(tableWidget_busbar->itemDelegate());
    }

    //一定要最后才删除
    STU_DELETE_PTR (m_dirKeyInput);
}

void CWiringIdSerialDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        CWiringIdSerial::wiringIdSerial(&m_idSerial);
        updateSettings();
        m_bModify = false;
        this->show();

        connect(tableWidget_contact, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(contactIdChanged(QTableWidgetItem *)));
        connect(tableWidget_busbar, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(busbarIdChanged(QTableWidgetItem *)));
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        tableWidget_contact->setFocus(Qt::TabFocusReason);
        tableWidget_contact->setCurrentCell(0, 0);
    }
}

void CWiringIdSerialDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CWiringIdSerialDlg::_LeaveContent data Changed";
        CWiringIdSerial::setWiringIdSerial(m_idSerial);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CWiringIdSerialDlg::_HideContent()
{
    if (!this->isHidden()) {
        disconnect(tableWidget_contact, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(contactIdChanged(QTableWidgetItem *)));
        disconnect(tableWidget_busbar, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(busbarIdChanged(QTableWidgetItem *)));
    }

    CBaseDialog::_HideContent();
}

MTableWidget* CWiringIdSerialDlg::createTableWidget(QString objectName, int item)
{
    static const QString s_caption[2][REPORT_ROWS] = 
    {
        {
            CWiringIdSerialDlg::tr("Contace A_UP ID Serail:"),
            CWiringIdSerialDlg::tr("Contace A_Down ID Serail:"),
            CWiringIdSerialDlg::tr("Contace B_UP ID Serail:"),
            CWiringIdSerialDlg::tr("Contace B_Down ID Serail:"),
            CWiringIdSerialDlg::tr("Contace C_UP ID Serail:"),
            CWiringIdSerialDlg::tr("Contace C_Down ID Serail:")
        },
        {
            CWiringIdSerialDlg::tr("Busbar A_UP ID Serail:"),
            CWiringIdSerialDlg::tr("Busbar A_Down ID Serail:"),
            CWiringIdSerialDlg::tr("Busbar B_UP ID Serail:"),
            CWiringIdSerialDlg::tr("Busbar B_Down ID Serail:"),
            CWiringIdSerialDlg::tr("Busbar C_UP ID Serail:"),
            CWiringIdSerialDlg::tr("Busbar C_Down ID Serail:")
        }
    };


    MTableWidget* tableWidget = new MTableWidget(REPORT_ROWS, 4, this);
    tableWidget->setObjectName(objectName);
    tableWidget->setFixedHeight(REPORT_H);
    tableWidget->setFixedWidth(REPORT_W);

    tableWidget->horizontalHeader()->hide();
    QHeaderView* verticalHeader = new QHeaderView(Qt::Vertical, tableWidget);
    verticalHeader->setObjectName("idSerial_vHeader");
    verticalHeader->setFixedWidth(CAPTION_WIDTH);
    verticalHeader->setHighlightSections(false);
    tableWidget->setVerticalHeader(verticalHeader);

    tableWidget->horizontalScrollBar()->hide();
    tableWidget->verticalScrollBar()->hide();

    tableWidget->setShowGrid(false);

    IDSerialEditDelegate* delegate = new IDSerialEditDelegate(tableWidget);
    delegate->setDirKeyInput(m_dirKeyInput);
    tableWidget->setItemDelegate(delegate);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int row = 0; row < REPORT_ROWS; row++) {
        QTableWidgetItem *verticalHeaderItem = new QTableWidgetItem(s_caption[item][row]);
        verticalHeaderItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        tableWidget->setVerticalHeaderItem(row, verticalHeaderItem);
        tableWidget->setRowHeight(0, REPORT_ITEM_H);
        for(int column = 0; column < 4; column++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setTextAlignment(Qt::AlignCenter);
            //newItem->setText(QString("1234"));
            newItem->setFlags(newItem->flags()&(~Qt::ItemIsUserCheckable));
            tableWidget->setItem(row, column, newItem);
            tableWidget->setColumnWidth(column, CONTENT_WIDTH);
        }
    }

    return tableWidget;
}

//更新设置到界面
void CWiringIdSerialDlg::updateSettings()
{
    QTableWidgetItem* item = NULL;
    quint8* id = NULL;
    for(int row = 0; row < REPORT_ROWS; row++) {
        id = (quint8*)&m_idSerial.contactID[row/2][row%2];
        for(int column = 0; column < 4; column++)
            tableWidget_contact->item(row, column)->setText(QString("%1").arg(id[column], 2, 16, QChar('0')));

        id = (quint8*)&m_idSerial.busbarID[row/2][row%2];
        for(int column = 0; column < 4; column++)
            tableWidget_busbar->item(row, column)->setText(QString("%1").arg(id[column], 2, 16, QChar('0')));
    }
}

void CWiringIdSerialDlg::tableWidgetChanged(quint8 order, QTableWidgetItem* item)
{
    Q_ASSERT(order < 2);
    Q_ASSERT(item->row() < 6 && item->row() >= 0);
    Q_ASSERT(item->column() < 4 && item->column() >= 0);

    quint8* id = NULL;
    uint val = item->text().toUInt(0, 16);
    if(order == 0) {
        id = (quint8*)&m_idSerial.contactID[item->row()/2][item->row()%2];
    }
    else {
        id = (quint8*)&m_idSerial.busbarID[item->row()/2][item->row()%2];
    }

    if (*id != val) {
        *id = val;
        m_bModify = true;
    }
}

void CWiringIdSerialDlg::contactIdChanged(QTableWidgetItem *item)
{
    tableWidgetChanged(0, item);
}

void CWiringIdSerialDlg::busbarIdChanged(QTableWidgetItem *item)
{
    tableWidgetChanged(1, item);
}

void CWiringIdSerialDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    int x = REPORT_POS_L-10;
    int y = REPORT_POS_T+REPORT_H+REPORT_ITEM_H/2; 
    int w = REPORT_W+10;
    //绘制分隔线
    painter.drawLine(x, y, x+w, y);

    painter.setPen(oldPen);
}

void CWiringIdSerialDlg::moveToNextWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == tableWidget_contact) {
        tableWidget_busbar->setFocus(Qt::TabFocusReason);
        tableWidget_busbar->setCurrentCell(0, tableWidget_contact->currentColumn());
        tableWidget_contact->setCurrentCell(-1,-1);
    }
    else {
        tableWidget_contact->setFocus(Qt::TabFocusReason);
        tableWidget_contact->setCurrentCell(0, tableWidget_busbar->currentColumn());
        tableWidget_busbar->setCurrentCell(-1,-1);
    }
}

void CWiringIdSerialDlg::moveToPreWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == tableWidget_contact) {
        tableWidget_busbar->setFocus(Qt::TabFocusReason);
        tableWidget_busbar->setCurrentCell(tableWidget_busbar->rowCount()-1, tableWidget_contact->currentColumn());
        tableWidget_contact->setCurrentCell(-1,-1);
    }
    else {
        tableWidget_contact->setFocus(Qt::TabFocusReason);
        tableWidget_contact->setCurrentCell(tableWidget_contact->rowCount()-1, tableWidget_busbar->currentColumn());
        tableWidget_busbar->setCurrentCell(-1,-1);
    }
}


void CWiringIdSerialDlg::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    qDebug() << "CWiringIdSerialDlg::keyPressEvent:" << hex << event->key();
    switch(key) 
    {
    case Qt::Key_Escape:
        {
            QWidget* currentFocusWidget = focusWidget();
            if (currentFocusWidget == tableWidget_contact) {
                tableWidget_contact->setCurrentCell(-1,-1);
            }
            else {
                tableWidget_busbar->setCurrentCell(-1,-1);
            }
        }
        event->ignore();
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
        event->ignore();
        break;
    case Qt::Key_Up:
        moveToPreWidget();
        event->accept();
        break;
    case Qt::Key_Down:
        moveToNextWidget();
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