#include "NaviMenuMgr.h"

#include <QtGui>
#include <NaviMenu>
#include <NaviMenuItem>
#include "common.h"

#include <mListWidget>
#include <ListCtrlMenu>
#include <stu_utility>
#include "common.h"
#include "MenuContentMgr.h"
#include <stu_config>
#include "debug.h"


CNaviMenuMgr::CNaviMenuMgr(QWidget *parent)
: m_parent(parent)
, m_pNaviMenu(0)
{

}

CNaviMenuMgr::~CNaviMenuMgr ()
{
    
}


void CNaviMenuMgr::init(void)
{
    CreateNaviMenus();
}

void CNaviMenuMgr::deinit(void)
{

}

void CNaviMenuMgr::CreateNaviMenus(void)
{
    const QString naviItemCaption[] = {
        QObject::tr("Param Config"),
        QObject::tr("Data Show"),
        QObject::tr("Const Value"),
        QObject::tr("Machine Verify"),
        QObject::tr("Motor Operator"),
        QObject::tr("Trend"),
        QObject::tr("Video"),
        QObject::tr("Event"),
    };

    m_pNaviMenu = new CNaviMenu(m_parent);
    m_pNaviMenu->setObjectName("NaviMenu");
    m_pNaviMenu->setGeometry(QRect(STU_P_NAVI_L, STU_P_NAVI_T, STU_P_NAVI_W, STU_P_NAVI_H));

    CNaviMenuItem *pushButton = 0;
    for(int i = 0; i < 8; i++) {
        pushButton = new CNaviMenuItem(m_pNaviMenu);
        pushButton->setObjectName(QString("NaviMenuItem%1").arg(i));
        pushButton->setGeometry(QRect(0, i*(STU_P_NAVI_ITEM_H+1), 90, STU_P_NAVI_ITEM_H));
        pushButton->setText(naviItemCaption[i]);
        m_pNaviMenu->addItem(pushButton);
    }

    pushButton = m_pNaviMenu->item(0);
    QRect rect = pushButton->rect();
    QPoint pos = pushButton->mapToGlobal(rect.topLeft());
    pos.setY(pos.y() + rect.height());
    pushButton->setChildMenu(CreateParamCfgMenu(pos.x(), pos.y(), rect.width()));

    pushButton = m_pNaviMenu->item(1);
    rect = pushButton->rect();
    pos = pushButton->mapToGlobal(rect.topLeft());
    pos.setY(pos.y() + rect.height());
    pushButton->setChildMenu(CreateDataShowMenu(pos.x(), pos.y(), rect.width()));

    pushButton = m_pNaviMenu->item(2);
    rect = pushButton->rect();
    pos = pushButton->mapToGlobal(rect.topLeft());
    pos.setY(pos.y() + rect.height());
    if (stu_config::isCP9000())
        pushButton->setChildMenu(CreateConstValueMenu(pos.x(), pos.y(), rect.width()));
    else
        pushButton->setContent(CMenuContentMgr::GetMenuContent(STU_CASTBACK_CONST_VALUE_CONTENT));

    pushButton = m_pNaviMenu->item(4);
    rect = pushButton->rect();
    pos = pushButton->mapToGlobal(rect.topLeft());
    pos.setY(pos.y() + rect.height());
    pushButton->setChildMenu(CreateElecOperatorMenu(pos.x(), pos.y(), rect.width()));

    pushButton = m_pNaviMenu->item(5);
    rect = pushButton->rect();
    pos = pushButton->mapToGlobal(rect.topLeft());
    pos.setY(pos.y() + rect.height());
    pushButton->setChildMenu(CreateTrendMenu(pos.x(), pos.y(), rect.width()));



    pushButton = m_pNaviMenu->item(7);
    rect = pushButton->rect();
    pos = pushButton->mapToGlobal(rect.topLeft());
    pos.setY(pos.y() + rect.height());
    pushButton->setContent(CMenuContentMgr::GetMenuContent(STU_EVENT_REPORT_CONTENT));
}

//////////////////////////////////////////////////////////////////////////
//
//  主菜单
//
//////////////////////////////////////////////////////////////////////////
CAbstractMenu* CNaviMenuMgr::CreateParamCfgMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_primary"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("System Param")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Elec Param")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Temp Hum Param")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Mechanical Property")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Motor Param")));

    if (h == -1) {
        h = listMenu->count()*27+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加子菜单
    QRect rect = listMenu->rect();
    QPoint pos = listMenu->mapToGlobal(rect.topLeft());
    pos.setX(pos.x() + STU_P_NAVI_W);
    listMenu->setChildMenu(0, CreateSystemCfgMenu(pos.x(), pos.y(), STU_P_NAVI_W));
    pos.setY(pos.y() + 27);
    listMenu->setChildMenu(1, CreateEnergyCfgMenu(pos.x(), pos.y(), STU_P_NAVI_W));
    pos.setY(pos.y() + 27);
    listMenu->setChildMenu(2, CreateTempHumCfgMenu(pos.x(), pos.y(), STU_P_NAVI_W));

    listMenu->autoStrectContent(false);
    listMenu->addContent(3, CMenuContentMgr::GetMenuContent(STU_MACHINE_CHARACTRISTIC_PARAM_CONTENT));
    listMenu->addContent(4, CMenuContentMgr::GetMenuContent(STU_MOTOR_PARAM_CONTENT));

    return listMenu;
}

