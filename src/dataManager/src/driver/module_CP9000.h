#pragma once
#include "module.h"
#include "CP9000Reg.h"

namespace Dev_CP9000 {

    /************************************************************************/
    /* ������ʾ                                                             */
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
    /* ������ʾ                                                             */
    /************************************************************************/
    struct DI_t {
        quint16 di[CP9000_MAX_DI_NUM];
    };
    class CDIConv {
    public:

    };

    /************************************************************************/
    /* ��ֵ                                                                 */
    /************************************************************************/
    struct constParam_t {
        quint16 ctrlWord[2];                        //������1��2
        quint16 curConstVal[3];                     //����1��2��3�ζ�ֵ
        quint16 curConstTime[3];                    //����1��2��3��ʱ��
        quint16 zeroSequenceCurConstValue[3];       //����1��2��3�ζ�ֵ
        quint16 zeroSequenceCurTime[3];
        quint16 curAccConstValue;                   //Acc-> Accelerated  ���ٶ�ֵ
        quint16 curAccTime;
        quint16 zeroSequenceCurAccConstValue;       //������ٶ�ֵ
        quint16 zeroSequenceCurAccTime;             //�������ʱ��
        quint16 compoundPressureLockingVol;         //��ѹ������ѹ
        quint16 curAntiTimeReference;               //������ʱ��׼
        quint16 curAntiTime;                        //������ʱʱ��

        quint16 zeroSequenceCurAntiTimeReference;   //����ʱ��׼
        quint16 zeroSequenceCurAntiTime;            //����ʱʱ��
        quint16 overloadCur;                        //�����ɵ���
        quint16 overloadWarningTime;                //�����ɸ澯ʱ��
        quint16 overloadTripTime;                   //��������բʱ��
        quint16 recloseSynchroCheckConstVal;        //�غ�բ��ͬ�ڶ�ֵ
        quint16 recloseTime;                        //�غ�բʱ��
        quint16 lowCycleComponentFreq;              //����Ԫ��Ƶ��
        quint16 lowCycleComponentTime;              //����Ԫ��ʱ��
        quint16 lowCycleLockVol;                    //���ܱ�����ѹ
        quint16 lowCycleLockSlip;                   //���ܱ�������
        quint16 lowVolComponentVol;                 //��ѹԪ����ѹ
        quint16 lowVolComponentTime;                //��ѹԪ��ʱ��
        quint16 lowVolLockSlip;                     //��ѹԪ������
        quint16 freqDiffLockConstVal;               //Ƶ�������ֵ
        quint16 quasiSameVolLock;                   //׼ͬѹ�����
        quint16 quasiSynchroAccLock;                //׼ͬ�ڼ��ٱ���
        quint16 closingPhaseTime;                   //��բ��ǰʱ��
        quint16 phaseAngleConstVal;                 //��ǰ�Ƕȶ�ֵ

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
    /* ѹ��Ͷ��                                                             */
    /************************************************************************/
    struct castBack_t {
        quint16 plateStatus;
    };

};






