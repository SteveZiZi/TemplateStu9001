#pragma once

#include <mThread>
#include "../driver/module.h"
#include <QMutex>

struct TempReordInfo {
    quint32 time;
    Dev_SM::WiringTempData_t temp;
};


class CMeasureTempRecorder : public MThread
{
    Q_OBJECT
public:
    enum {
        UPDATE_INTERVAL = 1000,                                            /*  ÿ�����һ������            */
        RECORD_INTERVAL = 60                                               /*  ÿ���Ӽ�¼һ������          */
    };

    enum RecordFlag {
        Update_Time_And_Data,
        Clear_All_Record,
        Update_Data_Only,
        Record_Init
    };
    typedef QList<TempReordInfo> DATABASE;

    static CMeasureTempRecorder* recorder();

    bool recordInfo(int pos, TempReordInfo* record);

signals:
    /*
     *  @type ȡֵ
     *   0: ����������
     *   1�����һ�����ݱ�����
     *  -1���б����
     */
    void dataUpdated(int type);

public slots:
    /*
     *  event ȡֵ����:
     *   enum SystemTimeEvent
     *   {
     *      DATE_TIME_NORMAL,               //ʱ������
     *      DATE_TIME_EXCEPTION,            //ʱ������쳣
     *      DATE_TIME_MODIFY,               //ʱ�䱻�޸�
     *      DATE_TIME_EXCEPT_RESTORE        //ʱ���쳣�� �Զ��ָ���ǰ��ʱ��
     *   };
     */
    void systemTimeException(int event);
    //�����µ�һ��  
    void systemTimeNewDay();    


private:
    virtual void run();
    void acquireNewTemp(TempReordInfo* tempInfo);

private:
    CMeasureTempRecorder();
    ~CMeasureTempRecorder();

private:
    DATABASE m_database;
    QMutex m_mutex;
    RecordFlag m_recordFlag;
};