/// @file
///     TrendCtrl.cpp
///
/// @brief
///     ����ͼ�ؼ�
///
/// @note
///
/// Copyright (c) 
///
/// ���ߣ�
///    yangyuchao  2015.10.23
///
/// �汾��
///    1.0.x.x
/// 
/// �޸���ʷ��
///    �� ʱ��         : �汾      :  ��ϸ��Ϣ    
///    :-------------- :-----------:----------------------------------------------------------
///    |2015.10.23     |1.0.000    |������
///
#include "TrendCtrl.h"
#include "BackGround.h"
#include "Scale.h"

#include "debug.h"

using namespace mTrend;

///
/// @brief
///     ���캯��
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
///     ��������
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
///     ��ʼ���ؼ�
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
///     ����������ʾ�����ȫ��������Ϣ
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
///     �ػ���Ϣ������
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
///     ���ƿؼ�����
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
///     ���ÿؼ�ǰ��
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

