#include "castbackConstValueSettingsDialog_cp6000.h"
#include "common.h"

#include <QtGui/QScrollBar>
#include <QtGui/QHeaderView>
#include <QKeyEvent>
#include <QMap>

#include <mTreeWidget>
#include <dirKeyInputForData>
#include <MLineEditDelegate>

#include "debug.h"


#define REPORT_POS_L        20
#define REPORT_POS_T        15

#define CAPTION_WIDTH       150
#define CONTENT_WIDTH       80
#define REPORT_ITEM_H       22

#define REPORT1_ROWS        15
#define REPORT2_ROWS        14

#define REPORT_W      (CAPTION_WIDTH+CONTENT_WIDTH+15)
#define REPORT_H      (REPORT_ITEM_H*16+5+13)

#define CAST_IN_COLOR   qRgb(255, 0, 0)
#define CAST_OUT_COLOR  qRgb(0, 255, 0)


#define setCastbackState(item, castIn) \
    if (castIn) { \
        item->setCheckState(1, Qt::Checked); \
    } \
    else { \
        item->setCheckState(1, Qt::Unchecked); \
    }

#define setCastbackStateWithColor(item, castIn) \
    if (castIn) { \
        item->setText(1, tr("Cast In")); \
        item->setTextColor(1, CAST_IN_COLOR); \
    } \
    else { \
        item->setText(1, tr("Cast Out")); \
        item->setTextColor(1, CAST_OUT_COLOR); \
    }

#define setConstSettings_Float(item, val, prec) \
    item->setText(1, QString("%1").arg(val, 0, 'f', prec, QChar('0')));

#define setConstSettings_Int(item, val) \
    item->setText(1, QString("%1").arg(val));



CCastbackConstValueCP6000Dlg::CCastbackConstValueCP6000Dlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_bModify(false)
, m_dev(NULL)
, m_bAllowModify(false)
{
    m_dev = CCP6000CastbackConstantValuesSettings::getInstance();

    m_dirKeyInputForData = new CDirKeyInputForData();
    m_dirKeyInputForData->addMaskChar('.');

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 
    
    m_treeWidget1 = createTreeWidget1("treeWidget_castback1");
    m_treeWidget1->setGeometry(REPORT_POS_L, REPORT_POS_T, REPORT_W, REPORT_H);
    m_treeWidget2 = createTreeWidget2("treeWidget_castback2");
    m_treeWidget2->setGeometry(REPORT_POS_L+REPORT_W+20, REPORT_POS_T, REPORT_W, REPORT_H);

    connect(m_treeWidget1, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(treeWidget1Changed(QTreeWidgetItem *, int)));
    connect(m_treeWidget2, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(treeWidget2Changed(QTreeWidgetItem *, int)));

    m_pfnTreeWidget1 << &CCastbackConstValueCP6000Dlg::curQuickBreakCastback
                     << &CCastbackConstValueCP6000Dlg::timeLimitQuickBreakCastback
                     << &CCastbackConstValueCP6000Dlg::overCurProtectCastback
                     << &CCastbackConstValueCP6000Dlg::recloseCastback
                     << &CCastbackConstValueCP6000Dlg::lowFreqDeloadingCastback
                     << &CCastbackConstValueCP6000Dlg::lowFreqSplittingCastback
                     << &CCastbackConstValueCP6000Dlg::lowVolSplittingCastback
                     << &CCastbackConstValueCP6000Dlg::smallCurGroundCastback
                     << &CCastbackConstValueCP6000Dlg::overLoadingCastback
                     << &CCastbackConstValueCP6000Dlg::negativeSequenceOverCurProtectCastback
                     << &CCastbackConstValueCP6000Dlg::zeroSequenceOverCurProtectCastback
                     << &CCastbackConstValueCP6000Dlg::overVolProtectCastback
                     << &CCastbackConstValueCP6000Dlg::lowVolProtectCastback
                     << &CCastbackConstValueCP6000Dlg::lostVolProtectCastback
                     << &CCastbackConstValueCP6000Dlg::negativeSequenceOverVolProtectCastback;

    m_pfnTreeWidget2 << &CCastbackConstValueCP6000Dlg::zeroSequenceOverVolProtectCastback
                     << &CCastbackConstValueCP6000Dlg::compoundVolOverCurCastback
                     << &CCastbackConstValueCP6000Dlg::automaticBusTransferCastback
                     << &CCastbackConstValueCP6000Dlg::overHeatingProtectCastback
                     << &CCastbackConstValueCP6000Dlg::reversePowerProtectCastback
                     << &CCastbackConstValueCP6000Dlg::IxOverCurProtectCastback
                     << &CCastbackConstValueCP6000Dlg::motorProtectCastback
                     << &CCastbackConstValueCP6000Dlg::nonElectricalProtectCastback
                     << &CCastbackConstValueCP6000Dlg::PTBreakWireCastback
                     << &CCastbackConstValueCP6000Dlg::CTBreakWireCastback
                     << &CCastbackConstValueCP6000Dlg::reserved0Castback
                     << &CCastbackConstValueCP6000Dlg::reserved1Castback
                     << &CCastbackConstValueCP6000Dlg::faultRecordCastback
                     << &CCastbackConstValueCP6000Dlg::controlLoopBreakWireCastback;

}

CCastbackConstValueCP6000Dlg::~CCastbackConstValueCP6000Dlg()
{
    if (m_treeWidget1) {
        delete dynamic_cast<MLineEditDelegate*>(m_treeWidget1->itemDelegate());
    }
    if (m_treeWidget2) {
        delete dynamic_cast<MLineEditDelegate*>(m_treeWidget2->itemDelegate());
    }
}

void CCastbackConstValueCP6000Dlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        this->show();
        m_bModify = false;
        m_dev->constValSettings(&m_settings);
        updateSettings();
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        m_treeWidget1->setFocus();
        m_treeWidget1->setCurrentItem(m_treeWidget1->topLevelItem(0));
    }
}

void CCastbackConstValueCP6000Dlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CCastbackConstValueCP6000Dlg::_LeaveContent data Changed";
        m_dev->setConstValSettings(m_settings);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

