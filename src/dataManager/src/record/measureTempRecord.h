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
        UPDATE_INTERVAL = 1000,                                            /*  每秒更新一次数据            */
        RECORD_INTERVAL = 60                                               /*  每分钟记录一次数据          */
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
     *  @type 取值
     *   0: 加入新数据
     *   1：最后一个数据被更新
     *  -1：列别被清空
     */
    void dataUpdated(int type);

public slots:
    /*
     *  event 取值如下:
     *   enum SystemTimeEvent
     *   {
     *      DATE_TIME_NORMAL,               //时间正常
     *      DATE_TIME_EXCEPTION,            //时间出现异常
     *      DATE_TIME_MODIFY,               //时间被修改
     *      DATE_TIME_EXCEPT_RESTORE        //时间异常后 自动恢复以前的时间
     *   };
     */
    void systemTimeException(int event);
    //进入新的一天  
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