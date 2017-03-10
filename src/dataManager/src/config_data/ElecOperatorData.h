
#pragma once

#include "../driver/module.h"

struct EO_CubicleOperateMode {
    bool bAutoOperator;
};

struct EO_CubicleStatus {
    bool bHeaterStart[2];
    bool bFanStart[2];
    bool bLampOn;
    bool bGateLock;
    bool bBarrowIn;
    bool bEarthingKnifeClosed;
    bool bHighVolOpenPhase;     //∏ﬂ—π»±œ‡
    bool bFaultOutput;          //π ’œ ‰≥ˆ
};

struct EO_FaultStatus {
    bool bOverVoltage;
    bool bUnderVoltage;
    bool bMotorShortCircuit;
    bool bMotorOverCurrent;
    bool bMotorStalled;
};

struct EO_MotorOperateAllow {
    bool allowOperateBarrow;
    bool allowOperateEarthKnife;
};

struct EO_MotorOperate {
    bool bBarrowTeleIn;
    bool bBarrowTeleOut;
    bool bEarthKnifeClose;
    bool bEarthKnifeOpen;
    bool bStop;
    bool bReset;
};

typedef struct Dev_SM::motorStatus_t EO_MotorStatus;


class CMarkup;
class CElecOperatorData
{
protected:
    CElecOperatorData(void);
    virtual ~CElecOperatorData(void);

public:
    static CElecOperatorData* getInstance();

public:
    bool GetCubicleOperateMode(EO_CubicleOperateMode* mode);
    bool SetCubicleOperateMode(const EO_CubicleOperateMode& mode);

    bool GetCubicleStatus(EO_CubicleStatus* status);
    bool SetCubicleStatus(const EO_CubicleStatus& status);

    bool GetMotorOperateAllowStatus(EO_MotorOperateAllow* status);
    bool GetMotorStatus(EO_MotorStatus* status);
    bool teleInBarrow();
    bool teleOutBarrow();
    bool closeEarthKnife();
    bool openEarthKnife();
    bool stopOper();
    bool resetOper();

    bool GetBarrowFaultStatus(EO_FaultStatus* status, bool bUpdate = true);
    bool GetEarthingKnifeFaultStatus(EO_FaultStatus* status, bool bUpdate = true);


private:
};

