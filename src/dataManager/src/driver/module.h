#pragma once

enum {
    PHASE_A,
    PHASE_B,
    PHASE_C,

    MAX_PHASE_NUM
};

enum DEV_ENUM
{
    DEV_STATE_MONITOR,      //监测设备
    DEV_CP9000,             //CP9000
    DEV_CP6000,             //CP6000
    DEV_MC,                 //机械特性

    MAX_DEV_NUM
};


enum ATTR_TYPE_ENUM
{
    AT_COILS,           // R: 01  W: s->05  m->0F
    AT_INPUT_COILS,     // R: 02  
    AT_REGISTERS,       // R: 03  W: s->06  m->10
    AT_INPUT_REGISTERS  // R: 04
};

struct AttrInfo_t
{
    int addr;           //对应的地址
    ATTR_TYPE_ENUM type;     //属性类型
    int nb;             //地址个数  一个地址是16位的
};

struct DevAttr_t 
{
    DEV_ENUM devItem;
    AttrInfo_t attr;

    DevAttr_t(DEV_ENUM item, int addr, ATTR_TYPE_ENUM type, int nb)
    {
        this->devItem = item;
        this->attr.addr = addr;
        this->attr.type = type;
        this->attr.nb = nb;
    }
};

#include "module_stateMonitor.h"
#include "module_cp9000.h"
#include "module_cp6000.h"


//  温湿度
#define ATTR_CHNL1_TH_WARNING       DevAttr_t(DEV_STATE_MONITOR,  CHN1_LOW_TEMP_CFG_REG,  AT_REGISTERS, 3)
#define ATTR_CHNL1_TH_VAL           DevAttr_t(DEV_STATE_MONITOR,  CHN1_TEMP_VAL_REG,      AT_REGISTERS, 2)
#define ATTR_CHNL2_TH_WARNING       DevAttr_t(DEV_STATE_MONITOR,  CHN2_LOW_TEMP_CFG_REG,  AT_REGISTERS, 3)
#define ATTR_CHNL2_TH_VAL           DevAttr_t(DEV_STATE_MONITOR,  CHN2_TEMP_VAL_REG,      AT_REGISTERS, 2)

//  母排  触头温度
#define ATTR_BUSBAR_TEMP_THRESHOLD  DevAttr_t(DEV_STATE_MONITOR, BUSBAR_TEMP_WARNING_THRESHOLD_REG,  AT_REGISTERS, 1)
#define ATTR_CONTACT_TEMP_THRESHOLD DevAttr_t(DEV_STATE_MONITOR, CONTACT_TEMP_WARNING_THRESHOLD_REG,  AT_REGISTERS, 1)
#define ATTR_BUSBAR_TEMP_VAL        DevAttr_t(DEV_STATE_MONITOR, BUSBAR_TEMP_VAL_REG,  AT_REGISTERS, sizeof(Dev_SM::BusbarTempData_t)/sizeof(quint16))
#define ATTR_CONTACT_TEMP_VAL       DevAttr_t(DEV_STATE_MONITOR, CONTACT_TEMP_VAL_REG,  AT_REGISTERS, sizeof(Dev_SM::ContactTempData_t)/sizeof(quint16))

//  母排  触头ID号
#define ATTR_BUSBAR_ID_VAL          DevAttr_t(DEV_STATE_MONITOR, BUSBAR_ID_REG,   AT_REGISTERS, 12)  //母排ID
#define ATTR_CONTACT_ID_VAL         DevAttr_t(DEV_STATE_MONITOR, CONTACT_ID_REG,  AT_REGISTERS, 12)  //触头ID
#define ATTR_WIRING_ID_VAL          DevAttr_t(DEV_STATE_MONITOR, BUSBAR_ID_REG,   AT_REGISTERS, 24)  //总访问接口

//  工作模式
#define ATTR_WORK_MODE              DevAttr_t(DEV_STATE_MONITOR, WORK_MODE_CFG_REG,   AT_REGISTERS, 1) 

//  PT CT 变比
#define ATTR_PT_CT_RATIO            DevAttr_t(DEV_STATE_MONITOR, PT_CT_RATIO_REG,   AT_REGISTERS, sizeof(Dev_SM::PtCtRatio_t)/sizeof(quint16)) 

//  测量数据
#define ATTR_MEASURE_FACTOR         DevAttr_t(DEV_STATE_MONITOR, MEASURE_FACTOR_REG, AT_REGISTERS, sizeof(Dev_SM::MeasureFactor_t)/sizeof(quint16)) 
#define ATTR_MEASURE_DATA           DevAttr_t(DEV_STATE_MONITOR, MEASURE_DATA_REG,   AT_REGISTERS, sizeof(Dev_SM::MeasureData_t)/sizeof(quint16)) 

