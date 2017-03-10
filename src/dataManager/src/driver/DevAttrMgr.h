#pragma once

#include <QMutex>
#include <lib_win32>
#include "module.h"

#include <qDebug>
#include <QList>


#pragma  pack (push,1) 
struct RequestFileInfo_t{
    quint16 fileNo;             //文件号
    quint16 recordNo;           //记录号
    quint16 recordLength;       //记录长度
};
struct ResultFileContent_t {
    quint8 length;              //记录内容的长度
    quint8 content[245];        //记录内容  长度由length决定
};
#pragma pack(pop)


class CModbusDev : public CComModbus
{
public:
    CModbusDev(const char* comName,
               Com_BaudRate baud = BR_9600, 
               Com_Parity parity = NO_PARITY, 
               int data_bit = 8, 
               int stop_bit = 1);

    virtual ~CModbusDev();

    /*
     *  初始化
     *  @Param In：
     *      slaveId：modbus设备的从机号
     */
    bool Init(int slaveId);
    void Deinit(void);
    bool isEnable() {return m_enable;}

    bool GetAttrs(AttrInfo_t& attr, void* dests);
    bool SetAttrs(AttrInfo_t& attr, void* dests);

    bool readRecordFile(const RequestFileInfo_t& request, ResultFileContent_t& content);

private:
    QMutex mutex; 
    bool m_enable;
};

struct ModbusConfig {
    const char* port;
    int baudRate;
    int slaveId;
    bool enable;
};

class CModbusDevMgr
{
public:

    static void init(const ModbusConfig* cfg, int num);

    //柜内操作
    static bool GetCubicleOperateMode(Dev_SM::cubicleOperateMode_t* data) {return GetAttrs(ATTR_SM_CUBICLE_OPERATE_MODE, data);}
    static bool SetCubicleOperateMode(Dev_SM::cubicleOperateMode_t* data) {return SetAttrs(ATTR_SM_CUBICLE_OPERATE_MODE, data);}

    static bool GetCubicleDOStatus(Dev_SM::DO_t* data) {return GetAttrs(ATTR_SM_DO, data);}
    static bool SetCubicleDOStatus(Dev_SM::DO_t* data) {return SetAttrs(ATTR_SM_DO, data);}
    static bool GetSmDI(Dev_SM::DI_t* data) {return GetAttrs(ATTR_SM_DI, data);}
    static bool GetElectriferousDisplay(Dev_SM::electriferousDisplay_t* data) {return GetAttrs(ATTR_ELECTRIFEROUS_DISPLAY, data);}

    //电机底盘车
    static bool GetMotorConfig(Dev_SM::motorConfig_t* data) {return GetAttrs(ATTR_SM_MOTOR_CONFIG, data);}
    static bool SetMotorConfig(Dev_SM::motorConfig_t* data) {return SetAttrs(ATTR_SM_MOTOR_CONFIG, data);}
    static bool GetMotorOperateAllowStatus(Dev_SM::motorOperateAllow_t* data) {return GetAttrs(ATTR_SM_MOTOR_OPERATE_ALLOW, data);}
    static bool operateMotor(Dev_SM::motorOperate_t* data) {return SetAttrs(ATTR_SM_MOTOR_OPERATE, data);}

    //机械特性
    static bool GetMachineCharaterTime(Dev_SM::devTime_t* data) {return GetAttrs(ATTR_MC_TIME, data);}
    static bool SetMachineCharaterTime(Dev_SM::devTime_t* data) {return SetAttrs(ATTR_MC_TIME, data);}

