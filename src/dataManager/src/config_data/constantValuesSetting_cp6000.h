#pragma once

#include "../driver/module.h"

struct ConstValueSettings
{
    quint16 nCtrlWord[2];                       //������1��2
    float  fCurConstValue[3];                   //����1��2��3�ζ�ֵ
    float  fCurConstTime[3];                    //����1��2��3��ʱ��
    float  fZeroSequenceCurConstValue[3];       //����1��2��3�ζ�ֵ
    float  fZeroSequenceCurTime[3];
    float  fCurAccConstValue;                   //Acc-> Accelerated  ���ٶ�ֵ
    float  fCurAccTime;
    float  fZeroSequenceCurAccConstValue;       //������ٶ�ֵ
    float  fZeroSequenceCurAccTime;             //�������ʱ��
    float  fCompoundPressureLockingVol;         //��ѹ������ѹ
    float  fCurAntiTimeReference;               //������ʱ��׼

    float  fCurAntiTime;                        //������ʱʱ��
    float  fZeroSequenceCurAntiTimeReference;   //����ʱ��׼
    float  fZeroSequenceCurAntiTime;            //����ʱʱ��
    float  fOverloadCur;                        //�����ɵ���
    float  fOverloadWarningTime;                //�����ɸ澯ʱ��
    float  fOverloadTripTime;                   //��������բʱ��
    float  fRecloseSynchroCheckConstVal;        //�غ�բ��ͬ�ڶ�ֵ
    float  fRecloseTime;                        //�غ�բʱ��
    float  fLowCycleComponentFreq;              //����Ԫ��Ƶ��
    float  fLowCycleComponentTime;              //����Ԫ��ʱ��
    float  fLowCycleLockVol;                    //���ܱ�����ѹ
    float  fLowCycleLockSlip;                   //���ܱ�������
    float  fLowVolComponentVol;                 //��ѹԪ����ѹ
    float  fLowVolComponentTime;                //��ѹԪ��ʱ��
    float  fLowVolLockSlip;                     //��ѹԪ������
    float  fFreqDiffLockConstVal;               //Ƶ�������ֵ
    float  fQuasiSameVolLock;                   //׼ͬѹ�����
    float  fQuasiSynchroAccLock;                //׼ͬ�ڼ��ٱ���
    float  fClosingPhaseTime;                   //��բ��ǰʱ��
    float  fPhaseAngleConstVal;                 //��ǰ�Ƕȶ�ֵ
};

struct SettingsLimit {
    float max;
    float min;
};

struct ConstValueLimit
{
    SettingsLimit  tCurConstValue[3];                   //����1��2��3�ζ�ֵ
    SettingsLimit  tCurConstTime[3];                    //����1��2��3��ʱ��
    SettingsLimit  tZeroSequenceCurConstValue[3];       //����1��2��3�ζ�ֵ
    SettingsLimit  tZeroSequenceCurTime[3];
    SettingsLimit  tCurAccConstValue;                   //Acc-> Accelerated  ���ٶ�ֵ
    SettingsLimit  tCurAccTime;
    SettingsLimit  tZeroSequenceCurAccConstValue;       //������ٶ�ֵ
    SettingsLimit  tZeroSequenceCurAccTime;             //�������ʱ��
    SettingsLimit  tCompoundPressureLockingVol;         //��ѹ������ѹ
    SettingsLimit  tCurAntiTimeReference;               //������ʱ��׼

    SettingsLimit  tCurAntiTime;                        //������ʱʱ��
    SettingsLimit  tZeroSequenceCurAntiTimeReference;   //����ʱ��׼
    SettingsLimit  tZeroSequenceCurAntiTime;            //����ʱʱ��
    SettingsLimit  tOverloadCur;                        //�����ɵ���
    SettingsLimit  tOverloadWarningTime;                //�����ɸ澯ʱ��
    SettingsLimit  tOverloadTripTime;                   //��������բʱ��
    SettingsLimit  tRecloseSynchroCheckConstVal;        //�غ�բ��ͬ�ڶ�ֵ
    SettingsLimit  tRecloseTime;                        //�غ�բʱ��
    SettingsLimit  tLowCycleComponentFreq;              //����Ԫ��Ƶ��
    SettingsLimit  tLowCycleComponentTime;              //����Ԫ��ʱ��
    SettingsLimit  tLowCycleLockVol;                    //���ܱ�����ѹ
    SettingsLimit  tLowCycleLockSlip;                   //���ܱ�������
    SettingsLimit  tLowVolComponentVol;                 //��ѹԪ����ѹ
    SettingsLimit  tLowVolComponentTime;                //��ѹԪ��ʱ��
    SettingsLimit  tLowVolLockSlip;                     //��ѹԪ������
    SettingsLimit  tFreqDiffLockConstVal;               //Ƶ�������ֵ
    SettingsLimit  tQuasiSameVolLock;                   //׼ͬѹ�����
    SettingsLimit  tQuasiSynchroAccLock;                //׼ͬ�ڼ��ٱ���
    SettingsLimit  tClosingPhaseTime;                   //��բ��ǰʱ��
    SettingsLimit  tPhaseAngleConstVal;                 //��ǰ�Ƕȶ�ֵ
};

class CConstValuesSetting
{
protected:
    CConstValuesSetting(void);
    virtual ~CConstValuesSetting(void);

public:
    ///
    /// @brief
    ///     ��ȡ����ʵ���ӿ�
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

