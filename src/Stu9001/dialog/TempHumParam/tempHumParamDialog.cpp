#include "tempHumParamDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <mDataEdit>
#include <dirKeyInputForData>

#include "debug.h"

#define REPORT_POS_L        170
#define REPORT_POS_T        60

#define CAPTION_WIDTH       140
#define CONTENT_WIDTH       75

#define REPORT_ITEM_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_ITEM_H       35



#define _create_temp(label, label_name, label_caption, dataEdit, dataEditName, data, x, y) \
    label = new QLabel(this);\
    label->setObjectName(label_name);\
    label->setText(label_caption);\
    label->move(x, y);\
    \
    dataEdit = new MDataEdit(data, 0, 'f', 2, QString::fromLocal8Bit(" ℃"), this);\
    dataEdit->setObjectName(dataEditName);\
    dataEdit->move(x+CAPTION_WIDTH, y-5);\
    dataEdit->setFixedWidth(CONTENT_WIDTH)

#define _create_humidity(label, label_name, label_caption, dataEdit, dataEditName, data, x, y) \
    label = new QLabel(this);\
    label->setObjectName(label_name);\
    label->setText(label_caption);\
    label->move(x, y);\
    \
    dataEdit = new MDataEdit(data, 0, 10, QString::fromLocal8Bit(" %"), this);\
    dataEdit->setObjectName(dataEditName);\
    dataEdit->move(x+CAPTION_WIDTH, y-5);\
    dataEdit->setFixedWidth(CONTENT_WIDTH)

CTempHumParamDlg::CTempHumParamDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    _create_temp(label_tempMax, "label_tempMax", tr("Temp Max Value:"),
                lineEdit_tempMax, "lineEdit_tempMax", 80.00f, x, y);

    y += REPORT_ITEM_H;
    _create_temp(label_tempMin, "label_tempMin", tr("Temp Min Value:"),
                 lineEdit_tempMin, "lineEdit_tempMin", 0.00f, x, y);

    //分割线
    y += REPORT_ITEM_H; 

    y += REPORT_ITEM_H; 
    _create_humidity(label_humMax, "label_humMax", tr("Hum Max Value:"),
                 lineEdit_humMax, "lineEdit_humMax", 80u, x, y);

    y += REPORT_ITEM_H;
    _create_humidity(label_humMin, "label_humMin", tr("Hum Min Value:"),
                 lineEdit_humMin, "lineEdit_humMin", 0u, x, y);

    m_dirKeyInput = new CDirKeyInputForData(5);
    m_dirKeyInput->addMaskChar('.');
    lineEdit_tempMax->setDirKeyInput(m_dirKeyInput);
    lineEdit_tempMin->setDirKeyInput(m_dirKeyInput);
    lineEdit_humMax->setDirKeyInput(m_dirKeyInput);
    lineEdit_humMin->setDirKeyInput(m_dirKeyInput);
}

CTempHumParamDlg::~CTempHumParamDlg()
{
    //一定要最后才删除
    STU_DELETE_PTR (m_dirKeyInput);
}

void CTempHumParamDlg::updateSettings(void)
{
    lineEdit_tempMax->setVar(QVariant(m_threshold[m_nItem].fTempMax));
    lineEdit_tempMin->setVar(QVariant(m_threshold[m_nItem].fTempMin));

    lineEdit_humMax->setVar(QVariant(m_threshold[m_nItem].nHumidityMax));
    lineEdit_humMin->setVar(QVariant(m_threshold[m_nItem].nHumidityMin));
}

//LineEdit changed
void CTempHumParamDlg::modifySettings(const QVariant& var)
{
    QWidget* focusWdiget = this->focusWidget();

    if (focusWdiget == lineEdit_tempMax) {
        float val = var.toFloat();
        if (val > 100.0 || val < 0.0) {
            lineEdit_tempMax->setVar(QVariant(m_threshold[m_nItem].fTempMax));
            return ;
        }
        if (qAbs(val-m_threshold[m_nItem].fTempMax) >= 0.01) {
            m_threshold[m_nItem].fTempMax = val;
            m_bModify = true;
        }
    }
    else if (focusWdiget == lineEdit_tempMin) {
        float val = var.toFloat();
        if (val > 100.0 || val < 0.0) {
            lineEdit_tempMin->setVar(QVariant(m_threshold[m_nItem].fTempMin));
            return ;
        }
        if (qAbs(val-m_threshold[m_nItem].fTempMin) >= 0.01) {
            m_threshold[m_nItem].fTempMin = val;
            m_bModify = true;
        }
    }
    else if (focusWdiget == lineEdit_humMax) {
        quint32 val = var.toUInt();
        if (val > 100) {
            lineEdit_humMax->setVar(QVariant(m_threshold[m_nItem].nHumidityMax));
            return ;
        }
        if (val != m_threshold[m_nItem].nHumidityMax) {
            m_threshold[m_nItem].nHumidityMax = val;
            m_bModify = true;
        }
    }
    else  {
        quint32 val = var.toUInt();
        if (val > 100) {
            lineEdit_humMin->setVar(QVariant(m_threshold[m_nItem].nHumidityMin));
            return ;
        }
        if (val != m_threshold[m_nItem].nHumidityMin) {
            m_threshold[m_nItem].nHumidityMin = val;
            m_bModify = true;
        }
    }
}

void CTempHumParamDlg::_ShowContent(int style, quint32 data)
{
    int item = (data == 2) ? 0 : 1;
    
    if (this->isHidden() || m_nItem != item) {
        m_nItem = item;
        CThumidityThreshold::THThreshold(m_nItem, &m_threshold[m_nItem]);
        updateSettings();
        m_bModify = false;
        this->show();
        connect(lineEdit_tempMax, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        connect(lineEdit_tempMin, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        connect(lineEdit_humMax, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        connect(lineEdit_humMin, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        lineEdit_tempMax->setFocus();
    }
}

void CTempHumParamDlg::_LeaveContent()
{
    if (m_bModify) {
        if ((m_threshold[m_nItem].fTempMax < m_threshold[m_nItem].fTempMin) ||
            (m_threshold[m_nItem].nHumidityMax < m_threshold[m_nItem].nHumidityMin))
        {
            qDebug() << "CTempHumParamDlg::_LeaveContent  error" ;
            return ;
        }
        qDebug() << "CTempHumParamDlg::_LeaveContent data Changed";
        CThumidityThreshold::setTHThreshold(m_nItem, m_threshold[m_nItem]);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CTempHumParamDlg::_HideContent()
{
    if (!this->isHidden()) {
        disconnect(lineEdit_tempMax, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        disconnect(lineEdit_tempMin, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        disconnect(lineEdit_humMax, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        disconnect(lineEdit_humMin, SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
    }

    CBaseDialog::_HideContent();
}

void CTempHumParamDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    int x = REPORT_POS_L-15;
    int y = REPORT_POS_T+REPORT_ITEM_H*2+REPORT_ITEM_H/2-10; 
    int w = REPORT_ITEM_W+15;
    //绘制分隔线
    painter.drawLine(x, y, x+w, y);

    painter.setPen(oldPen);
}

void CTempHumParamDlg::moveToNextWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == lineEdit_humMin) {
        lineEdit_tempMax->setFocus(Qt::TabFocusReason);
    }
    else {
        focusNextChild();
    }
}

void CTempHumParamDlg::moveToPreWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == lineEdit_tempMax) {
        lineEdit_humMin->setFocus(Qt::BacktabFocusReason);
    }
    else {
        focusPreviousChild();
    }
}