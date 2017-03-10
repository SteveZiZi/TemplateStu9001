#include "castbackConstantValuesSetting_cp6000.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

using namespace Dev_CP6000;

CCP6000CastbackConstantValuesSettings::CCP6000CastbackConstantValuesSettings()
{

}


CCP6000CastbackConstantValuesSettings* CCP6000CastbackConstantValuesSettings::getInstance()
{
    static CCP6000CastbackConstantValuesSettings settings;

    return &settings;
}

bool CCP6000CastbackConstantValuesSettings::constValSettings(CP6000CastBackConstValue_t* settings, bool update)
{
    if(!settings) {
        return false;
    }

    bool rc = true;
    if (update) {
        rc = (CModbusDevMgr::GetCP6000Castback(&m_castback) && CModbusDevMgr::GetCP6000ConstVal(&m_constVal));
    }

    settings->curQuickBreak.castIn = castBack_t::isCast(m_castback.curQuickBreak);
    settings->curQuickBreak.cur = constParam_t::realVal(m_constVal.curQuickBreak_cur);
    settings->curQuickBreak.delay = constParam_t::realVal(m_constVal.curQuickBreak_delay);
    settings->curQuickBreak.lowVolBlockingCastIn = castBack_t::isCast(m_castback.curQuickBreak_lowVolBlocking);
    settings->curQuickBreak.lowVolBlockingVol = constParam_t::realVal(m_constVal.curQuickBreak_lowVolBlockingVal);
    settings->curQuickBreak.dirBlockingCastIn = castBack_t::isCast(m_castback.curQuickBreak_dirBlocking);

    settings->timeLimitQuickBreak.castIn = castBack_t::isCast(m_castback.timeLimitQuickBreak);
    settings->timeLimitQuickBreak.cur = constParam_t::realVal(m_constVal.timeLimitQuickBreak_cur);
    settings->timeLimitQuickBreak.delay = constParam_t::realVal(m_constVal.timeLimitQuickBreak_delay);
    settings->timeLimitQuickBreak.lowVolBlockingCastIn = castBack_t::isCast(m_castback.timeLimitQuickBreak_lowVolBlocking);
    settings->timeLimitQuickBreak.lowVolBlockingVol = constParam_t::realVal(m_constVal.timeLimitQuickBreak_lowVolBlockingVal);
    settings->timeLimitQuickBreak.dirBlockingCastIn = castBack_t::isCast(m_castback.timeLimitQuickBreak_dirBlocking);

    settings->overCurProtect.castIn = castBack_t::isCast(m_castback.overCurProtect);
    settings->overCurProtect.cur = constParam_t::realVal(m_constVal.overCurProtect_cur);
    settings->overCurProtect.delay = constParam_t::realVal(m_constVal.overCurProtect_delay);
    settings->overCurProtect.lowVolBlockingCastIn = castBack_t::isCast(m_castback.overCurProtect_lowVolBlocking);
    settings->overCurProtect.lowVolBlockingVol = constParam_t::realVal(m_constVal.overCurProtect_lowVolBlockingVal);
    settings->overCurProtect.dirBlockingCastIn = castBack_t::isCast(m_castback.overCurProtect_dirBlocking);
    settings->overCurProtect.antiTimeCastIn = castBack_t::isCast(m_castback.overCurProtect_antiTime);
    settings->overCurProtect.antiTimeMethod = m_constVal.overCurProtect_antiTimeMethod/100;

    settings->reclose.castIn = castBack_t::isCast(m_castback.reclose);
    settings->reclose.delay = constParam_t::realVal(m_constVal.reclose_delay);
    settings->reclose.secondSectionAccCastIn = castBack_t::isCast(m_castback.reclose_secondSectionACC);
    settings->reclose.threeSectionAccCastIn = castBack_t::isCast(m_castback.reclose_threeSectionACC);
    settings->reclose.accDelay = constParam_t::realVal(m_constVal.reclose_accDelay);
    settings->reclose.noVolCastIn = castBack_t::isCast(m_castback.reclose_noVol);
    settings->reclose.syncCastIn = castBack_t::isCast(m_castback.reclose_sync);
    settings->reclose.allowClosingAngle = constParam_t::realVal(m_constVal.reclose_allowClosingAngle);

    settings->lowFreqDeloading.castIn = castBack_t::isCast(m_castback.lowFreqDeloading);
    settings->lowFreqDeloading.freq = constParam_t::realVal(m_constVal.lowFreqDeloading_freq);
    settings->lowFreqDeloading.delay = constParam_t::realVal(m_constVal.lowFreqDeloading_delay);
    settings->lowFreqDeloading.slipBlockingCastIn = castBack_t::isCast(m_castback.lowFreqDeloading_slipBlocking);
    settings->lowFreqDeloading.diffBlockingVal = constParam_t::realVal(m_constVal.lowFreqDeloading_diffBlockingVal);
    settings->lowFreqDeloading.reserved = constParam_t::realVal(m_constVal.lowFreqDeloading_reserve);

    settings->lowFreqSplitting.castIn = castBack_t::isCast(m_castback.lowFreqSplitting);
    settings->lowFreqSplitting.freq = constParam_t::realVal(m_constVal.lowFreqSplitting_freq);
    settings->lowFreqSplitting.delay = constParam_t::realVal(m_constVal.lowFreqSplitting_delay);

    settings->lowVolSplitting.castIn = castBack_t::isCast(m_castback.lowVolSplitting);
    settings->lowVolSplitting.vol = constParam_t::realVal(m_constVal.lowVolSplitting_vol);
    settings->lowVolSplitting.delay = constParam_t::realVal(m_constVal.lowVolSplitting_delay);

    settings->smallCurGround.castIn = castBack_t::isCast(m_castback.smallCurGround);
    settings->smallCurGround.cur = constParam_t::realVal(m_constVal.smallCurGround_zeroSequenceCur);
    settings->smallCurGround.vol = constParam_t::realVal(m_constVal.smallCurGround_zeroSequenceVol);
    settings->smallCurGround.delay = constParam_t::realVal(m_constVal.smallCurGround_delay);
    settings->smallCurGround.dirBlockingCastIn = castBack_t::isCast(m_castback.smallCurGround_dirBlocking);

    settings->overLoading.castIn = castBack_t::isCast(m_castback.overLoadingProtect);
    settings->overLoading.cur = constParam_t::realVal(m_constVal.overLoadingProtect_cur);
    settings->overLoading.delay = constParam_t::realVal(m_constVal.overLoadingProtect_delay);

    settings->negativeSequenceOverCurProtect.castIn = castBack_t::isCast(m_castback.negativeSequenceOverCurProtect);
    settings->negativeSequenceOverCurProtect.cur = constParam_t::realVal(m_constVal.negativeSequenceOverCurProtect_cur);
    settings->negativeSequenceOverCurProtect.delay = constParam_t::realVal(m_constVal.negativeSequenceOverCurProtect_delay);

    settings->zeroSequenceOverCurProtect.castIn = castBack_t::isCast(m_castback.zeroSequenceOverCurProtect);
    settings->zeroSequenceOverCurProtect.cur = constParam_t::realVal(m_constVal.zeroSequenceOverCurProtect_cur);
    settings->zeroSequenceOverCurProtect.delay = constParam_t::realVal(m_constVal.zeroSequenceOverCurProtect_delay);

    settings->overVolProtect.castIn = castBack_t::isCast(m_castback.overVolProtect);
    settings->overVolProtect.vol = constParam_t::realVal(m_constVal.overVolProtect_vol);
    settings->overVolProtect.delay = constParam_t::realVal(m_constVal.overVolProtect_delay);

    settings->lowVolProtect.castIn = castBack_t::isCast(m_castback.lowVolProtect);
    settings->lowVolProtect.vol = constParam_t::realVal(m_constVal.lowVolProtect_vol);
    settings->lowVolProtect.delay = constParam_t::realVal(m_constVal.lowVolProtect_delay);

    settings->lostVolProtect.castIn = castBack_t::isCast(m_castback.lostVolProtect);
    settings->lostVolProtect.vol = constParam_t::realVal(m_constVal.lostVolProtect_vol);
    settings->lostVolProtect.delay = constParam_t::realVal(m_constVal.lostVolProtect_delay);

    settings->negativeSequenceOverVolProtect.castIn = castBack_t::isCast(m_castback.negativeSequenceOverVolProtect);
    settings->negativeSequenceOverVolProtect.vol = constParam_t::realVal(m_constVal.negativeSequenceOverVolProtect_vol);
    settings->negativeSequenceOverVolProtect.delay = constParam_t::realVal(m_constVal.negativeSequenceOverVolProtect_delay);

    settings->zeroSequenceOverVolProtect.castIn = castBack_t::isCast(m_castback.zeroSequenceOverVolProtect);
    settings->zeroSequenceOverVolProtect.vol = constParam_t::realVal(m_constVal.zeroSequenceOverVolProtect_vol);
    settings->zeroSequenceOverVolProtect.delay = constParam_t::realVal(m_constVal.zeroSequenceOverVolProtect_delay);

    settings->compoundVolOverCur.castIn = castBack_t::isCast(m_castback.compoundVolOverCur);
    settings->compoundVolOverCur.cur = constParam_t::realVal(m_constVal.compoundVolOverCur_cur);
    settings->compoundVolOverCur.delay = constParam_t::realVal(m_constVal.compoundVolOverCur_delay);
    settings->compoundVolOverCur.lowVolBlockingCastIn = castBack_t::isCast(m_castback.compoundVolOverCur_lowVolBlocking);
    settings->compoundVolOverCur.lowVolBlockingVol = constParam_t::realVal(m_constVal.compoundVolOverCur_lowVolBlockingVal);
    settings->compoundVolOverCur.negativeSequenceVolBlockingCastIn = castBack_t::isCast(m_castback.compoundVolOverCur_negativeSequenceVolBlocking);
    settings->compoundVolOverCur.negativeSequenceVol = constParam_t::realVal(m_constVal.compoundVolOverCur_negativeSequenceVol);

    settings->automaticBusTransfer.castIn = castBack_t::isCast(m_castback.automaticBusTransfer);

    settings->automaticBusTransfer.castIn = castBack_t::isCast(m_castback.automaticBusTransfer);
    settings->automaticBusTransfer.vol = constParam_t::realVal(m_constVal.automaticBusTransfer_vol);
    settings->automaticBusTransfer.delay = constParam_t::realVal(m_constVal.automaticBusTransfer_delay);
    settings->automaticBusTransfer.method = castBack_t::isCast(m_castback.automaticBusTransfer_method);

    settings->overHeatingProtect.castIn = castBack_t::isCast(m_castback.overHeatingProtect);
    settings->overHeatingProtect.cur = constParam_t::realVal(m_constVal.overHeatingProtect_cur);
    settings->overHeatingProtect.delay = constParam_t::realVal(m_constVal.overHeatingProtect_delay);
    settings->overHeatingProtect.factor = m_constVal.overHeatingProtect_negaitveSquenceFactor/100;

    settings->reversePowerProtect.castIn = castBack_t::isCast(m_castback.reversePowerProtect);
    settings->reversePowerProtect.power = constParam_t::realVal(m_constVal.reversePowerProtect_power);
    settings->reversePowerProtect.delay = constParam_t::realVal(m_constVal.reversePowerProtect_delay);

    settings->IxOverCurProtect.castIn = castBack_t::isCast(m_castback.IxOverCurProtect);
    settings->IxOverCurProtect.cur = constParam_t::realVal(m_constVal.IxOverCurProtect_cur);
    settings->IxOverCurProtect.delay = constParam_t::realVal(m_constVal.IxOverCurProtect_delay);
    settings->IxOverCurProtect.antiTimeCastIn = castBack_t::isCast(m_castback.IxOverCurProtect_antiTime);
    settings->IxOverCurProtect.antiTimeMethod = m_constVal.IxOverCurProtect_antiTimeMethod/100;

    settings->motorProtect.castIn = castBack_t::isCast(m_castback.motorProtect);
    settings->motorProtect.startTimeTooLongCastIn = castBack_t::isCast(m_castback.motorProtect_startTimeTooLong);
    settings->motorProtect.startTime = constParam_t::realVal(m_constVal.motorProtect_startTime);
    settings->motorProtect.cur = constParam_t::realVal(m_constVal.motorProtect_rateCur);
    settings->motorProtect.factor = m_constVal.motorProtect_curFactor/100;

    settings->nonElectricalProtect.castIn = castBack_t::isCast(m_castback.nonElectricalProtect);
    settings->nonElectricalProtect.lightGasCastIn = castBack_t::isCast(m_castback.nonElectricalProtect_lightGas);
    settings->nonElectricalProtect.heavyGasCastIn = castBack_t::isCast(m_castback.nonElectricalProtect_heavyGas);
    settings->nonElectricalProtect.oilOverTempCastIn = castBack_t::isCast(m_castback.nonElectricalProtect_oilOverTemp);
    settings->nonElectricalProtect.oilHighTempCastIn = castBack_t::isCast(m_castback.nonElectricalProtect_oilOverTemp);

    settings->PTBreakWire.castIn = castBack_t::isCast(m_castback.PTBreakWire);

    settings->CTBreakWire.castIn = castBack_t::isCast(m_castback.CTBreakWire);

    settings->reserved[0].castIn = castBack_t::isCast(m_castback.reserved[0]);
    settings->reserved[1].castIn = castBack_t::isCast(m_castback.reserved[1]);

    settings->faultRecord.castIn = castBack_t::isCast(m_castback.faultRecord);

    settings->controlLoopBreakWire.castIn = castBack_t::isCast(m_castback.controlLoopBreakWire);

    return rc;
}

