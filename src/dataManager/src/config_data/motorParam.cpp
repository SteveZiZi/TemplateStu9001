#include "motorParam.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

using namespace Dev_SM;

CMotorParam::CMotorParam(void)
{
}

CMotorParam::~CMotorParam(void)
{
}


CMotorParam* CMotorParam::getInstance()
{
    static CMotorParam s_elecEnergyCfg;

    return &s_elecEnergyCfg;
}


bool CMotorParam::motorParamSettings(MotorParamSettings* settings)
{
    motorConfig_t config;
    if (CModbusDevMgr::GetMotorConfig(&config)) {
        settings->fRatedCur = motorConfig_t::realCur(config.ratedCur);
        settings->fRatedVol = motorConfig_t::realVol(config.ratedVol);
        settings->fWholeRoute = motorConfig_t::realRoute(config.wholeRoute);

        settings->bUnderVolProtect = motorConfig_t::enable(config.underVolProtect);
        settings->bBarrowStalledReturn = motorConfig_t::enable(config.stalledReturnAllow);
        settings->bBarrowPulseSignal = motorConfig_t::enable(config.barrowPulseSignalEn);
        return true;
    }
    return false;
}

bool CMotorParam::setMotorParamSettings(const MotorParamSettings& settings)
{
    motorConfig_t config;

    config.ratedCur = motorConfig_t::regCur(settings.fRatedCur);
    config.ratedVol = motorConfig_t::regVol(settings.fRatedVol);
    config.wholeRoute = motorConfig_t::regRoute(settings.fWholeRoute);

    config.underVolProtect = motorConfig_t::setEnable(settings.bUnderVolProtect);
    config.stalledReturnAllow = motorConfig_t::setEnable(settings.bBarrowStalledReturn);
    config.barrowPulseSignalEn = motorConfig_t::setEnable(settings.bBarrowPulseSignal);

    return CModbusDevMgr::SetMotorConfig(&config);
}