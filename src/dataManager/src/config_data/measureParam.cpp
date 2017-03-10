#include "MeasureParam.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"


CMeasureParam::CMeasureParam(void)
{
}

CMeasureParam::~CMeasureParam(void)
{
}


CMeasureParam* CMeasureParam::getInstance()
{
    static CMeasureParam s_param;

    return &s_param;
}

bool CMeasureParam::measureParam(MeasureParam* param, bool bUpdate/* = true*/)
{
    Q_ASSERT(param);
    bool rc = true;
    if (bUpdate) {
        rc = CModbusDevMgr::GetPtCtRatio(&m_ratio);
    }
    if (rc) {
        Dev_CP6000::basicConfig_t config;
        rc = CModbusDevMgr::GetCP6000BasicConfig(&config);
        param->nCTSample = (config.wireType == 0x0200) ? CT_STYLE_2  : CT_STYLE_3;
    }

    param->primaryPT = Dev_SM::PtCtRatio_t::realVal(m_ratio.pt);
    param->primaryCT = Dev_SM::PtCtRatio_t::realVal(m_ratio.ct);
    qDebug() << "CMeasureParam::measureParam  not whole param";

    return true;
}

bool CMeasureParam::setMeasureParam(const MeasureParam& param)
{
    m_ratio.pt = Dev_SM::PtCtRatio_t::regVal(param.primaryPT);
    m_ratio.ct = Dev_SM::PtCtRatio_t::regVal(param.primaryCT);

    Dev_CP6000::basicConfig_t config;
    config.wireType = (param.nCTSample == CT_STYLE_2) ? 0x0200 : 0x00;

    bool rc = CModbusDevMgr::SetCP6000BasicConfig(&config);
    if (rc) {
        rc = CModbusDevMgr::SetPtCtRatio(&m_ratio);
    }

    return rc;
}