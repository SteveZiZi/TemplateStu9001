#pragma once

#include <QtGui/QGroupBox>

class QLabel;
class QTimer;

//
//-----------------------------------------------------------------------------
// CNaviMenuMgr
//
//  管理导航菜单的创建
//-----------------------------------------------------------------------------
//
class CBottomBarMgr : public QGroupBox
{
    Q_OBJECT

public:
    CBottomBarMgr(QWidget* parent = 0);
    ~CBottomBarMgr();

public slots:
    void warning(const QString& text, int splashCnt, int splashInterval);

protected slots:
    void updateTime();

private:
    QLabel* label_time;
    QLabel* label_warning;

    QTimer* timer;
};