#pragma once

#include "../driver/module.h"

struct ConstValueSettings
{
    quint16 nCtrlWord[2];                       //控制字1、2
    float  fCurConstValue[3];                   //电流1、2、3段定值
    float  fCurConstTime[3];                    //电流1、2、3段时间
    float  fZeroSequenceCurConstValue[3];       //零序1、2、3段定值
    float  fZeroSequenceCurTime[3];
    float  fCurAccConstValue;                   //Acc-> Accelerated  加速定值
    float  fCurAccTime;
    float  fZeroSequenceCurAccConstValue;       //零序加速定值
    float  fZeroSequenceCurAccTime;             //零序加速时间
    float  fCompoundPressureLockingVol;         //复压闭锁电压
    float  fCurAntiTimeReference;               //电流反时基准

    float  fCurAntiTime;                        //电流反时时间
    float  fZeroSequenceCurAntiTimeReference;   //零序反时基准
    float  fZeroSequenceCurAntiTime;            //零序反时时间
    float  fOverloadCur;                        //过负荷电流
    float  fOverloadWarningTime;                //过负荷告警时间
    float  fOverloadTripTime;                   //过负荷跳闸时间
    float  fRecloseSynchroCheckConstVal;        //重合闸检同期定值
    float  fRecloseTime;                        //重合闸时间
    float  fLowCycleComponentFreq;              //低周元件频率
    float  fLowCycleComponentTime;              //低周元件时间
    float  fLowCycleLockVol;                    //低周闭锁电压
    float  fLowCycleLockSlip;                   //低周闭锁滑差
    float  fLowVolComponentVol;                 //低压元件电压
    float  fLowVolComponentTime;                //低压元件时间
    float  fLowVolLockSlip;                     //低压元件滑差
    float  fFreqDiffLockConstVal;               //频差闭锁定值
    float  fQuasiSameVolLock;                   //准同压差闭锁
    float  fQuasiSynchroAccLock;                //准同期加速闭锁
    float  fClosingPhaseTime;                   //合闸导前时间
    float  fPhaseAngleConstVal;                 //导前角度定值
};

struct SettingsLimit {
    float max;
    float min;
};

struct ConstValueLimit
{
    SettingsLimit  tCurConstValue[3];                   //电流1、2、3段定值
    SettingsLimit  tCurConstTime[3];                    //电流1、2、3段时间
    SettingsLimit  tZeroSequenceCurConstValue[3];       //零序1、2、3段定值
    SettingsLimit  tZeroSequenceCurTime[3];
    SettingsLimit  tCurAccConstValue;                   //Acc-> Accelerated  加速定值
    SettingsLimit  tCurAccTime;
    SettingsLimit  tZeroSequenceCurAccConstValue;       //零序加速定值
    SettingsLimit  tZeroSequenceCurAccTime;             //零序加速时间
    SettingsLimit  tCompoundPressureLockingVol;         //复压闭锁电压
    SettingsLimit  tCurAntiTimeReference;               //电流反时基准

    SettingsLimit  tCurAntiTime;                        //电流反时时间
    SettingsLimit  tZeroSequenceCurAntiTimeReference;   //零序反时基准
    SettingsLimit  tZeroSequenceCurAntiTime;            //零序反时时间
    SettingsLimit  tOverloadCur;                        //过负荷电流
    SettingsLimit  tOverloadWarningTime;                //过负荷告警时间
    SettingsLimit  tOverloadTripTime;                   //过负荷跳闸时间
    SettingsLimit  tRecloseSynchroCheckConstVal;        //重合闸检同期定值
    SettingsLimit  tRecloseTime;                        //重合闸时间
    SettingsLimit  tLowCycleComponentFreq;              //低周元件频率
    SettingsLimit  tLowCycleComponentTime;              //低周元件时间
    SettingsLimit  tLowCycleLockVol;                    //低周闭锁电压
    SettingsLimit  tLowCycleLockSlip;                   //低周闭锁滑差
    SettingsLimit  tLowVolComponentVol;                 //低压元件电压
    SettingsLimit  tLowVolComponentTime;                //低压元件时间
    SettingsLimit  tLowVolLockSlip;                     //低压元件滑差
    SettingsLimit  tFreqDiffLockConstVal;               //频差闭锁定值
    SettingsLimit  tQuasiSameVolLock;                   //准同压差闭锁
    SettingsLimit  tQuasiSynchroAccLock;                //准同期加速闭锁
    SettingsLimit  tClosingPhaseTime;                   //合闸导前时间
    SettingsLimit  tPhaseAngleConstVal;                 //导前角度定值
};

class CConstValuesSetting
{
protected:
    CConstValuesSetting(void);
    virtual ~CConstValuesSetting(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CConstValuesSetting* getInstance();

public:

    bool constValSettings(ConstValueSettings* settings, bool update = true);
    bool setConstValSettings(const ConstValueSettings& settings);

    const ConstValueLimit* constValLimit(void) {
        return &m_limit;
    }

private:
    bool loadConstValSettings();
    bool saveConstValSettings();
    
    bool loadConstValLimit(void);
private:
    ConstValueSettings m_settings;
    ConstValueLimit    m_limit;
};

