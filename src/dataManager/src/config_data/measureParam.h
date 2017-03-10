
#pragma once

#include "../driver/module.h"

enum CT_WIRE_TYPE_ENUM {
    CT_STYLE_2,
    CT_STYLE_3
};

struct MeasureParam {
    quint16 primaryPT;                     //PT变比
    quint16 primaryCT;                     //CT变比
    float fRatedVol;                       //标称电压
    float fRatedCur;                       //标称电流
    float fVolScale;                       //电压等级 380V 220V 100V 57.7V
    bool  bZeroSquence;                    //是否使能外界零序
    int   nCTSample;                       //CP6000 CT采样

    MeasureParam()
    {
        primaryPT = 10;
        primaryCT = 10;
        fRatedVol = 380;
        fRatedCur = 5;
        fVolScale = 380;
        bZeroSquence = false;
        nCTSample = 0;
    }
};


class CMarkup;
class CMeasureParam
{
protected:
    CMeasureParam(void);
    virtual ~CMeasureParam(void);

public:
    static CMeasureParam* getInstance();

public:
    bool measureParam(MeasureParam* param, bool bUpdate = true);
    bool setMeasureParam(const MeasureParam& param);

private:
    Dev_SM::PtCtRatio_t m_ratio;
};

