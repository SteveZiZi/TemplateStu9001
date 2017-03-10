#pragma once

namespace Dev_SM {

/************************************************************************/
/*  ���ڲ���                                                            */
/************************************************************************/
/*
 *  ��ʪ���趨ֵ
 *  
 *  \note:
 *      �¶ȵ�λ  0.1��
 *      ʪ�ȵ�λ  1��
 */
#define CHN1_LOW_TEMP_CFG_REG       0x04        //ͨ��1�����趨ֵ
#define CHN1_HIGH_HUM_CFG_REG       0x05        //ͨ��1��ʪ���趨ֵ
#define CHN1_HIGH_TEMP_CFG_REG      0x06        //ͨ��1���¶��趨ֵ
#define CHN2_LOW_TEMP_CFG_REG       0x07        //ͨ��2�����趨ֵ
#define CHN2_HIGH_HUM_CFG_REG       0x08        //ͨ��2��ʪ���趨ֵ
#define CHN2_HIGH_TEMP_CFG_REG      0x09        //ͨ��2���¶��趨ֵ

#define CHN1_TEMP_VAL_REG           0x11
#define CHN1_HUM_VAL_REG            0x12
#define CHN2_TEMP_VAL_REG           0x13
#define CHN2_HUM_VAL_REG            0x14


#define LOW_TEMP_CFG_MIN            0           //�����趨ֵ����Сֵ
#define LOW_TEMP_CFG_MAX            390         //�����趨ֵ�����ֵ
#define HIGH_TEMP_CFG_MIN           0           //�����趨ֵ����Сֵ
#define HIGH_TEMP_CFG_MAX           400         //�����趨ֵ�����ֵ
#define HIGH_HUM_CFG_MIN            0           //��ʪ���趨ֵ����Сֵ
#define HIGH_HUM_CFG_MAX            99          //��ʪ���趨ֵ�����ֵ


/*
 *  �̵�����DO���ֶ�ģʽǿ���л�
 */
#define CUBICLE_OPERATE_MODE_REG   0x0C

/*
 *  DO���״̬�����ƼĴ���
 */
#define CUBICLE_OPERATOR_REG        0x0D

//������ʾ
#define ELECTRIFEROUS_DISPLAY_REG   0x0E

//������DI
#define SM_DI_BASE_REG              0x16


/************************************************************************/
/* ĸ��  ��ͷ�¶�                                                       */
/************************************************************************/
/*
 *  16λ�Ĵ��� һ���ֽڱ�ʾһ��ֵ
 */
#define BUSBAR_TEMP_WARNING_THRESHOLD_REG       0x02E
#define CONTACT_TEMP_WARNING_THRESHOLD_REG      0x030

#define BUSBAR_TEMP_VAL_REG                     0x031
#define CONTACT_TEMP_VAL_REG                    0x034

/************************************************************************/
/* ĸ��  ��ͷID��                                                       */
/************************************************************************/
/*
 *  16λ�Ĵ��� һ���ֽڱ�ʾһ��ID��
 */
#define BUSBAR_ID_REG                           0x37
#define CONTACT_ID_REG                          0x42

/************************************************************************/
/*  ����ģʽ                                                            */
/************************************************************************/
#define WORK_MODE_CFG_REG                       0x4F
enum WORK_MODE_ENUM {
    THREE_PHASE_FOUR_WIRE,
    THREE_PHASE_THREE_WIRE = 1 << 7
};

/************************************************************************/
/* PT CT ���                                                           */
/************************************************************************/
#define PT_CT_RATIO_REG                         0x50

/************************************************************************/
/* ��������                                                             */
/************************************************************************/
#define MEASURE_FACTOR_REG                      0x57
#define MEASURE_DATA_REG                        0x59


/************************************************************************/
/*  �綯���̳�                                                          */
/************************************************************************/
//�������
#define MOTOR_CONFIG_REG                        0x9D

/*
 *  �����������
 *  
 *  @Note:
 *      ֻ�е�������������״̬�²���ִ�е����������
 */
#define MOTOR_OPERATE_REG                       0xA4
//�������״̬�Ĵ���
#define MOTOR_OPERATE_ALLOW_REG                 0xA7

/************************************************************************/
/* ��е����    ʹ��0x04������� 0x10д                                  */
/************************************************************************/
//ʱ��
#define MC_TIME_REG                             20

//���±�ʶ
#define MC_UPDATE_FLAG_REG                      40
enum MC_DataUpdateFlag {
    MC_UPDATE_SEPARATE_BRAKE_DATA   = 1 << 0,
    MC_UPDATE_CLOSE_BRAKE_DATA      = 1 << 1,
    MC_UPDATE_STORE_ENERGY_DATA     = 1 << 2
};
//״̬��ʶ
#define MC_SATUS_FLAG_REG                       41
enum MC_StatusFlag {
    MC_STATUS_CLOSE_BRAKE           = 1 << 0,   //0 ��բ    1 ��բ
    MC_STATUS_STORE_ENERGY          = 1 << 1,   //0 δ����  1 ����
    MC_STATUS_WORK                  = 1 << 2    //0 ����    1 ����
};

//��բ��Ϣ
#define MC_SEPARATE_BRAKE_INFO_REG              60
//��բ��Ϣ
#define MC_CLOSE_BRAKE_INFO__REG                90
//������Ϣ
#define MC_STORE_ENERGY_INFO_REG                115

//�����բλ��
#define MC_A_PHASE_SEPARATE_BRAKE_SHIFT_REG     130
#define MC_B_PHASE_SEPARATE_BRAKE_SHIFT_REG     630
#define MC_C_PHASE_SEPARATE_BRAKE_SHIFT_REG     1130

//�����բλ��
#define MC_A_PHASE_CLOSE_BRAKE_SHIFT_REG        1630
#define MC_B_PHASE_CLOSE_BRAKE_SHIFT_REG        2130
#define MC_C_PHASE_CLOSE_BRAKE_SHIFT_REG        2630

//��բ��Ȧ����
#define MC_SEPARATE_BRAKE_COIL_CURRENT_REG      3130
//��բ��Ȧ����
#define MC_CLOSE_BRAKE_COIL_CURRENT_REG         3630
//���ܵ������
#define MC_STORE_ENERGY_MOTOR_CURRENT_REG       4130

};