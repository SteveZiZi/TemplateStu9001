#include "NaviMenuItem.h"
#include "NaviMenu.h"
#include <QtGui/QtEvents>
#include <QtGui/QDialog>

#include "debug.h"

CNaviMenuItem::CNaviMenuItem(CNaviMenu *parent, CAbstractMenu* pChild, CAbstractMenuContent* pContent)
: MPushButton(parent)
, m_pChildMenu(pChild)
, m_pContent(pContent)
, m_pNaviMenu(parent)
{
    this->setDefault(true);
}

CNaviMenuItem::~CNaviMenuItem()
{
    if (m_pChildMenu) {
        delete m_pChildMenu;
    }
    if (m_pContent) {
        delete m_pContent;
    }
}


/*
 *  通知主菜单 对象已经退出
 */
void CNaviMenuItem::OnChildEsc()
{
    LeaveMenu();
    setFocus(Qt::BacktabFocusReason);
}

/*
 *  进入菜单
 */
void CNaviMenuItem::EnterMenu(ENTRANCE_STYLE style, quint32 param)
{
    if (strectchOut()) {
        return ;
    }
    SetPressMode(TRUE);
    if (m_pChildMenu) {
        m_pChildMenu->EnterMenu(CAbstractMenu::DISPLAY_OWNER, 0);
        m_pChildMenu->widget()->setFocus(Qt::TabFocusReason);
    }
    else if (m_pContent) {
        if (style == CAbstractMenu::DISPLAY_OWNER) {
            m_pContent->_ShowContent(CAbstractMenuContent::CONTENT_SHOW, 0);
        }
        else {
            m_pContent->_ShowContent(CAbstractMenuContent::CONTENT_FOCUE, 0);
        }
    }

    m_pNaviMenu->menuResize();
}

/*
 *  离开本菜单
 */
void CNaviMenuItem::LeaveMenu()
{
    if (strectchOut())
    {
        HideChildAndContenct();
        SetPressMode(FALSE);
        m_pNaviMenu->menuResize();

        CAbstractMenu* pParent = GetParentMenu();
        if (pParent)
            pParent->OnChildEsc();
    }
}

/*
 *  隐藏本菜单 及后级子菜单
 */
void CNaviMenuItem::HideMenu(void)
{
    HideChildAndContenct();
}

/*
 *  隐藏后级菜单
 */
void CNaviMenuItem::HideChildAndContenct(void)
{
    if (m_pChildMenu)
        m_pChildMenu->HideMenu();
    else if (m_pContent) {
        m_pContent->_HideContent();
    }
}

void CNaviMenuItem::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    qDebug() << "CNaviMenuItem::keyPressEvent  key:" << hex << key;

    switch(key) 
    {
    case Qt::Key_Escape:
    case Qt::Key_Left:
        if (strectchOut()) {
            LeaveMenu();
        }
        else 
            e->ignore();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Right:
        EnterMenu(CAbstractMenu::DISPLAY_CHILD, 0);
        break;
    case Qt::Key_Up:
        if (!strectchOut())
            m_pNaviMenu->moveToPre();
        break;
    case Qt::Key_Down:
        if (!strectchOut())
            m_pNaviMenu->moveToNext();
        break;
    default:
        MPushButton::keyPressEvent(e);
        break;
    }
}
