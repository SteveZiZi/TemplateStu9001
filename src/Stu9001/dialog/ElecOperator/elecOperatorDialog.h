#pragma once


#include "../baseDialog.h"
#include <ElecOperatorData>

class CCubicleViews;
class CCubicleOperator;
class CbarrowOperator;
class CEarthKnifeOperator;
class QTimer;

class CElecOperatorDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CElecOperatorDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CElecOperatorDlg();


    //override from CAbstractMenuContent
    virtual void _ShowContent(int style, quint32 data);
    virtual void _HideContent();

private slots:
    void changeOperatorMode(bool bAutoMode);
    void changeFanStatus(int item, bool start);
    void changeLampStatus(int item, bool start);
    void changeHeaterStatus(int item, bool start);
    void changeGateStatus(bool start);

    void barrowTeleIn();
    void barrowTeleOut();
    void barrowStop();
    void barrowReset();

    void earthKnifeTeleIn();
    void earthKnifeTeleOut();
    void earthKnifeStop();
    void earthKnifeReset();

    //自动模式下监测柜内状态
    void detectCubicleStatus();

private:
    //override from CBaseDialog
    virtual void moveToNextWidget() {}
    virtual void moveToPreWidget() {}

private:
    void updateOperateMode();
    void updateCubicleStatus();
    void updateBarrowStatus();
    void updateEarthKnifeStatus();

    void startDetectCubicle();
    void endDetectCubicle();

private:
    CCubicleViews* m_cubicleViews;
    CCubicleOperator* m_cubicleOperator;
    CbarrowOperator* m_barrowOperator;
    CEarthKnifeOperator* m_earthKnifeOperator;

    int m_item;

    CElecOperatorData* m_dev;

    EO_CubicleOperateMode m_operateMode;
    EO_CubicleStatus m_cubicleStatus;
    EO_FaultStatus   m_barrowFaultStatus;
    EO_FaultStatus   m_earthKnifeFaultStatus;

    QTimer*         m_cubicleOperatorTimer;
    //QTimer*         m_motor
};