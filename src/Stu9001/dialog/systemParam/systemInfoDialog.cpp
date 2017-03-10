#include "systemInfoDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <mComboBox>
#include <stu_config>
#include "debug.h"

#define SUB_WIDGET_POS_L        170
#define SUB_WIDGET_POS_T        80
#define SUB_WIDGET_OFFSET_X     120
#define SUB_WIDGET_OFFSET_Y     40

CSystemInfoDlg::CSystemInfoDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    int x = SUB_WIDGET_POS_L;
    int y = SUB_WIDGET_POS_T; 

    label_lan = new QLabel(this);
    label_lan->setObjectName("label_lan");
    label_lan->setText(tr("language:"));
    label_lan->move(x, y);
    
    comboBox_lan = new MComboBox(this);
    comboBox_lan->setObjectName("comboBox_lan");
    comboBox_lan->addItem(tr("Chiness"), 0);
    comboBox_lan->addItem(tr("English"), 1);
    comboBox_lan->move(x+SUB_WIDGET_OFFSET_X, y);
    comboBox_lan->setFixedHeight(comboBox_lan->size().height()-10);


    y += SUB_WIDGET_OFFSET_Y;
    label_machine = new QLabel(this);
    label_machine->setObjectName("label_machine");
    label_machine->setText(tr("Machine Model:"));
    label_machine->move(x, y);

    label_machineName = new QLabel(this);
    label_machineName->setObjectName("label_machineName");
    label_machineName->setText(stu_config::productModel());
    label_machineName->move(x+SUB_WIDGET_OFFSET_X, y);


    y += SUB_WIDGET_OFFSET_Y;
    label_version = new QLabel(this);
    label_version->setObjectName("label_version");
    label_version->setText(tr("Softwave Version:"));
    label_version->move(x, y);

    label_versionString = new QLabel(this);
    label_versionString->setObjectName("label_versionString");
    label_versionString->setText(stu_config::appVersion());
    label_versionString->move(x+SUB_WIDGET_OFFSET_X, y);


    y += SUB_WIDGET_OFFSET_Y;
    label_serialNo = new QLabel(this);
    label_serialNo->setObjectName("label_serialNo");
    label_serialNo->setText(tr("Serial Number:"));
    label_serialNo->move(x, y);

    label_serialNoString = new QLabel(this);
    label_serialNoString->setObjectName("label_serialNoString");
    label_serialNoString->setText(stu_config::productSerial());
    label_serialNoString->move(x+SUB_WIDGET_OFFSET_X, y);
}

CSystemInfoDlg::~CSystemInfoDlg()
{
    STU_DELETE_PTR (label_lan);
    STU_DELETE_PTR (comboBox_lan);

    STU_DELETE_PTR (label_machine);
    STU_DELETE_PTR (label_machineName);

    STU_DELETE_PTR (label_version);
    STU_DELETE_PTR (label_versionString);

    STU_DELETE_PTR (label_serialNo);
    STU_DELETE_PTR (label_serialNoString);
}



void CSystemInfoDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden())
        this->show();

	if (style == CAbstractMenuContent::CONTENT_FOCUE)
		comboBox_lan->setFocus();
}

void CSystemInfoDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
	const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
	painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    int x = SUB_WIDGET_POS_L;
    int y = SUB_WIDGET_POS_T+SUB_WIDGET_OFFSET_Y-10; 
    int w = SUB_WIDGET_OFFSET_X+90;
	//ªÊ÷∆Ω•±‰œﬂ
    QLinearGradient linerarGradient(x, 0, x+w, 0);
    linerarGradient.setColorAt(0.0, Qt::black);
    linerarGradient.setColorAt(0.5, QColor(STU_GREEN_LINE));
    linerarGradient.setColorAt(1.0, Qt::black);
    painter.setPen(QPen(QBrush(linerarGradient), 1));
    for(int i = 0; i < 4; i++) {
        painter.drawLine(x, y, x+w, y);
        y+=SUB_WIDGET_OFFSET_Y;
    }

	painter.setPen(oldPen);
}

void CSystemInfoDlg::moveToNextWidget()
{

}

void CSystemInfoDlg::moveToPreWidget()
{

}