#pragma once
#include <QDateTime>
#include <QtCore/qmath.h>
#include "module.h"
#include "StateMonitorReg.h"

namespace Dev_SM {

    /************************************************************************/
    /* Temp Hum                                                             */
    /************************************************************************/
    struct TempHumThreshold_t
    {
        quint16 tempMin;                 //温度下限值
        quint16 humMax;                  //湿度上限值
        quint16 tempMax;                 //温度上限值
        quint16 humMin;                  //湿度下限值
    };
    struct TempHumData_t
    {
        quint16 temp;
        quint16 hum;
    };
    class CTempHumConv {
    public:
        static float realTemp(quint16 temp) {return (float)(temp/10.0);}
        static quint16 regTemp(float ftemp) {return (quint16)(ftemp*10.0);}
        static quint32 realHum(quint16 hum) {return hum;}
        static quint16 regHum(quint32 hum) {return (quint16)hum;} 
    };

    /************************************************************************/
    /* 母排  触头温度                                                       */
    /************************************************************************/
    struct BusbarTempThreshold_t {
        quint16 threshold;                          //母排报警阀值
    };
    struct ContactTempThreshold_t {
        quint16 threshold;                          //触头报警阀值
    };
    struct BusbarTempData_t {
        quint8 temp[MAX_PHASE_NUM][2];             //三相母排进出线温度值
    };
    struct ContactTempData_t {
        quint8 temp[MAX_PHASE_NUM][2];             //三相触头进出线温度值
    };
    struct WiringTempThreshold_t {
        BusbarTempThreshold_t busbar; 
        ContactTempThreshold_t contact; 
    };
    struct WiringTempData_t {
        BusbarTempData_t busbar;
        ContactTempData_t contact;
    };
    class CWiringTempConv {
    public:
        static float realTemp(quint16 temp) {return (float)temp;}
        static quint16 regTemp(float ftemp) {return (quint16)ftemp;}
    };

    /************************************************************************/
    /* 母排  触头ID号                                                       */
    /************************************************************************/
    struct BusbarId_t {
        quint32 ID[2][MAX_PHASE_NUM];             //[2]:上下ID  [MAX_PHASE_NUM] 三相
    };
    struct ContactId_t {
        quint32 ID[2][MAX_PHASE_NUM];             //[2]:上下ID  [MAX_PHASE_NUM] 三相
    };
    struct WiringId_t {
        BusbarId_t busbar;
        ContactId_t contact;
    }; 

    /************************************************************************/
    /*  工作模式                                                            */
    /************************************************************************/

    /************************************************************************/
    /* PT CT 变比                                                           */
    /************************************************************************/
    struct PtCtRatio_t {
        quint16 pt;
        quint16 ct;
        static quint16 realVal(quint16 reg) {return reg;}
        static quint16 regVal(quint16 val) {return val;}
    };

    /************************************************************************/
    /* 测量数据                                                             */
    /************************************************************************/
    struct MeasureFactor_t {
        quint8 cur;
        quint8 vol;
        quint8 reserve;
        quint8 powr;
    };
    struct MeasureData_t {
        quint16 phaseVol[MAX_PHASE_NUM];
        quint16 wireVol[MAX_PHASE_NUM];
        quint16 phaseCur[MAX_PHASE_NUM];
        quint16 reserved;
        quint16 freq;
        quint16 powerP[MAX_PHASE_NUM];
        quint16 powerPS;
        quint16 powerQ[MAX_PHASE_NUM];
        quint16 powerQS;
        quint16 powerS[MAX_PHASE_NUM];
        quint16 powerSS;
        quint16 powerFactor[MAX_PHASE_NUM];
        quint16 powerFactorS;
    };
    class CMeasureDataConv {
    public:
        static float realCur(quint16 reg) {
            if (m_bGetFactor || getFactor()) 
                return (float)(((float)reg/10000.0)*qPow(10, m_factor.cur));
            return (float)(-1);
        }
        static float realVol(quint16 reg) {
            if (m_bGetFactor || getFactor())
                return (float)(((float)reg/10000.0)*qPow(10, m_factor.vol));
            return (float)(-1);
        }
        static float realPower(quint16 reg) {
            if (m_bGetFactor || getFactor()) 
                return (float)(((float)reg/10000.0)*qPow(10, m_factor.powr));
            return (float)(-1);
        }
        static float realPowerFactor(quint16 reg) {
            return (float)((float)reg/1000.0);
        }
        static float realFreq(quint16 reg) {
            return (float)((float)reg/100.0);
        }

    private:
        static bool getFactor(void);
        static MeasureFactor_t m_factor;
        static bool m_bGetFactor;
    };

    /************************************************************************/
    /* 柜内操作                                                             */
    /************************************************************************/
    struct cubicleOperateMode_t {
        quint16 reserved : 14;
        quint16 bManual : 1;        // 1：手动模式  0：自动模式
    };

    struct DO_t {
        quint16 heatingChnl1 : 1;
        quint16 heatingChnl2 : 1;
        quint16 fanChnl1 : 1;
        quint16 fanChnl2 : 1;
        quint16 loadLost : 1;
        quint16 highVolOpenPhase : 1;
        quint16 lamp : 1;
        quint16 lockGate : 1;
        quint16 faultOutput : 1;
    };

