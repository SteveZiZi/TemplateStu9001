#pragma once

#include <QtGui/QGroupBox>

class QLabel;

//
//-----------------------------------------------------------------------------
// CNaviMenuMgr
//
//  �������˵��Ĵ���
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