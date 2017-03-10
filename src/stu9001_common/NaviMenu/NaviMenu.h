#pragma once

#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class CNaviMenuItem;
class CNaviMenu : public QLabel
{
public:
    CNaviMenu(QWidget *parent=0, Qt::WindowFlags f=0);
    virtual ~CNaviMenu();

    void moveToNext(void);
    void moveToPre(void);

public slots:
    void menuResize();

public:
    void addItem(CNaviMenuItem* pMenuItem);
    CNaviMenuItem* item(int pos);
    int count(void);

private:
    virtual void keyPressEvent(QKeyEvent *e);

    typedef QList<CNaviMenuItem*> NaviMenuItemList;

    NaviMenuItemList::ConstIterator pos(CNaviMenuItem* item)
    {
        NaviMenuItemList::const_iterator it = listNaviMenuItem.constBegin();
        for( ; it != listNaviMenuItem.constEnd();it++){
            if (*it == item) {
                break;
            }
        }
        return it;
    }

private:
     NaviMenuItemList listNaviMenuItem;
};