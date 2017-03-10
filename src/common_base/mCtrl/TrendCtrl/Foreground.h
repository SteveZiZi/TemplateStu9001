#pragma once

#include "TrendCommon.h"
#include "decorate.h"
#include <vector>

namespace mTrend
{
    class CForeground : public CComponent
    {
    public: 

        CForeground(int id) 
        : CComponent(id)
        {
        }

        virtual ~CForeground()
        {
        }

        void Draw(QPainter* painter, const QRect& rect) {}
    };

};