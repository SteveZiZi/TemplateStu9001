#include "measureParamDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <mComboBox>
#include <mDataEdit>
#include <mLineEdit>
#include <dirKeyInputForData>

#include <stu_config>

#include "debug.h"

#define REPORT_POS_L        170
#define REPORT_POS_T        60

#define CAPTION_WIDTH       120
#define CONTENT_WIDTH       75

#define REPORT_ITEM_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_ITEM_H       42
#define REPORT_ROWS         7



CMeasureParamDlg::CMeasureParamDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
, m_bModify(false)
{
    m_dev = CMeasureParam::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    _create_label(label_primaryPT, tr("PT turns ration:"), x, y);
    _create_lineEdit_int(lineEdit_primaryPT, "lineEdit_primaryPT", 0x00, "", x+CAPTION_WIDTH, y-5);
    lineEdit_primaryPT->setFixedWidth(CONTENT_WIDTH);

    y += REPORT_ITEM_H;
    _create_label(label_primaryCT, tr("CT turns ration:"), x, y);
    _create_lineEdit_int(lineEdit_primaryCT, "lineEdit_primaryCT", 0x00, "", x+CAPTION_WIDTH, y-5);
    lineEdit_primaryCT->setFixedWidth(CONTENT_WIDTH);

    y += REPORT_ITEM_H;
    _create_label(label_CTSample, tr("CT Sample:"), x, y);
    _create_comboBox(comboBox_CTSample, "comboBox_CTSample", x+CAPTION_WIDTH, y);
    comboBox_CTSample->addItem("2CT", QVariant(0));
    comboBox_CTSample->addItem("3CT", QVariant(1));
    comboBox_CTSample->setFixedHeight(comboBox_CTSample->size().height()-10);
    comboBox_CTSample->setFixedWidth(CONTENT_WIDTH-15);
    if (stu_config::isCP9000()) {
        comboBox_CTSample->setFocusPolicy(Qt::NoFocus);
    }

    y += REPORT_ITEM_H;
    _create_label(label_RatedVol, tr("Rated Vol:"), x, y);
    _create_lineEdit_float(lineEdit_RatedVol, "lineEdit_RatedVol", 220.0f, 2, "V", x+CAPTION_WIDTH, y-5);
    lineEdit_RatedVol->setFixedWidth(CONTENT_WIDTH);
    lineEdit_RatedVol->setFocusPolicy(Qt::NoFocus);

    y += REPORT_ITEM_H;
    _create_label(label_RatedCur, tr("Rated Cur:"), x, y);
    _create_lineEdit_float(lineEdit_RatedCur, "lineEdit_RatedCur", 5.0f, 2, "A", x+CAPTION_WIDTH, y-5);
    lineEdit_RatedCur->setFixedWidth(CONTENT_WIDTH);
    lineEdit_RatedCur->setFocusPolicy(Qt::NoFocus);

    y += REPORT_ITEM_H;
    _create_label(label_volGrade, tr("Vol Grade:"), x, y);
    _create_comboBox(comboBox_volGrade, "comboBox_volGrade", x+CAPTION_WIDTH, y);
    comboBox_volGrade->addItem("380V", QVariant(380.0));
    comboBox_volGrade->addItem("220V", QVariant(220.0));
    comboBox_volGrade->addItem("110V", QVariant(110.0));
    comboBox_volGrade->addItem("57.7V", QVariant(57.7));
    comboBox_volGrade->setFixedWidth(CONTENT_WIDTH);
    comboBox_volGrade->setFixedHeight(comboBox_volGrade->size().height()-10);

    y += REPORT_ITEM_H;
    _create_label(label_zeroSquence, tr("Zero Squence:"), x, y);
    _create_comboBox(comboBox_zeroSquence, "comboBox_zeroSquence", x+CAPTION_WIDTH, y);
    comboBox_zeroSquence->addItem("FALSE", false);
    comboBox_zeroSquence->addItem("TRUE", true);
    comboBox_zeroSquence->setFixedWidth(CONTENT_WIDTH);
    comboBox_zeroSquence->setFixedHeight(comboBox_zeroSquence->size().height()-10);


    m_dirKeyInput = new CDirKeyInputForData();
    m_dirKeyInput->addMaskChar('.');
    lineEdit_primaryPT->setDirKeyInput(m_dirKeyInput);
    lineEdit_primaryCT->setDirKeyInput(m_dirKeyInput);
    lineEdit_RatedVol->setDirKeyInput(m_dirKeyInput);
    lineEdit_RatedCur->setDirKeyInput(m_dirKeyInput);
}

CMeasureParamDlg::~CMeasureParamDlg()
{
    STU_DELETE_PTR (m_dirKeyInput);
}