bool CCastbackConstValueCP6000Dlg::_modifyCastStatus(MTreeWidget* treeWidget, QTreeWidgetItem* item, int column)
{
    bool rc = false;

    if (!item->parent()) {
        rc = true;
    }
    else {
        if (item->flags()&Qt::ItemIsUserCheckable)
        {
            Qt::CheckState state = item->checkState(column);
            if (state == Qt::Checked) {
                if (item->text(column).compare(tr("Cast In")) == 0) {
                    rc = true;
                }
                else {
                    item->setText(column, tr("Cast In"));
                }
            }
            else {
                if (item->text(column).compare(tr("Cast Out")) == 0) {
                    rc = true;
                }
                else {
                    item->setText(column, tr("Cast Out"));
                }
            }

            QTreeWidgetItem* parent = item->parent();
            if (item == parent->child(0)) {
                setCastbackStateWithColor(parent, state);
            }
        }
    }

    return rc;
}

void CCastbackConstValueCP6000Dlg::treeWidget1Changed(QTreeWidgetItem *item, int column)
{
    if (column == 1) {
        //状态的修改已经处理完成，不需要识别数据的修改
        if (_modifyCastStatus(m_treeWidget1, item, column)) {
            return ;
        }

        if (!m_bAllowModify) {
            return;
        }
            
        m_bModify = true;
        QTreeWidgetItem* parent = item->parent();
        int topRow = m_treeWidget1->indexOfTopLevelItem(parent);
        int row = parent->indexOfChild(item);
        if (item->flags()&Qt::ItemIsUserCheckable) {
            (this->*m_pfnTreeWidget1[topRow])(row, QVariant((bool)(item->checkState(1) == Qt::Checked)));
        }
        else {
            (this->*m_pfnTreeWidget1[topRow])(row, QVariant(item->text(1)));
        }
    }
}

void CCastbackConstValueCP6000Dlg::treeWidget2Changed(QTreeWidgetItem *item, int column)
{
    if (column == 1) {
        //状态的修改已经处理完成，不需要识别数据的修改
        if (_modifyCastStatus(m_treeWidget2, item, column)) {
            return ;
        }

        if (!m_bAllowModify) {
            return;
        }

        m_bModify = true;
        QTreeWidgetItem* parent = item->parent();
        int topRow = m_treeWidget2->indexOfTopLevelItem(parent);
        int row = parent->indexOfChild(item);
        if (item->flags()&Qt::ItemIsUserCheckable) {
            (this->*m_pfnTreeWidget2[topRow])(row, QVariant((bool)(item->checkState(1) == Qt::Checked)));
        }
        else {
            (this->*m_pfnTreeWidget2[topRow])(row, QVariant(item->text(1)));
        }
    }
}

void CCastbackConstValueCP6000Dlg::moveToNextWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_treeWidget1) {
        int row = m_treeWidget1->indexOfTopLevelItem(m_treeWidget1->currentItem());
        m_treeWidget2->setFocus();
        if (row >= m_treeWidget2->topLevelItemCount()) {
            row = m_treeWidget2->topLevelItemCount()-1;
        }
        m_treeWidget2->setCurrentItem(m_treeWidget2->topLevelItem(row));
        m_treeWidget1->setCurrentItem(NULL);

    }
    else {
        int row = m_treeWidget2->indexOfTopLevelItem(m_treeWidget2->currentItem());
        m_treeWidget1->setFocus();
        if (row >= m_treeWidget1->topLevelItemCount()) {
            row = m_treeWidget1->topLevelItemCount()-1;
        }
        m_treeWidget1->setCurrentItem(m_treeWidget1->topLevelItem(row));
        m_treeWidget2->setCurrentItem(NULL);
    }
}

void CCastbackConstValueCP6000Dlg::moveToPreWidget() 
{
    moveToNextWidget();
}


void CCastbackConstValueCP6000Dlg::keyPressEvent(QKeyEvent *event)
{
    MTreeWidget* focusWidget = dynamic_cast<MTreeWidget*>(this->focusWidget());
    qDebug() << "CConstValueModifyDlg::keyPressEvent:" << hex << event->key();

    switch(event->key()) 
    {
    case Qt::Key_Escape:
        focusWidget->setCurrentItem(NULL, 0);
        event->ignore();
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
        moveToNextWidget();
        event->ignore();
        break;
    default:
        event->ignore();
        break;
    }

    if (!event->isAccepted()) {
        CBaseDialog::keyPressEvent(event);
    }
}



