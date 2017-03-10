
#pragma once

#include <mThread>
#include "../driver/module.h"
#include <QMutex>

using namespace Dev_SM;

struct HarmonicRecordItem {
    bool bCurrent;          //true：电流谐波告警   false：电压谐波告警
    quint8 harmOrder;       // 2~31次谐波
    float fval;             //谐波值
};

class CHarmonicRecorder : public MThread
{
    Q_OBJECT
protected:
    CHarmonicRecorder(void);
    virtual ~CHarmonicRecorder(void);

public:
    enum RecordFlag {
        Record_NewData,
        Record_Init
    };

    typedef QList<HarmonicRecordItem*> DATABASE;
    static CHarmonicRecorder* recorder();

signals:
    /*
     *  @dataType:   取值 MC_DataUpdateFlag 或的关系
     */
    void dataUpdated(int dataType);

public:

private:
    virtual void run();

    void destroyDataBase(DATABASE& db);

private:
    DATABASE            m_database;
    QMutex              m_mutex;
    RecordFlag          m_recordFlag;
};