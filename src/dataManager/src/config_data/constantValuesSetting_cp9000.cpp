#include "constantValuesSetting_cp9000.h"
#include "../driver/DevAttrMgr.h"

#include "debug.h"

CConstValuesSetting::CConstValuesSetting(void)
{
    loadConstValLimit();
}

CConstValuesSetting::~CConstValuesSetting(void)
{
}


CConstValuesSetting* CConstValuesSetting::getInstance()
{
    static CConstValuesSetting s_Cfg;

    return &s_Cfg;
}


bool CConstValuesSetting::constValSettings(ConstValueSettings* settings, bool update)
{
    if(!settings) {
        return false;
    }

    bool rc = true;
    if (update) {
        rc = loadConstValSettings();
    }

    memcpy(settings, &m_settings, sizeof(ConstValueSettings));

    return rc;
}

bool CConstValuesSetting::setConstValSettings(const ConstValueSettings& settings)
{
    memcpy(&m_settings, &settings, sizeof(ConstValueSettings));
    return saveConstValSettings();
}

bool CConstValuesSetting::loadConstValSettings()
{
    Dev_CP9000::constParam_t cp;
    if (CModbusDevMgr::GetCP9000ConstVal(&cp))
    {
        m_settings.nCtrlWord[0] = Dev_CP9000::constParam_t::realCtrlWord(cp.ctrlWord[0]);
        m_settings.nCtrlWord[1] = Dev_CP9000::constParam_t::realCtrlWord(cp.ctrlWord[1]);
        for(int i = 0; i < 3; i++)
            m_settings.fCurConstValue[i] = Dev_CP9000::constParam_t::realCur(cp.curConstVal[i]);
        for(int i = 0; i < 3; i++)
            m_settings.fCurConstTime[i] = Dev_CP9000::constParam_t::realTime(cp.curConstTime[i]);
        for(int i = 0; i < 3; i++)
            m_settings.fZeroSequenceCurConstValue[i] = Dev_CP9000::constParam_t::realCur(cp.zeroSequenceCurConstValue[i]);
        for(int i = 0; i < 3; i++) 
            m_settings.fZeroSequenceCurTime[i] = Dev_CP9000::constParam_t::realTime(cp.zeroSequenceCurTime[i]);
        m_settings.fCurAccConstValue = Dev_CP9000::constParam_t::realCur(cp.curAccConstValue);
        m_settings.fCurAccTime = Dev_CP9000::constParam_t::realTime(cp.curAccTime);
        m_settings.fZeroSequenceCurAccConstValue = Dev_CP9000::constParam_t::realCur(cp.zeroSequenceCurAccConstValue);
        m_settings.fZeroSequenceCurAccTime = Dev_CP9000::constParam_t::realTime(cp.zeroSequenceCurAccTime);
        m_settings.fCompoundPressureLockingVol = Dev_CP9000::constParam_t::realVol(cp.compoundPressureLockingVol);
        m_settings.fCurAntiTimeReference = Dev_CP9000::constParam_t::realCur(cp.curAntiTimeReference);
        m_settings.fCurAntiTime = Dev_CP9000::constParam_t::realTime(cp.curAntiTime);

        m_settings.fZeroSequenceCurAntiTimeReference = Dev_CP9000::constParam_t::realCur(cp.zeroSequenceCurAntiTimeReference);
        m_settings.fZeroSequenceCurAntiTime = Dev_CP9000::constParam_t::realTime(cp.zeroSequenceCurAntiTime);
        m_settings.fOverloadCur = Dev_CP9000::constParam_t::realCur(cp.overloadCur);
        m_settings.fOverloadWarningTime = Dev_CP9000::constParam_t::realOverloadTime(cp.overloadWarningTime);
        m_settings.fOverloadTripTime = Dev_CP9000::constParam_t::realOverloadTime(cp.overloadTripTime);
        m_settings.fRecloseSynchroCheckConstVal = Dev_CP9000::constParam_t::regAngle(cp.recloseSynchroCheckConstVal);
        m_settings.fRecloseTime = Dev_CP9000::constParam_t::realTime(cp.recloseTime);
        m_settings.fLowCycleComponentFreq = Dev_CP9000::constParam_t::realFreq(cp.lowCycleComponentFreq);
        m_settings.fLowCycleComponentTime = Dev_CP9000::constParam_t::realTime(cp.lowCycleComponentTime);
        m_settings.fLowCycleLockVol = Dev_CP9000::constParam_t::realVol(cp.lowCycleLockVol);
        m_settings.fLowCycleLockSlip = Dev_CP9000::constParam_t::realLowCycleLockSlip(cp.lowCycleLockSlip);
        m_settings.fLowVolComponentVol = Dev_CP9000::constParam_t::realVol(cp.lowVolComponentVol);
        m_settings.fLowVolComponentTime = Dev_CP9000::constParam_t::realTime(cp.lowVolComponentTime);
        m_settings.fLowVolLockSlip = Dev_CP9000::constParam_t::realLowVolLockSlip(cp.lowVolLockSlip);
        m_settings.fFreqDiffLockConstVal = Dev_CP9000::constParam_t::realVol(cp.freqDiffLockConstVal);
        m_settings.fQuasiSameVolLock = Dev_CP9000::constParam_t::realFreq(cp.quasiSameVolLock);
        m_settings.fQuasiSynchroAccLock = Dev_CP9000::constParam_t::realQuasiSynchroAccLock(cp.quasiSynchroAccLock);
        m_settings.fClosingPhaseTime = Dev_CP9000::constParam_t::realTime(cp.closingPhaseTime);
        m_settings.fPhaseAngleConstVal = Dev_CP9000::constParam_t::regAngle(cp.phaseAngleConstVal);

        return true;
    }
    return false;
}

