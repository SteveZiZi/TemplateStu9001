#include "systemTimeMonitor.h"

#include <QDateTime>
#include "debug.h"

#define NORMAL_INTERVAL         (5000)
#define EXCEPTION_INTERVAL      (1000)

#define NORMAL_ALLOW_OFFSET     (50)
#define EXCEPTION_ALLOW_OFFSET  (15)


typedef QList<QDateTime> DateTimeList;
class CSystemTimeMonitorPrivate
{
public:
    CSystemTimeMonitorPrivate() : m_event(DATE_TIME_NORMAL){ }
    ~CSystemTimeMonitorPrivate() { }

    DateTimeList m_normal;

    SystemTimeEvent m_event;
};


CSystemTimeMonitor::CSystemTimeMonitor(QObject *parent)
: MThread(parent)
, m_data(new CSystemTimeMonitorPrivate())
{
    start(NormalPriority);
}

CSystemTimeMonitor::~CSystemTimeMonitor()
{
    exit();
    delete m_data;
}


CSystemTimeMonitor* CSystemTimeMonitor::getInstance()
{
    static CSystemTimeMonitor monitor;
    return &monitor;
}


void CSystemTimeMonitor::run()
{
    qDebug() << "CSystemTimeMonitor::run";
    DateTimeList& normalList = m_data->m_normal;
    QDateTime exceptTime;
    SystemTimeEvent& event = m_data->m_event;
    QDateTime dateTime(QDateTime::currentDateTime());
    int interval = NORMAL_INTERVAL;
    int cnt = 0;

    normalList.reserve(5);
    for(int i = 0; i < 5; i++)
        normalList.append(dateTime);

    event = DATE_TIME_NORMAL;

    do
    {
        dateTime = QDateTime::currentDateTime();

        if (event == DATE_TIME_NORMAL) {
            const QDateTime& normalTime = normalList.at(4);
            if (dateTime < normalTime || normalTime.secsTo(dateTime) > NORMAL_ALLOW_OFFSET) {
                event = DATE_TIME_EXCEPTION;
                interval = EXCEPTION_INTERVAL;
                exceptTime = dateTime;
                cnt = 0;
                qDebug() << "CSystemTimeMonitor emit systemTimeException(DATE_TIME_EXCEPTION)";
                emit systemTimeException(event);
            }
            else {
                if (normalTime.date().day() != dateTime.date().day()) {
                    emit systemTimeNewDay();
                }
                normalList.pop_front();
                normalList.push_back(dateTime);
            }
        }
        else {
            if (dateTime < exceptTime || dateTime.secsTo(exceptTime) > NORMAL_ALLOW_OFFSET) {
                cnt = 0;
            }
            else {
                cnt++;
                if (cnt >= 5) {
                    if (dateTime > normalList.at(4) && normalList.at(4).secsTo(dateTime) <= NORMAL_ALLOW_OFFSET) {
                        qDebug() << "CSystemTimeMonitor emit systemTimeException(DATE_TIME_EXCEPT_RESTORE)";
                        emit systemTimeException(DATE_TIME_EXCEPT_RESTORE);
                    }
                    else {
                        emit systemTimeNewDay();
                        qDebug() << "CSystemTimeMonitor emit systemTimeException(DATE_TIME_MODIFY)";
                        emit systemTimeException(DATE_TIME_MODIFY);
                    }
                    event = DATE_TIME_NORMAL;
                    interval = NORMAL_INTERVAL;
                    normalList.clear();
                    for(int i = 0; i < 5; i++)
                        normalList.append(dateTime);
                }
            }
            exceptTime = dateTime;
        }
    }while(!waitCondition(interval));
}