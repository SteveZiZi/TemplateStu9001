#pragma once

/*********************************
 *  YHCP6000综保地址表
 *********************************/


/*
 *  时间寄存器
 *  @Note:
 *      可读可写，03功能码读取；06 10功能码写入
 */
#define CP6000_TIME_BASE_REG            0x0010

/*
 *  开入状态信息  
 *  只读，02功能码读取
 */
#define CP6000_DI_BASE_REG              0x0080


/*
 *  投退
 */
#define CP6000_CASTBACK_BASE_REG        0x6000

/*
 *  配置
 */
#define CP6000_BASIC_CONFIG_BASE_REG    0x2002

/*
 *  定值
 */
#define CP6000_CONST_VALUE_BASE_REG     0x2005


/*
 *  测量数据区
 */
#define CP6000_SAMPLE_DATA_BASE_REG    0x0000


/*
 *  事件标识区
 *  04功能码读取
 */
#define CP6000_EVENT_TAG_BASE_REG       0x2003