    struct DI_t {
        quint16 openPosition : 1;
        quint16 closePosition : 1;
        quint16 servicePosition : 1;
        quint16 testingPosition : 1;
        quint16 earthingKnifeOff : 1;
        quint16 spingEnergy : 1;
        quint16 earthingKnifeOn : 1;
        quint16 reserved0 : 1;
        quint16 frontDoorClosed : 1;
        quint16 backDoorClosed : 1;
        quint16 reserved1 : 2;
        quint16 remoteTeleIn : 1;
        quint16 remoteTeleOut : 1;
        quint16 faultReset : 1;
        quint16 reserved2 : 1;
    };
    struct electriferousDisplay_t {
        quint16 displayA : 1;
        quint16 displayB : 1;
        quint16 displayC : 1;
    };

    /************************************************************************/
    /*  电动底盘车                                                          */
    /************************************************************************/
    struct motorConfig_t {
        quint16 wholeRoute;
        quint16 stalledReturnAllow;
        quint16 ratedCur;
        quint16 ratedVol;
        quint16 barrowPulseSignalEn;
        quint16 underVolProtect;
        static float realCur(quint16 reg) {return (float)(reg/10.0);}
        static quint16 regCur(float cur) {return (quint16)(cur*10);}
        static float realVol(quint16 reg) {return (float)(reg);}
        static quint16 regVol(float vol) {return (quint16)(vol);}
        static float realRoute(quint16 reg) {return (float)(reg);}
        static quint16 regRoute(float route) {return (quint16)(route);}

        static bool enable(quint16 reg) {return (reg)?true:false;}
        static quint16 setEnable(bool enable) {return (quint16)(enable);}
    };

    struct motorOperate_t {
        quint16 barrowTeleIn : 1;
        quint16 barrowTeleOut : 1;
        quint16 stop : 1;
        quint16 earthKnifeClose : 1;
        quint16 earthKnifeOpen : 1;
        quint16 reset : 1;
    };
    struct motorOperateAllow_t {
        quint16 barrowOperate : 1;
        quint16 earthKnifeOperate : 1;
    };
    struct motorStatus_t {
        quint16 brakeClosed : 1;
        quint16 brakeOpened : 1;
        quint16 barrowActived : 1;
        quint16 barrowTesting : 1;
        quint16 earthKnifeClosed : 1;
        quint16 earthKnifeOpened : 1;
        quint16 frontGateClosed : 1;
        quint16 backGateClosed : 1;
        quint16 nearCubicleStatus1 : 1;
        quint16 nearCubicleStatus2 : 1;
        quint16 electricalStatus : 1;
        quint16 allowBarrowOperate : 1;
        quint16 allowEarthKnifeOperate : 1;
        quint16 reserved : 3;
    };


    /************************************************************************/
    /* 机械特性                                                             */
    /************************************************************************/
    struct devTime_t {
        quint16 second;
        quint16 minute;
        quint16 hour;
        quint16 day;
        quint16 month;
        quint16 year;

        static void realTime(const devTime_t& devTime, QDateTime* dateTime)
        {
            dateTime->setDate(QDate(devTime.year, devTime.month, devTime.day));
            dateTime->setTime(QTime(devTime.hour, devTime.minute, devTime.second));
        }
        static void realReg(const QDateTime& dateTime, devTime_t* devTime) 
        {
            devTime->year = dateTime.date().year();
            devTime->month = dateTime.date().month();
            devTime->day = dateTime.date().day();
            devTime->hour = dateTime.time().hour();
            devTime->minute = dateTime.time().minute();
            devTime->second = dateTime.time().second();
        }
    };

    struct machineCharaterUpdateFlag {
        quint16 flag;     //取值 MC_DataUpdateFlag 或的关系
    };
    struct machineCharaterStatusFlag {
        quint16 flag;     //取值 MC_RunStatusFlag 或的关系
    };
    struct separateBrakeInfo_t {
        devTime_t time;
        quint16 noSync;                 //分闸不同期
        struct {
            quint16 contactDistance;    //锄头开距
            quint16 wholeRoute;
            quint16 wholeTimes;
            quint16 separateBrakeSpeedAvg;
            quint16 separatingBrakeSpeed;
            quint16 bounceAMP;
        }phase[MAX_PHASE_NUM];
    };
    struct closeBrakeInfo_t {
        devTime_t time;
        quint16 noSync;                 //分闸不同期
        struct {
            quint16 contactOverRoute;    //锄头开距
            quint16 wholeRoute;
            quint16 wholeTimes;
            quint16 closeBrakeSpeedAvg;
            quint16 closingBrakeSpeed;
            quint16 bounceTime;
        }phase[MAX_PHASE_NUM];
    };
    struct storeEnergyInfo_t {
        quint16 time;
    };
    struct shiftInfo_t {
        quint16 pos[500];
    };
    struct coilCurrent_t {
        quint16 cur[500];
    };
    struct motorCurrent_t {
        quint16 cur[500];
    };

    class CMachineCharacterConv {
    public:
        static float realNoSync(quint16 reg) {return (float)(reg/10.0);}
        static float realContactDistance(quint16 reg) {return (float)(reg/100.0);}
        static float realContactOverRoute(quint16 reg) {return (float)(reg/100.0);}
        static float realWholeRoute(quint16 reg) {return (float)(reg/100.0);}
        static float realWholeTimes(quint16 reg) {return (float)(reg/10.0);}
        static float realAvgSpeed(quint16 reg) {return (float)(reg/1000.0);}
        static float realBounceAMP(quint16 reg) {return (float)(reg/100.0);}
        static float realBounceTime(quint16 reg) {return (float)(reg/10.0);}
        static float realStoreEnergyTime(quint16 reg) {return (float)(reg/100.0);}
        static float realShift(quint16 reg) {return (float)(reg/100.0);}
        static float realCur(quint16 reg) {return (float)(reg);}
    };
};







