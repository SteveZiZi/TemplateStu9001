#pragma once

namespace Dev_SM {

/************************************************************************/
/*  柜内操作                                                            */
/************************************************************************/
/*
 *  温湿度设定值
 *  
 *  \note:
 *      温度单位  0.1度
 *      湿度单位  1读
 */
#define CHN1_LOW_TEMP_CFG_REG       0x04        //通道1低温设定值
#define CHN1_HIGH_HUM_CFG_REG       0x05        //通道1高湿度设定值
#define CHN1_HIGH_TEMP_CFG_REG      0x06        //通道1高温度设定值
#define CHN2_LOW_TEMP_CFG_REG       0x07        //通道2低温设定值
#define CHN2_HIGH_HUM_CFG_REG       0x08        //通道2高湿度设定值
#define CHN2_HIGH_TEMP_CFG_REG      0x09        //通道2高温度设定值

#define CHN1_TEMP_VAL_REG           0x11
#define CHN1_HUM_VAL_REG            0x12
#define CHN2_TEMP_VAL_REG           0x13
#define CHN2_HUM_VAL_REG            0x14


#define LOW_TEMP_CFG_MIN            0           //低温设定值的最小值
#define LOW_TEMP_CFG_MAX            390         //低温设定值的最大值
#define HIGH_TEMP_CFG_MIN           0           //高温设定值的最小值
#define HIGH_TEMP_CFG_MAX           400         //高温设定值的最大值
#define HIGH_HUM_CFG_MIN            0           //高湿度设定值的最小值
#define HIGH_HUM_CFG_MAX            99          //高湿度设定值的最大值


/*
 *  继电器（DO）手动模式强制切换
 */
#define CUBICLE_OPERATE_MODE_REG   0x0C

/*
 *  DO输出状态及控制寄存器
 */
#define CUBICLE_OPERATOR_REG        0x0D

//带电显示
#define ELECTRIFEROUS_DISPLAY_REG   0x0E

//开入量DI
#define SM_DI_BASE_REG              0x16


/************************************************************************/
/* 母排  触头温度                                                       */
/************************************************************************/
/*
 *  16位寄存器 一个字节表示一项值
 */
#define BUSBAR_TEMP_WARNING_THRESHOLD_REG       0x02E
#define CONTACT_TEMP_WARNING_THRESHOLD_REG      0x030

#define BUSBAR_TEMP_VAL_REG                     0x031
#define CONTACT_TEMP_VAL_REG                    0x034

/************************************************************************/
/* 母排  触头ID号                                                       */
/************************************************************************/
/*
 *  16位寄存器 一个字节表示一个ID号
 */
#define BUSBAR_ID_REG                           0x37
#define CONTACT_ID_REG                          0x42

/************************************************************************/
/*  工作模式                                                            */
/************************************************************************/
#define WORK_MODE_CFG_REG                       0x4F
enum WORK_MODE_ENUM {
    THREE_PHASE_FOUR_WIRE,
    THREE_PHASE_THREE_WIRE = 1 << 7
};

/************************************************************************/
/* PT CT 变比                                                           */
/************************************************************************/
#define PT_CT_RATIO_REG                         0x50

/************************************************************************/
/* 测量数据                                                             */
/************************************************************************/
#define MEASURE_FACTOR_REG                      0x57
#define MEASURE_DATA_REG                        0x59


/************************************************************************/
/*  电动底盘车                                                          */
/************************************************************************/
//电机配置
#define MOTOR_CONFIG_REG                        0x9D

/*
 *  电机控制命令
 *  
 *  @Note:
 *      只有电机处于允许操作状态下才能执行电机控制命令
 */
#define MOTOR_OPERATE_REG                       0xA4
//电机就绪状态寄存器
#define MOTOR_OPERATE_ALLOW_REG                 0xA7

/************************************************************************/
/* 机械特性    使用0x04操作码读 0x10写                                  */
/************************************************************************/
//时间
#define MC_TIME_REG                             20

//更新标识
#define MC_UPDATE_FLAG_REG                      40
enum MC_DataUpdateFlag {
    MC_UPDATE_SEPARATE_BRAKE_DATA   = 1 << 0,
    MC_UPDATE_CLOSE_BRAKE_DATA      = 1 << 1,
    MC_UPDATE_STORE_ENERGY_DATA     = 1 << 2
};
//状态标识
#define MC_SATUS_FLAG_REG                       41
enum MC_StatusFlag {
    MC_STATUS_CLOSE_BRAKE           = 1 << 0,   //0 分闸    1 合闸
    MC_STATUS_STORE_ENERGY          = 1 << 1,   //0 未储能  1 储能
    MC_STATUS_WORK                  = 1 << 2    //0 隔离    1 工作
};

//分闸信息
#define MC_SEPARATE_BRAKE_INFO_REG              60
//合闸信息
#define MC_CLOSE_BRAKE_INFO__REG                90
//储能信息
#define MC_STORE_ENERGY_INFO_REG                115

//三相分闸位移
#define MC_A_PHASE_SEPARATE_BRAKE_SHIFT_REG     130
#define MC_B_PHASE_SEPARATE_BRAKE_SHIFT_REG     630
#define MC_C_PHASE_SEPARATE_BRAKE_SHIFT_REG     1130

//三相合闸位移
#define MC_A_PHASE_CLOSE_BRAKE_SHIFT_REG        1630
#define MC_B_PHASE_CLOSE_BRAKE_SHIFT_REG        2130
#define MC_C_PHASE_CLOSE_BRAKE_SHIFT_REG        2630

//分闸线圈电流
#define MC_SEPARATE_BRAKE_COIL_CURRENT_REG      3130
//合闸线圈电流
#define MC_CLOSE_BRAKE_COIL_CURRENT_REG         3630
//储能点击电流
#define MC_STORE_ENERGY_MOTOR_CURRENT_REG       4130

};