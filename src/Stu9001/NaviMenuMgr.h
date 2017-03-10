#pragma once


class QWidget;
class CNaviMenu;
class CNaviMenuItem;
class CAbstractMenu;

//
//-----------------------------------------------------------------------------
// CNaviMenuMgr
//
//  管理导航菜单的创建
//-----------------------------------------------------------------------------
//
class CNaviMenuMgr
{
public:
    //
    //=============================================================================
    // 控件创建及样式
    //=============================================================================
    //
    CNaviMenuMgr (QWidget *parent);
    virtual ~CNaviMenuMgr ();

    enum NAVI_MENU_ENUM{
        PARAM_CFG_ITEM = 0,
        DATA_SHOW_ITEM,
        SET_VALUE_ITEM,
        DEVICE_VERIFY_ITEM,
        ELEC_OPERAT_ITEM,
        TREND_CHART_ITEM,
        SHOW_VIDEO_ITEM,
        EVENT_REPORT_ITEM
    };

    enum PARAM_CFG_MENU_ENUM{
        SYSTEM_CFG_ITEM = 0,
        ENERGY_CFG_ITEM,
        TEMP_HUMIDITY_CFG_ITEM,
        MACHINERY_CHARACTERISTIC_ITEM,
        MOTOR_CFG_ITEM
    };

public:
    void init(void);
    void deinit(void);

    QWidget* parent() {return m_parent;}

protected:
    void CreateNaviMenus(void);

private:
    CAbstractMenu* CreateParamCfgMenu(int x, int y, int w, int h = -1);
    CAbstractMenu* CreateSystemCfgMenu(int x, int y, int w, int h = -1);
    CAbstractMenu* CreateEnergyCfgMenu(int x, int y, int w, int h = -1);
    CAbstractMenu* CreateTempHumCfgMenu(int x, int y, int w, int h = -1);

    CAbstractMenu* CreateDataShowMenu(int x, int y, int w, int h = -1);

    CAbstractMenu* CreateConstValueMenu(int x, int y, int w, int h = -1);

    CAbstractMenu* CreateElecOperatorMenu(int x, int y, int w, int h = -1);

    CAbstractMenu* CreateTrendMenu(int x, int y, int w, int h = -1);

private:
    QWidget* m_parent;
    CNaviMenu* m_pNaviMenu;
};


