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
        DISPLAY_OWNER,              //����ʾ����
        OWNER_FOCUS,                //�����ý���
        DISPLAY_CHILD,              //��ʾchild ����������
        ENTER_CHILD                 //����child��������child��
    }ENTRANCE_STYLE;

    CAbstractMenu(CAbstractMenu* pParentObj = NULL);
    virtual ~CAbstractMenu();

    /*
     *  �����Ӳ˵��˳��Ĵ���
     */
    virtual void OnChildEsc() = 0;

    /*
     *  ����˵�
     */
    virtual void EnterMenu(ENTRANCE_STYLE style, quint32 param) = 0;

    /*
     *  �뿪���˵� ������һ���˵�
     */
    virtual void LeaveMenu() = 0;

    /*
     *  ���ر��˵� �����Ӳ˵�
     */
    virtual void HideMenu(void) = 0;

    /*
     *  ���غ󼶲˵�
     */
    virtual void HideChildAndContenct(void) = 0;

    virtual QWidget* widget() = 0;

public:
    void SetParentMenu(CAbstractMenu* parent) {m_pParentObj = parent;}
    CAbstractMenu* GetParentMenu() {return m_pParentObj;}

private:
    CAbstractMenu* m_pParentObj;
};

