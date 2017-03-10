#include "ExceptionEventMgr.h"


#include <systemTimeMonitor>
#include <measureTempRecorder>
#include <eventReportRecorder>
#include <machineCharacterRecorder>

#include "debug.h"

CExceptionEventMgr::CExceptionEventMgr()
{
}

CExceptionEventMgr::~CExceptionEventMgr()
{

}

CExceptionEventMgr* CExceptionEventMgr::getInstance()
{
    static CExceptionEventMgr mgr;
    return &mgr;
}

void CExceptionEventMgr::init()
{
    connect(CSystemTimeMonitor::getInstance(), SIGNAL(systemTimeException(int)), CMeasureTempRecorder::recorder(), SLOT(systemTimeException(int)));
    connect(CSystemTimeMonitor::getInstance(), SIGNAL(systemTimeNewDay()), CMeasureTempRecorder::recorder(), SLOT(systemTimeNewDay()));

    CMeasureTempRecorder::recorder()->start(QThread::HighPriority);
    CEventReportRecorder::recorder()->start(QThread::HighestPriority);
    CMachineCharacterRecorder::recorder()->start(QThread::HighPriority);
}

void CExceptionEventMgr::deinit()
{
    disconnect(CSystemTimeMonitor::getInstance(), SIGNAL(systemTimeException(int)), CMeasureTempRecorder::recorder(), SLOT(systemTimeException(int)));
    disconnect(CSystemTimeMonitor::getInstance(), SIGNAL(systemTimeNewDay()), CMeasureTempRecorder::recorder(), SLOT(systemTimeNewDay()));

    CSystemTimeMonitor::getInstance()->exitThread();
    CMachineCharacterRecorder::recorder()->exitThread();
    CMeasureTempRecorder::recorder()->exitThread();
    CEventReportRecorder::recorder()->exitThread();

    //等待线程安全退出
    CSystemTimeMonitor::getInstance()->wait(100);
    CMeasureTempRecorder::recorder()->wait(100);
    CEventReportRecorder::recorder()->wait(100);
    CMachineCharacterRecorder::recorder()->wait(100);

    CSystemTimeMonitor::getInstance()->quit();
    CMeasureTempRecorder::recorder()->quit();
    CEventReportRecorder::recorder()->quit();
    CMachineCharacterRecorder::recorder()->quit();
}