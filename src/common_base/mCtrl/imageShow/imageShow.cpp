#include "imageShow.h"

#include <QPainter>

#include "debug.h"

CImageShow::CImageShow(QWidget* parent)
: QLabel(parent)
, m_timer(NULL)
, m_item(0)
{

}

CImageShow::~CImageShow()
{
    clear();

    if (m_timer) {
        stopPlay();
        delete m_timer;
        m_timer = NULL;
    }
}


void CImageShow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);

    painter.setBrush(*currentBrush());

    painter.drawRect(this->rect());
}