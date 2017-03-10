#pragma once

#include <mPushButton>

#include "AbstractMenu.h"

class CNaviMenu;

class CNaviMenuItem : public CAbstractMenu, public MPushButton
{
public:
    CNaviMenuItem(CNaviMenu *parent, CAbstractMenu* pChild = 0, CAbstractMenuContent* pContent = 0);
    virtual ~CNaviMenuItem();

    ///
    ///< from CAbstractObj
    ///
    /*
     *  处理子菜单退出的代码
     */
    virtual void OnChildEsc();

    /*
     *  进入菜单
     */
    virtual void EnterMenu(ENTRANCE_STYLE style, quint32 param);

    /*
     *  离开本菜单 返回上一级菜单
     */
    virtual void LeaveMenu();

    /*
     *  隐藏本菜单 及后级子菜单
     */
    virtual void HideMenu(void);

    /*
     *  隐藏后级菜单
     */
    virtual void HideChildAndContenct(void);

    virtual QWidget* widget() {return dynamic_cast<QWidget*>(this);}
    ///
    ///< end from CAbstractObj
    ///



    bool strectchOut() {return pressMode();}


    void setChildMenu(CAbstractMenu* pChild) {
        pChild->SetParentMenu(this);
        m_pChildMenu = pChild;
    }
    CAbstractMenu* childMenu(void) {
        return m_pChildMenu;
    }

    void setContent(CAbstractMenuContent* pContent) {
        pContent->_SetMenu(this);
        m_pContent = pContent;
    }
    CAbstractMenuContent* content() {return m_pContent;}


    friend CNaviMenu;

private:
    virtual void keyPressEvent(QKeyEvent *e);

private:
    CAbstractMenu* m_pChildMenu;
    CAbstractMenuContent* m_pContent;
    CNaviMenu* m_pNaviMenu;

};