void CMeasureParamDlg::updateParam(void)
{
    lineEdit_primaryPT->setVar(QVariant(m_param.primaryPT));
    lineEdit_primaryCT->setVar(QVariant(m_param.primaryCT));

    lineEdit_RatedVol->setVar(QVariant(m_param.fRatedVol));
    lineEdit_RatedCur->setVar(QVariant(m_param.fRatedCur));

    comboBox_volGrade->setCurrentIndex(comboBox_volGrade->findData(QVariant(m_param.fVolScale)));
    comboBox_zeroSquence->setCurrentIndex(comboBox_zeroSquence->findData(QVariant(m_param.bZeroSquence)));

    comboBox_CTSample->setCurrentIndex(comboBox_CTSample->findData(QVariant(m_param.nCTSample)));
}

void CMeasureParamDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        m_dev->measureParam(&m_param);
        updateParam();
        m_bModify = false;
        this->show();

        connect(lineEdit_primaryPT, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyPrimaryPT(const QVariant&)));
        connect(lineEdit_primaryCT, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyPrimaryCT(const QVariant&)));
        connect(lineEdit_RatedVol, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyRatedVol(const QVariant&)));
        connect(lineEdit_RatedCur, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyRatedCur(const QVariant&)));

        connect(comboBox_volGrade, SIGNAL(currentIndexChanged(int)), this, SLOT(modifyVolGrade(int)));
        connect(comboBox_zeroSquence, SIGNAL(currentIndexChanged(int)), this, SLOT(modifyZeroSquence(int)));
        connect(comboBox_CTSample, SIGNAL(currentIndexChanged(int)), this, SLOT(modifyCTSample(int)));
    }

	if (style == CAbstractMenuContent::CONTENT_FOCUE)
		lineEdit_primaryPT->setFocus();
}

void CMeasureParamDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CMeasureParamDlg::_LeaveContent data Changed";
        m_dev->setMeasureParam(m_param);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CMeasureParamDlg::_HideContent()
{
    if (!this->isHidden()) {
        disconnect(lineEdit_primaryPT, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyPrimaryPT(const QVariant&)));
        disconnect(lineEdit_primaryCT, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyPrimaryCT(const QVariant&)));
        disconnect(lineEdit_RatedVol, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyRatedVol(const QVariant&)));
        disconnect(lineEdit_RatedCur, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifyRatedCur(const QVariant&)));

        disconnect(comboBox_volGrade, SIGNAL(currentIndexChanged(int)), this, SLOT(modifyVolGrade(int)));
        disconnect(comboBox_zeroSquence, SIGNAL(currentIndexChanged(int)), this, SLOT(modifyZeroSquence(int)));
        disconnect(comboBox_CTSample, SIGNAL(currentIndexChanged(int)), this, SLOT(modifyCTSample(int)));
    }

    CBaseDialog::_HideContent();
}

void CMeasureParamDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    int x = REPORT_POS_L;
    int y = REPORT_POS_T+REPORT_ITEM_H-10; 
    int w = REPORT_ITEM_W;
    //ªÊ÷∆Ω•±‰œﬂ
    QLinearGradient linerarGradient(x, 0, x+w, 0);
    linerarGradient.setColorAt(0.0, Qt::black);
    linerarGradient.setColorAt(0.5, QColor(STU_GREEN_LINE));
    linerarGradient.setColorAt(1.0, Qt::black);
    painter.setPen(QPen(QBrush(linerarGradient), 1));
    for(int i = 0; i < REPORT_ROWS; i++) {
        painter.drawLine(x, y, x+w, y);
        y+=REPORT_ITEM_H;
    }

    painter.setPen(oldPen);
}

void CMeasureParamDlg::moveToNextWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == comboBox_zeroSquence) {
        lineEdit_primaryPT->setFocus(Qt::TabFocusReason);
    }
    else {
        focusNextChild();
    }
}

void CMeasureParamDlg::moveToPreWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == lineEdit_primaryPT) {
        comboBox_zeroSquence->setFocus(Qt::BacktabFocusReason);
    }
    else {
        focusPreviousChild();
    }
}


void CMeasureParamDlg::modifyPrimaryPT(const QVariant& var)
{
    m_param.primaryPT = var.toUInt();
    m_bModify = true;
}

void CMeasureParamDlg::modifyPrimaryCT(const QVariant& var)
{
    m_param.primaryCT = var.toUInt();
    m_bModify = true;
}

void CMeasureParamDlg::modifyRatedVol(const QVariant& var)
{
    m_param.fRatedVol = var.toDouble();
    m_bModify = true;
}

void CMeasureParamDlg::modifyRatedCur(const QVariant& var)
{
    m_param.fRatedCur = var.toDouble();
    m_bModify = true;
}

void CMeasureParamDlg::modifyVolGrade(int index)
{
    m_param.fVolScale = comboBox_volGrade->itemData(index).toFloat();
    m_param.fRatedVol = m_param.fVolScale;
    lineEdit_RatedVol->setVar(QVariant(m_param.fRatedVol));
    m_bModify = true;
}

void CMeasureParamDlg::modifyZeroSquence(int index)
{
    m_param.bZeroSquence = comboBox_zeroSquence->itemData(index).toBool();
    m_bModify = true;
}

void CMeasureParamDlg::modifyCTSample(int index)
{
    m_param.nCTSample = comboBox_CTSample->itemData(index).toInt();
    m_bModify = true;
}