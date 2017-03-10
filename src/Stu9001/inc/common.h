#pragma once



//////////////////////////////////////////////////////////////////////////
// 美化控件
// #define CReportH CListCtrlT_HLine
// #define CReportV CListCtrlT_VLine
// #define CReportVM CListCtrlT_VLineMidH




//////////////////////////////////////////////////////////////////////////
// 窗口定位坐标

#define STU_SCREEN_L                    0
#define STU_SCREEN_TP                   0
#define STU_SCREEN_W                    640
#define STU_SCREEN_H                    480

// topbar
#define STU_P_TOP_L                     0
#define STU_P_TOP_T                     0
#define STU_P_TOP_W                     STU_SCREEN_W
#define STU_P_TOP_H                     28

// bottombar
#define STU_P_BOTTOM_L                  0
#define STU_P_BOTTOM_T                  452
#define STU_P_BOTTOM_W                  STU_SCREEN_W
#define STU_P_BOTTOM_H                 (STU_SCREEN_H-STU_P_BOTTOM_T)

//naviMenu
#define STU_P_NAVI_L                    0
#define STU_P_NAVI_T                   (STU_P_TOP_H+1)
#define STU_P_NAVI_W                    90
#define STU_P_NAVI_H                   (STU_SCREEN_H-STU_P_TOP_H-STU_P_BOTTOM_H-2)

#define STU_P_NAVI_ITEM_H               35                              /*  单个导航菜单的高度          */

// body
#define STU_P_BODY1_L                  (STU_P_NAVI_W+1)
#define STU_P_BODY1_T                  (STU_P_NAVI_T)
#define STU_P_BODY1_W                  (STU_SCREEN_W-STU_P_BODY1_L)
#define STU_P_BODY1_H                  (STU_P_NAVI_H)

#define STU_P_BODY2_L                  (STU_P_BODY1_L+STU_P_NAVI_W)
#define STU_P_BODY2_T                  (STU_P_NAVI_T)
#define STU_P_BODY2_W                  (STU_SCREEN_W-STU_P_BODY2_L)
#define STU_P_BODY2_H                  (STU_P_NAVI_H)

//系统参数
#define STU_SYSTEM_CONFIG_CONTENT           (0x00)
#define STU_SET_PASSWORD_CONTENT            (0x01)
#define STU_NETWORK_SETTINGS_CONTENT        (0x02)
#define STU_TIME_SETTINGS_CONTENT           (0x03)
#define STU_SIMULATION_VIEWS_CONTENT        (0x04)
//电能参数
#define STU_MEASURE_PARAM_CONTENT           (0x10)
#define STU_HARNOICS_PARAM_CONTENT          (0x11)
#define STU_WIRING_TYPES_CONTENT            (0x12)
//温湿参数
#define STU_WIRING_MEASURE_TEMP_PARAM_CONTENT   (0x20)
#define STU_WIRING_ID_SERIAL_CONTENT        (0x21)
#define STU_TH1_CONTENT                     (0x22)
#define STU_TH2_CONTENT                     (0x23)
//机械特性
#define STU_MACHINE_CHARACTRISTIC_PARAM_CONTENT (0x30)
//电机参数
#define STU_MOTOR_PARAM_CONTENT             (0x40)


#define STU_MEASURE_SHOW_CONTENT            (0x100)
#define STU_SAMPLE_SHOW_CONTENT             (0x110)
#define STU_SWITCH_IN_SHOW_CONTENT          (0x120)
#define STU_TEMP_HUM_SHOW_CONTENT           (0x130)

#define STU_CONST_VALUE_MODIFY_CONTENT      (0x200)
#define STU_PLATE_CASTBACK_CONTENT          (0x210)
#define STU_CASTBACK_CONST_VALUE_CONTENT    (0x220)

#define STU_ELEC_OPERATOR_CONTENT           (0x400)


#define STU_WIRING_MEASURE_TEMP_TREND_CONTENT   (0x500)
#define STU_CUBICLE_TEMP_HUM_TREND_CONTENT      (0x510)
#define STU_MACHINE_CHARACTRISTIC_TREND_CONTENT (0x520)
#define STU_HARNOICS_PARAM_TREND_CONTENT        (0x530)


#define STU_EVENT_REPORT_CONTENT            (0x700)


#define STU_FONT_FAMILY                    (QString::fromLocal8Bit("微软雅黑"))
#define STU_FONT_HEIGHT                     12
#define STU_FONT_WEIGHT                     QFont::Normal


#define STU_GREEN_LINE                      qRgb(27, 133, 118)



#define STU_DELETE_PTR(ptr) if (ptr) { delete ptr; ptr = NULL;}


#define _create_label(label, label_caption, x, y)\
    label = new QLabel(this);\
    label->setText(label_caption);\
    label->move(x, y)

#define _create_comboBox(comboBox, comboBoxName, x, y)\
    comboBox = new MComboBox(this);\
    comboBox->setObjectName(comboBoxName);\
    comboBox->move(x, y)

#define _create_lineEdit_float(dataEdit, dataEditName, data, prec, unit, x, y) \
    dataEdit = new MDataEdit(data, 0, 'f', prec, unit, this);\
    dataEdit->setObjectName(dataEditName);\
    dataEdit->move(x, y)

#define _create_lineEdit_int(dataEdit, dataEditName, data, unit, x, y) \
    dataEdit = new MDataEdit(data, 0, 10, unit, this);\
    dataEdit->setObjectName(dataEditName);\
    dataEdit->move(x, y)