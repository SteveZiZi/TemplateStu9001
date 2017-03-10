
#pragma once

#include "../driver/module.h"

struct SwitchInputShowData 
{
    bool bAutomaticBusTransferLock;
    bool bServicePosition;
    bool bTestingPosition;
    bool bOpenPosition;
    bool bClosedPosition;
    bool bEarthingKnifeOn;
    bool bEarthingKnifeOff;
    bool bSpingEnergy;
    bool bRemoteTeleOut;
    bool bRemoteTeleIn;
    bool bContralateralOpen;            //对侧分位
    bool bRemotePosition;
    bool bFaultReset;
    bool bFrontDoorStatus;
    bool bBackDoorStatus;
    bool bElectriferousDisplay[3];            //带电量显示A~C
    union {
        struct {
            bool bNonElectrical[4];             //非电量1~4
        }cp9000;
        struct {
            bool bLightGas;
            bool bHeavyGas;
            bool bOilOverTemp;
            bool bOilHighestTemp;
        }cp6000;
    };
    bool bSwitchInput[8];               //开入1~8
};

struct SM_SwitchInput_t;
struct IP_SwitchInput_t;
class CSwitchInputShowData
{
protected:
    CSwitchInputShowData(void);
    virtual ~CSwitchInputShowData(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CSwitchInputShowData* getInstance();

public:
    bool GetSwitchInputShowData(SwitchInputShowData* data);
};

