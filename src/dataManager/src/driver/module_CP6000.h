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
     *  采用BCD格式编码的
     */
    struct devTime_t {
        quint16 year;       //  当前年(2000～2099)
        quint16 month;      //  当前月(1～12)
        quint16 day;        //  当前日(1～31)
        quint16 hour;       //  当前时(0～23)
        quint16 minute;     //  当前分(0～59)
        quint16 second;     //  当前秒(0～59)
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
     *  投退定值
     */
    struct castBack_t {
        quint16 curQuickBreak;                      //电流速断
        quint16 curQuickBreak_lowVolBlocking;
        quint16 curQuickBreak_dirBlocking;
        quint16 timeLimitQuickBreak;                //限时速断
        quint16 timeLimitQuickBreak_lowVolBlocking;
        quint16 timeLimitQuickBreak_dirBlocking;
        quint16 overCurProtect;
        quint16 overCurProtect_lowVolBlocking;
        quint16 overCurProtect_dirBlocking;
        quint16 overCurProtect_antiTime;
        quint16 reclose;
        quint16 reclose_noVol;                      //检无压
        quint16 reclose_sync;                       //检同期
        quint16 reclose_secondSectionACC;           //二段后加速
        quint16 reclose_threeSectionACC;            //三段后加速
        quint16 lowFreqDeloading;
        quint16 lowFreqDeloading_slipBlocking;      //滑差闭锁
        quint16 lowFreqSplitting;                   //低频解列
        quint16 lowVolSplitting;                    //低压解列
        quint16 smallCurGround;                     //小电流接地
        quint16 smallCurGround_dirBlocking;
        quint16 overLoadingProtect;
        quint16 negativeSequenceOverCurProtect;
        quint16 zeroSequenceOverCurProtect;
        quint16 overVolProtect;
        quint16 lowVolProtect;
        quint16 lostVolProtect;
        quint16 negativeSequenceOverVolProtect;
        quint16 zeroSequenceOverVolProtect;
        quint16 compoundVolOverCur;                //复合电压过流
        quint16 compoundVolOverCur_lowVolBlocking;
        quint16 compoundVolOverCur_negativeSequenceVolBlocking;
        quint16 automaticBusTransfer;               //备自投
        quint16 automaticBusTransfer_method;        //备自投方式   0方式一，1方式二
        quint16 overHeatingProtect;
        quint16 reversePowerProtect;
        quint16 motorProtect_startTimeTooLong;
        quint16 IxOverCurProtect;
        quint16 IxOverCurProtect_antiTime;          //反时限
        quint16 motorProtect;
        quint16 nonElectricalProtect;
        quint16 nonElectricalProtect_lightGas;
        quint16 nonElectricalProtect_heavyGas;
        quint16 nonElectricalProtect_oilOverTemp;   //过温
        quint16 nonElectricalProtect_oilHighTemp;   //超高温
        quint16 PTBreakWire;
        quint16 CTBreakWire;
        quint16 reserved[2];
        quint16 faultRecord;
        quint16 controlLoopBreakWire;

        static bool isCast(quint16 reg) {return (bool)(reg != 0);}
        static quint16 realReg(bool cast) {return (quint16)(cast);}
    };

    /*
     *  基本设置
     */
    struct basicConfig_t {
        quint16 wireType;
    };

    /*
     *  定值
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
        quint16 overCurProtect_antiTimeMethod;          //反时限类型
        quint16 reclose_delay;
        quint16 reclose_accDelay;
        quint16 reclose_allowClosingAngle;              //允许合闸角
        quint16 lowFreqDeloading_freq;
        quint16 lowFreqDeloading_delay;
        quint16 lowFreqDeloading_diffBlockingVal;       //频差闭锁值
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
     *  测量数据区
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
     *  开入
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
        quint16 contralateralOpen;  //对侧分位
        quint16 lockAutomaticBusTransfer;    //闭锁备自投
        quint16 lightGas;
        quint16 heavyGas;
        quint16 oilOverTemp;        //油温过高
        quint16 oilHighestTemp;     //油温超高
    };

    /*
     *  事件标识 区
     */
    struct EventTag_t {
        quint16 soeCnt;         //SOE计数器
        quint16 diChangedCnt;   //开入变位
        quint16 recordCnt;      //故障录波计数
    };

    /*
     *  录波文件头
     */
    struct RecrodHeader_cp6000 {
        quint16 faultNo;
        quint16 reserved[4];
        struct {
            quint16 year;
            quint16 month;
            quint16 day;
            quint16 hour;
            quint16 minute;         //低位在后，高位无效
            quint16 ms;             //高低8位对应真是毫秒的高低8位
        }eventTime;
    };
    /*
     *  录波采样值
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