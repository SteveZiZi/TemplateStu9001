
#pragma once

#include "../driver/module.h"
#include "SampleShowData.h"

struct SampleShowData_cp6000 
{
    SampleVal freq;
    SampleVal phaseVol[MAX_PHASE_NUM];
    SampleVal lineVol[MAX_PHASE_NUM];
    SampleVal Ux;
    SampleVal protectCur[MAX_PHASE_NUM];
    SampleVal zeroSequenceVol;
    SampleVal zeroSequenceCur;
    SampleVal sequenceVol[MAX_PHASE_NUM];
    SampleVal sequenceCur[MAX_PHASE_NUM];
};

class CSampleShowData_cp6000
{
protected:
    CSampleShowData_cp6000(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CSampleShowData_cp6000* getInstance();

public:
    void GetSampleShowData(SampleShowData_cp6000* data, bool update = true);

private:
    Dev_CP6000::sampleData_t m_data;
};

