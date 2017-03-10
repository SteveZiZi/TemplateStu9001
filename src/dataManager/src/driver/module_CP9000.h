#pragma once
#include "module.h"
#include "CP9000Reg.h"

namespace Dev_CP9000 {

    /************************************************************************/
    /* 采样显示                                                             */
    /************************************************************************/
    struct sampleData_t {
        struct _sampleVal_t {
            quint16 rms;
            quint16 angle;
        };

        _sampleVal_t phaseVol[MAX_PHASE_NUM];
        _sampleVal_t phaseCur[MAX_PHASE_NUM];
        _sampleVal_t Uab;
        _sampleVal_t Ubc;
        _sampleVal_t Uca;
        _sampleVal_t Ux;
        _sampleVal_t zeroSequenceCur[MAX_PHASE_NUM];
        _sampleVal_t zeroSequenceVol[MAX_PHASE_NUM];

        static float realCur(quint16 reg) { return (float)((float)reg/100.0); }
        static float realVol(quint16 reg) { return (float)((float)reg/100.0); }
        static float realAngle(quint16 reg) { return (float)((float)reg/100.0); }
    };

    /************************************************************************/
    /* 开入显示                                                             */
    /************************************************************************/
    struct DI_t {
        quint16 di[CP9000_MAX_DI_NUM];
    };
    class CDIConv {
    public:

    };

    /************************************************************************/
    /* 定值                                                                 */
    /************************************************************************/
    struct constParam_t {
        quint16 ctrlWord[2];                        //控制字1、2
        quint16 curConstVal[3];                     //电流1、2、3段定值
        quint16 curConstTime[3];                    //电流1、2、3段时间
        quint16 zeroSequenceCurConstValue[3];       //零序1、2、3段定值
        quint16 zeroSequenceCurTime[3];
        quint16 curAccConstValue;                   //Acc-> Accelerated  加速定值
        quint16 curAccTime;
        quint16 zeroSequenceCurAccConstValue;       //零序加速定值
        quint16 zeroSequenceCurAccTime;             //零序加速时间
        quint16 compoundPressureLockingVol;         //复压闭锁电压
        quint16 curAntiTimeReference;               //电流反时基准
        quint16 curAntiTime;                        //电流反时时间

        quint16 zeroSequenceCurAntiTimeReference;   //零序反时基准
        quint16 zeroSequenceCurAntiTime;            //零序反时时间
        quint16 overloadCur;                        //过负荷电流
        quint16 overloadWarningTime;                //过负荷告警时间
        quint16 overloadTripTime;                   //过负荷跳闸时间
        quint16 recloseSynchroCheckConstVal;        //重合闸检同期定值
        quint16 recloseTime;                        //重合闸时间
        quint16 lowCycleComponentFreq;              //低周元件频率
        quint16 lowCycleComponentTime;              //低周元件时间
        quint16 lowCycleLockVol;                    //低周闭锁电压
        quint16 lowCycleLockSlip;                   //低周闭锁滑差
        quint16 lowVolComponentVol;                 //低压元件电压
        quint16 lowVolComponentTime;                //低压元件时间
        quint16 lowVolLockSlip;                     //低压元件滑差
        quint16 freqDiffLockConstVal;               //频差闭锁定值
        quint16 quasiSameVolLock;                   //准同压差闭锁
        quint16 quasiSynchroAccLock;                //准同期加速闭锁
        quint16 closingPhaseTime;                   //合闸导前时间
        quint16 phaseAngleConstVal;                 //导前角度定值

        static quint16 realCtrlWord(quint16 reg) {return reg;}
        static quint16 regCtrlWord(quint16 val) {return val;}
        static float realCur(quint16 reg) {return (float)((reg)/100.0);}
        static quint16 regCur(float val) {return (quint16)(val*100);}
        static float realVol(quint16 reg) {return (float)((reg)/100.0);}
        static quint16 regVol(float val) {return (quint16)(val*100);}
        static float realAngle(quint16 reg) {return (float)((reg)/100.0);}
        static quint16 regAngle(float val) {return (quint16)(val*100);}
        static float realTime(quint16 reg) {return (float)((reg)/1000.0);}
        static quint16 regTime(float val) {return (quint16)(val*1000);}
        static float realFreq(quint16 reg) {return (float)((reg)/1000.0);}
        static quint16 regFreq(float val) {return (quint16)(val*1000);}

        static float realOverloadTime(quint16 reg) {return (float)((reg));}
        static quint16 regOverloadTime(float val) {return (quint16)(val);}

        static float realLowCycleLockSlip(quint16 reg) {return (float)((reg)/100.0);}
        static quint16 regLowCycleLockSlip(float val) {return (quint16)(val*100);}
        static float realLowVolLockSlip(quint16 reg) {return (float)((reg)/100.0);}
        static quint16 regLowVolLockSlip(float val) {return (quint16)(val*100);}
        static float realQuasiSynchroAccLock(quint16 reg) {return (float)((reg)/1000.0);}
        static quint16 regQuasiSynchroAccLock(float val) {return (quint16)(val*1000);}
    };
    /************************************************************************/
    /* 压板投退                                                             */
    /************************************************************************/
    struct castBack_t {
        quint16 plateStatus;
    };

};