    static bool GetMachineCharaterUpdateFlag(Dev_SM::machineCharaterUpdateFlag* data) {return GetAttrs(ATTR_MC_DataUpdateFlag, data);}
    static bool GetMachineCharaterStatus(Dev_SM::machineCharaterStatusFlag* data) {return GetAttrs(ATTR_MC_StatusFlag, data);}
    static bool GetSeparateBrakeInfo(Dev_SM::separateBrakeInfo_t* data) {return GetAttrs(ATTR_MC_SeparateBrakeInfo, data);}
    static bool GetCloseBrakeInfo(Dev_SM::closeBrakeInfo_t* data) {return GetAttrs(ATTR_MC_CloseBrakeInfo, data);}
    static bool GetStoreEnergyInfo(Dev_SM::storeEnergyInfo_t* data) {return GetAttrs(ATTR_MC_StoreEnergyInfo, data);}
    static bool GetSeparateBrakeShiftA(Dev_SM::shiftInfo_t* data) {return GetAttrs(ATTR_MC_SeparateBrakeShiftA, data);}
    static bool GetSeparateBrakeShiftB(Dev_SM::shiftInfo_t* data) {return GetAttrs(ATTR_MC_SeparateBrakeShiftB, data);}
    static bool GetSeparateBrakeShiftC(Dev_SM::shiftInfo_t* data) {return GetAttrs(ATTR_MC_SeparateBrakeShiftC, data);}
    static bool GetCloseBrakeShiftA(Dev_SM::shiftInfo_t* data) {return GetAttrs(ATTR_MC_CloseBrakeShiftA, data);}
    static bool GetCloseBrakeShiftB(Dev_SM::shiftInfo_t* data) {return GetAttrs(ATTR_MC_CloseBrakeShiftB, data);}
    static bool GetCloseBrakeShiftC(Dev_SM::shiftInfo_t* data) {return GetAttrs(ATTR_MC_CloseBrakeShiftC, data);}
    static bool GetSeparateBrakeCoilCur(Dev_SM::coilCurrent_t* data) {return GetAttrs(ATTR_MC_SeparateBrakeCoilCur, data);}
    static bool GetCloseBrakeCoilCur(Dev_SM::coilCurrent_t* data) {return GetAttrs(ATTR_MC_CloseBrakeCoilCur, data);}
    static bool GetStoreEnergyMotorCur(Dev_SM::motorCurrent_t* data) {return GetAttrs(ATTR_MC_StoreEnergyMotorCur, data);}

    static bool GetContactTempThreshold(Dev_SM::ContactTempThreshold_t* data) {return GetAttrs(ATTR_CONTACT_TEMP_THRESHOLD, data);}
    static bool SetContactTempThreshold(Dev_SM::ContactTempThreshold_t* data) {return SetAttrs(ATTR_CONTACT_TEMP_THRESHOLD, data);}
    static bool GetContactTemp(Dev_SM::ContactTempData_t* data) {return GetAttrs(ATTR_CONTACT_TEMP_VAL, data);}

    static bool GetBusbarTempThreshold(Dev_SM::BusbarTempThreshold_t* data) {return GetAttrs(ATTR_BUSBAR_TEMP_THRESHOLD, data);}
    static bool SetBusbarTempThreshold(Dev_SM::BusbarTempThreshold_t* data) {return SetAttrs(ATTR_BUSBAR_TEMP_THRESHOLD, data);}
    static bool GetBusbarTemp(Dev_SM::BusbarTempData_t* data) {return GetAttrs(ATTR_BUSBAR_TEMP_VAL, data);}

    static bool GetChnl1TempThreshold(Dev_SM::TempHumThreshold_t* data) {return GetAttrs(ATTR_CHNL1_TH_WARNING, data);}
    static bool SetChnl1TempThreshold(Dev_SM::TempHumThreshold_t* data) {return SetAttrs(ATTR_CHNL1_TH_WARNING, data);}
    static bool GetChnl1TempHum(Dev_SM::TempHumData_t* data) {return GetAttrs(ATTR_CHNL1_TH_VAL, data);}

    static bool GetChnl2TempThreshold(Dev_SM::TempHumThreshold_t* data) {return GetAttrs(ATTR_CHNL2_TH_WARNING, data);}
    static bool SetChnl2TempThreshold(Dev_SM::TempHumThreshold_t* data) {return SetAttrs(ATTR_CHNL2_TH_WARNING, data);}
    static bool GetChnl2TempHum(Dev_SM::TempHumData_t* data) {return GetAttrs(ATTR_CHNL2_TH_VAL, data);}

