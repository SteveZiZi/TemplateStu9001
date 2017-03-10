#include "baseDialog.h"
#include "common.h"

#include <QApplication>
#include <QtGui/QKeyEvent>

#include "debug.h"

CBaseDialog::CBaseDialog(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(STU_P_BODY1_L, STU_P_BODY1_T, STU_P_BODY1_W, STU_P_BODY1_H);
    hide();
    setFont(QFont(STU_FONT_FAMILY, STU_FONT_HEIGHT, STU_FONT_WEIGHT));
}

CBaseDialog::~CBaseDialog()
{

}

void CBaseDialog::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    qDebug() << "CBaseDialog::keyPressEvent:" << hex << event->key();

    switch(key) 
    {
    case Qt::Key_Escape:
        _LeaveContent();
        event->accept();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        event->accept();
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        if (dirKeyDown(key)) {
            event->accept();
        }
        break;
    case Qt::Key_F7:
        qApp->exit();
        event->accept();
        break;
    default:
        break;
    }

    if (!event->isAccepted()) {
        QDialog::keyPressEvent(event);
    }
}

void CBaseDialog::_ShowContent(int style, quint32 data)
{
    this->show();
    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        this->setFocus();
    }
    else if (style == CAbstractMenuContent::CONTENT_SHOW) {

    }
}

void CBaseDialog::_LeaveContent()
{
	CAbstractMenu* pParent = _GetMenu();
	if (pParent)
		pParent->OnChildEsc();
}

void CBaseDialog::_HideContent()
{
    if (this->isVisible()) {
        this->hide();
    }
}




bool CBaseDialog::dirKeyDown(int key)
{
    if (key == Qt::Key_Down) {
        moveToNextWidget();
    }
    else if (key == Qt::Key_Up) {
        moveToPreWidget();
    }

    return true;
}