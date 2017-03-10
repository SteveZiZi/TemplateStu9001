#pragma once
#include <QDateTime>
#include "module.h"
#include "CP6000Reg.h"



inline quint8 BCDtoASCII(quint8 bcd)
{
    return (bcd&0x0F) + ((bcd>>4)&0x0F)*10;
}

inline quint8 ASCIItoBCD(quint8 asc) 
{
    return ((asc/10)<<4) + (asc%10);
}

namespace Dev_CP6000 {

    /*
     *  ����BCD��ʽ�����
     */
    struct devTime_t {
        quint16 year;       //  ��ǰ��(2000��2099)
        quint16 month;      //  ��ǰ��(1��12)
        quint16 day;        //  ��ǰ��(1��31)
        quint16 hour;       //  ��ǰʱ(0��23)
        quint16 minute;     //  ��ǰ��(0��59)
        quint16 second;     //  ��ǰ��(0��59)
    };
    class CDevTimeConv {
    public:
        static void realTime(const devTime_t& devTime, QDateTime* dateTime)
        {
            dateTime->setDate(QDate(BCDtoASCII(devTime.year)+2000, BCDtoASCII(devTime.month), BCDtoASCII(devTime.day)));
            dateTime->setTime(QTime(BCDtoASCII(devTime.hour), BCDtoASCII(devTime.minute), BCDtoASCII(devTime.second)));
        }
        static void realReg(const QDateTime& dateTime, devTime_t* devTime) 
        {
            devTime->year = ASCIItoBCD(dateTime.date().year()-2000);
            devTime->month = ASCIItoBCD(dateTime.date().month());
            devTime->day = ASCIItoBCD(dateTime.date().day());
            devTime->hour = ASCIItoBCD(dateTime.time().hour());
            devTime->minute = ASCIItoBCD(dateTime.time().minute());
            devTime->second = ASCIItoBCD(dateTime.time().second());
        }
    };

    /*
     *  Ͷ�˶�ֵ
     */
    struct castBack_t {
        quint16 curQuickBreak;                      //�����ٶ�
        quint16 curQuickBreak_lowVolBlocking;
        quint16 curQuickBreak_dirBlocking;
        quint16 timeLimitQuickBreak;                //��ʱ�ٶ�
        quint16 timeLimitQuickBreak_lowVolBlocking;
        quint16 timeLimitQuickBreak_dirBlocking;
        quint16 overCurProtect;
        quint16 overCurProtect_lowVolBlocking;
        quint16 overCurProtect_dirBlocking;
        quint16 overCurProtect_antiTime;
        quint16 reclose;
        quint16 reclose_noVol;                      //����ѹ
        quint16 reclose_sync;                       //��ͬ��
        quint16 reclose_secondSectionACC;           //���κ����
        quint16 reclose_threeSectionACC;            //���κ����
        quint16 lowFreqDeloading;
        quint16 lowFreqDeloading_slipBlocking;      //�������
        quint16 lowFreqSplitting;                   //��Ƶ����
        quint16 lowVolSplitting;                    //��ѹ����
        quint16 smallCurGround;                     //С�����ӵ�
        quint16 smallCurGround_dirBlocking;
        quint16 overLoadingProtect;
        quint16 negativeSequenceOverCurProtect;
        quint16 zeroSequenceOverCurProtect;
        quint16 overVolProtect;
        quint16 lowVolProtect;
        quint16 lostVolProtect;
        quint16 negativeSequenceOverVolProtect;
        quint16 zeroSequenceOverVolProtect;
        quint16 compoundVolOverCur;                //���ϵ�ѹ����
        quint16 compoundVolOverCur_lowVolBlocking;
        quint16 compoundVolOverCur_negativeSequenceVolBlocking;
        quint16 automaticBusTransfer;               //����Ͷ
        quint16 automaticBusTransfer_method;        //����Ͷ��ʽ   0��ʽһ��1��ʽ��
        quint16 overHeatingProtect;
        quint16 reversePowerProtect;
        quint16 motorProtect_startTimeTooLong;
        quint16 IxOverCurProtect;
        quint16 IxOverCurProtect_antiTime;          //��ʱ��
        quint16 motorProtect;
        quint16 nonElectricalProtect;
        quint16 nonElectricalProtect_lightGas;
        quint16 nonElectricalProtect_heavyGas;
        quint16 nonElectricalProtect_oilOverTemp;   //����
        quint16 nonElectricalProtect_oilHighTemp;   //������
        quint16 PTBreakWire;
        quint16 CTBreakWire;
        quint16 reserved[2];
        quint16 faultRecord;
        quint16 controlLoopBreakWire;

        static bool isCast(quint16 reg) {return (bool)(reg != 0);}
        static quint16 realReg(bool cast) {return (quint16)(cast);}
    };

    /*
     *  ��������
     */
    struct basicConfig_t {
        quint16 wireType;
    };

