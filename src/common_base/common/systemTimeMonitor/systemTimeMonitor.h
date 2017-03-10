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
    //ʱ���쳣֪ͨ
    void systemTimeException(int event);
    //�����µ�һ�� �󷢳�֪ͨ   ���ʱ�䱻�޸ĺ�Ҳ�ᷢ����֪ͨ
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