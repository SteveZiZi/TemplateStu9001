#pragma once

#include "../driver/module.h"


struct curQuickBreakCastback_t {
    bool castIn;
    float cur;
    float delay;
    bool lowVolBlockingCastIn;
    float lowVolBlockingVol;
    bool dirBlockingCastIn;
};

struct timeLimitQuickBreakCastback_t {
    bool castIn;
    float cur;
    float delay;
    bool lowVolBlockingCastIn;
    float lowVolBlockingVol;
    bool dirBlockingCastIn;
};

struct overCurProtectCastback_t {
    bool castIn;
    float cur;
    float delay;
    bool lowVolBlockingCastIn;
    float lowVolBlockingVol;
    bool dirBlockingCastIn;
    bool antiTimeCastIn;
    quint16 antiTimeMethod;
};

struct recloseCastback_t {
    bool castIn;
    float delay;
    bool secondSectionAccCastIn;
    bool threeSectionAccCastIn;
    float accDelay;
    bool noVolCastIn;
    bool syncCastIn;
    float allowClosingAngle;
};

struct lowFreqDeloadingCastback_t {
    bool castIn;
    float freq;
    float delay;
    bool slipBlockingCastIn;
    float diffBlockingVal;
    float reserved;
};

struct lowFreqSplittingCastback_t {
    bool castIn;
    float freq;
    float delay;
};

struct lowVolSplittingCastback_t {
    bool castIn;
    float vol;
    float delay;
};

struct smallCurGroundCastback_t {
    bool castIn;
    float cur;
    float vol;
    float delay;
    bool dirBlockingCastIn;
};

struct overLoadingCastback_t {
    bool castIn;
    float cur;
    float delay;
};

struct negativeSequenceOverCurProtectCastback_t {
    bool castIn;
    float cur;
    float delay;
};

struct zeroSequenceOverCurProtectCastback_t {
    bool castIn;
    float cur;
    float delay;
};

struct overVolProtectCastback_t {
    bool castIn;
    float vol;
    float delay;
};

struct lowVolProtectCastback_t {
    bool castIn;
    float vol;
    float delay;
};

struct lostVolProtectCastback_t {
    bool castIn;
    float vol;
    float delay;
};

struct negativeSequenceOverVolProtectCastback_t {
    bool castIn;
    float vol;
    float delay;
};


struct zeroSequenceOverVolProtectCastback_t {
    bool castIn;
    float vol;
    float delay;
};

struct compoundVolOverCurCastback_t {
    bool castIn;
    float cur;
    float delay;
    bool lowVolBlockingCastIn;
    float lowVolBlockingVol;
    bool negativeSequenceVolBlockingCastIn;
    float negativeSequenceVol;
};

struct automaticBusTransferCastback_t {
    bool castIn;
    float vol;
    float delay;
    bool method;
};

struct overHeatingProtectCastback_t {
    bool castIn;
    float cur;
    float delay;
    quint16 factor;
};

struct reversePowerProtectCastback_t {
    bool castIn;
    float power;
    float delay;
};

struct IxOverCurProtectCastback_t {
    bool castIn;
    float cur;
    float delay;
    bool antiTimeCastIn;
    quint16 antiTimeMethod;
};

struct motorProtectCastback_t {
    bool castIn;
    bool startTimeTooLongCastIn;
    float startTime;
    float cur;
    quint16 factor;
};

struct nonElectricalProtectCastback_t {
    bool castIn;
    bool lightGasCastIn;
    bool heavyGasCastIn;
    bool oilOverTempCastIn;
    bool oilHighTempCastIn;
};

struct PTBreakWireCastback_t {
    bool castIn;
};

struct CTBreakWireCastback_t {
    bool castIn;
};

struct reservedCastback_t {
    bool castIn;
};

struct faultRecordCastback_t {
    bool castIn;
};

struct controlLoopBreakWireCastback_t {
    bool castIn;
};


struct CP6000CastBackConstValue_t {
    curQuickBreakCastback_t curQuickBreak;
    timeLimitQuickBreakCastback_t timeLimitQuickBreak;
    overCurProtectCastback_t overCurProtect;
    recloseCastback_t reclose;
    lowFreqDeloadingCastback_t lowFreqDeloading;
    lowFreqSplittingCastback_t lowFreqSplitting;
    lowVolSplittingCastback_t lowVolSplitting;
    smallCurGroundCastback_t smallCurGround;
    overLoadingCastback_t overLoading;
    negativeSequenceOverCurProtectCastback_t negativeSequenceOverCurProtect;
    zeroSequenceOverCurProtectCastback_t zeroSequenceOverCurProtect;
    overVolProtectCastback_t overVolProtect;
    lowVolProtectCastback_t lowVolProtect;
    lostVolProtectCastback_t lostVolProtect;
    negativeSequenceOverVolProtectCastback_t negativeSequenceOverVolProtect;
    
    zeroSequenceOverVolProtectCastback_t zeroSequenceOverVolProtect;
    compoundVolOverCurCastback_t compoundVolOverCur;
    automaticBusTransferCastback_t automaticBusTransfer;
    overHeatingProtectCastback_t overHeatingProtect;
    reversePowerProtectCastback_t reversePowerProtect;
    IxOverCurProtectCastback_t IxOverCurProtect;
    motorProtectCastback_t motorProtect;
    nonElectricalProtectCastback_t nonElectricalProtect;
    PTBreakWireCastback_t PTBreakWire;
    CTBreakWireCastback_t CTBreakWire;
    reservedCastback_t reserved[2];
    faultRecordCastback_t faultRecord;
    controlLoopBreakWireCastback_t controlLoopBreakWire;
};


class CCP6000CastbackConstantValuesSettings
{
protected:
    CCP6000CastbackConstantValuesSettings();

public:
    static CCP6000CastbackConstantValuesSettings* getInstance();

    bool constValSettings(CP6000CastBackConstValue_t* settings, bool update = true);
    bool setConstValSettings(const CP6000CastBackConstValue_t& settings);

//     const ConstValueLimit* constValLimit(void) {
//         return &m_limit;
//     }

private:
    Dev_CP6000::castBack_t m_castback;
    Dev_CP6000::constParam_t m_constVal;
};




