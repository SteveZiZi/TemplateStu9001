#include "TempHumidityParam.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"


CTempHumidityParam::CTempHumidityParam(void)
{
}

CTempHumidityParam::~CTempHumidityParam(void)
{
}

CTempHumidityParam* CTempHumidityParam::getInstance()
{
    static CTempHumidityParam s_cfg;

    return &s_cfg;
}


bool CTempHumidityParam::wiringTempThreshold(WIRING_TEMP_THRESHOLD* pTempThreshold, bool bUpdate)
{
    Q_ASSERT(pTempThreshold);
    bool rc = true;
    if (bUpdate) {
        rc = CModbusDevMgr::GetBusbarTempThreshold(&m_wiringTempThreshold.busbar);
        if (rc)
            rc = CModbusDevMgr::GetContactTempThreshold(&m_wiringTempThreshold.contact);
    }

    if (rc) {
        for(int i = 0; i < MAX_PHASE_NUM; i++) {
            pTempThreshold->fBusbarTemp[i] = Dev_SM::CWiringTempConv::realTemp(m_wiringTempThreshold.busbar.threshold);
            pTempThreshold->fContactTemp[i] = Dev_SM::CWiringTempConv::realTemp(m_wiringTempThreshold.contact.threshold);            
        }
    }
    
    return rc;
}

bool CTempHumidityParam::setWiringTempThreshold(const WIRING_TEMP_THRESHOLD& tempThreshold)
{
    m_wiringTempThreshold.busbar.threshold = Dev_SM::CWiringTempConv::regTemp(tempThreshold.fBusbarTemp[0]);
    m_wiringTempThreshold.contact.threshold = Dev_SM::CWiringTempConv::regTemp(tempThreshold.fContactTemp[0]);

    return (CModbusDevMgr::SetBusbarTempThreshold(&m_wiringTempThreshold.busbar) && 
            CModbusDevMgr::SetContactTempThreshold(&m_wiringTempThreshold.contact));
}

bool CTempHumidityParam::wiringIdSerial(WIRING_ID_SERIAL* pId, bool bUpdate)
{
    Q_ASSERT(pId);
    bool rc = true;
    if (bUpdate) {
        rc = CModbusDevMgr::GetWiringId(&m_wiringId);
    }

    if (rc) {
        for(int i = 0; i < MAX_PHASE_NUM; i++) {
            pId->busbarID[i][0] = m_wiringId.busbar.ID[0][i];
            pId->busbarID[i][1] = m_wiringId.busbar.ID[1][i];
            pId->contactID[i][0] = m_wiringId.contact.ID[0][i];
            pId->contactID[i][1] = m_wiringId.contact.ID[1][i];
        }
    }

    return rc;
}

bool CTempHumidityParam::setWiringIdSerial(const WIRING_ID_SERIAL& Id)
{
    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        m_wiringId.busbar.ID[0][i] = Id.busbarID[i][0];
        m_wiringId.busbar.ID[1][i] = Id.busbarID[i][1];
        m_wiringId.contact.ID[0][i] = Id.contactID[i][0];
        m_wiringId.contact.ID[1][i] = Id.contactID[i][1];
    }

    return CModbusDevMgr::SetWiringId(&m_wiringId);
}


bool CTempHumidityParam::THThreshold(quint32 chnl, TEMP_HUMIDITY_THRESHOLD* pTH1, bool bUpdate)
{
    Q_ASSERT(pTH1);
    Q_ASSERT(chnl < 2);
    bool rc = true;
    if (bUpdate) {
        if (chnl == 0)
            rc = CModbusDevMgr::GetChnl1TempThreshold(&m_thThreshold[chnl]);
        else
            rc = CModbusDevMgr::GetChnl2TempThreshold(&m_thThreshold[chnl]);
    }

    if (rc) {
        pTH1->fTempMax = Dev_SM::CTempHumConv::realTemp(m_thThreshold[chnl].tempMax);
        pTH1->fTempMin = Dev_SM::CTempHumConv::realTemp(m_thThreshold[chnl].tempMin);
        pTH1->nHumidityMax = Dev_SM::CTempHumConv::realHum(m_thThreshold[chnl].humMax);
        pTH1->nHumidityMin = Dev_SM::CTempHumConv::realHum(m_thThreshold[chnl].humMin);

        qDebug() << "CTempHumidityParam::THThreshold  not humidity min val";
    }

    return rc;
}

bool CTempHumidityParam::setTHThreshold(quint32 chnl, const TEMP_HUMIDITY_THRESHOLD& TH)
{
    Q_ASSERT(chnl < 2);
    m_thThreshold[chnl].tempMax = Dev_SM::CTempHumConv::regTemp(TH.fTempMax);
    m_thThreshold[chnl].tempMin = Dev_SM::CTempHumConv::regTemp(TH.fTempMin);
    m_thThreshold[chnl].humMax = Dev_SM::CTempHumConv::regHum(TH.nHumidityMax);
    m_thThreshold[chnl].humMin = Dev_SM::CTempHumConv::regHum(TH.nHumidityMin);

    if (chnl == 0)
        return CModbusDevMgr::SetChnl1TempThreshold(&m_thThreshold[chnl]);
    else
        return CModbusDevMgr::SetChnl2TempThreshold(&m_thThreshold[chnl]);
}