static void addChildItem(QTreeWidgetItem* parentItem, const QStringList& caption, const QList<bool>& castback)
{
    for(int i = 0; i < caption.size(); i++) {
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList()<<caption[i]<<"");
        item->setTextColor(0, STU_GREEN_LINE);
        item->setTextColor(1, STU_GREEN_LINE);
        if (i<castback.size() && castback[i]) {
//             item->setCheckState(1, Qt::Checked);
//             item->setText(1, CCastbackConstValueCP6000Dlg::tr("Cast In"));
        }
        else {
            item->setText(1, "0.00");
            Qt::ItemFlags flags = item->flags();
            flags &= ~Qt::ItemIsUserCheckable;
            flags |= Qt::ItemIsEditable;
            item->setFlags(flags);
        }
        parentItem->addChild(item);
    }
}
MTreeWidget* CCastbackConstValueCP6000Dlg::createTreeWidget1(QString objectName)
{
    treeWidgetInfo curQuickBreak;
    curQuickBreak.caption   <<  CCastbackConstValueCP6000Dlg::tr("curQuickBreak")
                            <<  CCastbackConstValueCP6000Dlg::tr("curQuickBreak_cur")
                            <<  CCastbackConstValueCP6000Dlg::tr("curQuickBreak_delay")
                            <<  CCastbackConstValueCP6000Dlg::tr("curQuickBreak_lowVolBlocking")
                            <<  CCastbackConstValueCP6000Dlg::tr("curQuickBreak_lowVolBlockingVal")
                            <<  CCastbackConstValueCP6000Dlg::tr("curQuickBreak_dirBlocking");
    curQuickBreak.style << true << false << false << true << false << true;

    treeWidgetInfo timeLimitQuickBreak;
    timeLimitQuickBreak.caption <<  CCastbackConstValueCP6000Dlg::tr("timeLimitQuickBreak")
                                <<  CCastbackConstValueCP6000Dlg::tr("timeLimitQuickBreak_cur")
                                <<  CCastbackConstValueCP6000Dlg::tr("timeLimitQuickBreak_delay")
                                <<  CCastbackConstValueCP6000Dlg::tr("timeLimitQuickBreak_lowVolBlocking")
                                <<  CCastbackConstValueCP6000Dlg::tr("timeLimitQuickBreak_lowVolBlockingVal")
                                <<  CCastbackConstValueCP6000Dlg::tr("timeLimitQuickBreak_dirBlocking");
    timeLimitQuickBreak.style << true << false << false << true << false << true;

    treeWidgetInfo overCurProtect;
    overCurProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect")
                            <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect_cur")
                            <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect_delay")
                            <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect_lowVolBlocking")
                            <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect_lowVolBlockingVal")
                            <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect_dirBlocking")
                            <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect_antiTime")
                            <<  CCastbackConstValueCP6000Dlg::tr("overCurProtect_antiTimeMethod");
    overCurProtect.style << true << false << false << true << false << true << true << false;

    treeWidgetInfo reclose;
    reclose.caption <<  CCastbackConstValueCP6000Dlg::tr("reclose")
                    <<  CCastbackConstValueCP6000Dlg::tr("reclose_delay")
                    <<  CCastbackConstValueCP6000Dlg::tr("reclose_secondSectionACC")
                    <<  CCastbackConstValueCP6000Dlg::tr("reclose_threeSectionACC")
                    <<  CCastbackConstValueCP6000Dlg::tr("reclose_accDelay")
                    <<  CCastbackConstValueCP6000Dlg::tr("reclose_noVol")
                    <<  CCastbackConstValueCP6000Dlg::tr("reclose_sync")
                    <<  CCastbackConstValueCP6000Dlg::tr("reclose_allowClosingAngle");
    reclose.style << true << false << true << true << false << true << true << false;

    treeWidgetInfo lowFreqDeloading;
    lowFreqDeloading.caption <<  CCastbackConstValueCP6000Dlg::tr("lowFreqDeloading")
                             <<  CCastbackConstValueCP6000Dlg::tr("lowFreqDeloading_freq")
                             <<  CCastbackConstValueCP6000Dlg::tr("lowFreqDeloading_delay")
                             <<  CCastbackConstValueCP6000Dlg::tr("lowFreqDeloading_slipBlocking")
                             <<  CCastbackConstValueCP6000Dlg::tr("lowFreqDeloading_diffBlockingVal")
                             <<  CCastbackConstValueCP6000Dlg::tr("lowFreqDeloading_reserve");
    lowFreqDeloading.style << true << false << false << true << true << false;

    treeWidgetInfo lowFreqSplitting;
    lowFreqSplitting.caption <<  CCastbackConstValueCP6000Dlg::tr("lowFreqSplitting")
                             <<  CCastbackConstValueCP6000Dlg::tr("lowFreqSplitting_freq")
                             <<  CCastbackConstValueCP6000Dlg::tr("lowFreqSplitting_delay");
    lowFreqSplitting.style << true << false << false;

    treeWidgetInfo lowVolSplitting;
    lowVolSplitting.caption <<  CCastbackConstValueCP6000Dlg::tr("lowVolSplitting")
                            <<  CCastbackConstValueCP6000Dlg::tr("lowVolSplitting_freq")
                            <<  CCastbackConstValueCP6000Dlg::tr("lowVolSplitting_delay");
    lowVolSplitting.style << true << false << false;

    treeWidgetInfo smallCurGround;
    smallCurGround.caption  <<  CCastbackConstValueCP6000Dlg::tr("smallCurGround")
                            <<  CCastbackConstValueCP6000Dlg::tr("smallCurGround_zeroSequenceCur")
                            <<  CCastbackConstValueCP6000Dlg::tr("smallCurGround_zeroSequenceVol")
                            <<  CCastbackConstValueCP6000Dlg::tr("smallCurGround_delay")
                            <<  CCastbackConstValueCP6000Dlg::tr("smallCurGround_dirBlocking");
    smallCurGround.style << true << false << false << false << true;

    treeWidgetInfo overLoading;
    overLoading.caption <<  CCastbackConstValueCP6000Dlg::tr("overLoadingProtect")
                        <<  CCastbackConstValueCP6000Dlg::tr("overLoadingProtect_cur")
                        <<  CCastbackConstValueCP6000Dlg::tr("overLoadingProtect_delay");
    overLoading.style << true << false << false;


    treeWidgetInfo negativeSequenceOverCurProtect;
    negativeSequenceOverCurProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("negativeSequenceOverCurProtect")
                                            <<  CCastbackConstValueCP6000Dlg::tr("negativeSequenceOverCurProtect_cur")
                                            <<  CCastbackConstValueCP6000Dlg::tr("negativeSequenceOverCurProtect_delay");
    negativeSequenceOverCurProtect.style << true << false << false;

    treeWidgetInfo zeroSequenceOverCurProtect;
    zeroSequenceOverCurProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("zeroSequenceOverCurProtect")
                                        <<  CCastbackConstValueCP6000Dlg::tr("zeroSequenceOverCurProtect_cur")
                                        <<  CCastbackConstValueCP6000Dlg::tr("zeroSequenceOverCurProtect_delay");
    zeroSequenceOverCurProtect.style << true << false << false;

    treeWidgetInfo overVolProtect;
    overVolProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("overVolProtect")
                            <<  CCastbackConstValueCP6000Dlg::tr("overVolProtect_vol")
                            <<  CCastbackConstValueCP6000Dlg::tr("overVolProtect_delay");
    overVolProtect.style << true << false << false;

    treeWidgetInfo lowVolProtect;
    lowVolProtect.caption   <<  CCastbackConstValueCP6000Dlg::tr("lowVolProtect")
                            <<  CCastbackConstValueCP6000Dlg::tr("lowVolProtect_vol")
                            <<  CCastbackConstValueCP6000Dlg::tr("lowVolProtect_delay");
    lowVolProtect.style << true << false << false;

    treeWidgetInfo lostVolProtect;
    lostVolProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("lostVolProtect")
                            <<  CCastbackConstValueCP6000Dlg::tr("lostVolProtect_vol")
                            <<  CCastbackConstValueCP6000Dlg::tr("lostVolProtect_delay");
    lostVolProtect.style << true << false << false;

    treeWidgetInfo negativeSequenceOverVolProtect;
    negativeSequenceOverVolProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("negativeSequenceOverVolProtect")
                                            <<  CCastbackConstValueCP6000Dlg::tr("negativeSequenceOverVolProtect_vol")
                                            <<  CCastbackConstValueCP6000Dlg::tr("negativeSequenceOverVolProtect_delay");
    negativeSequenceOverVolProtect.style << true << false << false;

    QList<treeWidgetInfo*> listTreeWidgetInfo;
    listTreeWidgetInfo << &curQuickBreak
                       << &timeLimitQuickBreak
                       << &overCurProtect
                       << &reclose
                       << &lowFreqDeloading
                       << &lowFreqSplitting
                       << &lowVolSplitting
                       << &smallCurGround
                       << &overLoading
                       << &negativeSequenceOverCurProtect
                       << &zeroSequenceOverCurProtect
                       << &overVolProtect
                       << &lowVolProtect
                       << &lostVolProtect
                       << &negativeSequenceOverVolProtect;

    return _createTreeWidget(objectName, listTreeWidgetInfo);
}