bool CCP6000CastbackConstantValuesSettings::setConstValSettings(const CP6000CastBackConstValue_t& settings)
{
    m_castback.curQuickBreak = castBack_t::realReg(settings.curQuickBreak.castIn);
    m_constVal.curQuickBreak_cur = constParam_t::realReg(settings.curQuickBreak.cur);
    m_constVal.curQuickBreak_delay = constParam_t::realReg(settings.curQuickBreak.delay);
    m_castback.curQuickBreak_lowVolBlocking = castBack_t::realReg(settings.curQuickBreak.lowVolBlockingCastIn);
    m_constVal.curQuickBreak_lowVolBlockingVal = constParam_t::realReg(settings.curQuickBreak.lowVolBlockingVol);
    m_castback.curQuickBreak_dirBlocking = castBack_t::realReg(settings.curQuickBreak.dirBlockingCastIn);

    m_castback.timeLimitQuickBreak = castBack_t::realReg(settings.timeLimitQuickBreak.castIn);
    m_constVal.timeLimitQuickBreak_cur = constParam_t::realReg(settings.timeLimitQuickBreak.cur);
    m_constVal.timeLimitQuickBreak_delay = constParam_t::realReg(settings.timeLimitQuickBreak.delay);
    m_castback.timeLimitQuickBreak_lowVolBlocking = castBack_t::realReg(settings.timeLimitQuickBreak.lowVolBlockingCastIn);
    m_constVal.timeLimitQuickBreak_lowVolBlockingVal = constParam_t::realReg(settings.timeLimitQuickBreak.lowVolBlockingVol);
    m_castback.timeLimitQuickBreak_dirBlocking = castBack_t::realReg(settings.timeLimitQuickBreak.dirBlockingCastIn);

    m_castback.overCurProtect = castBack_t::realReg(settings.overCurProtect.castIn);
    m_constVal.overCurProtect_cur = constParam_t::realReg(settings.overCurProtect.cur);
    m_constVal.overCurProtect_delay = constParam_t::realReg(settings.overCurProtect.delay );
    m_castback.overCurProtect_lowVolBlocking = castBack_t::realReg(settings.overCurProtect.lowVolBlockingCastIn );
    m_constVal.overCurProtect_lowVolBlockingVal = constParam_t::realReg(settings.overCurProtect.lowVolBlockingVol );
    m_castback.overCurProtect_dirBlocking = castBack_t::realReg(settings.overCurProtect.dirBlockingCastIn );
    m_castback.overCurProtect_antiTime = castBack_t::realReg(settings.overCurProtect.antiTimeCastIn );
    m_constVal.overCurProtect_antiTimeMethod = settings.overCurProtect.antiTimeMethod*100;

    m_castback.reclose = castBack_t::realReg(settings.reclose.castIn );
    m_constVal.reclose_delay = constParam_t::realReg(settings.reclose.delay );
    m_castback.reclose_secondSectionACC = castBack_t::realReg(settings.reclose.secondSectionAccCastIn );
    m_castback.reclose_threeSectionACC = castBack_t::realReg(settings.reclose.threeSectionAccCastIn );
    m_constVal.reclose_accDelay = constParam_t::realReg(settings.reclose.accDelay);
    m_castback.reclose_noVol = castBack_t::realReg(settings.reclose.noVolCastIn);
    m_castback.reclose_sync = castBack_t::realReg(settings.reclose.syncCastIn);
    m_constVal.reclose_allowClosingAngle = constParam_t::realReg(settings.reclose.allowClosingAngle);

    m_castback.lowFreqDeloading = castBack_t::realReg(settings.lowFreqDeloading.castIn);
    m_constVal.lowFreqDeloading_freq = constParam_t::realReg(settings.lowFreqDeloading.freq);
    m_constVal.lowFreqDeloading_delay = constParam_t::realReg(settings.lowFreqDeloading.delay);
    m_castback.lowFreqDeloading_slipBlocking = castBack_t::realReg(settings.lowFreqDeloading.slipBlockingCastIn );
    m_constVal.lowFreqDeloading_diffBlockingVal = constParam_t::realReg(settings.lowFreqDeloading.diffBlockingVal );
    m_constVal.lowFreqDeloading_reserve = constParam_t::realReg(settings.lowFreqDeloading.reserved );

    m_castback.lowFreqSplitting = castBack_t::realReg(settings.lowFreqSplitting.castIn);
    m_constVal.lowFreqSplitting_freq = constParam_t::realReg(settings.lowFreqSplitting.freq);
    m_constVal.lowFreqSplitting_delay = constParam_t::realReg(settings.lowFreqSplitting.delay);

    m_castback.lowVolSplitting = castBack_t::realReg(settings.lowVolSplitting.castIn);
    m_constVal.lowVolSplitting_vol = constParam_t::realReg(settings.lowVolSplitting.vol);
    m_constVal.lowVolSplitting_delay = constParam_t::realReg(settings.lowVolSplitting.delay);

    m_castback.smallCurGround = castBack_t::realReg(settings.smallCurGround.castIn);
    m_constVal.smallCurGround_zeroSequenceCur = constParam_t::realReg(settings.smallCurGround.cur);
    m_constVal.smallCurGround_zeroSequenceVol = constParam_t::realReg(settings.smallCurGround.vol);
    m_constVal.smallCurGround_delay = constParam_t::realReg(settings.smallCurGround.delay);
    m_castback.smallCurGround_dirBlocking = castBack_t::realReg(settings.smallCurGround.dirBlockingCastIn);

    m_castback.overLoadingProtect = castBack_t::realReg(settings.overLoading.castIn);
    m_constVal.overLoadingProtect_cur = constParam_t::realReg(settings.overLoading.cur);
    m_constVal.overLoadingProtect_delay = constParam_t::realReg(settings.overLoading.delay);

    m_castback.negativeSequenceOverCurProtect = castBack_t::realReg(settings.negativeSequenceOverCurProtect.castIn);
    m_constVal.negativeSequenceOverCurProtect_cur = constParam_t::realReg(settings.negativeSequenceOverCurProtect.cur);
    m_constVal.negativeSequenceOverCurProtect_delay = constParam_t::realReg(settings.negativeSequenceOverCurProtect.delay);

    m_castback.zeroSequenceOverCurProtect = castBack_t::realReg(settings.zeroSequenceOverCurProtect.castIn);
    m_constVal.zeroSequenceOverCurProtect_cur = constParam_t::realReg(settings.zeroSequenceOverCurProtect.cur);
    m_constVal.zeroSequenceOverCurProtect_delay = constParam_t::realReg(settings.zeroSequenceOverCurProtect.delay);

    m_castback.overVolProtect = castBack_t::realReg(settings.overVolProtect.castIn);
    m_constVal.overVolProtect_vol = constParam_t::realReg(settings.overVolProtect.vol);
    m_constVal.overVolProtect_delay = constParam_t::realReg(settings.overVolProtect.delay);

    m_castback.lowVolProtect = castBack_t::realReg(settings.lowVolProtect.castIn);
    m_constVal.lowVolProtect_vol = constParam_t::realReg(settings.lowVolProtect.vol);
    m_constVal.lowVolProtect_delay = constParam_t::realReg(settings.lowVolProtect.delay);

    m_castback.lostVolProtect = castBack_t::realReg(settings.lostVolProtect.castIn);
    m_constVal.lostVolProtect_vol = constParam_t::realReg(settings.lostVolProtect.vol);
    m_constVal.lostVolProtect_delay = constParam_t::realReg(settings.lostVolProtect.delay);

    m_castback.negativeSequenceOverVolProtect = castBack_t::realReg(settings.negativeSequenceOverVolProtect.castIn);
    m_constVal.negativeSequenceOverVolProtect_vol = constParam_t::realReg(settings.negativeSequenceOverVolProtect.vol);
    m_constVal.negativeSequenceOverVolProtect_delay = constParam_t::realReg(settings.negativeSequenceOverVolProtect.delay);

    m_castback.zeroSequenceOverVolProtect = castBack_t::realReg(settings.zeroSequenceOverVolProtect.castIn);
    m_constVal.zeroSequenceOverVolProtect_vol = constParam_t::realReg(settings.zeroSequenceOverVolProtect.vol);
    m_constVal.zeroSequenceOverVolProtect_delay = constParam_t::realReg(settings.zeroSequenceOverVolProtect.delay);

    m_castback.compoundVolOverCur = castBack_t::realReg(settings.compoundVolOverCur.castIn);
    m_constVal.compoundVolOverCur_cur = constParam_t::realReg(settings.compoundVolOverCur.cur);
    m_constVal.compoundVolOverCur_delay = constParam_t::realReg(settings.compoundVolOverCur.delay);
    m_castback.compoundVolOverCur_lowVolBlocking = castBack_t::realReg(settings.compoundVolOverCur.lowVolBlockingCastIn);
    m_constVal.compoundVolOverCur_lowVolBlockingVal = constParam_t::realReg(settings.compoundVolOverCur.lowVolBlockingVol);
    m_castback.compoundVolOverCur_negativeSequenceVolBlocking = castBack_t::realReg(settings.compoundVolOverCur.negativeSequenceVolBlockingCastIn);
    m_constVal.compoundVolOverCur_negativeSequenceVol = constParam_t::realReg(settings.compoundVolOverCur.negativeSequenceVol);

    m_castback.automaticBusTransfer = castBack_t::realReg(settings.automaticBusTransfer.castIn);
    m_constVal.automaticBusTransfer_vol = constParam_t::realReg(settings.automaticBusTransfer.vol);
    m_constVal.automaticBusTransfer_delay = constParam_t::realReg(settings.automaticBusTransfer.delay);
    m_castback.automaticBusTransfer_method = castBack_t::realReg(settings.automaticBusTransfer.method);

    m_castback.overHeatingProtect = castBack_t::realReg(settings.overHeatingProtect.castIn);
    m_constVal.overHeatingProtect_cur = constParam_t::realReg(settings.overHeatingProtect.cur);
    m_constVal.overHeatingProtect_delay = constParam_t::realReg(settings.overHeatingProtect.delay);
    m_constVal.overHeatingProtect_negaitveSquenceFactor = settings.overHeatingProtect.factor; 

    m_castback.reversePowerProtect = castBack_t::realReg(settings.reversePowerProtect.castIn);
    m_constVal.reversePowerProtect_power = constParam_t::realReg(settings.reversePowerProtect.power);
    m_constVal.reversePowerProtect_delay = constParam_t::realReg(settings.reversePowerProtect.delay);

    m_castback.IxOverCurProtect = castBack_t::realReg(settings.IxOverCurProtect.castIn);
    m_constVal.IxOverCurProtect_cur = constParam_t::realReg(settings.IxOverCurProtect.cur);
    m_constVal.IxOverCurProtect_delay = constParam_t::realReg(settings.IxOverCurProtect.delay);
    m_castback.IxOverCurProtect_antiTime = castBack_t::realReg(settings.IxOverCurProtect.antiTimeCastIn);
    m_constVal.IxOverCurProtect_antiTimeMethod = settings.IxOverCurProtect.antiTimeMethod*100; 

    m_castback.motorProtect = castBack_t::realReg(settings.motorProtect.castIn);
    m_castback.motorProtect_startTimeTooLong = castBack_t::realReg(settings.motorProtect.startTimeTooLongCastIn);
    m_constVal.motorProtect_startTime = constParam_t::realReg(settings.motorProtect.startTime);
    m_constVal.motorProtect_rateCur = constParam_t::realReg(settings.motorProtect.cur);
    m_constVal.motorProtect_curFactor = settings.motorProtect.factor*100;

    m_castback.nonElectricalProtect = castBack_t::realReg(settings.nonElectricalProtect.castIn);
    m_castback.nonElectricalProtect_lightGas = castBack_t::realReg(settings.nonElectricalProtect.lightGasCastIn);
    m_castback.nonElectricalProtect_heavyGas = castBack_t::realReg(settings.nonElectricalProtect.heavyGasCastIn);
    m_castback.nonElectricalProtect_oilOverTemp = castBack_t::realReg(settings.nonElectricalProtect.oilOverTempCastIn);
    m_castback.nonElectricalProtect_oilOverTemp = castBack_t::realReg(settings.nonElectricalProtect.oilHighTempCastIn);

    m_castback.PTBreakWire = castBack_t::realReg(settings.PTBreakWire.castIn);

    m_castback.CTBreakWire = castBack_t::realReg(settings.CTBreakWire.castIn);

    m_castback.reserved[0] = castBack_t::realReg(settings.reserved[0].castIn);
    m_castback.reserved[1] = castBack_t::realReg(settings.reserved[1].castIn);

    m_castback.faultRecord = castBack_t::realReg(settings.faultRecord.castIn);

    m_castback.controlLoopBreakWire = castBack_t::realReg(settings.controlLoopBreakWire.castIn);

    CModbusDevMgr::SetCP6000Castback(&m_castback);

    for(volatile int i = 0; i < 0x2000; i++) {
        for(volatile int j = 0; j < 0x4000; j++);
    }

    return (/*CModbusDevMgr::SetCP6000Castback(&m_castback) && */CModbusDevMgr::SetCP6000ConstVal(&m_constVal));
}