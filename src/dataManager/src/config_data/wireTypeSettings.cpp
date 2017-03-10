#include "wireTypeSettings.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"



CWireTypeSettings::CWireTypeSettings(void)
{
}

CWireTypeSettings::~CWireTypeSettings(void)
{
}


CWireTypeSettings* CWireTypeSettings::getInstance()
{
    static CWireTypeSettings s_param;

    return &s_param;
}

bool CWireTypeSettings::wireTypeSettings(WIRE_LINK_STYLE_ENUM* settings, bool bUpdate/* = true*/)
{
    Q_ASSERT(settings);
    bool rc = true;
    if (bUpdate) {
        rc = CModbusDevMgr::GetWorkMode(&m_wireType);
    }

    if (m_wireType & (1<<7)) {
        *settings = THREE_PHASE_FOUR_WIRE_HighLeg;
    }
    else {
        *settings = THREE_PHASE_THREE_WIRE_Delta;
    }

    return rc;
}


bool CWireTypeSettings::setWireTypeSettings(const WIRE_LINK_STYLE_ENUM& settings)
{
    if (settings == THREE_PHASE_FOUR_WIRE_HighLeg) 
        m_wireType = 1 << 7;
    else 
        m_wireType = 0;

    return CModbusDevMgr::SetWorkMode(&m_wireType);
}