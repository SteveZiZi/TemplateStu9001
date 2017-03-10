#include "networkSettingDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <MIPAddrEdit>
#include <dirKeyInput>

#include "debug.h"

#define REPORT_POS_L        150
#define REPORT_POS_T        80

#define CAPTION_WIDTH       80
#define DESCRIBE_WIDTH      100
#define CONTENT_WIDTH       140

#define REPORT_ITEM_W      (CAPTION_WIDTH+DESCRIBE_WIDTH+CONTENT_WIDTH)
#define REPORT_ITEM_H       40




CNetworkSettingDlg::CNetworkSettingDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    label_net1 = new QLabel(this);
    label_net1->setObjectName("label_net1");
    label_net1->setText(tr("Net1:"));
    label_net1->move(x, y);
    
    label_ipAddr1 = new QLabel(this);
    label_ipAddr1->setObjectName("label_ipAddr1");
    label_ipAddr1->setText(tr("IpAddr:"));
    label_ipAddr1->move(x+CAPTION_WIDTH, y);

    lineEdit_ipAddr1 = new MIPAddrEdit(this);
    lineEdit_ipAddr1->setObjectName("lineEdit_ipAddr1");
    lineEdit_ipAddr1->move(x+CAPTION_WIDTH+DESCRIBE_WIDTH, y-5);
    lineEdit_ipAddr1->setFixedWidth(CONTENT_WIDTH);
    lineEdit_ipAddr1->setText("192.168.1.2");

    y += REPORT_ITEM_H;
    label_defaultGatewaye1 = new QLabel(this);
    label_defaultGatewaye1->setObjectName("label_defaultGatewaye1");
    label_defaultGatewaye1->setText(tr("Default Gatewaye:"));
    label_defaultGatewaye1->move(x+CAPTION_WIDTH, y);

    lineEdit_defaultGatewaye1 = new MIPAddrEdit(this);
    lineEdit_defaultGatewaye1->setObjectName("lineEdit_defaultGatewaye1");
    lineEdit_defaultGatewaye1->move(x+CAPTION_WIDTH+DESCRIBE_WIDTH, y-5);
    lineEdit_defaultGatewaye1->setFixedWidth(CONTENT_WIDTH);
    lineEdit_defaultGatewaye1->setText("192.168.1.254");


    y += REPORT_ITEM_H;
    label_net2 = new QLabel(this);
    label_net2->setObjectName("label_net2");
    label_net2->setText(tr("Net2:"));
    label_net2->move(x, y);

    label_ipAddr2 = new QLabel(this);
    label_ipAddr2->setObjectName("label_ipAddr2");
    label_ipAddr2->setText(tr("IpAddr:"));
    label_ipAddr2->move(x+CAPTION_WIDTH, y);

    lineEdit_ipAddr2 = new MIPAddrEdit(this);
    lineEdit_ipAddr2->setObjectName("lineEdit_ipAddr2");
    lineEdit_ipAddr2->move(x+CAPTION_WIDTH+DESCRIBE_WIDTH, y-5);
    lineEdit_ipAddr2->setFixedWidth(CONTENT_WIDTH);
    lineEdit_ipAddr2->setText("192.168.1.3");

    y += REPORT_ITEM_H;
    label_defaultGatewaye2 = new QLabel(this);
    label_defaultGatewaye2->setObjectName("label_defaultGatewaye2");
    label_defaultGatewaye2->setText(tr("Default Gatewaye:"));
    label_defaultGatewaye2->move(x+CAPTION_WIDTH, y);

    lineEdit_defaultGatewaye2 = new MIPAddrEdit(this);
    lineEdit_defaultGatewaye2->setObjectName("lineEdit_defaultGatewaye2");
    lineEdit_defaultGatewaye2->move(x+CAPTION_WIDTH+DESCRIBE_WIDTH, y-5);
    lineEdit_defaultGatewaye2->setFixedWidth(CONTENT_WIDTH);
    lineEdit_defaultGatewaye2->setText("192.168.1.254");


    m_dirKeyInput = new CDirKeyInput(15);
    m_dirKeyInput->addMaskChar('.');
    lineEdit_ipAddr1->setDirKeyInput(m_dirKeyInput);
    lineEdit_defaultGatewaye1->setDirKeyInput(m_dirKeyInput);
    lineEdit_ipAddr2->setDirKeyInput(m_dirKeyInput);
    lineEdit_defaultGatewaye2->setDirKeyInput(m_dirKeyInput);
}

CNetworkSettingDlg::~CNetworkSettingDlg()
{
    STU_DELETE_PTR (label_net1);
    STU_DELETE_PTR (label_ipAddr1);
    STU_DELETE_PTR (lineEdit_ipAddr1);
    STU_DELETE_PTR (label_defaultGatewaye1);
    STU_DELETE_PTR (lineEdit_defaultGatewaye1);

    STU_DELETE_PTR (label_net2);
    STU_DELETE_PTR (label_ipAddr2);
    STU_DELETE_PTR (lineEdit_ipAddr2);
    STU_DELETE_PTR (label_defaultGatewaye2);
    STU_DELETE_PTR (lineEdit_defaultGatewaye2);

    //一定要最后才删除
    STU_DELETE_PTR (m_dirKeyInput);
}



void CNetworkSettingDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden())
        this->show();

	if (style == CAbstractMenuContent::CONTENT_FOCUE)
		lineEdit_ipAddr1->setFocus();
}

void CNetworkSettingDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
	const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
	painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    int x = REPORT_POS_L;
    int y = REPORT_POS_T+REPORT_ITEM_H-10; 
    int w = REPORT_ITEM_W;
	//绘制渐变线
    QLinearGradient linerarGradient(x, 0, x+w, 0);
    linerarGradient.setColorAt(0.0, Qt::black);
    linerarGradient.setColorAt(0.5, QColor(STU_GREEN_LINE));
    linerarGradient.setColorAt(1.0, Qt::black);
    painter.setPen(QPen(QBrush(linerarGradient), 1));
    for(int i = 0; i < 4; i++) {
        painter.drawLine(x, y, x+w, y);
        y+=REPORT_ITEM_H;
    }

	painter.setPen(oldPen);
}

void CNetworkSettingDlg::moveToNextWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == lineEdit_defaultGatewaye2) {
        lineEdit_ipAddr1->setFocus(Qt::TabFocusReason);
    }
    else {
        focusNextChild();
    }
}

void CNetworkSettingDlg::moveToPreWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == lineEdit_ipAddr1) {
        lineEdit_defaultGatewaye2->setFocus(Qt::BacktabFocusReason);
    }
    else {
        focusPreviousChild();
    }
}