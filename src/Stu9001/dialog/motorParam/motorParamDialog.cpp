#include "motorParamDialog.h"
#include "common.h"

#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <mComboBox>
#include <mDataEdit>
#include <mLineEdit>
#include <dirKeyInputForData>

#include "debug.h"

#define REPORT_POS_L        110
#define REPORT_POS_T        40

#define CAPTION_WIDTH       180
#define CONTENT_WIDTH       75

#define REPORT_ITEM_W      (CAPTION_WIDTH+CONTENT_WIDTH)
#define REPORT_ITEM_H       30


CMotorParamDlg::CMotorParamDlg(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    m_dev = CMotorParam::getInstance();

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    static QString captionName[REPORT_ROWS] = {
        CMotorParamDlg::tr("motor rated current"),
        CMotorParamDlg::tr("motor rated voltage"),
        CMotorParamDlg::tr("motor whole route"),
        CMotorParamDlg::tr("motor under vol protect"),

        CMotorParamDlg::tr("barrow stalled return"),
        CMotorParamDlg::tr("barrow pulse signal")
    };

    static char* s_unit[LINE_EDIT_NUM] = {
        "A", "V", ""
    };
    static bool s_isComboBox[REPORT_ROWS] = {
        0, 0, 0,
        1, 1, 1
    };

    int lineEditCnt = 0;
    int comboBoxCnt = 0;
    for(int i = 0; i < REPORT_ROWS; i++)
    {
        if ( i == 4) {
            y += REPORT_ITEM_H;     //跳过分割线
        }
        _create_label(m_label[i], captionName[i], x, y);
        if (s_isComboBox[i]) {
            _create_comboBox(m_comboBox[comboBoxCnt], QString("comboBox_motorParam%1").arg(comboBoxCnt), x+CAPTION_WIDTH, y);
            m_comboBox[comboBoxCnt]->addItem(CMotorParamDlg::tr("brake_disable"), false);
            m_comboBox[comboBoxCnt]->addItem(CMotorParamDlg::tr("brake_enable"), true);
            m_comboBox[comboBoxCnt]->setFixedHeight(m_comboBox[comboBoxCnt]->size().height()-10);
            m_comboBox[comboBoxCnt]->setFixedWidth(CONTENT_WIDTH-5);
            comboBoxCnt++;
        }
        else {
            if (lineEditCnt != 2) {
                _create_lineEdit_float(m_lineEdit[lineEditCnt], QString("lineEdit_motorParam%1").arg(lineEditCnt), 
                                       0.0f, 2, s_unit[lineEditCnt], x+CAPTION_WIDTH, y);
            }
            else {
                _create_lineEdit_float(m_lineEdit[lineEditCnt], QString("lineEdit_motorParam%1").arg(lineEditCnt), 
                                       0.0f, 0, s_unit[lineEditCnt], x+CAPTION_WIDTH, y);
            }
            m_lineEdit[lineEditCnt]->setFixedWidth(CONTENT_WIDTH);
            lineEditCnt++;
        }
        y += REPORT_ITEM_H;
    }

    m_dirKeyInput = new CDirKeyInputForData();
    m_dirKeyInput->addMaskChar('.');
    for(int i = 0; i < LINE_EDIT_NUM; i++) {
        m_lineEdit[i]->setDirKeyInput(m_dirKeyInput);
    }
}

CMotorParamDlg::~CMotorParamDlg()
{
    //一定要最后才删除
    STU_DELETE_PTR (m_dirKeyInput);
}


void CMotorParamDlg::updateSettings(void)
{
    float* fVal = &m_settings.fRatedCur;
    for(int i = 0; i < LINE_EDIT_NUM; i++) {
        m_lineEdit[i]->setVar(QVariant(fVal[i]));
    }

    bool* bVal = &m_settings.bUnderVolProtect;
    for(int i = 0; i < COMBOBOX_NUM; i++) {
        m_comboBox[i]->setCurrentIndex(m_comboBox[i]->findData(QVariant(bVal[i])));
    }
}

//LineEdit changed
void CMotorParamDlg::modifySettings(const QVariant& var)
{
    QWidget* focusWdiget = this->focusWidget();
    float* val = &m_settings.fRatedCur;

    for(int i = 0; i < LINE_EDIT_NUM; i++) {
        if (focusWdiget == m_lineEdit[i]) {
            val[i] = var.toFloat();
            m_bModify = true;
            break;
        }
    }
}

//ComboBox changed
void CMotorParamDlg::modifySettings(int index)
{
    QWidget* focusWdiget = this->focusWidget();
    bool* val = &m_settings.bBarrowStalledReturn;

    for(int i = 0; i < COMBOBOX_NUM; i++) {
        if (focusWdiget == m_comboBox[i]) {
            val[i] = m_comboBox[i]->itemData(index).toBool();
            m_bModify = true;
            break;
        }
    }
}


void CMotorParamDlg::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        m_dev->motorParamSettings(&m_settings);
        updateSettings();
        m_bModify = false;
        this->show();

        for(int i = 0; i < LINE_EDIT_NUM; i++){
            connect(m_lineEdit[i], SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        }
        for(int i = 0; i < LINE_EDIT_NUM; i++){
            connect(m_comboBox[i], SIGNAL(currentIndexChanged(int)), this, SLOT(modifySettings(int)));
        }
    }

	if (style == CAbstractMenuContent::CONTENT_FOCUE)
		m_lineEdit[0]->setFocus();
}

void CMotorParamDlg::_LeaveContent()
{
    if (m_bModify) {
        qDebug() << "CMotorParamDlg::_LeaveContent data Changed";
        m_dev->setMotorParamSettings(m_settings);
        m_bModify = false;
    }

    CBaseDialog::_LeaveContent();
}

void CMotorParamDlg::_HideContent()
{
    if (!this->isHidden()) {
        for(int i = 0; i < LINE_EDIT_NUM; i++){
            disconnect(m_lineEdit[i], SIGNAL(dataChanged(const QVariant&)), this, SLOT(modifySettings(const QVariant&)));
        }
        for(int i = 0; i < LINE_EDIT_NUM; i++){
            disconnect(m_comboBox[i], SIGNAL(currentIndexChanged(int)), this, SLOT(modifySettings(int)));
        }
    }

    CBaseDialog::_HideContent();
}

void CMotorParamDlg::paintEvent(QPaintEvent *event)
{
    CBaseDialog::paintEvent(event);

    QPainter painter(this);
    const QPen& oldPen = painter.pen();
    painter.setPen(QPen(STU_GREEN_LINE));

    int x = REPORT_POS_L-15;
    int w = REPORT_ITEM_W+30;
    //绘制分隔线
    int y = REPORT_POS_T+REPORT_ITEM_H*4+REPORT_ITEM_H/2-5;
    painter.drawLine(x, y, x+w, y);

    painter.setPen(oldPen);
}

void CMotorParamDlg::moveToNextWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_comboBox[COMBOBOX_NUM-1]) {
        m_lineEdit[0]->setFocus(Qt::TabFocusReason);
    }
    else {
        focusNextChild();
    }
}

void CMotorParamDlg::moveToPreWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_lineEdit[0]) {
        m_comboBox[COMBOBOX_NUM-1]->setFocus(Qt::BacktabFocusReason);
    }
    else {
        focusPreviousChild();
    }
}