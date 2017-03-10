
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
    ///     ��ȡ����ʵ���ӿ�
    ///
    static CTempHumShowData* getInstance();

public:
    /*
     *  @Note��
     *      update=true�������½����ߵ��¶�ֵ
     */
    bool GetContectTemp(TempShowData* data);
    bool GetBusbarTemp(TempShowData* data);
    /*
     *  @Note��
     *      update=true��������ͨ��1��ͨ��2��ʪ��
     */
    bool GetCubicleHum(HumidityData* data);
};