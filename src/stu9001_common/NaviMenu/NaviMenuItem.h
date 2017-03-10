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
     *  �����Ӳ˵��˳��Ĵ���
     */
    virtual void OnChildEsc();

    /*
     *  ����˵�
     */
    virtual void EnterMenu(ENTRANCE_STYLE style, quint32 param);

    /*
     *  �뿪���˵� ������һ���˵�
     */
    virtual void LeaveMenu();

    /*
     *  ���ر��˵� �����Ӳ˵�
     */
    virtual void HideMenu(void);

    /*
     *  ���غ󼶲˵�
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