/************************************************************************/
/* 柜内操作                                                             */
/************************************************************************/
//操作模式
#define ATTR_SM_CUBICLE_OPERATE_MODE    DevAttr_t(DEV_STATE_MONITOR, CUBICLE_OPERATE_MODE_REG, AT_REGISTERS, sizeof(Dev_SM::cubicleOperateMode_t)/sizeof(quint16))
//DO 输出及状态
#define ATTR_SM_DO                  DevAttr_t(DEV_STATE_MONITOR, CUBICLE_OPERATOR_REG, AT_REGISTERS, sizeof(Dev_SM::DO_t)/sizeof(quint16)) 
//DI
#define ATTR_SM_DI                  DevAttr_t(DEV_STATE_MONITOR, SM_DI_BASE_REG, AT_REGISTERS, sizeof(Dev_SM::DI_t)/sizeof(quint16)) 
//带电显示
#define ATTR_ELECTRIFEROUS_DISPLAY  DevAttr_t(DEV_STATE_MONITOR, ELECTRIFEROUS_DISPLAY_REG, AT_REGISTERS, sizeof(Dev_SM::electriferousDisplay_t)/sizeof(quint16)) 

/************************************************************************/
/*  电动底盘车                                                          */
/************************************************************************/
#define ATTR_SM_MOTOR_CONFIG        DevAttr_t(DEV_STATE_MONITOR, MOTOR_CONFIG_REG, AT_REGISTERS, sizeof(Dev_SM::motorConfig_t)/sizeof(quint16)) 
#define ATTR_SM_MOTOR_OPERATE       DevAttr_t(DEV_STATE_MONITOR, MOTOR_OPERATE_REG, AT_REGISTERS, sizeof(Dev_SM::motorOperate_t)/sizeof(quint16)) 
#define ATTR_SM_MOTOR_OPERATE_ALLOW DevAttr_t(DEV_STATE_MONITOR, MOTOR_OPERATE_ALLOW_REG, AT_REGISTERS, sizeof(Dev_SM::motorOperateAllow_t)/sizeof(quint16)) 
#define ATTR_SM_MOTOR_STATUS        DevAttr_t(DEV_STATE_MONITOR, MOTOR_STATUS_REG, AT_REGISTERS, sizeof(Dev_SM::motorStatus_t)/sizeof(quint16)) 

/************************************************************************/
/* 机械特性                                                             */
/************************************************************************/
//时间
#define ATTR_MC_TIME                    DevAttr_t(DEV_MC, MC_TIME_REG, AT_REGISTERS, sizeof(Dev_SM::devTime_t)/sizeof(quint16)) 

//更新标识
#define ATTR_MC_DataUpdateFlag          DevAttr_t(DEV_MC, MC_UPDATE_FLAG_REG, AT_REGISTERS, sizeof(Dev_SM::machineCharaterUpdateFlag)/sizeof(quint16)) 
//状态标识
#define ATTR_MC_StatusFlag              DevAttr_t(DEV_MC, MC_SATUS_FLAG_REG, AT_REGISTERS, sizeof(Dev_SM::machineCharaterStatusFlag)/sizeof(quint16)) 

//分闸信息
#define ATTR_MC_SeparateBrakeInfo       DevAttr_t(DEV_MC, MC_SEPARATE_BRAKE_INFO_REG, AT_REGISTERS, sizeof(Dev_SM::separateBrakeInfo_t)/sizeof(quint16)) 
//合闸信息
#define ATTR_MC_CloseBrakeInfo          DevAttr_t(DEV_MC, MC_CLOSE_BRAKE_INFO__REG, AT_REGISTERS, sizeof(Dev_SM::closeBrakeInfo_t)/sizeof(quint16)) 
//储能信息
#define ATTR_MC_StoreEnergyInfo         DevAttr_t(DEV_MC, MC_STORE_ENERGY_INFO_REG, AT_REGISTERS, sizeof(Dev_SM::storeEnergyInfo_t)/sizeof(quint16)) 

//三相分闸位移
#define ATTR_MC_SeparateBrakeShiftA     DevAttr_t(DEV_MC, MC_A_PHASE_SEPARATE_BRAKE_SHIFT_REG, AT_REGISTERS, sizeof(Dev_SM::shiftInfo_t)/sizeof(quint16)) 
#define ATTR_MC_SeparateBrakeShiftB     DevAttr_t(DEV_MC, MC_B_PHASE_SEPARATE_BRAKE_SHIFT_REG, AT_REGISTERS, sizeof(Dev_SM::shiftInfo_t)/sizeof(quint16)) 
#define ATTR_MC_SeparateBrakeShiftC     DevAttr_t(DEV_MC, MC_C_PHASE_SEPARATE_BRAKE_SHIFT_REG, AT_REGISTERS, sizeof(Dev_SM::shiftInfo_t)/sizeof(quint16)) 

