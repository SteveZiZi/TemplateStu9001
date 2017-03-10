#pragma once

#include "TrendCommon.h"
#include "decorate.h"

namespace mTrend
{
    class CBackGround : public CComponent
    {
    public: 
        CBackGround(quint32 id);
        ~CBackGround();

        //override
        void Draw(QPainter* painter, const QRect& rect);
    };

};