#pragma once

#include <mListWidget>
#include "AbstractMenu.h"

#include <QMap>

class CListCtrlMenu : public CAbstractMenu, public MListWidget
{
public:
    CListCtrlMenu(QWidget *parent=0, CAbstractMenu* pParentObj = 0);
    virtual ~CListCtrlMenu();

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


    /*
     *  添加Menu Content
     *  
     *  @Note：
     *      item=-1：对本菜单的子项都有效
     */
    bool addContent(int item, CAbstractMenuContent* pContent);
    CAbstractMenuContent* content(int item);
    int contentCount(void);
    void autoStrectContent(bool bAuto = true) {m_bAutoStretchContent = bAuto;}

    /*
     *  子菜单接口
     */
    bool setChildMenu(int item, CAbstractMenu* childObj);
    CAbstractMenu* childMenu(int item);
    int childMenuCount(void);


    void moveToNext(void);
    void moveToPre(void);

protected:
    virtual void keyPressEvent(QKeyEvent *e);

private:
    void destroyAllChild(void);
    void destroyAllContent(void);

private:
    typedef QMap<int, CAbstractMenu*> mapChildMenu;
    typedef QMap<int, CAbstractMenuContent*> mapMenuContent;

    ENTRANCE_STYLE m_entranceStyle;
    int _curSelItem;
    bool           m_bAutoStretchContent;

    mapMenuContent m_mapContent;
    mapChildMenu m_mapChild;
};


inline bool CListCtrlMenu::setChildMenu(int item, CAbstractMenu* childObj)
{
    if (childMenu(item)) {
        return false;
    }
    childObj->SetParentMenu(this);
    m_mapChild.insert(item, childObj);
    return true;
}

inline CAbstractMenu* CListCtrlMenu::childMenu(int item) 
{
    mapChildMenu::iterator it = m_mapChild.find(item);
    if(it != m_mapChild.end()) {
        return it.value();
    }
    return NULL;
}

inline int CListCtrlMenu::childMenuCount(void)
{
    return m_mapChild.size();
}

inline void CListCtrlMenu::destroyAllChild(void)
{
    int nCount = childMenuCount();
    CAbstractMenu* pObj = NULL;

    for(int i = 0; i < nCount; i++)
    {
        pObj = childMenu(i);
        if (pObj) {
            delete pObj;
        }
    }
    m_mapChild.clear();
}


inline bool CListCtrlMenu::addContent(int item, CAbstractMenuContent* pContent)
{
    if (content(item)) {
        return false;
    }
    pContent->_SetMenu(this);
    m_mapContent.insert(item, pContent);
    return TRUE;
}

inline CAbstractMenuContent* CListCtrlMenu::content(int item)
{
    mapMenuContent::iterator it = m_mapContent.find(item);
    if(it != m_mapContent.end()) {
        return it.value();
    }
    else {
        it = m_mapContent.find(-1);
        if (it != m_mapContent.end()) {
            return it.value();
        }
    }
    return NULL;
}

inline int CListCtrlMenu::contentCount(void)
{
    return m_mapContent.size();
}

inline void CListCtrlMenu::destroyAllContent(void)
{
    //由CMenuContentMgr统一销毁
//     int nCount = contentCount();
//     CAbstractMenuContent* pObj = NULL;
// 
//     for(int i = 0; i < nCount; i++)
//     {
//         pObj = content(i);
//         if (pObj) {
//             delete pObj;
//         }
//     }
// 
//     m_mapContent.clear();
}