/// @file
///     TrendCtrl.cpp
///
/// @brief
///     波形图控件
///
/// @note
///
/// Copyright (c) 
///
/// 作者：
///    yangyuchao  2015.10.23
///
/// 版本：
///    1.0.x.x
/// 
/// 修改历史：
///    ： 时间         : 版本      :  详细信息    
///    :-------------- :-----------:----------------------------------------------------------
///    |2015.10.23     |1.0.000    |创建类
///
#include "TrendCtrl.h"
#include "BackGround.h"
#include "Scale.h"

#include "debug.h"

using namespace mTrend;

///
/// @brief
///     构造函数
///
CTrendCtrl::CTrendCtrl(CComponent* bg, CComponent* fg, QWidget* parent)
: QLabel(parent)
, m_pBackGround(bg)
, m_pForeGround(fg)
, m_backgroundPixmap(NULL)
, m_foregroundPixmap(NULL)
{
}

///
/// @brief
///     析构函数
///
CTrendCtrl::~CTrendCtrl()
{
    if (m_pBackGround) {
        delete m_pBackGround;
        m_pBackGround = NULL;
    }
    if (m_pForeGround) {
        delete m_pForeGround;
        m_pForeGround = NULL;
    }

    if (m_backgroundPixmap) {
        delete m_backgroundPixmap;
        m_backgroundPixmap = NULL;
    }
    if (m_foregroundPixmap) {
        delete m_foregroundPixmap;
        m_foregroundPixmap = NULL;
    }
}

///
/// @brief
///     初始化控件
///
/// @return
///
///
void CTrendCtrl::Init()
{
    DrawBkgnd();
    ResetForgnd();
}

///
/// @brief
///     擦除波形显示区域的全部波形信息
///
/// @return
///
///
void CTrendCtrl::EraseWave()
{
    ResetForgnd();
}

///
/// @brief
///     重绘消息处理函数
///
/// @return
///
void CTrendCtrl::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *m_foregroundPixmap);
}

///
/// @brief
///     绘制控件背景
///
/// @return
///
void CTrendCtrl::DrawBkgnd()
{
    if (!m_backgroundPixmap) {
        m_backgroundPixmap = new QPixmap(size());
    }
    QPainter painter(m_backgroundPixmap);
    m_pBackGround->Draw(&painter, rect());
}

///
/// @brief
///     重置控件前景
///
/// @return
///
void CTrendCtrl::ResetForgnd()
{
    Q_ASSERT(m_backgroundPixmap);
    if (m_foregroundPixmap)  {
        *m_foregroundPixmap = *m_backgroundPixmap;
    }
    else {
        m_foregroundPixmap = new QPixmap(*m_backgroundPixmap);
    }
}

void CTrendCtrl::DrawForegound()
{
    Q_ASSERT(m_foregroundPixmap);
    QPainter painter(m_foregroundPixmap);
    m_pForeGround->Draw(&painter, rect());
}

