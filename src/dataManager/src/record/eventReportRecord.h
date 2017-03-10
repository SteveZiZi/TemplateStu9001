#pragma once

#include <mThread>
#include "../driver/module.h"
#include "../driver/DevAttrMgr.h"
#include <QMutex>


struct EventTime_cp6000 {
    quint8 year;       //  当前年(2000～2099)
    quint8 month;      //  当前月(1～12)
    quint8 day;        //  当前日(1～31)
    quint8 hour;       //  当前时(0～23)
    quint8 minute;     //  当前分(0～59)
    quint8 second;     //  当前秒(0～59)
    quint16 ms;
};

enum EventType_Enum {
    ET_DI_CHANGED = 23,         // 1 ~ 23
    ET_ACTION_EVENT = 59,       // 24 ~ 59
    ET_SELF_CHECK = 255         // 60 ~ 255
};

/*
 *  事件记录条目
 *  @Description:
 *      如果该事件有录波，则事件反生时间的日期+recordNo 对应录波文件名
 */
#define Event_Record_Start 0x5AA5
#define Event_Record_End   0x1234
struct EventRecordItem
{
    quint16 recordStart;        //开始标志  固定为  Event_Record_Start
    EventTime_cp6000 eventTime;
    quint8 eventStyle;          //取值  EventType_Enum
    union {
        bool diStatus;
        float fActionValue;
    };
    bool bRecord;
    quint32 recordNo;
    quint16 recordEnd;        //结束标识   固定为  Event_Record_End
    EventRecordItem() : recordStart(Event_Record_Start), recordEnd(Event_Record_End) {}
};


struct RecrodHeader_cp6000 {
    quint16 faultNo;
    EventTime_cp6000 eventTime;
};

struct RecordSmv_cp6000 {
    quint16 sampleNo;
    float phaseVol[3];
    float protectCur[3];
    float zeroSequenceVol;
    float zeroSequenceCur;
    float Ux;
    quint16 diStatus;
};


class CEventReportRecorder : public MThread
{
    Q_OBJECT
public:
    enum {
        UPDATE_INTERVAL_MS = 500,                                       /*  每500ms更新一次数据         */
        RECORD_INTERVAL_MS = 60000                                      /*  每分钟记录一次数据          */
    };

    enum RecordFlag {
        Record_NewData,         //有新的记录
        Record_NewMonth,        //新的一个月到来，需要切换缓冲区，并丢弃上上个月的数据
        Record_Init
    };

    typedef QList<EventRecordItem*> DATABASE;

    static CEventReportRecorder* recorder();

    bool recordInfo(int pos, EventRecordItem* record);

signals:
    /*
     *  @type 取值
     *  >0: 加入新数据的条数
     *  -1：列别被清空
     */
    void dataUpdated(int type);

public slots:
    //进入新的一天  
    void systemTimeNewDay();    


private:
    virtual void run();

    bool loadDataBase(DATABASE& db, QString& fileName);
    void destroyDataBase(DATABASE& db);

    //返回新事件记录的条数
    int detectNewEvent();
    void eventToEventRoport(const ResultFileContent_t& content, EventRecordItem& eventReport);
    void getRecord(quint32 recordNo, quint8* buf);
    bool saveRecordToFile(const EventRecordItem& eventItem, const quint8* record, quint32 len);
    void destoryRecordFile(const EventRecordItem& eventItem);
    bool saveCurEventToFile();

private:
    CEventReportRecorder();
    ~CEventReportRecorder();

private:
    DATABASE m_database[2];             //保存两个月的记录
    DATABASE* m_preMonthDB;             //指向上一个月的记录
    DATABASE* m_curMonthDB;             //指向当前月的记录
    QMutex m_mutex;
    RecordFlag m_recordFlag;
    quint8 m_curMonth;

    quint16 m_soeCnt;
    quint16 m_diChangedCnt;

    quint32 m_recordNo;
    QString m_curEventFileName;
    QString m_preEventFileName;
    quint32 m_curEventFileLength;
};