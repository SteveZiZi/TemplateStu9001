
#pragma once

#include "../driver/module.h"

enum CT_WIRE_TYPE_ENUM {
    CT_STYLE_2,
    CT_STYLE_3
};

struct MeasureParam {
    quint16 primaryPT;                     //PT���
    quint16 primaryCT;                     //CT���
    float fRatedVol;                       //��Ƶ�ѹ
    float fRatedCur;                       //��Ƶ���
    float fVolScale;                       //��ѹ�ȼ� 380V 220V 100V 57.7V
    bool  bZeroSquence;                    //�Ƿ�ʹ���������
    int   nCTSample;                       //CP6000 CT����

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

