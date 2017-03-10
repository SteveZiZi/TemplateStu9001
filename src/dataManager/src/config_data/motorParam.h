#pragma once

#include "../driver/module.h"


struct MotorParamSettings {
    float fRatedCur;     //电机驱动额定电流
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
    ///     获取配置实例接口
    ///
    static CMotorParam* getInstance();

public:
    bool motorParamSettings(MotorParamSettings* settings);
    bool setMotorParamSettings(const MotorParamSettings& settings);
};