    static bool GetWiringId(Dev_SM::WiringId_t* data) {return GetAttrs(ATTR_WIRING_ID_VAL, data);}
    static bool SetWiringId(Dev_SM::WiringId_t* data) {return SetAttrs(ATTR_WIRING_ID_VAL, data);}

    static bool GetCP9000ConstVal(Dev_CP9000::constParam_t* data) {return GetAttrs(ATTR_CP9000_COSNT_PARAM, data);}
    static bool SetCP9000ConstVal(Dev_CP9000::constParam_t* data) {return SetAttrs(ATTR_CP9000_COSNT_PARAM, data);}
    static bool GetPlateCastBack(Dev_CP9000::castBack_t* data) {return GetAttrs(ATTR_CP9000_CAST_BACK, data);}
    static bool SetPlateCastBack(Dev_CP9000::castBack_t* data) {return SetAttrs(ATTR_CP9000_CAST_BACK, data);}
    static bool GetCP6000ConstVal(Dev_CP6000::constParam_t* data) {return GetAttrs(ATTR_CP6000_COSNT_PARAM, data);}
    static bool SetCP6000ConstVal(Dev_CP6000::constParam_t* data) {return SetAttrs(ATTR_CP6000_COSNT_PARAM, data);}
    static bool GetCP6000Castback(Dev_CP6000::castBack_t* data) {return GetAttrs(ATTR_CP6000_CAST_BACK, data);}
    static bool SetCP6000Castback(Dev_CP6000::castBack_t* data) {return SetAttrs(ATTR_CP6000_CAST_BACK, data);}
    static bool SetCP6000BasicConfig(Dev_CP6000::basicConfig_t* data) {return SetAttrs(ATTR_CP6000_BASIC_CONFIG, data);}
    static bool GetCP6000BasicConfig(Dev_CP6000::basicConfig_t* data) {return GetAttrs(ATTR_CP6000_BASIC_CONFIG, data);}

    static bool GetPtCtRatio(Dev_SM::PtCtRatio_t* data) {return GetAttrs(ATTR_PT_CT_RATIO, data);}
    static bool SetPtCtRatio(Dev_SM::PtCtRatio_t* data) {return SetAttrs(ATTR_PT_CT_RATIO, data);}

    static bool GetWorkMode(quint16* data) {return GetAttrs(ATTR_WORK_MODE, data);}
    static bool SetWorkMode(quint16* data) {return SetAttrs(ATTR_WORK_MODE, data);}

    static bool GetMeasureFactor(Dev_SM::MeasureFactor_t* data) {return GetAttrs(ATTR_MEASURE_FACTOR, data);}
    static bool GetMeasureData(Dev_SM::MeasureData_t* data) {return GetAttrs(ATTR_MEASURE_DATA, data);}

    static bool GetCP9000SampleData(Dev_CP9000::sampleData_t * data) {return GetAttrs(ATTR_CP9000_SAMPLE_DATA, data);}
    static bool GetCP9000DI(Dev_CP9000::DI_t* data) {return GetAttrs(ATTR_CP9000_DI, data);}

    static bool GetCP6000SampleData(Dev_CP6000::sampleData_t * data) {return GetAttrs(ATTR_CP6000_SAMPLE_DATA, data);}
    static bool GetCP6000DI(Dev_CP6000::DI_t* data) {return GetAttrs(ATTR_CP6000_DI, data);}
    static bool GetCP6000Time(Dev_CP6000::devTime_t* data) {return GetAttrs(ATTR_CP6000_Time, data);}
    static bool SetCP6000Time(Dev_CP6000::devTime_t* data) {return SetAttrs(ATTR_CP6000_Time, data);}
    static bool GetCP6000EventTag(Dev_CP6000::EventTag_t* data) {return GetAttrs(ATTR_CP6000_EVENT_TAG, data);}
    static bool GetCP6000EventRecord(const RequestFileInfo_t& request, ResultFileContent_t& content) {return readRecordFile(DEV_CP6000, request, content);}
    static bool requestCP6000RecordFile(int fileNo);

private:
    static bool GetAttrs(DevAttr_t& devAttr, void* dests);
    static bool SetAttrs(DevAttr_t& devAttr, void* dests);
    static bool readRecordFile(DEV_ENUM devItem, const RequestFileInfo_t& request, ResultFileContent_t& content);

private:
    CModbusDevMgr();
    ~CModbusDevMgr();