    /*
     *  ��ֵ
     */
    struct constParam_t {
        quint16 curQuickBreak_cur;
        quint16 curQuickBreak_delay;
        quint16 curQuickBreak_lowVolBlockingVal;
        quint16 timeLimitQuickBreak_cur;
        quint16 timeLimitQuickBreak_delay;
        quint16 timeLimitQuickBreak_lowVolBlockingVal;
        quint16 overCurProtect_cur;
        quint16 overCurProtect_delay;
        quint16 overCurProtect_lowVolBlockingVal;
        quint16 overCurProtect_antiTimeMethod;          //��ʱ������
        quint16 reclose_delay;
        quint16 reclose_accDelay;
        quint16 reclose_allowClosingAngle;              //�����բ��
        quint16 lowFreqDeloading_freq;
        quint16 lowFreqDeloading_delay;
        quint16 lowFreqDeloading_diffBlockingVal;       //Ƶ�����ֵ
        quint16 lowFreqDeloading_reserve;
        quint16 lowFreqSplitting_freq;
        quint16 lowFreqSplitting_delay;
        quint16 lowVolSplitting_vol;
        quint16 lowVolSplitting_delay;
        quint16 smallCurGround_zeroSequenceCur;
        quint16 smallCurGround_zeroSequenceVol;
        quint16 smallCurGround_delay;
        quint16 overLoadingProtect_cur;
        quint16 overLoadingProtect_delay;
        quint16 negativeSequenceOverCurProtect_cur;
        quint16 negativeSequenceOverCurProtect_delay;
        quint16 zeroSequenceOverCurProtect_cur;
        quint16 zeroSequenceOverCurProtect_delay;
        quint16 overVolProtect_vol;
        quint16 overVolProtect_delay;
        quint16 lowVolProtect_vol;
        quint16 lowVolProtect_delay;
        quint16 lostVolProtect_vol;
        quint16 lostVolProtect_delay;
        quint16 negativeSequenceOverVolProtect_vol;
        quint16 negativeSequenceOverVolProtect_delay;
        quint16 zeroSequenceOverVolProtect_vol;
        quint16 zeroSequenceOverVolProtect_delay;
        quint16 compoundVolOverCur_cur;
        quint16 compoundVolOverCur_lowVolBlockingVal;
        quint16 compoundVolOverCur_negativeSequenceVol;
        quint16 compoundVolOverCur_delay;
        quint16 automaticBusTransfer_vol;
        quint16 automaticBusTransfer_delay;
        quint16 overHeatingProtect_cur;
        quint16 overHeatingProtect_delay;
        quint16 overHeatingProtect_negaitveSquenceFactor;
        quint16 reversePowerProtect_power;
        quint16 reversePowerProtect_delay;
        quint16 IxOverCurProtect_cur;
        quint16 IxOverCurProtect_delay;
        quint16 IxOverCurProtect_antiTimeMethod;
        quint16 motorProtect_startTime;
        quint16 motorProtect_rateCur;
        quint16 motorProtect_curFactor;

        static float realVal(quint16 reg) {return (float)(reg/100.0f);}
        static quint16 realReg(float val) {return (quint16)(val*100);}
    };

    /*
     *  ����������
     */
    struct sampleData_t {
        quint16 freq;
        quint16 phaseVol[MAX_PHASE_NUM];
        quint16 lineVol[MAX_PHASE_NUM];
        quint16 protectCur[MAX_PHASE_NUM];
        quint16 externZeroSequenceVol;
        quint16 externZeroSequenceCur;
        quint16 Ux;
        quint16 sequenceVol[3];
        quint16 sequenceCur[3];

        quint16 anglePhaseVol[MAX_PHASE_NUM];
        quint16 angleProtectCur[MAX_PHASE_NUM];
        quint16 angleExternZeroSequenceVol;
        quint16 angleExternZeroSequenceCur;
        quint16 angleUx;


        static float realVol(quint16 reg) {return (float)(reg/100.0f);}
        static float realCur(quint16 reg) {return (float)(reg/100.0f);}
        static float realFreq(quint16 reg) {return (float)(reg/100.0f);}
        static float realAngle(quint16 reg) {return (float)(reg/10.0f);}
    };

    /*
     *  ����
     */
    struct DI_t {
        quint16 openPosition;
        quint16 closePosition;
        quint16 servicePosition;
        quint16 testingPosition;
        quint16 earthingKnifeOff;
        quint16 earthingKnifeOn;
        quint16 spingEnergy;
        quint16 remotePosition;
        quint16 contralateralOpen;  //�Բ��λ
        quint16 lockAutomaticBusTransfer;    //��������Ͷ
        quint16 lightGas;
        quint16 heavyGas;
        quint16 oilOverTemp;        //���¹���
        quint16 oilHighestTemp;     //���³���
    };

    /*
     *  �¼���ʶ ��
     */
    struct EventTag_t {
        quint16 soeCnt;         //SOE������
        quint16 diChangedCnt;   //�����λ
        quint16 recordCnt;      //����¼������
    };

    /*
     *  ¼���ļ�ͷ
     */
    struct RecrodHeader_cp6000 {
        quint16 faultNo;
        quint16 reserved[4];
        struct {
            quint16 year;
            quint16 month;
            quint16 day;
            quint16 hour;
            quint16 minute;         //��λ�ں󣬸�λ��Ч
            quint16 ms;             //�ߵ�8λ��Ӧ���Ǻ���ĸߵ�8λ
        }eventTime;
    };
    /*
     *  ¼������ֵ
     */
    struct RecordSmv_cp6000 {
        quint16 sampleNo;
        quint16 phaseVol[3];
        quint16 protectCur[3];
        quint16 zeroSequenceVol;
        quint16 zeroSequenceCur;
        quint16 Ux;
        quint16 diStatus;
        quint16 protectStatus;
    };
};