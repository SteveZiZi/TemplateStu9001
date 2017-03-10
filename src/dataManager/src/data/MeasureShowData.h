
#pragma once

#include "../driver/module.h"

struct MeasureShowData 
{
    float phaseVol[MAX_PHASE_NUM];
    float lineVol[MAX_PHASE_NUM];
    float Current[MAX_PHASE_NUM];
    float ActivePower[MAX_PHASE_NUM];
    float ReactivePower[MAX_PHASE_NUM];
    float ApparentPower[MAX_PHASE_NUM];
    float PowerFactor[MAX_PHASE_NUM];
    float Frequence;
    float ActivePowerS;
    float ReactivePowerS;
    float ApparentPowerS;
    float PowerFactorS;
};

class CMeasureShowData
{
protected:
    CMeasureShowData(void);
    virtual ~CMeasureShowData(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CMeasureShowData* getInstance();

public:
    void GetMeasureShowData(MeasureShowData* data, bool update = true);

private:
    Dev_SM::MeasureData_t m_data;
};

