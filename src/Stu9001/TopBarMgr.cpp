#include "TopBarMgr.h"
#include "common.h"
#include <QtGui>

#include "debug.h"

CTopBarMgr::CTopBarMgr(QWidget* parent)
: QGroupBox(parent)
{
    caption = new QLabel(this);
    caption->setText(QString::fromLocal8Bit("STU9001¿ª¹Ø¹ñÖÇÄÜÖÕ¶Ë"));
    caption->setGeometry(5, 0, 200, STU_P_TOP_H);
    caption->setObjectName("caption");
}

CTopBarMgr::~CTopBarMgr()
{

}