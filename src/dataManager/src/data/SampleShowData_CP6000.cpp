#include "SampleShowData_CP6000.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

///
/// @brief
///    ¹¹Ôìº¯Êý
///
CSampleShowData_cp6000::CSampleShowData_cp6000(void)
{
}


CSampleShowData_cp6000* CSampleShowData_cp6000::getInstance()
{
    static CSampleShowData_cp6000 s_data;

    return &s_data;
}

void CSampleShowData_cp6000::GetSampleShowData(SampleShowData_cp6000* data, bool update)
{
    Q_ASSERT(data);
    if (update) 
        CModbusDevMgr::GetCP6000SampleData(&m_data);

    qDebug() << "CSampleShowData_cp6000::GetSampleShowData  no whole data";

    data->freq.fMeasure = Dev_CP6000::sampleData_t::realFreq(m_data.freq);

    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->phaseVol[i].fAngle    = Dev_CP6000::sampleData_t::realAngle(m_data.anglePhaseVol[i]);
        data->phaseVol[i].fMeasure  = Dev_CP6000::sampleData_t::realVol(m_data.phaseVol[i]);
    }
    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->lineVol[i].fMeasure  = Dev_CP6000::sampleData_t::realVol(m_data.lineVol[i]);
    }
    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->protectCur[i].fAngle    = Dev_CP6000::sampleData_t::realAngle(m_data.angleProtectCur[i]);
        data->protectCur[i].fMeasure  = Dev_CP6000::sampleData_t::realCur(m_data.protectCur[i]);
    }

    data->zeroSequenceVol.fAngle = Dev_CP6000::sampleData_t::realAngle(m_data.angleExternZeroSequenceVol);
    data->zeroSequenceVol.fMeasure = Dev_CP6000::sampleData_t::realVol(m_data.externZeroSequenceVol);
    data->zeroSequenceCur.fAngle = Dev_CP6000::sampleData_t::realAngle(m_data.angleExternZeroSequenceCur);
    data->zeroSequenceCur.fMeasure = Dev_CP6000::sampleData_t::realVol(m_data.externZeroSequenceCur);

    data->Ux.fAngle = Dev_CP6000::sampleData_t::realAngle(m_data.angleUx);
    data->Ux.fMeasure = Dev_CP6000::sampleData_t::realVol(m_data.Ux);

    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->sequenceVol[i].fMeasure   = Dev_CP6000::sampleData_t::realVol(m_data.sequenceVol[i]);
    }
    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        data->sequenceCur[i].fMeasure   = Dev_CP6000::sampleData_t::realCur(m_data.sequenceCur[i]);
    }
}