MTreeWidget* CCastbackConstValueCP6000Dlg::createTreeWidget2(QString objectName)
{
    treeWidgetInfo zeroSequenceOverVolProtect;
    zeroSequenceOverVolProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("zeroSequenceOverVolProtect")
                                        <<  CCastbackConstValueCP6000Dlg::tr("zeroSequenceOverVolProtect_vol")
                                        <<  CCastbackConstValueCP6000Dlg::tr("zeroSequenceOverVolProtect_delay");
    zeroSequenceOverVolProtect.style << true << false << false;

    treeWidgetInfo compoundVolOverCur;
    compoundVolOverCur.caption  <<  CCastbackConstValueCP6000Dlg::tr("compoundVolOverCur")
                                <<  CCastbackConstValueCP6000Dlg::tr("compoundVolOverCur_cur")
                                <<  CCastbackConstValueCP6000Dlg::tr("compoundVolOverCur_delay")
                                <<  CCastbackConstValueCP6000Dlg::tr("compoundVolOverCur_lowVolBlocking")
                                <<  CCastbackConstValueCP6000Dlg::tr("compoundVolOverCur_lowVolBlockingVal")
                                <<  CCastbackConstValueCP6000Dlg::tr("compoundVolOverCur_negativeSequenceVolBlocking")
                                <<  CCastbackConstValueCP6000Dlg::tr("compoundVolOverCur_negativeSequenceVol");
    compoundVolOverCur.style << true << false << false << true << false << true << false;

    treeWidgetInfo automaticBusTransfer;
    automaticBusTransfer.caption  <<  CCastbackConstValueCP6000Dlg::tr("automaticBusTransfer")
                                  <<  CCastbackConstValueCP6000Dlg::tr("automaticBusTransfer_vol")
                                  <<  CCastbackConstValueCP6000Dlg::tr("automaticBusTransfer_delay")
                                  <<  CCastbackConstValueCP6000Dlg::tr("automaticBusTransfer_method");
    automaticBusTransfer.style << true << false << false << false;

    treeWidgetInfo overHeatingProtect;
    overHeatingProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("overHeatingProtect")
                                <<  CCastbackConstValueCP6000Dlg::tr("overHeatingProtect_cur")
                                <<  CCastbackConstValueCP6000Dlg::tr("overHeatingProtect_delay")
                                <<  CCastbackConstValueCP6000Dlg::tr("overHeatingProtect_negaitveSquenceFactor");
    overHeatingProtect.style << true << false << false << false;

    treeWidgetInfo reversePowerProtect;
    reversePowerProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("reversePowerProtect")
                                 <<  CCastbackConstValueCP6000Dlg::tr("reversePowerProtect_power")
                                 <<  CCastbackConstValueCP6000Dlg::tr("reversePowerProtect_delay");
    reversePowerProtect.style << true << false << false;

    treeWidgetInfo IxOverCurProtect;
    IxOverCurProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("IxOverCurProtect")
                              <<  CCastbackConstValueCP6000Dlg::tr("IxOverCurProtect_cur")
                              <<  CCastbackConstValueCP6000Dlg::tr("IxOverCurProtect_delay")
                              <<  CCastbackConstValueCP6000Dlg::tr("IxOverCurProtect_antiTime")
                              <<  CCastbackConstValueCP6000Dlg::tr("IxOverCurProtect_antiTimeMethod");
    IxOverCurProtect.style << true << false << false << true << false;

    treeWidgetInfo motorProtect;
    motorProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("motorProtect")
                          <<  CCastbackConstValueCP6000Dlg::tr("motorProtect_startTimeTooLong")
                          <<  CCastbackConstValueCP6000Dlg::tr("motorProtect_startTime")
                          <<  CCastbackConstValueCP6000Dlg::tr("motorProtect_rateCur")
                          <<  CCastbackConstValueCP6000Dlg::tr("motorProtect_curFactor");
    motorProtect.style << true << true << false << false << false;

    treeWidgetInfo nonElectricalProtect;
    nonElectricalProtect.caption  <<  CCastbackConstValueCP6000Dlg::tr("nonElectricalProtect")
                                  <<  CCastbackConstValueCP6000Dlg::tr("nonElectricalProtect_lightGas")
                                  <<  CCastbackConstValueCP6000Dlg::tr("nonElectricalProtect_heavyGas")
                                  <<  CCastbackConstValueCP6000Dlg::tr("nonElectricalProtect_oilOverTemp")
                                  <<  CCastbackConstValueCP6000Dlg::tr("nonElectricalProtect_oilHighestTemp");
    nonElectricalProtect.style << true << true << true << true << true;

    treeWidgetInfo PTBreakWire;
    PTBreakWire.caption  <<  CCastbackConstValueCP6000Dlg::tr("PTBreakWire");
    PTBreakWire.style << true;

    treeWidgetInfo CTBreakWire;
    CTBreakWire.caption  <<  CCastbackConstValueCP6000Dlg::tr("CTBreakWire");
    CTBreakWire.style << true;

    treeWidgetInfo reserved0;
    reserved0.caption  <<  CCastbackConstValueCP6000Dlg::tr("reserved");
    reserved0.style << true;
    treeWidgetInfo reserved1;
    reserved1.caption  <<  CCastbackConstValueCP6000Dlg::tr("reserved");
    reserved1.style << true;

    treeWidgetInfo faultRecord;
    faultRecord.caption  <<  CCastbackConstValueCP6000Dlg::tr("faultRecord");
    faultRecord.style << true;

    treeWidgetInfo controlLoopBreakWire;
    controlLoopBreakWire.caption  <<  CCastbackConstValueCP6000Dlg::tr("controlLoopBreakWire");
    controlLoopBreakWire.style << true;


    QList<treeWidgetInfo*> listTreeWidgetInfo;
    listTreeWidgetInfo << &zeroSequenceOverVolProtect
                       << &compoundVolOverCur
                       << &automaticBusTransfer
                       << &overHeatingProtect
                       << &reversePowerProtect
                       << &IxOverCurProtect
                       << &motorProtect
                       << &nonElectricalProtect
                       << &PTBreakWire
                       << &CTBreakWire
                       << &reserved0
                       << &reserved1
                       << &faultRecord
                       << &controlLoopBreakWire;

    return _createTreeWidget(objectName, listTreeWidgetInfo);
}

