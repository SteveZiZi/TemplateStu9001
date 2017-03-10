#pragma once

#include "../driver/module.h"


struct PlateCastParam
{
    bool bCurCast[3];                   //����1��2��3��
    bool bZeroSequenceCast[3];          //����1��2��3��
    bool bCurAccSectionCast;
    bool bZeroSequenceAccSectionCast;
    bool bCurAntiTimeCast;
    bool bZeroSequenceAntiTimeCast;
    bool bOverloadWarningCast;
    bool bOverloadTripCast;
    bool bReclosingCast;
    bool bLowCycleSplitCast;
    bool bLowVolSplitCast;
};


class CPlateCastConfig
{
protected:
    CPlateCastConfig(void);
    virtual ~CPlateCastConfig(void);

public:
    ///
    /// @brief
    ///     ��ȡ����ʵ���ӿ�
    ///
    static CPlateCastConfig* getInstance();

public:
    bool plateConfig(PlateCastParam* config, bool bUpdate = false);
    bool setPlateConfig(const PlateCastParam& config);

private:
    Dev_CP9000::castBack_t m_plateCastStatus;
};

