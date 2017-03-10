
#pragma once

#include <mThread>
#include "../driver/module.h"
#include <QMutex>

using namespace Dev_SM;

struct HarmonicRecordItem {
    bool bCurrent;          //true������г���澯   false����ѹг���澯
    quint8 harmOrder;       // 2~31��г��
    float fval;             //г��ֵ
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
     *  @dataType:   ȡֵ MC_DataUpdateFlag ��Ĺ�ϵ
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