
#pragma once

#include "../driver/module.h"
#include "SampleShowData.h"

struct SampleShowData_cp9000
{
    SampleVal phaseVol[MAX_PHASE_NUM];
    SampleVal phaseCur[MAX_PHASE_NUM];
    SampleVal Uab;
    SampleVal Ubc;
    SampleVal Uca;
    SampleVal Ux;
    SampleVal sequenceCur[MAX_PHASE_NUM];
    SampleVal sequenceVol[MAX_PHASE_NUM];
};

class CSampleShowData_cp9000
{
protected:
    CSampleShowData_cp9000(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CSampleShowData_cp9000* getInstance();

public:
    void GetSampleShowData(SampleShowData_cp9000* data, bool update = true);

private:
    Dev_CP9000::sampleData_t m_data;
};