MTreeWidget* CCastbackConstValueCP6000Dlg::_createTreeWidget(QString objectName, QList<treeWidgetInfo*>& listTreeWidgetInfo)
{
    MTreeWidget* treeWidget = new MTreeWidget(this);
    treeWidget->setObjectName(objectName);

    QHeaderView* hHeader = new QHeaderView(Qt::Horizontal, treeWidget);
    hHeader->setObjectName("castback_hHeader");
    hHeader->setFixedHeight(0/*REPORT_ITEM_H*/);
    hHeader->setHighlightSections(false);
    treeWidget->setHeader(hHeader);

    treeWidget->horizontalScrollBar()->hide();
    treeWidget->verticalScrollBar()->hide();
    treeWidget->setAlternatingRowColors(true);

    QTreeWidgetItem* headerItem = new QTreeWidgetItem(QStringList()<<tr("caption")<<tr("settings"));
    treeWidget->setHeaderItem(headerItem);
    treeWidget->setColumnWidth(0, CAPTION_WIDTH);
    treeWidget->setColumnWidth(1, CONTENT_WIDTH);

    MLineEditDelegate* delegate = new MLineEditDelegate(treeWidget);
    delegate->setDirKeyInput(m_dirKeyInputForData);
    treeWidget->setItemDelegate(delegate);

    //设定各个项 
    QTreeWidgetItem*  topItem = NULL;
    for(int i = 0; i < listTreeWidgetInfo.size(); i++) {
        topItem = new QTreeWidgetItem(QStringList()<<listTreeWidgetInfo[i]->caption[0]<< tr("Cast In"));
        topItem->setSizeHint(0, QSize(CAPTION_WIDTH, REPORT_ITEM_H));
        topItem->setTextColor(0, qRgb(0x9C, 0xC8, 0x85));
        topItem->setTextColor(1, qRgb(0x9C, 0xC8, 0x85));
        topItem->setFlags(topItem->flags()&(~Qt::ItemIsUserCheckable));

        treeWidget->addTopLevelItem(topItem);
        addChildItem(topItem, listTreeWidgetInfo[i]->caption, listTreeWidgetInfo[i]->style);
    }

    return treeWidget;
}


