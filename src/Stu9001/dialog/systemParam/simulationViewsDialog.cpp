#include "simulationViewsDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QDateTime>

#include "debug.h"

#define REPORT_POS_L        200
#define REPORT_POS_T        50

#define CAPTION_WIDTH       80
#define CONTENT_WIDTH       60

#define REPORT_ITEM_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_ITEM_H       40



CSimulationViewsDlg::CSimulationViewsDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 


}

CSimulationViewsDlg::~CSimulationViewsDlg()
{

}



void CSimulationViewsDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden())
        this->show();

// 	if (style == CAbstractMenuContent::CONTENT_FOCUE)
// 		lineEdit_year->setFocus();
}

void CSimulationViewsDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());
    painter.setPen(oldPen);
}