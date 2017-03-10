
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
    bool bContralateralOpen;            //�Բ��λ
    bool bRemotePosition;
    bool bFaultReset;
    bool bFrontDoorStatus;
    bool bBackDoorStatus;
    bool bElectriferousDisplay[3];            //��������ʾA~C
    union {
        struct {
            bool bNonElectrical[4];             //�ǵ���1~4
        }cp9000;
        struct {
            bool bLightGas;
            bool bHeavyGas;
            bool bOilOverTemp;
            bool bOilHighestTemp;
        }cp6000;
    };
    bool bSwitchInput[8];               //����1~8
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
    ///     ��ȡ����ʵ���ӿ�
    ///
    static CSwitchInputShowData* getInstance();

public:
    bool GetSwitchInputShowData(SwitchInputShowData* data);
};