void CCastbackConstValueCP6000Dlg::updateSettings()
{
    QTreeWidgetItem* topItem = NULL;

    m_bAllowModify = false;

    topItem = m_treeWidget1->topLevelItem(0);
    setCastbackStateWithColor(topItem, m_settings.curQuickBreak.castIn);
    setCastbackState(topItem->child(0), m_settings.curQuickBreak.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.curQuickBreak.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.curQuickBreak.delay, 2);
    setCastbackState(topItem->child(3), m_settings.curQuickBreak.lowVolBlockingCastIn);
    setConstSettings_Float(topItem->child(4), m_settings.curQuickBreak.lowVolBlockingVol, 2);
    setCastbackState(topItem->child(5), m_settings.curQuickBreak.dirBlockingCastIn);

    topItem = m_treeWidget1->topLevelItem(1);
    setCastbackStateWithColor(topItem, m_settings.timeLimitQuickBreak.castIn);
    setCastbackState(topItem->child(0), m_settings.timeLimitQuickBreak.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.timeLimitQuickBreak.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.timeLimitQuickBreak.delay, 2);
    setCastbackState(topItem->child(3), m_settings.timeLimitQuickBreak.lowVolBlockingCastIn);
    setConstSettings_Float(topItem->child(4), m_settings.timeLimitQuickBreak.lowVolBlockingVol, 2);
    setCastbackState(topItem->child(5), m_settings.timeLimitQuickBreak.dirBlockingCastIn);

    topItem = m_treeWidget1->topLevelItem(2);
    setCastbackStateWithColor(topItem, m_settings.overCurProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.overCurProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.overCurProtect.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.overCurProtect.delay, 2);
    setCastbackState(topItem->child(3), m_settings.overCurProtect.lowVolBlockingCastIn);
    setConstSettings_Float(topItem->child(4), m_settings.overCurProtect.lowVolBlockingVol, 2);
    setCastbackState(topItem->child(5), m_settings.overCurProtect.dirBlockingCastIn);
    setCastbackState(topItem->child(6), m_settings.overCurProtect.antiTimeCastIn);
    //待确定
    setConstSettings_Int(topItem->child(7), m_settings.overCurProtect.antiTimeMethod);

    topItem = m_treeWidget1->topLevelItem(3);
    setCastbackStateWithColor(topItem, m_settings.reclose.castIn);
    setCastbackState(topItem->child(0), m_settings.reclose.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.reclose.delay, 2);
    setCastbackState(topItem->child(2), m_settings.reclose.secondSectionAccCastIn);
    setCastbackState(topItem->child(3), m_settings.reclose.threeSectionAccCastIn);
    setConstSettings_Float(topItem->child(4), m_settings.reclose.accDelay, 2);
    setCastbackState(topItem->child(5), m_settings.reclose.noVolCastIn);
    setCastbackState(topItem->child(6), m_settings.reclose.syncCastIn);
    setConstSettings_Float(topItem->child(7), m_settings.reclose.allowClosingAngle, 2);

    topItem = m_treeWidget1->topLevelItem(4);
    setCastbackStateWithColor(topItem, m_settings.lowFreqDeloading.castIn);
    setCastbackState(topItem->child(0), m_settings.lowFreqDeloading.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.lowFreqDeloading.freq, 2);
    setConstSettings_Float(topItem->child(2), m_settings.lowFreqDeloading.delay, 2);
    setCastbackState(topItem->child(3), m_settings.lowFreqDeloading.slipBlockingCastIn);
    setConstSettings_Float(topItem->child(4), m_settings.lowFreqDeloading.diffBlockingVal, 2);
    setConstSettings_Float(topItem->child(5), m_settings.lowFreqDeloading.reserved, 2);

    topItem = m_treeWidget1->topLevelItem(5);
    setCastbackStateWithColor(topItem, m_settings.lowFreqSplitting.castIn);
    setCastbackState(topItem->child(0), m_settings.lowFreqSplitting.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.lowFreqSplitting.freq, 2);
    setConstSettings_Float(topItem->child(2), m_settings.lowFreqSplitting.delay, 2);

    topItem = m_treeWidget1->topLevelItem(6);
    setCastbackStateWithColor(topItem, m_settings.lowVolSplitting.castIn);
    setCastbackState(topItem->child(0), m_settings.lowVolSplitting.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.lowVolSplitting.vol, 2);
    setConstSettings_Float(topItem->child(2), m_settings.lowVolSplitting.delay, 2);

    topItem = m_treeWidget1->topLevelItem(7);
    setCastbackStateWithColor(topItem, m_settings.smallCurGround.castIn);
    setCastbackState(topItem->child(0), m_settings.smallCurGround.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.smallCurGround.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.smallCurGround.vol, 2);
    setConstSettings_Float(topItem->child(3), m_settings.smallCurGround.delay, 2);
    setConstSettings_Float(topItem->child(4), m_settings.smallCurGround.dirBlockingCastIn, 2);

    topItem = m_treeWidget1->topLevelItem(8);
    setCastbackStateWithColor(topItem, m_settings.overLoading.castIn);
    setCastbackState(topItem->child(0), m_settings.overLoading.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.overLoading.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.overLoading.delay, 2);

    topItem = m_treeWidget1->topLevelItem(9);
    setCastbackStateWithColor(topItem, m_settings.negativeSequenceOverCurProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.negativeSequenceOverCurProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.negativeSequenceOverCurProtect.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.negativeSequenceOverCurProtect.delay, 2);

    topItem = m_treeWidget1->topLevelItem(10);
    setCastbackStateWithColor(topItem, m_settings.zeroSequenceOverCurProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.zeroSequenceOverCurProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.zeroSequenceOverCurProtect.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.zeroSequenceOverCurProtect.delay, 2);

    topItem = m_treeWidget1->topLevelItem(11);
    setCastbackStateWithColor(topItem, m_settings.overVolProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.overVolProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.overVolProtect.vol, 2);
    setConstSettings_Float(topItem->child(2), m_settings.overVolProtect.delay, 2);

    topItem = m_treeWidget1->topLevelItem(12);
    setCastbackStateWithColor(topItem, m_settings.lowVolProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.lowVolProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.lowVolProtect.vol, 2);
    setConstSettings_Float(topItem->child(2), m_settings.lowVolProtect.delay, 2);

    topItem = m_treeWidget1->topLevelItem(13);
    setCastbackStateWithColor(topItem, m_settings.lostVolProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.lostVolProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.lostVolProtect.vol, 2);
    setConstSettings_Float(topItem->child(2), m_settings.lostVolProtect.delay, 2);

    topItem = m_treeWidget1->topLevelItem(14);
    setCastbackStateWithColor(topItem, m_settings.negativeSequenceOverVolProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.negativeSequenceOverVolProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.negativeSequenceOverVolProtect.vol, 2);
    setConstSettings_Float(topItem->child(2), m_settings.negativeSequenceOverVolProtect.delay, 2);


    topItem = m_treeWidget2->topLevelItem(0);
    setCastbackStateWithColor(topItem, m_settings.zeroSequenceOverVolProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.zeroSequenceOverVolProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.zeroSequenceOverVolProtect.vol, 2);
    setConstSettings_Float(topItem->child(2), m_settings.zeroSequenceOverVolProtect.delay, 2);

    topItem = m_treeWidget2->topLevelItem(1);
    setCastbackStateWithColor(topItem, m_settings.compoundVolOverCur.castIn);
    setCastbackState(topItem->child(0), m_settings.compoundVolOverCur.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.compoundVolOverCur.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.compoundVolOverCur.delay, 2);
    setCastbackState(topItem->child(3), m_settings.compoundVolOverCur.lowVolBlockingCastIn);
    setConstSettings_Float(topItem->child(4), m_settings.compoundVolOverCur.delay, 2);
    setCastbackState(topItem->child(5), m_settings.compoundVolOverCur.negativeSequenceVolBlockingCastIn);
    setConstSettings_Float(topItem->child(6), m_settings.compoundVolOverCur.negativeSequenceVol, 2);

    topItem = m_treeWidget2->topLevelItem(2);
    setCastbackStateWithColor(topItem, m_settings.automaticBusTransfer.castIn);
    setCastbackState(topItem->child(0), m_settings.automaticBusTransfer.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.automaticBusTransfer.vol, 2);
    setConstSettings_Float(topItem->child(2), m_settings.automaticBusTransfer.delay, 2);
    //待处理
    setConstSettings_Int(topItem->child(3), m_settings.automaticBusTransfer.method+1);

    topItem = m_treeWidget2->topLevelItem(3);
    setCastbackStateWithColor(topItem, m_settings.overHeatingProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.overHeatingProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.overHeatingProtect.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.overHeatingProtect.delay, 2);
    setConstSettings_Int(topItem->child(3), m_settings.overHeatingProtect.factor);

    topItem = m_treeWidget2->topLevelItem(4);
    setCastbackStateWithColor(topItem, m_settings.reversePowerProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.reversePowerProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.reversePowerProtect.power, 2);
    setConstSettings_Float(topItem->child(2), m_settings.reversePowerProtect.delay, 2);

    topItem = m_treeWidget2->topLevelItem(5);
    setCastbackStateWithColor(topItem, m_settings.IxOverCurProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.IxOverCurProtect.castIn);
    setConstSettings_Float(topItem->child(1), m_settings.IxOverCurProtect.cur, 2);
    setConstSettings_Float(topItem->child(2), m_settings.IxOverCurProtect.delay, 2);
    setCastbackState(topItem->child(3), m_settings.IxOverCurProtect.antiTimeCastIn);
    //待处理
    setConstSettings_Int(topItem->child(4), m_settings.IxOverCurProtect.antiTimeMethod);

    topItem = m_treeWidget2->topLevelItem(6);
    setCastbackStateWithColor(topItem, m_settings.motorProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.motorProtect.castIn);
    setCastbackState(topItem->child(1), m_settings.motorProtect.startTimeTooLongCastIn);
    setConstSettings_Float(topItem->child(2), m_settings.motorProtect.startTime, 2);
    setConstSettings_Float(topItem->child(3), m_settings.motorProtect.cur, 2);
    setConstSettings_Int(topItem->child(4), m_settings.motorProtect.factor);

    topItem = m_treeWidget2->topLevelItem(7);
    setCastbackStateWithColor(topItem, m_settings.nonElectricalProtect.castIn);
    setCastbackState(topItem->child(0), m_settings.nonElectricalProtect.castIn);
    setCastbackState(topItem->child(1), m_settings.nonElectricalProtect.lightGasCastIn);
    setCastbackState(topItem->child(2), m_settings.nonElectricalProtect.heavyGasCastIn);
    setCastbackState(topItem->child(3), m_settings.nonElectricalProtect.oilOverTempCastIn);
    setCastbackState(topItem->child(4), m_settings.nonElectricalProtect.oilHighTempCastIn);

    topItem = m_treeWidget2->topLevelItem(8);
    setCastbackStateWithColor(topItem, m_settings.PTBreakWire.castIn);
    setCastbackState(topItem->child(0), m_settings.PTBreakWire.castIn);

    topItem = m_treeWidget2->topLevelItem(9);
    setCastbackStateWithColor(topItem, m_settings.CTBreakWire.castIn);
    setCastbackState(topItem->child(0), m_settings.CTBreakWire.castIn);

    topItem = m_treeWidget2->topLevelItem(10);
    setCastbackStateWithColor(topItem, m_settings.reserved[0].castIn);
    setCastbackState(topItem->child(0), m_settings.reserved[0].castIn);

    topItem = m_treeWidget2->topLevelItem(11);
    setCastbackStateWithColor(topItem, m_settings.reserved[1].castIn);
    setCastbackState(topItem->child(0), m_settings.reserved[1].castIn);

    topItem = m_treeWidget2->topLevelItem(12);
    setCastbackStateWithColor(topItem, m_settings.faultRecord.castIn);
    setCastbackState(topItem->child(0), m_settings.faultRecord.castIn);

    topItem = m_treeWidget2->topLevelItem(13);
    setCastbackStateWithColor(topItem, m_settings.controlLoopBreakWire.castIn);
    setCastbackState(topItem->child(0), m_settings.controlLoopBreakWire.castIn);

    m_bAllowModify = true;
}

