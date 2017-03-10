#pragma once

#include <MThread>
#include <QWaitCondition>

#include <stu_global.h>

class CSystemTimeMonitorPrivate;
class CSystemTimeMonitor : public MThread
{
    Q_OBJECT

public:
    static CSystemTimeMonitor* getInstance();

signals:
    //时间异常通知
    void systemTimeException(int event);
    //进入新的一天 后发出通知   如果时间被修改后，也会发出该通知
    void systemTimeNewDay();    

protected:
    CSystemTimeMonitor(QObject *parent = 0);
    ~CSystemTimeMonitor();

protected:
    virtual void run();

private:
    CSystemTimeMonitorPrivate* m_data;
    bool m_bExitThread;
};