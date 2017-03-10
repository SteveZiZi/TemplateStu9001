#include "cubicleOperator.h"
#include "common.h"

#include <QtGui/QLabel>
#include <MComboBox>
#include <QPainter>
#include <QKeyEvent>

#include "debug.h"

#define REPORT_POS_L        0
#define REPORT_POS_T        20

#define CAPTION_WIDTH       100
#define CONTENT_WIDTH       70
#define REPORT_ITEM_H       40

#define REPORT_W        (CAPTION_WIDTH+CONTENT_WIDTH+20)


enum OPERATROR_ITEM {
    ITEM_MODE =0,
    ITEM_HEATER1,
    ITEM_HEATER2,
    ITEM_FAN1,
    ITEM_FAN2,
    ITEM_LAMP,
    ITEM_GATE
};


CCubicleOperator::CCubicleOperator(QWidget *parent)
: QGroupBox(parent)
{
    QLinearGradient linerarGradient(0, 0, REPORT_W, 0);
    linerarGradient.setColorAt(0.0, Qt::black);
    linerarGradient.setColorAt(0.5, STU_GREEN_LINE);
    linerarGradient.setColorAt(1.0, Qt::black);

    m_linearGradientPen = QPen(QBrush(linerarGradient),1);

    createCtrl();
    m_firstEnableWidget = m_comboBox[0];
    m_lastEnableWidget = m_comboBox[ROWS-1];
    connect(m_comboBox[ITEM_MODE], SIGNAL(currentIndexChanged(int)), this, SLOT(modeComboBoxSelChanged(int)));

    connect(m_comboBox[ITEM_FAN1], SIGNAL(currentIndexChanged(int)), this, SLOT(fan1ComboBoxSelChanged(int)));
    connect(m_comboBox[ITEM_FAN2], SIGNAL(currentIndexChanged(int)), this, SLOT(fan2ComboBoxSelChanged(int)));

    connect(m_comboBox[ITEM_HEATER1], SIGNAL(currentIndexChanged(int)), this, SLOT(heater1ComboBoxSelChanged(int)));
    connect(m_comboBox[ITEM_HEATER2], SIGNAL(currentIndexChanged(int)), this, SLOT(heater2ComboBoxSelChanged(int)));

    connect(m_comboBox[ITEM_LAMP], SIGNAL(currentIndexChanged(int)), this, SLOT(lampComboBoxSelChanged(int)));
    connect(m_comboBox[ITEM_GATE], SIGNAL(currentIndexChanged(int)), this, SLOT(gateComboBoxSelChanged(int)));
}

CCubicleOperator::~CCubicleOperator()
{
    for(int i = 0; i < ROWS; i++) {
        STU_DELETE_PTR(m_label[i]);
        STU_DELETE_PTR(m_comboBox[i]);
    }
}


MComboBox* CCubicleOperator::comboBox(int row)
{
    if(row < ROWS && row >= 0) {
        return m_comboBox[row];
    }
    Q_ASSERT(false);
    return NULL;
}


void CCubicleOperator::createCtrl()
{
    static QString captionName[ROWS] = {
        CCubicleOperator::tr("mode:"),
        CCubicleOperator::tr("Heater1:"),
        CCubicleOperator::tr("Heater2:"),
        CCubicleOperator::tr("Fan1:"),
        CCubicleOperator::tr("Fan2:"),
        CCubicleOperator::tr("Lamp:"),
        CCubicleOperator::tr("Gate:"),
    };

    int x = REPORT_POS_L;
    int y = REPORT_POS_T; 

    for(int i = 0; i < ROWS; i++) {
        _create_label(m_label[i], captionName[i], x, y);
        _create_comboBox(m_comboBox[i], QString("CubicleOperator%1").arg(i), x+CAPTION_WIDTH+5, y);
        m_comboBox[i]->setFixedHeight(m_comboBox[i]->size().height()-10);
        m_comboBox[i]->setFixedWidth(CONTENT_WIDTH);
        if (i != 0) {
            m_comboBox[i]->addItem(CCubicleOperator::tr("close"), 0);
            m_comboBox[i]->addItem(CCubicleOperator::tr("start"), 1);
        }
        else {
            m_comboBox[i]->addItem(CCubicleOperator::tr("manual mode"), 0);
            m_comboBox[i]->addItem(CCubicleOperator::tr("auto mode"), 1);
        }
        y += REPORT_ITEM_H;
    }
}

void CCubicleOperator::paintEvent(QPaintEvent *event)
{
    int x = REPORT_POS_L;
    int y = REPORT_POS_T+REPORT_ITEM_H-10; 

    QPainter painter(this);
    
    const QPen& oldPen = painter.pen();
    painter.setPen(m_linearGradientPen);

    for(int i = 0; i < ROWS; i++) {
        painter.drawLine(x, y, x+REPORT_W, y);
        y += REPORT_ITEM_H;
    }
}

void CCubicleOperator::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    qDebug() << "CCubicleOperator::keyPressEvent:" << hex << event->key();

    switch(key) 
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
        event->accept();
        break;
    case Qt::Key_Up:
        moveToPreWidget();
        event->accept();
        break;
    case Qt::Key_Down:
        moveToNextWidget();
        event->accept();
        break;
    default:
        event->ignore();
        break;
    }

    if (!event->isAccepted()) {
        QGroupBox::keyPressEvent(event);
    }
}


void CCubicleOperator::moveToNextWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_lastEnableWidget) {
        m_firstEnableWidget->setFocus(Qt::TabFocusReason);
    }
    else {
        focusNextChild();
    } 
}

void CCubicleOperator::moveToPreWidget()
{
    QWidget* currentFocusWidget = focusWidget();
    if (currentFocusWidget == m_firstEnableWidget) {
        m_lastEnableWidget->setFocus(Qt::TabFocusReason);
    }
    else {
        focusPreviousChild();
    } 
}


/*
**  改变柜内操控的模式，自动模式下，其他下拉框禁止获得焦点
*/
void CCubicleOperator::modeComboBoxSelChanged(int sel)
{
    bool bAuto = (sel == 1);
    for(int i = 1; i < ROWS; i++) {
        m_comboBox[i]->setDisabled(bAuto);
    }

    if (bAuto) {
        m_lastEnableWidget = m_comboBox[0];
    }
    else {
        m_lastEnableWidget = m_comboBox[ROWS-1];
    }

    emit modeChanged(bAuto);
}

void CCubicleOperator::fan1ComboBoxSelChanged(int sel)
{
    emit fanStatusChanged(0, (sel==1));
}

void CCubicleOperator::fan2ComboBoxSelChanged(int sel)
{
    emit fanStatusChanged(1, (sel==1));
}

void CCubicleOperator::lampComboBoxSelChanged(int sel)
{
    emit lampStatusChanged(0, (sel==1));
    emit lampStatusChanged(1, (sel==1));
}

void CCubicleOperator::heater1ComboBoxSelChanged(int sel)
{
    emit heaterStatusChanged(0, (sel==1));
}

void CCubicleOperator::heater2ComboBoxSelChanged(int sel)
{
    emit heaterStatusChanged(1, (sel==1));
}

void CCubicleOperator::gateComboBoxSelChanged(int sel)
{
    emit gateStatusChanged((sel==1));
}


