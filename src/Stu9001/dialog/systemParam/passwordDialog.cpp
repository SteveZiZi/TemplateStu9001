#include "passwordDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <mLineEdit>
#include <dirKeyInput>

#include "debug.h"

#define SUB_WIDGET_POS_L        170
#define SUB_WIDGET_POS_T        80
#define SUB_WIDGET_OFFSET_X     120
#define SUB_WIDGET_OFFSET_Y     40

#define EDIT_WIDTH              80

CPasswordDlg::CPasswordDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    int x = SUB_WIDGET_POS_L;
    int y = SUB_WIDGET_POS_T;

    label_oldPassword = new QLabel(this);
    label_oldPassword->setObjectName("label_oldPassword");
    label_oldPassword->setText(tr("Old Password:"));
    label_oldPassword->move(x, y);

    lineEdit_oldPassword = new MLineEdit(this);
    lineEdit_oldPassword->setObjectName("lineEdit_oldPassword");
    lineEdit_oldPassword->setText("");
    lineEdit_oldPassword->move(x+SUB_WIDGET_OFFSET_X, y-5);
    lineEdit_oldPassword->setFixedWidth(EDIT_WIDTH);


    y += SUB_WIDGET_OFFSET_Y;
    label_newPassword = new QLabel(this);
    label_newPassword->setObjectName("label_newPassword");
    label_newPassword->setText(tr("New Password:"));
    label_newPassword->move(x, y);

    lineEdit_newPassword = new MLineEdit(this);
    lineEdit_newPassword->setObjectName("lineEdit_newPassword");
    lineEdit_newPassword->setText("");
    lineEdit_newPassword->move(x+SUB_WIDGET_OFFSET_X, y-5);
    lineEdit_newPassword->setFixedWidth(EDIT_WIDTH);


    y += SUB_WIDGET_OFFSET_Y;
    label_confirmPassword = new QLabel(this);
    label_confirmPassword->setObjectName("label_confirmPassword");
    label_confirmPassword->setText(tr("Confirm Password:"));
    label_confirmPassword->move(x, y);

    lineEdit_confirmPassword = new MLineEdit(this);
    lineEdit_confirmPassword->setObjectName("lineEdit_confirmPassword");
    lineEdit_confirmPassword->setText("");
    lineEdit_confirmPassword->move(x+SUB_WIDGET_OFFSET_X, y-5);
    lineEdit_confirmPassword->setFixedWidth(EDIT_WIDTH);


    m_dirKeyInput = new CDirKeyInput();
    lineEdit_oldPassword->setDirKeyInput(m_dirKeyInput);
    lineEdit_newPassword->setDirKeyInput(m_dirKeyInput);
    lineEdit_confirmPassword->setDirKeyInput(m_dirKeyInput);
}

CPasswordDlg::~CPasswordDlg()
{
    STU_DELETE_PTR(label_oldPassword);
    STU_DELETE_PTR (lineEdit_oldPassword);

    STU_DELETE_PTR (label_newPassword);
    STU_DELETE_PTR (lineEdit_newPassword);

    STU_DELETE_PTR (label_confirmPassword);
    STU_DELETE_PTR (lineEdit_confirmPassword);

    //一定要最后才删除
    STU_DELETE_PTR (m_dirKeyInput);
}



void CPasswordDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden())
        this->show();

	if (style == CAbstractMenuContent::CONTENT_FOCUE)
		lineEdit_oldPassword->setFocus();
}

void CPasswordDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    int x = SUB_WIDGET_POS_L;
    int y = SUB_WIDGET_POS_T+SUB_WIDGET_OFFSET_Y-10; 
    int w = SUB_WIDGET_OFFSET_X+EDIT_WIDTH;
    //绘制渐变线
    QLinearGradient linerarGradient(x, 0, x+w, 0);
    linerarGradient.setColorAt(0.0, Qt::black);
    linerarGradient.setColorAt(0.5, QColor(STU_GREEN_LINE));
    linerarGradient.setColorAt(1.0, Qt::black);
    painter.setPen(QPen(QBrush(linerarGradient), 1));
    for(int i = 0; i < 3; i++) {
        painter.drawLine(x, y, x+w, y);
        y+=SUB_WIDGET_OFFSET_Y;
    }

    painter.setPen(oldPen);
}


void CPasswordDlg::moveToNextWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == lineEdit_confirmPassword) {
        lineEdit_oldPassword->setFocus(Qt::TabFocusReason);
    }
    else {
        focusNextChild();
    }
}

void CPasswordDlg::moveToPreWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == lineEdit_oldPassword) {
        lineEdit_confirmPassword->setFocus(Qt::BacktabFocusReason);
    }
    else {
        focusPreviousChild();
    }
}