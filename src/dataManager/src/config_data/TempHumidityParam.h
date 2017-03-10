#pragma once

#include "../driver/module.h"


struct WIRING_TEMP_THRESHOLD {
    float fContactTemp[MAX_PHASE_NUM];          //���ഥͷ������ֵ
    float fBusbarTemp[MAX_PHASE_NUM];           //����ĸ�ű�����ֵ
};

struct WIRING_ID_SERIAL {
    quint32 busbarID[MAX_PHASE_NUM][2];         //����ĸ������ID��
    quint32 contactID[MAX_PHASE_NUM][2];        //���ഥͷ����ID��
};

struct TEMP_HUMIDITY_THRESHOLD {
    float fTempMax;                 //�¶�����ֵ
    float fTempMin;                 //�¶�����ֵ
    quint32 nHumidityMax;           //ʪ������ֵ
    quint32 nHumidityMin;           //ʪ������ֵ
};

class CTempHumidityParam
{
protected:
    CTempHumidityParam(void);
    virtual ~CTempHumidityParam(void);

public:
    static CTempHumidityParam* getInstance();

    bool wiringTempThreshold(WIRING_TEMP_THRESHOLD* pTempThreshold, bool bUpdate = true);
    bool setWiringTempThreshold(const WIRING_TEMP_THRESHOLD& tempThreshold);

    bool wiringIdSerial(WIRING_ID_SERIAL* pId, bool bUpdate = true);
    bool setWiringIdSerial(const WIRING_ID_SERIAL& Id);

    // chnl = 0 or chnl == 1
    bool THThreshold(quint32 chnl, TEMP_HUMIDITY_THRESHOLD* pTH, bool bUpdate = true);
    // chnl = 0 or chnl == 1
    bool setTHThreshold(quint32 chnl, const TEMP_HUMIDITY_THRESHOLD& TH);

private:
    Dev_SM::WiringTempThreshold_t m_wiringTempThreshold;
    Dev_SM::WiringId_t  m_wiringId;
    Dev_SM::TempHumThreshold_t m_thThreshold[2];
};


class CWiringTempThreshold 
{
public:
    static bool wiringTempThreshold(WIRING_TEMP_THRESHOLD* pTempThreshold, bool bUpdate = true) 
    {
        return CTempHumidityParam::getInstance()->wiringTempThreshold(pTempThreshold, bUpdate);
    }

    static bool setWiringTempThreshold(const WIRING_TEMP_THRESHOLD& tempThreshold)
    {
        return CTempHumidityParam::getInstance()->setWiringTempThreshold(tempThreshold);
    }
};

class CWiringIdSerial 
{
public:
    static bool wiringIdSerial(WIRING_ID_SERIAL* pId, bool bUpdate = true)
    {
        return CTempHumidityParam::getInstance()->wiringIdSerial(pId, bUpdate);
    }

    static bool setWiringIdSerial(const WIRING_ID_SERIAL& Id)
    {
        return CTempHumidityParam::getInstance()->setWiringIdSerial(Id);
    }
};

class CThumidityThreshold 
{
public:
    // chnl = 0 or chnl == 1
    static bool THThreshold(quint32 chnl, TEMP_HUMIDITY_THRESHOLD* pTH, bool bUpdate = true)
    {
        return CTempHumidityParam::getInstance()->THThreshold(chnl, pTH, bUpdate);
    }

    // chnl = 0 or chnl == 1
    static bool setTHThreshold(quint32 chnl, const TEMP_HUMIDITY_THRESHOLD& TH)
    {
        return CTempHumidityParam::getInstance()->setTHThreshold(chnl, TH);
    }
};


