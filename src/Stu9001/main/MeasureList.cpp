#include "MeasureList.h"
#include "MeasureItem.h"

#include <QtGui>

#include <MeasureShowData>
#include <TempHumShowData>
#include <WireTypeSettings>

#include "common.h"
#include "debug.h"

CMeasureList::CMeasureList(QWidget* parent)
: QGroupBox(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateMeasure()));

    m_measureDev = CMeasureShowData::getInstance();
    m_tempHumDev = CTempHumShowData::getInstance();
    m_wireTypeDev = CWireTypeSettings::getInstance();
}

CMeasureList::~CMeasureList()
{
    if (m_timer && m_timer->isActive())
        m_timer->stop();
    destroy();
}



void CMeasureList::create(void)
{
    CMeasureItem* item = NULL;

    int x0 = 10;
    int x1 = size().width()/2 + 10;
    int y = 35;
    int h = 35;

    struct caption {
        char* name;
        char* value;
        char* unit;
    };

    struct caption  measure[] = {
        {"Ia:",     "0.000",    "A"},
        {"Ib:",     "0.000",    "A"},
        {"Ic:",     "0.000",    "A"},
        {"Uab:",    "10.00",    "kV"},
        {"Ubc:",    "10.00",    "kV"},
        {"Uac:",    "10.00",    "kV"},
        {"F:",      "50.00",    "Hz"},
        {"PFa:",    "0.920",    ""},
        {"PFb:",    "0.920",    ""},
        {"PFc:",    "0.920",    ""},
    };

    struct caption  TempHum[] = {
        {"A上:",    "26.0",    "℃"},
        {"A下:",    "26.0",    "℃"},
        {"B上:",    "26.0",    "℃"},
        {"B下:",    "26.0",    "℃"},
        {"C上:",    "26.0",    "℃"},
        {"C下:",    "26.0",    "℃"},
        {"TP1:",    "25.0",    "℃"},
        {"TP2:",    "25.0",    "℃"},
        {"HD1:",    "75%",      ""},
        {"HD2:",    "75%",      ""},
    };

    for(int i = 0; i < sizeof(measure)/sizeof(measure[0]); i++)
    {
        item = new CMeasureItem(this, QString::fromLocal8Bit(measure[i].name),
                                      QString::fromLocal8Bit(measure[i].value),
                                      QString::fromLocal8Bit(measure[i].unit));
        item->move(x0, y);
        m_measureList.append(item);
        y += h;
    }

    y = 35;
    for(int i = 0; i < sizeof(TempHum)/sizeof(TempHum[0]); i++)
    {
        item = new CMeasureItem(this, QString::fromLocal8Bit(TempHum[i].name),
                                      QString::fromLocal8Bit(TempHum[i].value),
                                      QString::fromLocal8Bit(TempHum[i].unit));
        item->move(x1, y);
        m_measureList.append(item);
        y += h;
    }

    m_timer->start(500);
}

void CMeasureList::destroy(void)
{
    for(MeasureList::Iterator it = m_measureList.begin(); it != m_measureList.end(); it++)
    {
        delete *it;
    }
    m_measureList.clear();
}

void CMeasureList::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawText(50, 20, QString::fromLocal8Bit("测量状态"));
    painter.drawText(200, 20, QString::fromLocal8Bit("温湿状态"));

    painter.setPen(QPen(STU_GREEN_LINE));

    int x = 10;
    int y = 30;
    int l = size().width()-20;
    painter.drawLine(x, y, x+l, y);

    x += l / 2;
    l = size().height() - y - 20;
    painter.drawLine(x, y, x, y+l);
}

void CMeasureList::updateMeasure()
{
    WIRE_LINK_STYLE_ENUM link = THREE_PHASE_THREE_WIRE_Delta;
    m_wireTypeDev->wireTypeSettings(&link);
    if (link != THREE_PHASE_THREE_WIRE_Delta) {
        m_measureList[3]->setCaption(QString("Ua:"));
        m_measureList[4]->setCaption(QString("Ub:"));
        m_measureList[5]->setCaption(QString("Uc:"));
    }
    else {
        m_measureList[3]->setCaption(QString("Uab:"));
        m_measureList[4]->setCaption(QString("Ubc:"));
        m_measureList[5]->setCaption(QString("Uca:"));
    }
    MeasureShowData measureData;
    m_measureDev->GetMeasureShowData(&measureData);
    for(int i = 0; i < 3; i++) {
        m_measureList[0+i]->setValue(QString("%1").arg(measureData.Current[i], 0, 'f', 2, QChar('0')));
        if (link != THREE_PHASE_THREE_WIRE_Delta) 
            m_measureList[3+i]->setValue(QString("%1").arg(measureData.lineVol[i], 0, 'f', 2, QChar('0')));
        else 
            m_measureList[3+i]->setValue(QString("%1").arg(measureData.phaseVol[i], 0, 'f', 2, QChar('0')));
        m_measureList[7+i]->setValue(QString("%1").arg(measureData.PowerFactor[i], 0, 'f', 2, QChar('0')));
    }
    m_measureList[6]->setValue(QString("%1").arg(measureData.Frequence, 0, 'f', 2, QChar('0')));


    TempShowData tempData;
    m_tempHumDev->GetContectTemp(&tempData);
    for(int chnl = 0; chnl < 2; chnl++) {
        for(int i = 0; i < 3; i++) {
            m_measureList[10+chnl+i*2]->setValue(QString("%1").arg(tempData.fTemp[chnl][i], 0, 'f', 2, QChar('0')));
        }
    }

    HumidityData humData;
    m_tempHumDev->GetCubicleHum(&humData);

    for(int chnl = 0; chnl < 2; chnl++) {
        m_measureList[16+chnl]->setValue(QString("%1").arg(humData.fTemp[chnl], 0, 'f', 2, QChar('0')));
        m_measureList[18+chnl]->setValue(QString("%1%").arg(humData.fTumidity[chnl], 0, 'f', 0));
    }
}


void CMeasureList::startRefreshTask(quint32 ms)
{
    Q_ASSERT(m_timer);
    m_timer->start(ms);
}

void CMeasureList::stopRefreshTask()
{
    m_timer->stop();
}