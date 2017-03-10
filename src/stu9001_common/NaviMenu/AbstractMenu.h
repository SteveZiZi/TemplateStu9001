#pragma once

#include <qglobal.h>
#include <QtGui/QWidget>

class CAbstractMenu;
class CAbstractMenuContent
{
public:
    CAbstractMenuContent(CAbstractMenu* pMenu = NULL);
    virtual ~CAbstractMenuContent();

    enum {
        CONTENT_SHOW,
        CONTENT_FOCUE,
        CONTENT_HIDE
    };

    virtual void _ShowContent(int style, quint32 data) = 0;
    virtual void _LeaveContent() = 0;
    virtual void _HideContent() = 0;

    CAbstractMenu* _GetMenu(void) {return m_pMenu;}
    void _SetMenu(CAbstractMenu* pMenu) {m_pMenu = pMenu;}

private:
    CAbstractMenu* m_pMenu;
};

class QSize;
class CAbstractMenu
{
public:
    typedef enum {
        UN_INIT,
        DISPLAY_OWNER,              //仅显示自身
        OWNER_FOCUS,                //自身获得焦点
        DISPLAY_CHILD,              //显示child 焦点在自身
        ENTER_CHILD                 //进入child，焦点在child上
    }ENTRANCE_STYLE;

    CAbstractMenu(CAbstractMenu* pParentObj = NULL);
    virtual ~CAbstractMenu();

    /*
     *  处理子菜单退出的代码
     */
    virtual void OnChildEsc() = 0;

    /*
     *  进入菜单
     */
    virtual void EnterMenu(ENTRANCE_STYLE style, quint32 param) = 0;

    /*
     *  离开本菜单 返回上一级菜单
     */
    virtual void LeaveMenu() = 0;

    /*
     *  隐藏本菜单 及后级子菜单
     */
    virtual void HideMenu(void) = 0;

    /*
     *  隐藏后级菜单
     */
    virtual void HideChildAndContenct(void) = 0;

    virtual QWidget* widget() = 0;

public:
    void SetParentMenu(CAbstractMenu* parent) {m_pParentObj = parent;}
    CAbstractMenu* GetParentMenu() {return m_pParentObj;}

private:
    CAbstractMenu* m_pParentObj;
};

