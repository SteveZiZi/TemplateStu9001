#include "stu9001.h"
#include <QKeyEvent>
#include <QtGui>
#include <QApplication>

#include <mListWidget>
#include "../MenuContentMgr.h"
#include "../NaviMenuMgr.h"
#include "../ExceptionEventMgr.h"
#include "../TopBarMgr.h"
#include "../BottomBarMgr.h"
#include "../main/MixImage.h"
#include "../main/MeasureList.h"
#include "../main/MeasureItem.h"

#include <modbusDevMgr>
#include <stu_config>

#include "common.h"

#include "debug.h"

#define MAIN_IMAGE_WIDTH            239
#define MAIN_IMAGE_HEIGHT           419

#define MEASURE_LIST_L             (STU_P_BODY1_L+MAIN_IMAGE_WIDTH+1)
#define MEASURE_LIST_T             (STU_P_BODY1_T)
#define MEASURE_LIST_W             (STU_SCREEN_W-MEASURE_LIST_L)
#define MEASURE_LIST_H             (STU_P_BODY1_H)


Stu9001::Stu9001(QWidget *parent, Qt::WFlags flags)
    : QDialog(parent, flags)
    , m_pNaviMenuMgr(NULL)
    , m_pTopBarMgr(NULL)
    , m_pBottomBarMgr(NULL)
    , m_pMainImage(NULL)
    , m_pMeasureList(NULL)
{
    setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    /*
     *  数据层的初始化
     */
    ModbusConfig modbus[stu_config::MODBUS_DEV_NUM];
    QByteArray ba[stu_config::MODBUS_DEV_NUM]; 
    for(int i = 0; i < stu_config::MODBUS_DEV_NUM; i++) {
        ba[i] = stu_config::devComPort(i).toLatin1(); 
        modbus[i].port = ba[i].data();
        modbus[i].baudRate = stu_config::devComBaudRate(i);
        modbus[i].slaveId = stu_config::devComSlaveId(i);
        modbus[i].enable = stu_config::devComIsEnable(i);
    }
    CModbusDevMgr::init(modbus, stu_config::MODBUS_DEV_NUM);

    CExceptionEventMgr::getInstance()->init();

    m_pTopBarMgr = new CTopBarMgr(this);
    m_pTopBarMgr->setGeometry(STU_P_TOP_L, STU_P_TOP_T, STU_P_TOP_W, STU_P_TOP_H);
    m_pTopBarMgr->setObjectName(QString::fromLocal8Bit("topBarMgr"));

    m_pBottomBarMgr = new CBottomBarMgr(this);
    m_pBottomBarMgr->setGeometry(STU_P_BOTTOM_L, STU_P_BOTTOM_T, STU_P_BOTTOM_W, STU_P_BOTTOM_H);
    m_pBottomBarMgr->setObjectName(QString::fromLocal8Bit("bottomBarMgr"));

    m_pMainImage = new CMixImage(this);
    m_pMainImage->setGeometry(STU_P_BODY1_L, STU_P_BODY1_T, MAIN_IMAGE_WIDTH, MAIN_IMAGE_HEIGHT);
    m_pMainImage->setObjectName(QString::fromLocal8Bit("mainImage"));
    m_pMainImage->lower();

    m_pMeasureList = new CMeasureList(this);
    m_pMeasureList->setGeometry(MEASURE_LIST_L, MEASURE_LIST_T, MEASURE_LIST_W, MEASURE_LIST_H);
    m_pMeasureList->setObjectName(QString::fromLocal8Bit("measureList"));
    m_pMeasureList->create();
    m_pMeasureList->lower();

    CMenuContentMgr::GetInstance()->SetMainDlg(this);
    m_pNaviMenuMgr = new CNaviMenuMgr(this);
    m_pNaviMenuMgr->init();
}

Stu9001::~Stu9001()
{
    CExceptionEventMgr::getInstance()->deinit();
}

void Stu9001::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    qDebug() << "Stu9001::keyPressEvent:" << hex << event->key();

    if (key == Qt::Key_Escape || key == Qt::Key_Return || key ==  Qt::Key_Enter) {
        event->accept();
    }
    else if (key == Qt::Key_F7) {
        qApp->exit();
    }
    else {
        QDialog::keyPressEvent(event);
    }
}

void Stu9001::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::Yes ==
        QMessageBox::question(this, QString::fromLocal8Bit("退出程序"), QString::fromLocal8Bit("确定退出程序"), QMessageBox::Yes|QMessageBox::No))
    {
        event->accept();
    }
    else {
        event->ignore();
    }
}