#pragma once

#include <QtGui/QGroupBox>

class QLabel;

//
//-----------------------------------------------------------------------------
// CNaviMenuMgr
//
//  管理导航菜单的创建
//-----------------------------------------------------------------------------
//
class CTopBarMgr : public QGroupBox
{
    Q_OBJECT

public:
    CTopBarMgr(QWidget* parent = 0);
    ~CTopBarMgr();

private:
    QLabel* caption;
};