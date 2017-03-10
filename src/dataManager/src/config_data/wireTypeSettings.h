#pragma once

#include "../driver/module.h"


enum WIRE_LINK_STYLE_ENUM {
    THREE_PHASE_FOUR_WIRE_WYE,              //�������� WYE
    THREE_PHASE_THREE_WIRE_Delta,           //�������� Delta
    THREE_PHASE_FOUR_WIRE_HighLeg,          //�������� High Leg
};

class CWireTypeSettings
{
protected:
    CWireTypeSettings(void);
    virtual ~CWireTypeSettings(void);

public:
    ///
    /// @brief
    ///     ��ȡ����ʵ���ӿ�
    ///
    static CWireTypeSettings* getInstance();

public:
    bool wireTypeSettings(WIRE_LINK_STYLE_ENUM* settings, bool bUpdate = true);
    bool setWireTypeSettings(const WIRE_LINK_STYLE_ENUM& param);

private:
    quint16 m_wireType;
};

