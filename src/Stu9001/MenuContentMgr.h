#pragma once

class CAbstractMenu;
class CAbstractMenuContent;
class QWidget;

#include <QtGlobal>
#include <QMap>

class CMenuContentMgr 
{
public:
    static CMenuContentMgr* GetInstance();
    static CAbstractMenuContent* GetMenuContent(quint32 pageID);

    void SetMainDlg(QWidget* main);

private:
    CAbstractMenuContent* CreateContent(quint32 pageID);
    void RemoveContent();

private:
    CMenuContentMgr();
    ~CMenuContentMgr();

private:
    typedef QMap<int, CAbstractMenuContent*> mapMenuContent;
    mapMenuContent m_menuContent;

    QWidget* m_parent;

};