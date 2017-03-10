#include "ListCtrlMenu.h"

#include <QtGui>

#include "debug.h"

CListCtrlMenu::CListCtrlMenu(QWidget *parent, CAbstractMenu* pParentObj)
: MListWidget(parent)
, CAbstractMenu(pParentObj)
, m_entranceStyle(UN_INIT)
, _curSelItem(0)
, m_bAutoStretchContent(true)
{
}

CListCtrlMenu::~CListCtrlMenu()
{
    destroyAllChild();
    destroyAllContent();
}

/*
 *  处理子菜单退出的代码
 */
void CListCtrlMenu::OnChildEsc()
{
    m_entranceStyle = DISPLAY_CHILD;
    setFocus(Qt::BacktabFocusReason);
    setCurrentRow(_curSelItem);
}

/*
 *  进入菜单
 */
void CListCtrlMenu::EnterMenu(ENTRANCE_STYLE style, quint32 param)
{
    if (style == UN_INIT) {
        return ;
    }

    if (!isVisible()) {
        show();
    }
    if (style == OWNER_FOCUS) {
        setFocus(Qt::TabFocusReason);
    }

    CAbstractMenu* pChildObj = childMenu(_curSelItem);
    if (pChildObj) {
        if (style == ENTER_CHILD) {
            pChildObj->EnterMenu(OWNER_FOCUS, _curSelItem);
        }
        else if (style == DISPLAY_CHILD) {
            pChildObj->EnterMenu(DISPLAY_CHILD, _curSelItem);
        }
    }

    CAbstractMenuContent* pContent = content(_curSelItem);
    if (pContent){
        if (style == ENTER_CHILD) {
            pContent->_ShowContent(CAbstractMenuContent::CONTENT_FOCUE, _curSelItem);
            this->raise();
        }
        else if (style == DISPLAY_CHILD) {
            pContent->_ShowContent(CAbstractMenuContent::CONTENT_SHOW, _curSelItem);
            this->raise();
        }
        else {
            if (m_bAutoStretchContent) {
                pContent->_ShowContent(CAbstractMenuContent::CONTENT_SHOW, _curSelItem);
                this->raise();
            }
        }
    }

    if (pContent || pChildObj)
        m_entranceStyle = style;

    setCurrentRow(_curSelItem);
}

/*
 *  离开本菜单
 */
void CListCtrlMenu::LeaveMenu()
{
    m_entranceStyle = UN_INIT;
    CAbstractMenu* pParent = GetParentMenu();
    if (pParent)
        pParent->OnChildEsc();
}

/*
 *  隐藏本菜单 及后级子菜单
 */
void CListCtrlMenu::HideMenu(void)
{
    if (isVisible()) {
        HideChildAndContenct();
        hide();
        _curSelItem = 0;
        setCurrentRow(_curSelItem);
    }
}

/*
 *  隐藏后级菜单
 */
void CListCtrlMenu::HideChildAndContenct(void)
{
    CAbstractMenu* pChild = childMenu(_curSelItem);
    if (pChild) {
        pChild->HideMenu();
    }

    CAbstractMenuContent* pContent = content(_curSelItem);
    if (pContent) {
        pContent->_HideContent();
    }
}

void CListCtrlMenu::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    qDebug() << "CNaviMenuItem::keyPressEvent  key:" << hex << key;

    switch(key) 
    {
    case Qt::Key_Escape:
    case Qt::Key_Left:
        LeaveMenu();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Right:
        EnterMenu(CAbstractMenu::ENTER_CHILD, _curSelItem);
        break;
    case Qt::Key_Up:
        moveToPre();
        break;
    case Qt::Key_Down:
        moveToNext();
        break;
    default:
        MListWidget::keyPressEvent(e);
        break;
    }
}


void CListCtrlMenu::moveToNext(void)
{
    HideChildAndContenct();
    _curSelItem++;
    if (_curSelItem >= this->count()) 
        _curSelItem = 0;
    setCurrentRow(_curSelItem);
    EnterMenu(m_entranceStyle, _curSelItem);
}

void CListCtrlMenu::moveToPre(void)
{
    HideChildAndContenct();
    _curSelItem--;
    if (_curSelItem < 0) 
        _curSelItem = this->count()-1;

    setCurrentRow(_curSelItem);
    EnterMenu(m_entranceStyle, _curSelItem);
}