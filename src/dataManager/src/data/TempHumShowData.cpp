#include "TempHumShowData.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

using namespace Dev_SM;

///
/// @brief
///    构造函数
///
CTempHumShowData::CTempHumShowData(void)
{
}

///
/// @brief
///    析构函数
///
CTempHumShowData::~CTempHumShowData(void)
{
}


CTempHumShowData* CTempHumShowData::getInstance()
{
    static CTempHumShowData s_data;

    return &s_data;
}

bool CTempHumShowData::GetContectTemp(TempShowData* data)
{
    Q_ASSERT(data);

    ContactTempData_t contact;
    ContactTempThreshold_t threshold;

    bool rc = CModbusDevMgr::GetContactTemp(&contact);
    if (rc) {
        for(int i = 0; i < MAX_PHASE_NUM; i++) {
            data->fTemp[0][i] = Dev_SM::CWiringTempConv::realTemp(contact.temp[i][0]);
            data->fTemp[1][i] = Dev_SM::CWiringTempConv::realTemp(contact.temp[i][1]);
        }
        rc = CModbusDevMgr::GetContactTempThreshold(&threshold);
        if (rc)
            data->fThreshold = Dev_SM::CWiringTempConv::realTemp(threshold.threshold);
    }
    
    return rc;
}

bool CTempHumShowData::GetBusbarTemp(TempShowData* data)
{
    Q_ASSERT(data);

    BusbarTempData_t busbar;
    BusbarTempThreshold_t threshold;

    bool rc = CModbusDevMgr::GetBusbarTemp(&busbar);
    if (rc) {
        for(int i = 0; i < MAX_PHASE_NUM; i++) {
            data->fTemp[0][i] = Dev_SM::CWiringTempConv::realTemp(busbar.temp[i][0]);
            data->fTemp[1][i] = Dev_SM::CWiringTempConv::realTemp(busbar.temp[i][1]);
        }
        rc = CModbusDevMgr::GetBusbarTempThreshold(&threshold);
        if (rc)
            data->fThreshold = Dev_SM::CWiringTempConv::realTemp(threshold.threshold);
    }

    return rc;
}

bool CTempHumShowData::GetCubicleHum(HumidityData* data)
{
    Q_ASSERT(data);

    TempHumData_t TH;
    bool rc = CModbusDevMgr::GetChnl1TempHum(&TH);
    if (rc) {
        data->fTemp[0] = Dev_SM::CTempHumConv::realTemp(TH.temp);
        data->fTumidity[0] = (float)Dev_SM::CTempHumConv::realHum(TH.hum);
        
        rc = CModbusDevMgr::GetChnl2TempHum(&TH);
        if (rc) {
            data->fTemp[1] = Dev_SM::CTempHumConv::realTemp(TH.temp);
            data->fTumidity[1] = (float)Dev_SM::CTempHumConv::realHum(TH.hum);
        }
    }

    return rc;
}