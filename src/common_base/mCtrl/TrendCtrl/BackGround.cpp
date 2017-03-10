#include "background.h"
#include "Scale.h"

#include "debug.h"

using namespace mTrend;

CBackGround::CBackGround(quint32 id)
: CComponent(id)
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::Draw(QPainter* painter, const QRect& rect)
{
    painter->fillRect(rect, WFG_CTRL_BKGND_COLOR);
}