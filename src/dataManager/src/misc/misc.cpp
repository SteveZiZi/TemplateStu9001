#include "misc.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"


CDataLevelMisc::CDataLevelMisc(void)
{
}

CDataLevelMisc::~CDataLevelMisc(void)
{
}


CDataLevelMisc* CDataLevelMisc::getInstance()
{
    static CDataLevelMisc s_data;

    return &s_data;
}


bool CDataLevelMisc::GetCP6000Time(QDateTime* dateTime)
{
    Dev_CP6000::devTime_t tm;
    if (CModbusDevMgr::GetCP6000Time(&tm)) {
        Dev_CP6000::CDevTimeConv::realTime(tm, dateTime);
        return true;
    }
    return false;
}

bool CDataLevelMisc::SetCP6000Time(const QDateTime& dateTime)
{
    Dev_CP6000::devTime_t tm;
    Dev_CP6000::CDevTimeConv::realReg(dateTime, &tm);
    return CModbusDevMgr::SetCP6000Time(&tm);
}



bool CDataLevelMisc::GetMachineCharacterTime(QDateTime* dateTime)
{
    Dev_SM::devTime_t tm;
    if (CModbusDevMgr::GetMachineCharaterTime(&tm)) {
        Dev_SM::devTime_t::realTime(tm, dateTime);
        return true;
    }
    return false;
}

bool CDataLevelMisc::SetMachineCharacterTime(const QDateTime& dateTime)
{
    Dev_SM::devTime_t tm;
    Dev_SM::devTime_t::realReg(dateTime, &tm);
    return CModbusDevMgr::SetMachineCharaterTime(&tm);
}