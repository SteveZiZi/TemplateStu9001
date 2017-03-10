#pragma once

#include <QList>
#include "../baseDialog.h"
#include <castbackConstantValuesSetting_cp6000.h>

class CDirKeyInputForData;
class QTreeWidgetItem;
class MTreeWidget;

class CCastbackConstValueCP6000Dlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    struct treeWidgetInfo {
        QStringList caption;
        QList<bool> style;
    };

    typedef bool (CCastbackConstValueCP6000Dlg::*PFN_MODIFY_SETTING)(int row, QVariant& var);

    CCastbackConstValueCP6000Dlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CCastbackConstValueCP6000Dlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

protected slots:
    void treeWidget1Changed(QTreeWidgetItem *item, int column);
    void treeWidget2Changed(QTreeWidgetItem *item, int column);

private:
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    MTreeWidget* createTreeWidget1(QString objectName);
    MTreeWidget* createTreeWidget2(QString objectName);
    //更新设置到界面
    void updateSettings();

    MTreeWidget* _createTreeWidget(QString objectName, QList<treeWidgetInfo*>& listTreeWidgetInfo);
    bool _modifyCastStatus(MTreeWidget* treeWidget, QTreeWidgetItem* item, int column);

    bool curQuickBreakCastback(int row, QVariant& var);
    bool timeLimitQuickBreakCastback(int row, QVariant& var);
    bool overCurProtectCastback(int row, QVariant& var);
    bool recloseCastback(int row, QVariant& var);
    bool lowFreqDeloadingCastback(int row, QVariant& var);
    bool lowFreqSplittingCastback(int row, QVariant& var);
    bool lowVolSplittingCastback(int row, QVariant& var);
    bool smallCurGroundCastback(int row, QVariant& var);
    bool overLoadingCastback(int row, QVariant& var);
    bool negativeSequenceOverCurProtectCastback(int row, QVariant& var);
    bool zeroSequenceOverCurProtectCastback(int row, QVariant& var);
    bool overVolProtectCastback(int row, QVariant& var);
    bool lowVolProtectCastback(int row, QVariant& var);
    bool lostVolProtectCastback(int row, QVariant& var);
    bool negativeSequenceOverVolProtectCastback(int row, QVariant& var);

    bool zeroSequenceOverVolProtectCastback(int row, QVariant& var);
    bool compoundVolOverCurCastback(int row, QVariant& var);
    bool automaticBusTransferCastback(int row, QVariant& var);
    bool overHeatingProtectCastback(int row, QVariant& var);
    bool reversePowerProtectCastback(int row, QVariant& var);
    bool IxOverCurProtectCastback(int row, QVariant& var);
    bool motorProtectCastback(int row, QVariant& var);
    bool nonElectricalProtectCastback(int row, QVariant& var);
    bool PTBreakWireCastback(int row, QVariant& var);
    bool CTBreakWireCastback(int row, QVariant& var);
    bool reserved0Castback(int row, QVariant& var);
    bool reserved1Castback(int row, QVariant& var);
    bool faultRecordCastback(int row, QVariant& var);
    bool controlLoopBreakWireCastback(int row, QVariant& var);

private:
    MTreeWidget* m_treeWidget1;
    MTreeWidget* m_treeWidget2;

    CDirKeyInputForData* m_dirKeyInputForData;

    CCP6000CastbackConstantValuesSettings* m_dev;
    CP6000CastBackConstValue_t m_settings;
    bool        m_bModify;
    bool        m_bAllowModify;

    QList<PFN_MODIFY_SETTING> m_pfnTreeWidget1;
    QList<PFN_MODIFY_SETTING> m_pfnTreeWidget2;

    PFN_MODIFY_SETTING m_pfn;
};