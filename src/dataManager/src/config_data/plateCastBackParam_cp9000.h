#pragma once

#include "../driver/module.h"


struct PlateCastParam
{
    bool bCurCast[3];                   //电流1、2、3段
    bool bZeroSequenceCast[3];          //零序1、2、3段
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
    ///     获取配置实例接口
    ///
    static CPlateCastConfig* getInstance();

public:
    bool plateConfig(PlateCastParam* config, bool bUpdate = false);
    bool setPlateConfig(const PlateCastParam& config);

private:
    Dev_CP9000::castBack_t m_plateCastStatus;
};

