#include "plateCastBackParam_cp9000.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"


///
/// @brief
///    构造函数
///
CPlateCastConfig::CPlateCastConfig(void)
{
}

///
/// @brief
///    析构函数
///
CPlateCastConfig::~CPlateCastConfig(void)
{
}


CPlateCastConfig* CPlateCastConfig::getInstance()
{
    static CPlateCastConfig s_Cfg;
    return &s_Cfg;
}

bool CPlateCastConfig::plateConfig(PlateCastParam* settings, bool bUpdate/* = false*/)
{
    bool rc = true;
    if (bUpdate) {
        rc = CModbusDevMgr::GetPlateCastBack(&m_plateCastStatus);
    }
    
    bool* status = (bool*)(&settings->bCurCast[0]);
    for(int i = 0; i < 16; i++) {
        *status = (m_plateCastStatus.plateStatus&(1 << 16)) ? true : false;
        status++;
    }

    return rc;
}

bool CPlateCastConfig::setPlateConfig(const PlateCastParam& settings)
{
    bool* status = (bool*)(&settings.bCurCast[0]);
    m_plateCastStatus.plateStatus = 0;
    for(int i = 0; i < 16; i++) {
        m_plateCastStatus.plateStatus |= *status << i;
        status++;
    }
    return CModbusDevMgr::SetPlateCastBack(&m_plateCastStatus);
}
