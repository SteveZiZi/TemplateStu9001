#pragma once

#include "../driver/module.h"


enum WIRE_LINK_STYLE_ENUM {
    THREE_PHASE_FOUR_WIRE_WYE,              //三相四线 WYE
    THREE_PHASE_THREE_WIRE_Delta,           //三相三线 Delta
    THREE_PHASE_FOUR_WIRE_HighLeg,          //三相四线 High Leg
};

class CWireTypeSettings
{
protected:
    CWireTypeSettings(void);
    virtual ~CWireTypeSettings(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CWireTypeSettings* getInstance();

public:
    bool wireTypeSettings(WIRE_LINK_STYLE_ENUM* settings, bool bUpdate = true);
    bool setWireTypeSettings(const WIRE_LINK_STYLE_ENUM& param);

private:
    quint16 m_wireType;
};