    static CModbusDevMgr* getInstance();

private:
    CModbusDev* m_arrDev[MAX_DEV_NUM];
};

inline bool CModbusDevMgr::GetAttrs(DevAttr_t& devAttr, void* dests)
{
    if (devAttr.devItem == DEV_STATE_MONITOR && CModbusDevMgr::getInstance()->m_arrDev[DEV_STATE_MONITOR]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->GetAttrs(devAttr.attr, dests);
    }

    if (devAttr.devItem == DEV_CP6000 && CModbusDevMgr::getInstance()->m_arrDev[DEV_CP6000]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->GetAttrs(devAttr.attr, dests);
    }

    if (devAttr.devItem == DEV_MC && CModbusDevMgr::getInstance()->m_arrDev[DEV_MC]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->GetAttrs(devAttr.attr, dests);
    }

    if (devAttr.devItem == DEV_CP9000 && CModbusDevMgr::getInstance()->m_arrDev[DEV_CP9000]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->GetAttrs(devAttr.attr, dests);
    }

    return false;
}

inline bool CModbusDevMgr::SetAttrs(DevAttr_t& devAttr, void* dests)
{
    if (devAttr.devItem == DEV_STATE_MONITOR && CModbusDevMgr::getInstance()->m_arrDev[DEV_STATE_MONITOR]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->SetAttrs(devAttr.attr, dests);
    }
    if (devAttr.devItem == DEV_CP6000 && CModbusDevMgr::getInstance()->m_arrDev[DEV_CP6000]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->SetAttrs(devAttr.attr, dests);
    }
    if (devAttr.devItem == DEV_MC && CModbusDevMgr::getInstance()->m_arrDev[DEV_MC]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->SetAttrs(devAttr.attr, dests);
    }
    if (devAttr.devItem == DEV_CP9000 && CModbusDevMgr::getInstance()->m_arrDev[DEV_CP9000]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devAttr.devItem]->SetAttrs(devAttr.attr, dests);
    }

    return false;
}

inline bool CModbusDevMgr::readRecordFile(DEV_ENUM devItem, const RequestFileInfo_t& request, ResultFileContent_t& content)
{
    if (devItem == DEV_STATE_MONITOR && CModbusDevMgr::getInstance()->m_arrDev[DEV_STATE_MONITOR]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devItem]->readRecordFile(request, content);
    }
    if (devItem == DEV_CP6000 && CModbusDevMgr::getInstance()->m_arrDev[DEV_CP6000]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devItem]->readRecordFile(request, content);
    }
    if (devItem == DEV_MC && CModbusDevMgr::getInstance()->m_arrDev[DEV_MC]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devItem]->readRecordFile(request, content);
    }
    if (devItem == DEV_CP9000 && CModbusDevMgr::getInstance()->m_arrDev[DEV_CP9000]->isEnable()) {
        return CModbusDevMgr::getInstance()->m_arrDev[devItem]->readRecordFile(request, content);
    }
    return false;
}


inline bool CModbusDevMgr::requestCP6000RecordFile(int fileNo)
{
    quint8 req[] = {
        CModbusDevMgr::getInstance()->m_arrDev[DEV_CP6000]->slaveId(),
        0x18,
        0x00,
        fileNo,
        0x00,
        0x01,
        0x00,
        0x00
    };
    return CModbusDevMgr::getInstance()->m_arrDev[DEV_CP6000]->sendRawRequest(req, 6);
}

