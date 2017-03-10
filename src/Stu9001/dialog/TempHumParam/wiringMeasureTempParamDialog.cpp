#include "wiringMeasureTempParamDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <mDataEdit>
#include <dirKeyInputForData>

#include "debug.h"

#define REPORT_POS_L        150
#define REPORT_POS_T        60

#define CAPTION_WIDTH       180
#define CONTENT_WIDTH       75

#define REPORT_ITEM_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_ITEM_H       35



#define _create_list(label, label_name, label_caption, dataEdit, dataEditName, data, x, y) \
    label = new QLabel(this);\
    label->setObjectName(label_name);\
    label->setText(label_caption);\
    label->move(x, y);\
    \
    dataEdit = new MDataEdit(data, 0, 'f', 2, QString::fromLocal8Bit(" ℃"), this);\
    dataEdit->setObjectName(dataEditName);\
    dataEdit->move(x+CAPTION_WIDTH, y-5);\
    dataEdit->setFixedWidth(CONTENT_WIDTH)

CWiringMeasureTempParamDlg::CWiringMeasureTempParamDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    _create_list(m_label[0], "label_contactA", tr("Temp Threshold for phase A contact:"),
                 m_lineEdit[0], "lineEdit_contactA", 75.00f, x, y);

    y += REPORT_ITEM_H;
    _create_list(m_label[1], "label_contactB", tr("Temp Threshold for phase B contact:"),
                 m_lineEdit[1], "lineEdit_contactB", 75.00f, x, y);

    y += REPORT_ITEM_H;
    _create_list(m_label[2], "label_contactC", tr("Temp Threshold for phase C contact:"),
                 m_lineEdit[2], "lineEdit_contactC", 75.00f, x, y);

    //分割线
    y += REPORT_ITEM_H; 

    y += REPORT_ITEM_H; 
    _create_list(m_label[3], "label_busbarA", tr("Temp Threshold for phase A busbar:"),
                 m_lineEdit[3], "lineEdit_busbarA", 75.00f, x, y);

    y += REPORT_ITEM_H;
    _create_list(m_label[4], "label_busbarB", tr("Temp Threshold for phase B busbar:"),
                 m_lineEdit[4], "lineEdit_busbarB", 75.00f, x, y);

    y += REPORT_ITEM_H;
    _create_list(m_label[5], "label_busbarC", tr("Temp Threshold for phase C busbar:"),
                 m_lineEdit[5], "lineEdit_busbarC", 75.00f, x, y);

    m_dirKeyInput = new CDirKeyInputForData(5);
    m_dirKeyInput->addMaskChar('.');
    for(int i = 0; i < REPORT_ROWS; i++)
        m_lineEdit[i]->setDirKeyInput(m_dirKeyInput);
}

CWiringMeasureTempParamDlg::~CWiringMeasureTempParamDlg()
{
    //一定要最后才删除
    STU_DELETE_PTR (m_dirKeyInput);
}

void CWiringMeasureTempParamDlg::updateSettings(void)
{
    float* fThreshold = (float*)(&m_threshold);
    for (int i = 0 ; i < REPORT_ROWS; i++) {
        m_lineEdit[i]->setVar(QVariant(fThreshold[i]));
    }
}

//LineEdit changed
void CWiringMeasureTempParamDlg::modifySettings(const QVariant& var)
{
    QWidget* focusWdiget = this->focusWidget();
    float* fThreshold = (float*)(&m_threshold);
    float val = var.toFloat();

    for(int i = 0; i < MAX_PHASE_NUM; i++) {
        if (focusWdiget == m_lineEdit[i])
        {
            if (val > 100.0 || val < 0.00 || qAbs(val-fThreshold[i]) < 0.01) {
                m_lineEdit[i]->setVar(QVariant(fThreshold[i]));
            }
            else {
                fThreshold[i] = val;
                m_bModify = true;
            }
            break;
        }
    }
}

void CWiringMeasureTempParamDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        CWiringTempThreshold::wiringTempThreshold(&m_threshold);
        updateSettings();
        m_bModify = false;
        this->show();
        for(int i = 0; i < REPORT_ROWS; i++)
            connect(m_lineEdit[i], SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
    }

    if (style == CAbstractMenuContent::CONTENT_FOCUE) {
        m_lineEdit[0]->setFocus();
    }
}

void CWiringMeasureTempParamDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CWiringMeasureTempParamDlg::_LeaveContent data Changed";
        CWiringTempThreshold::setWiringTempThreshold(m_threshold);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CWiringMeasureTempParamDlg::_HideContent()
{
    if (!this->isHidden()) {
        for(int i = 0; i < REPORT_ROWS; i++)
            disconnect(m_lineEdit[i], SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
    }

    CBaseDialog::_HideContent();
}

void CWiringMeasureTempParamDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));
    painter.drawLine(STU_P_NAVI_W, 0, STU_P_NAVI_W, size().height());

    int x = REPORT_POS_L-15;
    int y = REPORT_POS_T+REPORT_ITEM_H*3+REPORT_ITEM_H/2-10; 
    int w = REPORT_ITEM_W+15;
    //绘制分隔线
    painter.drawLine(x, y, x+w, y);

    painter.setPen(oldPen);
}

void CWiringMeasureTempParamDlg::moveToNextWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_lineEdit[REPORT_ROWS-1]) {
        m_lineEdit[0]->setFocus(Qt::TabFocusReason);
    }
    else {
        focusNextChild();
    }
}

void CWiringMeasureTempParamDlg::moveToPreWidget() 
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_lineEdit[0]) {
        m_lineEdit[REPORT_ROWS-1]->setFocus(Qt::BacktabFocusReason);
    }
    else {
        focusPreviousChild();
    }
}