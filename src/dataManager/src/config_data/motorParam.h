#pragma once

#include "../driver/module.h"


struct MotorParamSettings {
    float fRatedCur;     //������������
    float fRatedVol;
    float fWholeRoute;
    bool  bUnderVolProtect;
    bool  bBarrowStalledReturn;
    bool  bBarrowPulseSignal;
};


class CMotorParam
{
protected:
    CMotorParam(void);
    virtual ~CMotorParam(void);

public:
    ///
    /// @brief
    ///     ��ȡ����ʵ���ӿ�
    ///
    static CMotorParam* getInstance();

public:
    bool motorParamSettings(MotorParamSettings* settings);
    bool setMotorParamSettings(const MotorParamSettings& settings);
};