bool CConstValuesSetting::saveConstValSettings()
{
    Dev_CP9000::constParam_t cp;

    cp.ctrlWord[0] = Dev_CP9000::constParam_t::regCtrlWord(m_settings.nCtrlWord[0]);
    cp.ctrlWord[1] = Dev_CP9000::constParam_t::regCtrlWord(m_settings.nCtrlWord[1]);
    for(int i = 0; i < 3; i++)
        cp.curConstVal[i] = Dev_CP9000::constParam_t::regCur(m_settings.fCurConstValue[i]);
    for(int i = 0; i < 3; i++)
        cp.curConstTime[i] = Dev_CP9000::constParam_t::regTime(m_settings.fCurConstTime[i]);
    for(int i = 0; i < 3; i++)
        cp.zeroSequenceCurConstValue[i] = Dev_CP9000::constParam_t::regCur(m_settings.fZeroSequenceCurConstValue[i]);
    for(int i = 0; i < 3; i++) 
        cp.zeroSequenceCurTime[i] = Dev_CP9000::constParam_t::regTime(m_settings.fZeroSequenceCurTime[i]);
    cp.curAccConstValue = Dev_CP9000::constParam_t::regCur(m_settings.fCurAccConstValue);
    cp.curAccTime = Dev_CP9000::constParam_t::regTime(m_settings.fCurAccTime);
    cp.zeroSequenceCurAccConstValue = Dev_CP9000::constParam_t::regCur(m_settings.fZeroSequenceCurAccConstValue);
    cp.zeroSequenceCurAccTime = Dev_CP9000::constParam_t::regTime(m_settings.fZeroSequenceCurAccTime);
    cp.compoundPressureLockingVol = Dev_CP9000::constParam_t::regVol(m_settings.fCompoundPressureLockingVol);
    cp.curAntiTimeReference = Dev_CP9000::constParam_t::regCur(m_settings.fCurAntiTimeReference);
    cp.curAntiTime = Dev_CP9000::constParam_t::regTime(m_settings.fCurAntiTime);

    cp.zeroSequenceCurAntiTimeReference = Dev_CP9000::constParam_t::regCur(m_settings.fZeroSequenceCurAntiTimeReference);
    cp.zeroSequenceCurAntiTime = Dev_CP9000::constParam_t::regTime(m_settings.fZeroSequenceCurAntiTime);
    cp.overloadCur = Dev_CP9000::constParam_t::regCur(m_settings.fOverloadCur);
    cp.overloadWarningTime = Dev_CP9000::constParam_t::regOverloadTime(m_settings.fOverloadWarningTime);
    cp.overloadTripTime = Dev_CP9000::constParam_t::regOverloadTime(m_settings.fOverloadTripTime);
    cp.recloseSynchroCheckConstVal = Dev_CP9000::constParam_t::regAngle(m_settings.fRecloseSynchroCheckConstVal);
    cp.recloseTime = Dev_CP9000::constParam_t::regTime(m_settings.fRecloseTime);
    cp.lowCycleComponentFreq = Dev_CP9000::constParam_t::regFreq(m_settings.fLowCycleComponentFreq);
    cp.lowCycleComponentTime = Dev_CP9000::constParam_t::regTime(m_settings.fLowCycleComponentTime);
    cp.lowCycleLockVol = Dev_CP9000::constParam_t::regVol(m_settings.fLowCycleLockVol);
    cp.lowCycleLockSlip = Dev_CP9000::constParam_t::regLowCycleLockSlip(m_settings.fLowCycleLockSlip);
    cp.lowVolComponentVol = Dev_CP9000::constParam_t::regVol(m_settings.fLowVolComponentVol);
    cp.lowVolComponentTime = Dev_CP9000::constParam_t::regTime(m_settings.fLowVolComponentTime);
    cp.lowVolLockSlip = Dev_CP9000::constParam_t::regLowVolLockSlip(m_settings.fLowVolLockSlip);
    cp.freqDiffLockConstVal = Dev_CP9000::constParam_t::regVol(m_settings.fFreqDiffLockConstVal);
    cp.quasiSameVolLock = Dev_CP9000::constParam_t::regFreq(m_settings.fQuasiSameVolLock);
    cp.quasiSynchroAccLock = Dev_CP9000::constParam_t::regQuasiSynchroAccLock(m_settings.fQuasiSynchroAccLock);
    cp.closingPhaseTime = Dev_CP9000::constParam_t::regTime(m_settings.fClosingPhaseTime);
    cp.phaseAngleConstVal = Dev_CP9000::constParam_t::regAngle(m_settings.fPhaseAngleConstVal);

    return (CModbusDevMgr::SetCP9000ConstVal(&cp) ? true : false);
}

