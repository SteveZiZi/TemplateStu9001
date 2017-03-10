#pragma once

/***********************************************
 *  YHCP9625 综保地址表
 ***********************************************/

/*
 *  十路DO线圈状态  开出
 *  @Note：
 *      使用功能码01读  05写
 */
#define CP9000_DO_BASE_REG             0x00
#define CP9000_MAX_DO_NUM              10


/*
 *  32路DI开入量
 *  @Note：
 *      使用功能码02读
 */
#define CP9000_DI_BASE_REG          0x00
#define CP9000_MAX_DI_NUM              32

/************************************************************************/
/* 保持寄存器   使用功能吗03读  10写                                    */
/************************************************************************/
/*
 *  保护有效值
 */
#define CP9000_PROTECT_RMS_REG         0x00

/*
 *  测量有效值
 */
#define CP9000_MEASURE_RMS_REG         0x20

/*
 *  时间寄存器
 */
#define CP9000_TIME_BASE_REG           0x1000

/*
 *  定值参数寄存器
 */
#define CP9000_CONST_PARAM_REG         0x1100

/*
 *  压板投退寄存器
 */
#define CP9000_PLATE_CAST_BACK_REG     0x1200

/*
 *  事件报表寄存器
 */
#define CP9000_EVENT_REPORT_BASE_REG   0x1300
