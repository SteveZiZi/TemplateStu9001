#pragma once

#include <QtGui>

///
/// @brief
///     �ؼ��ı�����ɫ
///
#define WFG_CTRL_BKGND_COLOR    qRgb(0,0,0)            ///< ��ɫ

///
/// @brief
///     �����Ĭ�����ã�����������ʽ�Լ����⡢X-Y��߿̶ȡ�����������Ϣ���α�������Ϣ�������С����ɫ
///
#define WFG_FONT_STYLE             "΢���ź�"
#define WFG_TITLE_FONT_SIZE        10
#define WFG_TITLE_FONT_COLOR       qRgb(255,255,255)      ///< ��ɫ
#define WFG_SCALE_FONT_SIZE        10
#define WFG_SCALE_FONT_COLOR       qRgb(255,255,255)      ///< ů��ɫ
#define WFG_WAVEDESC_FONT_SIZE     15
#define WFG_CURSORDESC_FONT_SIZE   10
#define WFG_CURSORDESC1_FONT_COLOR qRgb(255,140,0)        ///< ���ɫ
#define WFG_CURSORDESC2_FONT_COLOR qRgb(220,20,60)        ///< �Ⱥ�

#define WFG_LINE_SOLID              1

///
/// @brief
///     ������ʾ�����Ĭ�����ã��߿���ڲ���������������͡���Ⱥ���ɫ
///
#define WFG_WAVE_AREA_BORDER_STYLE Qt::SolidLine
#define WFG_WAVE_AREA_BORDER_WIDTH 1
#define WFG_WAVE_AREA_GRID_STYLE   Qt::DashLine
#define WFG_WAVE_AREA_GRID_WIDTH   0
#define WFG_WAVE_AREA_GRID_COLOR   qRgb(128,128,105)   ///< ���ɫ

#define WFG_WAVE_LINE_STYLE        Qt::SolidLine
#define WFG_WAVE_LINE_WIDTH        1


//ID��

namespace mTrend
{
    struct Margin
    {
        int left;
        int right;
        int top;
        int bottom;
        Margin(int x, int y) {
            left = right = x;
            top = bottom = y;
        }
        Margin(int l, int r, int t, int b) {
            left = l; right = r;
            top = t; bottom = b;
        }
        Margin() {
            left = right = 0;
            top = bottom = 0;
        }
        void setMargin(int x, int y) {
            left = right = x;
            top = bottom = y;
        }
        void setMargin(int l, int t, int r, int b) {
            left = l; right = r;
            top = t; bottom = b;
        }
    };

    enum {
        NEGATIVE = 1 << 0,
        POSITIVE = 1 << 1
    };

    struct ScaleInfo
    {
        int gridCountX;                                             //  XY���ĸ���
        int gridCountY;
        int intervalX;                                              //  �̶ȼ��
        int intervalY;
        int divIntervalX;                                           //  С�̶ȳ�  
        int divIntervalY;
        float fScaleX;                                              //  �̶ȳߵı���
        float fScaleY;

        Margin  magin;
        QRect   rectClient;

        int axisDirX;                                                //  X Y�᷽��  
        int axisDirY;

        QPoint GetCenterPoint() {
            QPoint center;
            if (axisDirY == POSITIVE)
                center.setY(rectClient.bottom()-magin.bottom);
            else if(axisDirY == NEGATIVE) 
                center.setY(rectClient.top()+magin.top);
            else if (axisDirY == (NEGATIVE|POSITIVE))
                center.setY(rectClient.height()/2+8);
            else
                Q_ASSERT(false);

            if (axisDirX == POSITIVE)
                center.setX(rectClient.left()+magin.left);
            else if(axisDirX == NEGATIVE) 
                center.setX(rectClient.right()-magin.right);
            else if (axisDirX == (NEGATIVE|POSITIVE))
                center.setX(rectClient.width()/2-10);
            else
                Q_ASSERT(false);

            return center;
        }

        int GetWidth() {
            //����X-Y�̶�ֵ�ļ��
            return (rectClient.width() - (magin.left+magin.right) - 10);
        }
        int GetHeight() {
            return (rectClient.height() - (magin.top + magin.bottom) - 10);
        }

        float GetSpanWidthX() {
            return (float)(rectClient.width() - (magin.left+magin.right) - 10) / (float)gridCountX;
        }
        float GetSpanWidthY() {
            return (float)(rectClient.height() - (magin.top + magin.bottom) - 10) / (float)gridCountY;
        }
    };

    enum {
        BACKGROUND_ID       = 0x00000000,
        SCALE_ID            = 0x01000000,
        DESCRIPTION_1_ID    = 0x02000001,
        DESCRIPTION_2_ID    = 0x02000002,
        DESCRIPTION_3_ID    = 0x02000003,
        DESCRIPTION_4_ID    = 0x02000004,

        FOREGROUND_ID       = 0x81000000,
        TREND_1_ID          = 0x82000001,
        TREND_2_ID          = 0x82000002,
        GRID_ID             = 0x83000000,

        NULL_COMPONENT_ID   = 0xFFFFFFFF
    };

};