bool CConstValuesSetting::loadConstValLimit(void)
{
    qDebug() << "CConstValuesSetting::loadConstValLimit  no object";

    m_limit.tCurConstValue[0].min = 0.20;
    m_limit.tCurConstValue[0].max = 100.00;
    m_limit.tCurConstValue[1].min = 0.20;
    m_limit.tCurConstValue[1].max = 100.00;
    m_limit.tCurConstValue[2].min = 0.20;
    m_limit.tCurConstValue[2].max = 100.00;

    m_limit.tCurConstTime[0].min = 0.000;
    m_limit.tCurConstTime[0].max = 5.000;
    m_limit.tCurConstTime[1].min = 0.100;
    m_limit.tCurConstTime[1].max = 20.000;
    m_limit.tCurConstTime[2].min = 0.100;
    m_limit.tCurConstTime[2].max = 20.000;

    m_limit.tZeroSequenceCurConstValue[0].min = 0.10;
    m_limit.tZeroSequenceCurConstValue[0].max = 20.00;
    m_limit.tZeroSequenceCurConstValue[1].min = 0.10;
    m_limit.tZeroSequenceCurConstValue[1].max = 20.00;
    m_limit.tZeroSequenceCurConstValue[2].min = 0.10;
    m_limit.tZeroSequenceCurConstValue[2].max = 20.00;

    m_limit.tZeroSequenceCurTime[0].min = 0.000;
    m_limit.tZeroSequenceCurTime[0].max = 5.000;
    m_limit.tZeroSequenceCurTime[1].min = 0.100;
    m_limit.tZeroSequenceCurTime[1].max = 20.000;
    m_limit.tZeroSequenceCurTime[2].min = 0.100;
    m_limit.tZeroSequenceCurTime[2].max = 20.000;

    m_limit.tCurAccConstValue.min = 0.20;
    m_limit.tCurAccConstValue.max = 100.00;
    m_limit.tCurAccTime.min = 0.000;
    m_limit.tCurAccTime.max = 5.000;
    m_limit.tZeroSequenceCurAccConstValue.min = 0.10;
    m_limit.tZeroSequenceCurAccConstValue.max = 20.00;
    m_limit.tZeroSequenceCurAccTime.min = 0.100;
    m_limit.tZeroSequenceCurAccTime.max = 5.000;

    m_limit.tCompoundPressureLockingVol.min = 1.00;
    m_limit.tCompoundPressureLockingVol.max = 120.00;
    m_limit.tCurAntiTimeReference.min = 0.200;
    m_limit.tCurAntiTimeReference.max = 100.000;


    m_limit.tCurAntiTime.min = 0.005;
    m_limit.tCurAntiTime.max = 127.000;

    m_limit.tZeroSequenceCurAntiTimeReference.min = 0.100;
    m_limit.tZeroSequenceCurAntiTimeReference.max = 20.00;
    m_limit.tZeroSequenceCurAntiTime.min = 0.005;
    m_limit.tZeroSequenceCurAntiTime.max = 127.000;

    m_limit.tOverloadCur.min = 0.20;
    m_limit.tOverloadCur.max = 100.00;
    m_limit.tOverloadWarningTime.min = 6;
    m_limit.tOverloadWarningTime.max = 9000;
    m_limit.tOverloadTripTime.min = 1;
    m_limit.tOverloadTripTime.max = 9000;

    m_limit.tRecloseSynchroCheckConstVal.min = 10.00;
    m_limit.tRecloseSynchroCheckConstVal.max = 50.00;
    m_limit.tRecloseTime.min = 0.200;
    m_limit.tRecloseTime.max = 20.000;

    m_limit.tLowCycleComponentFreq.min = 45.00;
    m_limit.tLowCycleComponentFreq.max = 49.50;
    m_limit.tLowCycleComponentTime.min = 0.100;
    m_limit.tLowCycleComponentTime.max = 20.000;
    m_limit.tLowCycleLockVol.min = 10.00;
    m_limit.tLowCycleLockVol.max = 120.00;
    m_limit.tLowCycleLockSlip.min = 0.50;
    m_limit.tLowCycleLockSlip.max = 20.00;

    m_limit.tLowVolComponentVol.min = 20.00;
    m_limit.tLowVolComponentVol.max = 60.00;
    m_limit.tLowVolComponentTime.min = 0.100;
    m_limit.tLowVolComponentTime.max = 20.000;
    m_limit.tLowVolLockSlip.min = 10.00;
    m_limit.tLowVolLockSlip.max = 60.00;

    m_limit.tFreqDiffLockConstVal.min = 0.00;
    m_limit.tFreqDiffLockConstVal.max = 20.00;
    m_limit.tQuasiSameVolLock.min = 0.000;
    m_limit.tQuasiSameVolLock.max = 2.000;
    m_limit.tQuasiSynchroAccLock.min = 0.000;
    m_limit.tQuasiSynchroAccLock.max = 5.000;

    m_limit.tClosingPhaseTime.min = 0.000;
    m_limit.tClosingPhaseTime.max = 2.000;
    m_limit.tPhaseAngleConstVal.min = 0.00;
    m_limit.tPhaseAngleConstVal.max = 90.00;

    return true;
}