CAbstractMenu* CNaviMenuMgr::CreateDataShowMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_primary"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("Measure Show")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Sample Show")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Switch In Show")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Temp Hum Show")));

    if (h == -1) {
        h = listMenu->count()*27+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加子菜单
    listMenu->autoStrectContent(false);
    listMenu->addContent(0, CMenuContentMgr::GetMenuContent(STU_MEASURE_SHOW_CONTENT));
    listMenu->addContent(1, CMenuContentMgr::GetMenuContent(STU_SAMPLE_SHOW_CONTENT));
    listMenu->addContent(2, CMenuContentMgr::GetMenuContent(STU_SWITCH_IN_SHOW_CONTENT));
    listMenu->addContent(3, CMenuContentMgr::GetMenuContent(STU_TEMP_HUM_SHOW_CONTENT));

    return listMenu;
}

CAbstractMenu* CNaviMenuMgr::CreateConstValueMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_primary"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("Const Value Modfiy")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Plate Castback")));

    if (h == -1) {
        h = listMenu->count()*27+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加子菜单
    listMenu->autoStrectContent(false);
    listMenu->addContent(0, CMenuContentMgr::GetMenuContent(STU_CONST_VALUE_MODIFY_CONTENT));
    listMenu->addContent(1, CMenuContentMgr::GetMenuContent(STU_PLATE_CASTBACK_CONTENT));

    return listMenu;
}

CAbstractMenu* CNaviMenuMgr::CreateElecOperatorMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_primary"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("cubicle operator")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("barrow operator")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("earth knife operator")));

    if (h == -1) {
        h = listMenu->count()*27+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加子菜单
    listMenu->autoStrectContent(false);
    listMenu->addContent(-1, CMenuContentMgr::GetMenuContent(STU_ELEC_OPERATOR_CONTENT));

    return listMenu;
}

CAbstractMenu* CNaviMenuMgr::CreateTrendMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_primary"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("Wiring Measure Temp")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Cubicle Temp")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Machine Characteristic")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Harmonics Param")));

    if (h == -1) {
        h = listMenu->count()*27+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加子菜单
    listMenu->autoStrectContent(false);
    listMenu->addContent(0, CMenuContentMgr::GetMenuContent(STU_WIRING_MEASURE_TEMP_TREND_CONTENT));
    listMenu->addContent(1, CMenuContentMgr::GetMenuContent(STU_CUBICLE_TEMP_HUM_TREND_CONTENT));
    listMenu->addContent(2, CMenuContentMgr::GetMenuContent(STU_MACHINE_CHARACTRISTIC_TREND_CONTENT));
    listMenu->addContent(3, CMenuContentMgr::GetMenuContent(STU_HARNOICS_PARAM_TREND_CONTENT));

    return listMenu;
}

//////////////////////////////////////////////////////////////////////////
//
//  参数设置 
//
//////////////////////////////////////////////////////////////////////////
/*
 *  参数设置 -> 系统参数
 */
CAbstractMenu* CNaviMenuMgr::CreateSystemCfgMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_second"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("System Info")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Password Setting")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Network Setting")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Time Setting")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Simulation Views")));
    if (h == -1) {
        h = listMenu->count()*35+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加页面
	listMenu->addContent(0, CMenuContentMgr::GetMenuContent(STU_SYSTEM_CONFIG_CONTENT));
    listMenu->addContent(1, CMenuContentMgr::GetMenuContent(STU_SET_PASSWORD_CONTENT));
    listMenu->addContent(2, CMenuContentMgr::GetMenuContent(STU_NETWORK_SETTINGS_CONTENT));
    listMenu->addContent(3, CMenuContentMgr::GetMenuContent(STU_TIME_SETTINGS_CONTENT));
    listMenu->addContent(4, CMenuContentMgr::GetMenuContent(STU_SIMULATION_VIEWS_CONTENT));

    return listMenu;
}
/*
 *  参数设置 -> 电能参数
 */
CAbstractMenu* CNaviMenuMgr::CreateEnergyCfgMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_second"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("Measure Param")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Haronics Param")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Wiring Types")));

    if (h == -1) {
        h = listMenu->count()*35+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加页面
    listMenu->addContent(0, CMenuContentMgr::GetMenuContent(STU_MEASURE_PARAM_CONTENT));
    listMenu->addContent(1, CMenuContentMgr::GetMenuContent(STU_HARNOICS_PARAM_CONTENT));
    listMenu->addContent(2, CMenuContentMgr::GetMenuContent(STU_WIRING_TYPES_CONTENT));

    return listMenu;
}

/*
 *  参数设置 -> 温湿参数
 */
CAbstractMenu* CNaviMenuMgr::CreateTempHumCfgMenu(int x, int y, int w, int h)
{
    CListCtrlMenu* listMenu = new CListCtrlMenu(m_parent);
    listMenu->setObjectName(QString::fromUtf8("ListCtrlMenu_second"));

    listMenu->addItem(new QListWidgetItem(QObject::tr("Wiring Measure Temp Param")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("Wiring ID Serial")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("TH1")));
    listMenu->addItem(new QListWidgetItem(QObject::tr("TH2")));

    if (h == -1) {
        h = listMenu->count()*35+5;
    }
    listMenu->setGeometry(QRect(x, y, w, h));

    for(int i = 0; i < listMenu->count(); i++) {
        QListWidgetItem* item = listMenu->item(i);
        item->setTextAlignment(Qt::AlignCenter);
    }
    listMenu->hide();

    //添加页面
    listMenu->addContent(0, CMenuContentMgr::GetMenuContent(STU_WIRING_MEASURE_TEMP_PARAM_CONTENT));
    listMenu->addContent(1, CMenuContentMgr::GetMenuContent(STU_WIRING_ID_SERIAL_CONTENT));
    listMenu->addContent(2, CMenuContentMgr::GetMenuContent(STU_TH1_CONTENT));
    listMenu->addContent(3, CMenuContentMgr::GetMenuContent(STU_TH2_CONTENT));

    return listMenu;
}