bool CCastbackConstValueCP6000Dlg::curQuickBreakCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.curQuickBreak.castIn = var.toBool();
        break;
    case 1:
        m_settings.curQuickBreak.cur = var.toFloat();
        break;
    case 2:
        m_settings.curQuickBreak.delay = var.toFloat();
        break;
    case 3:
        m_settings.curQuickBreak.lowVolBlockingCastIn = var.toBool();
        break;
    case 4:
        m_settings.curQuickBreak.lowVolBlockingVol = var.toFloat();
        break;
    case 5:
        m_settings.curQuickBreak.dirBlockingCastIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::timeLimitQuickBreakCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.timeLimitQuickBreak.castIn = var.toBool();
        break;
    case 1:
        m_settings.timeLimitQuickBreak.cur = var.toFloat();
        break;
    case 2:
        m_settings.timeLimitQuickBreak.delay = var.toFloat();
        break;
    case 3:
        m_settings.timeLimitQuickBreak.lowVolBlockingCastIn = var.toBool();
        break;
    case 4:
        m_settings.timeLimitQuickBreak.lowVolBlockingVol = var.toFloat();
        break;
    case 5:
        m_settings.timeLimitQuickBreak.dirBlockingCastIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::overCurProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.overCurProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.overCurProtect.cur = var.toFloat();
        break;
    case 2:
        m_settings.overCurProtect.delay = var.toFloat();
        break;
    case 3:
        m_settings.overCurProtect.lowVolBlockingCastIn = var.toBool();
        break;
    case 4:
        m_settings.overCurProtect.lowVolBlockingVol = var.toFloat();
        break;
    case 5:
        m_settings.overCurProtect.dirBlockingCastIn = var.toBool();
        break;
    case 6:
        m_settings.overCurProtect.antiTimeCastIn = var.toBool();
        break;
    case 7:
        m_settings.overCurProtect.antiTimeMethod = var.toUInt();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::recloseCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.reclose.castIn = var.toBool();
        break;
    case 1:
        m_settings.reclose.delay = var.toFloat();
        break;
    case 2:
        m_settings.reclose.secondSectionAccCastIn = var.toBool();
        break;
    case 3:
        m_settings.reclose.threeSectionAccCastIn = var.toBool();
        break;
    case 4:
        m_settings.reclose.accDelay = var.toFloat();
        break;
    case 5:
        m_settings.reclose.noVolCastIn = var.toBool();
        break;
    case 6:
        m_settings.reclose.syncCastIn = var.toBool();
        break;
    case 7:
        m_settings.reclose.allowClosingAngle = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::lowFreqDeloadingCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.lowFreqDeloading.castIn = var.toBool();
        break;
    case 1:
        m_settings.lowFreqDeloading.freq = var.toFloat();
        break;
    case 2:
        m_settings.lowFreqDeloading.delay = var.toFloat();
        break;
    case 3:
        m_settings.lowFreqDeloading.slipBlockingCastIn = var.toBool();
        break;
    case 4:
        m_settings.lowFreqDeloading.diffBlockingVal = var.toFloat();
        break;
    case 5:
        m_settings.reclose.allowClosingAngle = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::lowFreqSplittingCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.lowFreqSplitting.castIn = var.toBool();
        break;
    case 1:
        m_settings.lowFreqSplitting.freq = var.toFloat();
        break;
    case 2:
        m_settings.lowFreqSplitting.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::lowVolSplittingCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.lowVolSplitting.castIn = var.toBool();
        break;
    case 1:
        m_settings.lowVolSplitting.vol = var.toFloat();
        break;
    case 2:
        m_settings.lowVolSplitting.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::smallCurGroundCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.smallCurGround.castIn = var.toBool();
        break;
    case 1:
        m_settings.smallCurGround.cur = var.toFloat();
        break;
    case 2:
        m_settings.smallCurGround.delay = var.toFloat();
        break;
    case 3:
        m_settings.smallCurGround.dirBlockingCastIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::overLoadingCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.overLoading.castIn = var.toBool();
        break;
    case 1:
        m_settings.overLoading.cur = var.toFloat();
        break;
    case 2:
        m_settings.overLoading.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::negativeSequenceOverCurProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.negativeSequenceOverCurProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.negativeSequenceOverCurProtect.cur = var.toFloat();
        break;
    case 2:
        m_settings.negativeSequenceOverCurProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::zeroSequenceOverCurProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.zeroSequenceOverCurProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.zeroSequenceOverCurProtect.cur = var.toFloat();
        break;
    case 2:
        m_settings.zeroSequenceOverCurProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::overVolProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.overVolProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.overVolProtect.vol = var.toFloat();
        break;
    case 2:
        m_settings.overVolProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::lowVolProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.lowVolProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.lowVolProtect.vol = var.toFloat();
        break;
    case 2:
        m_settings.lowVolProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::lostVolProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.lostVolProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.lostVolProtect.vol = var.toFloat();
        break;
    case 2:
        m_settings.lostVolProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::negativeSequenceOverVolProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.negativeSequenceOverVolProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.negativeSequenceOverVolProtect.vol = var.toFloat();
        break;
    case 2:
        m_settings.negativeSequenceOverVolProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}


