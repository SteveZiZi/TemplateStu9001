#include "ElecOperatorData.h"
#include "../driver/module.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

using namespace Dev_SM;

///
/// @brief
///    构造函数
///
CElecOperatorData::CElecOperatorData(void)
{
}

///
/// @brief
///    析构函数
///
CElecOperatorData::~CElecOperatorData(void)
{
}


CElecOperatorData* CElecOperatorData::getInstance()
{
    static CElecOperatorData s_elecEnergyCfg;

    return &s_elecEnergyCfg;
}

bool CElecOperatorData::GetCubicleOperateMode(EO_CubicleOperateMode* mode)
{
    cubicleOperateMode_t oper;
    if (CModbusDevMgr::GetCubicleOperateMode(&oper)) {
        mode->bAutoOperator = !oper.bManual;
        return true;
    }

    return false;
}

bool CElecOperatorData::SetCubicleOperateMode(const EO_CubicleOperateMode& mode)
{
    cubicleOperateMode_t oper = {0};
    oper.bManual = !mode.bAutoOperator;
    return CModbusDevMgr::SetCubicleOperateMode(&oper);
}


bool CElecOperatorData::GetCubicleStatus(EO_CubicleStatus* status)
{
    Q_ASSERT(status);
    DO_t cubicleDO = {0};
    if (CModbusDevMgr::GetCubicleDOStatus(&cubicleDO)) {
        status->bFanStart[0] = cubicleDO.fanChnl1;
        status->bFanStart[1] = cubicleDO.fanChnl2;
        status->bHeaterStart[0] = cubicleDO.heatingChnl1;
        status->bHeaterStart[1] = cubicleDO.heatingChnl2;
        status->bLampOn = cubicleDO.lamp;
        status->bGateLock = cubicleDO.lockGate;
        status->bHighVolOpenPhase = cubicleDO.highVolOpenPhase;
        status->bFaultOutput = cubicleDO.faultOutput;
        return true;
    }

    return false;
}

bool CElecOperatorData::SetCubicleStatus(const EO_CubicleStatus& status)
{
    DO_t cubicleDO = {0};
    if (status.bFanStart[0])
        cubicleDO.fanChnl1 = 1;
    if (status.bFanStart[1])
        cubicleDO.fanChnl2 = 1;
    if (status.bHeaterStart[0])
        cubicleDO.heatingChnl1 = 1;
    if (status.bHeaterStart[1])
        cubicleDO.heatingChnl2 = 1;
    if (status.bLampOn)
        cubicleDO.lamp = 1;
    if (status.bGateLock)
        cubicleDO.lockGate = 1;
    if (status.bHighVolOpenPhase)
        cubicleDO.highVolOpenPhase = 1;
    if (status.bFaultOutput)
        cubicleDO.faultOutput = 1;

    return CModbusDevMgr::SetCubicleDOStatus(&cubicleDO);
}

bool CElecOperatorData::GetMotorOperateAllowStatus(EO_MotorOperateAllow* status)
{
    motorOperateAllow_t allow;
    if (CModbusDevMgr::GetMotorOperateAllowStatus(&allow)) {
        status->allowOperateBarrow = allow.barrowOperate;
        status->allowOperateEarthKnife = allow.earthKnifeOperate;
        return true;
    }
    return false;
}

bool CElecOperatorData::GetMotorStatus(EO_MotorStatus* status)
{
    return false;
    //return CModbusDevMgr::GetMotorStatus(status);
}


bool CElecOperatorData::teleInBarrow()
{
    Dev_SM::motorOperate_t oper = {0};
    oper.barrowTeleIn = true;
    return CModbusDevMgr::operateMotor(&oper);
}
bool CElecOperatorData::teleOutBarrow()
{
    Dev_SM::motorOperate_t oper = {0};
    oper.barrowTeleOut = true;
    return CModbusDevMgr::operateMotor(&oper);
}
bool CElecOperatorData::closeEarthKnife()
{
    Dev_SM::motorOperate_t oper = {0};
    oper.earthKnifeClose = true;
    return CModbusDevMgr::operateMotor(&oper);
}
bool CElecOperatorData::openEarthKnife()
{
    Dev_SM::motorOperate_t oper = {0};
    oper.earthKnifeOpen = true;
    return CModbusDevMgr::operateMotor(&oper);
}
bool CElecOperatorData::stopOper()
{
    Dev_SM::motorOperate_t oper = {0};
    oper.stop = true;
    return CModbusDevMgr::operateMotor(&oper);
}
bool CElecOperatorData::resetOper()
{
    Dev_SM::motorOperate_t oper = {0};
    oper.reset = true;
    return CModbusDevMgr::operateMotor(&oper);
}



bool CElecOperatorData::GetBarrowFaultStatus(EO_FaultStatus* status, bool bUpdate/* = false*/)
{
    Q_ASSERT(status);

    if (bUpdate) {
        //get status
        qDebug() << " CElecOperatorData::GetBarrowFaultStatus not object";
    }

    //memcpy(status, &m_BarrowFaultStatus, sizeof(EO_FaultStatus));

    return true;
}

bool CElecOperatorData::GetEarthingKnifeFaultStatus(EO_FaultStatus* status, bool bUpdate/* = false*/)
{
    Q_ASSERT(status);

    if (bUpdate) {
        //get status
        qDebug() << " CElecOperatorData::GetEarthingKnifeFaultStatus not object";
    }

    //memcpy(status, &m_EarthingKnifeFaultStatus, sizeof(EO_FaultStatus));

    return true;
}