//三相合闸位移
#define ATTR_MC_CloseBrakeShiftA        DevAttr_t(DEV_MC, MC_A_PHASE_CLOSE_BRAKE_SHIFT_REG, AT_REGISTERS, sizeof(Dev_SM::shiftInfo_t)/sizeof(quint16)) 
#define ATTR_MC_CloseBrakeShiftB        DevAttr_t(DEV_MC, MC_B_PHASE_CLOSE_BRAKE_SHIFT_REG, AT_REGISTERS, sizeof(Dev_SM::shiftInfo_t)/sizeof(quint16)) 
#define ATTR_MC_CloseBrakeShiftC        DevAttr_t(DEV_MC, MC_C_PHASE_CLOSE_BRAKE_SHIFT_REG, AT_REGISTERS, sizeof(Dev_SM::shiftInfo_t)/sizeof(quint16)) 

//分闸线圈电流
#define ATTR_MC_SeparateBrakeCoilCur    DevAttr_t(DEV_MC, MC_SEPARATE_BRAKE_COIL_CURRENT_REG, AT_REGISTERS, sizeof(Dev_SM::coilCurrent_t)/sizeof(quint16)) 
//合闸线圈电流
#define ATTR_MC_CloseBrakeCoilCur       DevAttr_t(DEV_MC, MC_CLOSE_BRAKE_COIL_CURRENT_REG, AT_REGISTERS, sizeof(Dev_SM::coilCurrent_t)/sizeof(quint16)) 
//储能点击电流
#define ATTR_MC_StoreEnergyMotorCur     DevAttr_t(DEV_MC, MC_STORE_ENERGY_MOTOR_CURRENT_REG, AT_REGISTERS, sizeof(Dev_SM::motorCurrent_t)/sizeof(quint16)) 



/************************************************************************/
/* CP9000                                                               */
/************************************************************************/

//  开入显示
#define ATTR_CP9000_DI              DevAttr_t(DEV_CP9000, CP9000_DI_BASE_REG, AT_INPUT_COILS, sizeof(Dev_CP9000::DI_t)/sizeof(quint16)) 

//  采样显示
#define ATTR_CP9000_SAMPLE_DATA     DevAttr_t(DEV_CP9000, CP9000_PROTECT_RMS_REG,   AT_REGISTERS, sizeof(Dev_CP9000::sampleData_t)/sizeof(quint16)) 

//  定值
#define ATTR_CP9000_COSNT_PARAM     DevAttr_t(DEV_CP9000, CP9000_CONST_PARAM_REG,   AT_REGISTERS, sizeof(Dev_CP9000::constParam_t)/sizeof(quint16)) 

//  压板投退
#define ATTR_CP9000_CAST_BACK       DevAttr_t(DEV_CP9000, CP9000_PLATE_CAST_BACK_REG,   AT_REGISTERS, sizeof(Dev_CP9000::castBack_t)/sizeof(quint16)) 



/************************************************************************/
/* CP6000                                                               */
/************************************************************************/

//  开入显示
#define ATTR_CP6000_DI              DevAttr_t(DEV_CP6000, CP6000_DI_BASE_REG, AT_INPUT_COILS, sizeof(Dev_CP6000::DI_t)/sizeof(quint16)) 

//  时间设置
#define ATTR_CP6000_Time            DevAttr_t(DEV_CP6000, CP6000_TIME_BASE_REG, AT_REGISTERS, sizeof(Dev_CP6000::devTime_t)/sizeof(quint16))

#define ATTR_CP6000_BASIC_CONFIG    DevAttr_t(DEV_CP6000, CP6000_BASIC_CONFIG_BASE_REG, AT_REGISTERS, sizeof(Dev_CP6000::basicConfig_t)/sizeof(quint16))

//  定值
#define ATTR_CP6000_COSNT_PARAM     DevAttr_t(DEV_CP6000, CP6000_CONST_VALUE_BASE_REG, AT_REGISTERS, sizeof(Dev_CP6000::constParam_t)/sizeof(quint16))

// 压板投退
#define ATTR_CP6000_CAST_BACK       DevAttr_t(DEV_CP6000, CP6000_CASTBACK_BASE_REG, AT_COILS, sizeof(Dev_CP6000::castBack_t)/sizeof(quint16))

//测量值
#define ATTR_CP6000_SAMPLE_DATA     DevAttr_t(DEV_CP6000, CP6000_SAMPLE_DATA_BASE_REG, AT_INPUT_REGISTERS, sizeof(Dev_CP6000::sampleData_t)/sizeof(quint16))

//事件标识
#define ATTR_CP6000_EVENT_TAG       DevAttr_t(DEV_CP6000, CP6000_EVENT_TAG_BASE_REG, AT_INPUT_REGISTERS, sizeof(Dev_CP6000::EventTag_t)/sizeof(quint16))
