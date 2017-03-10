#include "MeasureShowData.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

Dev_SM::MeasureFactor_t Dev_SM::CMeasureDataConv::m_factor;
bool Dev_SM::CMeasureDataConv::m_bGetFactor = false;

bool Dev_SM::CMeasureDataConv::getFactor(void)
{
    m_bGetFactor = CModbusDevMgr::GetMeasureFactor(&m_factor);
    return m_bGetFactor;
}

///
/// @brief
///    构造函数
///
CMeasureShowData::CMeasureShowData(void)
{
}

///
/// @brief
///    析构函数
///
CMeasureShowData::~CMeasureShowData(void)
{
}


CMeasureShowData* CMeasureShowData::getInstance()
{
    static CMeasureShowData s_data;

    return &s_data;
}

void CMeasureShowData::GetMeasureShowData(MeasureShowData* data, bool update)
{
    Q_ASSERT(data);

    if (update) {
        CModbusDevMgr::GetMeasureData(&m_data);
    }

    for(int i = 0; i < MAX_PHASE_NUM; i++) 
        data->phaseVol[i] = Dev_SM::CMeasureDataConv::realVol(m_data.phaseVol[i]);
    for(int i = 0; i < MAX_PHASE_NUM; i++) 
        data->lineVol[i] = Dev_SM::CMeasureDataConv::realVol(m_data.wireVol[i]);
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        data->Current[i] = Dev_SM::CMeasureDataConv::realCur(m_data.phaseCur[i]);
    for(int i = 0; i < MAX_PHASE_NUM; i++) 
        data->ActivePower[i] = Dev_SM::CMeasureDataConv::realPower(m_data.powerP[i]);
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        data->ReactivePower[i] = Dev_SM::CMeasureDataConv::realPower(m_data.powerQ[i]);
    for(int i = 0; i < MAX_PHASE_NUM; i++)
        data->ApparentPower[i] = Dev_SM::CMeasureDataConv::realPower(m_data.powerS[i]);
    for(int i = 0; i < MAX_PHASE_NUM; i++) 
        data->PowerFactor[i] = Dev_SM::CMeasureDataConv::realPowerFactor(m_data.powerFactor[i]);
    data->Frequence = Dev_SM::CMeasureDataConv::realFreq(m_data.freq);
    data->ActivePowerS = Dev_SM::CMeasureDataConv::realPower(m_data.powerPS);
    data->ReactivePowerS = Dev_SM::CMeasureDataConv::realPower(m_data.powerQS);
    data->ApparentPowerS = Dev_SM::CMeasureDataConv::realPower(m_data.powerSS);
    data->PowerFactorS = Dev_SM::CMeasureDataConv::realPowerFactor(m_data.freq);
}