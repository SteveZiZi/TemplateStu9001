#include "SampleShowData_CP9000.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

///
/// @brief
///    ¹¹Ôìº¯Êý
///
CSampleShowData_cp9000::CSampleShowData_cp9000(void)
{
}


CSampleShowData_cp9000* CSampleShowData_cp9000::getInstance()
{
    static CSampleShowData_cp9000 s_data;

    return &s_data;
}

void CSampleShowData_cp9000::GetSampleShowData(SampleShowData_cp9000* data, bool update)
{
    Q_ASSERT(data);
    if (update) 
        CModbusDevMgr::GetCP9000SampleData(&m_data);

    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->phaseVol[i].fAngle    = Dev_CP9000::sampleData_t::realAngle(m_data.phaseVol[i].angle);
        data->phaseVol[i].fMeasure  = Dev_CP9000::sampleData_t::realVol(m_data.phaseVol[i].rms);
    }
    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->phaseCur[i].fAngle    = Dev_CP9000::sampleData_t::realAngle(m_data.phaseCur[i].angle);
        data->phaseCur[i].fMeasure  = Dev_CP9000::sampleData_t::realCur(m_data.phaseCur[i].rms);
    }

    data->Uab.fAngle    = Dev_CP9000::sampleData_t::realAngle(m_data.Uab.angle);
    data->Uab.fMeasure  = Dev_CP9000::sampleData_t::realVol(m_data.Uab.rms);
    data->Ubc.fAngle    = Dev_CP9000::sampleData_t::realAngle(m_data.Ubc.angle);
    data->Ubc.fMeasure  = Dev_CP9000::sampleData_t::realVol(m_data.Ubc.rms);
    data->Uca.fAngle    = Dev_CP9000::sampleData_t::realAngle(m_data.Uca.angle);
    data->Uca.fMeasure  = Dev_CP9000::sampleData_t::realVol(m_data.Uca.rms);
    data->Ux.fAngle     = Dev_CP9000::sampleData_t::realAngle(m_data.Ux.angle);
    data->Ux.fMeasure   = Dev_CP9000::sampleData_t::realVol(m_data.Ux.rms);

    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->sequenceCur[i].fAngle     = Dev_CP9000::sampleData_t::realAngle(m_data.zeroSequenceCur[i].angle);
        data->sequenceCur[i].fMeasure   = Dev_CP9000::sampleData_t::realCur(m_data.zeroSequenceCur[i].rms);
    }
    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->sequenceCur[i].fAngle     = Dev_CP9000::sampleData_t::realAngle(m_data.zeroSequenceCur[i].angle);
        data->sequenceCur[i].fMeasure   = Dev_CP9000::sampleData_t::realCur(m_data.zeroSequenceCur[i].rms);
    }
}