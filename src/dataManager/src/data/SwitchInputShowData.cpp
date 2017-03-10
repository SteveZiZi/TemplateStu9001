#include "SwitchInputShowData.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"
///
/// @brief
///    构造函数
///
CSwitchInputShowData::CSwitchInputShowData(void)
{
}

///
/// @brief
///    析构函数
///
CSwitchInputShowData::~CSwitchInputShowData(void)
{
}


CSwitchInputShowData* CSwitchInputShowData::getInstance()
{
    static CSwitchInputShowData s_data;

    return &s_data;
}

bool CSwitchInputShowData::GetSwitchInputShowData(SwitchInputShowData* data)
{
    Q_ASSERT(data);
    Dev_SM::DI_t smDI;
    Dev_CP6000::DI_t cp6000DI;
    Dev_SM::electriferousDisplay_t elec;

    CModbusDevMgr::GetSmDI(&smDI);
    CModbusDevMgr::GetElectriferousDisplay(&elec);
    CModbusDevMgr::GetCP6000DI(&cp6000DI);

    data->bAutomaticBusTransferLock = cp6000DI.lockAutomaticBusTransfer;
    data->bServicePosition = cp6000DI.servicePosition || smDI.servicePosition;
    data->bTestingPosition = cp6000DI.testingPosition || smDI.testingPosition;
    data->bOpenPosition = cp6000DI.openPosition || smDI.openPosition;
    data->bClosedPosition = cp6000DI.closePosition || smDI.closePosition;
    data->bEarthingKnifeOff = cp6000DI.earthingKnifeOff || smDI.earthingKnifeOff;
    data->bEarthingKnifeOn = cp6000DI.earthingKnifeOn || smDI.earthingKnifeOn;
    data->bSpingEnergy = cp6000DI.spingEnergy || smDI.spingEnergy;
    data->bRemoteTeleOut = smDI.remoteTeleOut;
    data->bRemoteTeleIn = smDI.remoteTeleIn;
    data->bContralateralOpen = cp6000DI.contralateralOpen;
    data->bRemotePosition = cp6000DI.remotePosition;
    data->bFaultReset = smDI.faultReset;
    data->bFrontDoorStatus = smDI.frontDoorClosed;
    data->bBackDoorStatus = smDI.backDoorClosed;
    data->bElectriferousDisplay[0] = elec.displayA;
    data->bElectriferousDisplay[1] = elec.displayB;
    data->bElectriferousDisplay[2] = elec.displayC;
    data->cp6000.bLightGas = cp6000DI.lightGas;
    data->cp6000.bHeavyGas = cp6000DI.heavyGas;
    data->cp6000.bOilOverTemp = cp6000DI.oilOverTemp;
    data->cp6000.bOilHighestTemp = cp6000DI.oilHighestTemp;
    for(int i = 0; i < sizeof(data->bSwitchInput)/sizeof(data->bSwitchInput[0]); i++) {
        data->bSwitchInput[i] = false;
    }

    return true;
}