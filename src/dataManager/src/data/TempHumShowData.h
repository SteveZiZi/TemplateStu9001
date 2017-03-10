
#pragma once

#include "../driver/module.h"

struct TempShowData {
    float fTemp[2][MAX_PHASE_NUM];
    float fThreshold;
};

struct HumidityData {
    float fTemp[2];
    float fTumidity[2];
};

class CTempHumShowData
{
protected:
    CTempHumShowData(void);
    virtual ~CTempHumShowData(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CTempHumShowData* getInstance();

public:
    /*
     *  @Note：
     *      update=true，将更新进出线的温度值
     */
    bool GetContectTemp(TempShowData* data);
    bool GetBusbarTemp(TempShowData* data);
    /*
     *  @Note：
     *      update=true，将更新通道1和通道2的湿度
     */
    bool GetCubicleHum(HumidityData* data);
};