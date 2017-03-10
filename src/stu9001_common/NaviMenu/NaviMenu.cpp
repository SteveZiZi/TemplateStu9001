#include "NaviMenu.h"
#include "NaviMenuItem.h"

#include <QtGui>

#include "debug.h"


CNaviMenu::CNaviMenu(QWidget *parent, Qt::WindowFlags f)
: QLabel(parent, f)
{
}

CNaviMenu::~CNaviMenu()
{

}

void CNaviMenu::moveToNext(void)
{
    NaviMenuItemList::ConstIterator it = pos(dynamic_cast<CNaviMenuItem*>(QWidget::focusWidget()));
    it++;
    if (it == listNaviMenuItem.constEnd()) {
        (*listNaviMenuItem.constBegin())->setFocus();
    }
    else {
        (*it)->setFocus();
    }
}

void CNaviMenu::moveToPre(void)
{
    NaviMenuItemList::ConstIterator it = pos(dynamic_cast<CNaviMenuItem*>(QWidget::focusWidget()));
    if (it == listNaviMenuItem.constBegin()) {
        it = listNaviMenuItem.constEnd();
    }
    (*(--it))->setFocus();
}


void CNaviMenu::menuResize()
{
    CNaviMenuItem* pItem = NULL;
    int y = 0;
    for(int i = 0; i < listNaviMenuItem.size(); i++) {
        pItem = listNaviMenuItem.at(i);
        pItem->move(0, y);
        y += pItem->size().height() + 1;
        if (pItem->strectchOut() && pItem->childMenu()) {
            QSize size = pItem->childMenu()->widget()->size();
            y += size.height();
        }
    }
}


void CNaviMenu::addItem(CNaviMenuItem* pMenuItem)
{
    pMenuItem->m_pNaviMenu = this;
    listNaviMenuItem.append(pMenuItem);
}

CNaviMenuItem* CNaviMenu::item(int pos)
{
    Q_ASSERT(pos < listNaviMenuItem.size());

    return listNaviMenuItem.at(pos);
}

int CNaviMenu::count(void)
{
    return listNaviMenuItem.size();
}


void CNaviMenu::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "CNaviMenu::keyPressEvent" << hex << e->key();

    switch(e->key()) 
    {
    case Qt::Key_Escape:
        this->setFocus();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        item(0)->setFocus();
        break;
    default:
        QLabel::keyPressEvent(e);
        break;
    }
}