bool CCastbackConstValueCP6000Dlg::zeroSequenceOverVolProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.zeroSequenceOverVolProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.zeroSequenceOverVolProtect.vol = var.toFloat();
        break;
    case 2:
        m_settings.zeroSequenceOverVolProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::compoundVolOverCurCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.compoundVolOverCur.castIn = var.toBool();
        break;
    case 1:
        m_settings.compoundVolOverCur.cur = var.toFloat();
        break;
    case 2:
        m_settings.compoundVolOverCur.delay = var.toFloat();
        break;
    case 3:
        m_settings.compoundVolOverCur.lowVolBlockingCastIn = var.toBool();
        break;
    case 4:
        m_settings.compoundVolOverCur.lowVolBlockingVol = var.toFloat();
        break;
    case 5:
        m_settings.compoundVolOverCur.negativeSequenceVolBlockingCastIn = var.toBool();
        break;
    case 6:
        m_settings.compoundVolOverCur.negativeSequenceVol = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::automaticBusTransferCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.automaticBusTransfer.castIn = var.toBool();
        break;
    case 1:
        m_settings.automaticBusTransfer.vol = var.toFloat();
        break;
    case 2:
        m_settings.automaticBusTransfer.delay = var.toFloat();
        break;
    case 3:
        m_settings.automaticBusTransfer.method = var.toUInt();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::overHeatingProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.overHeatingProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.overHeatingProtect.cur = var.toFloat();
        break;
    case 2:
        m_settings.overHeatingProtect.delay = var.toFloat();
        break;
    case 3:
        m_settings.overHeatingProtect.factor = var.toUInt();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::reversePowerProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.reversePowerProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.reversePowerProtect.power = var.toFloat();
        break;
    case 2:
        m_settings.reversePowerProtect.delay = var.toFloat();
        break;
    default:
        rc = false;
        break;
    }
    return rc;
}

bool CCastbackConstValueCP6000Dlg::IxOverCurProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.IxOverCurProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.IxOverCurProtect.cur = var.toFloat();
        break;
    case 2:
        m_settings.IxOverCurProtect.delay = var.toFloat();
        break;
    case 3:
        m_settings.IxOverCurProtect.antiTimeCastIn = var.toBool();
        break;
    case 4:
        m_settings.IxOverCurProtect.antiTimeMethod = var.toUInt();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::motorProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.motorProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.motorProtect.startTimeTooLongCastIn = var.toBool();
        break;
    case 2:
        m_settings.motorProtect.startTime = var.toFloat();
        break;
    case 3:
        m_settings.motorProtect.cur = var.toFloat();
        break;
    case 4:
        m_settings.motorProtect.factor = var.toUInt();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::nonElectricalProtectCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.nonElectricalProtect.castIn = var.toBool();
        break;
    case 1:
        m_settings.nonElectricalProtect.lightGasCastIn = var.toBool();
        break;
    case 2:
        m_settings.nonElectricalProtect.heavyGasCastIn = var.toBool();
        break;
    case 3:
        m_settings.nonElectricalProtect.oilOverTempCastIn = var.toBool();
        break;
    case 4:
        m_settings.nonElectricalProtect.oilHighTempCastIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::PTBreakWireCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.PTBreakWire.castIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::CTBreakWireCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.CTBreakWire.castIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::reserved0Castback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.reserved[0].castIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::reserved1Castback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.reserved[1].castIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::faultRecordCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.faultRecord.castIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}

bool CCastbackConstValueCP6000Dlg::controlLoopBreakWireCastback(int row, QVariant& var)
{
    bool rc = true;
    switch(row) {
    case 0:
        m_settings.controlLoopBreakWire.castIn = var.toBool();
        break;
    default:
        rc = false;
        break;
    }

    return rc;
}


