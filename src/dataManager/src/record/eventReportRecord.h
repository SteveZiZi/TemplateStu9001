#pragma once

#include <mThread>
#include "../driver/module.h"
#include "../driver/DevAttrMgr.h"
#include <QMutex>


struct EventTime_cp6000 {
    quint8 year;       //  ��ǰ��(2000��2099)
    quint8 month;      //  ��ǰ��(1��12)
    quint8 day;        //  ��ǰ��(1��31)
    quint8 hour;       //  ��ǰʱ(0��23)
    quint8 minute;     //  ��ǰ��(0��59)
    quint8 second;     //  ��ǰ��(0��59)
    quint16 ms;
};

enum EventType_Enum {
    ET_DI_CHANGED = 23,         // 1 ~ 23
    ET_ACTION_EVENT = 59,       // 24 ~ 59
    ET_SELF_CHECK = 255         // 60 ~ 255
};

/*
 *  �¼���¼��Ŀ
 *  @Description:
 *      ������¼���¼�������¼�����ʱ�������+recordNo ��Ӧ¼���ļ���
 */
#define Event_Record_Start 0x5AA5
#define Event_Record_End   0x1234
struct EventRecordItem
{
    quint16 recordStart;        //��ʼ��־  �̶�Ϊ  Event_Record_Start
    EventTime_cp6000 eventTime;
    quint8 eventStyle;          //ȡֵ  EventType_Enum
    union {
        bool diStatus;
        float fActionValue;
    };
    bool bRecord;
    quint32 recordNo;
    quint16 recordEnd;        //������ʶ   �̶�Ϊ  Event_Record_End
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
        UPDATE_INTERVAL_MS = 500,                                       /*  ÿ500ms����һ������         */
        RECORD_INTERVAL_MS = 60000                                      /*  ÿ���Ӽ�¼һ������          */
    };

    enum RecordFlag {
        Record_NewData,         //���µļ�¼
        Record_NewMonth,        //�µ�һ���µ�������Ҫ�л������������������ϸ��µ�����
        Record_Init
    };

    typedef QList<EventRecordItem*> DATABASE;

    static CEventReportRecorder* recorder();

    bool recordInfo(int pos, EventRecordItem* record);

signals:
    /*
     *  @type ȡֵ
     *  >0: ���������ݵ�����
     *  -1���б����
     */
    void dataUpdated(int type);

public slots:
    //�����µ�һ��  
    void systemTimeNewDay();    


private:
    virtual void run();

    bool loadDataBase(DATABASE& db, QString& fileName);
    void destroyDataBase(DATABASE& db);

    //�������¼���¼������
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
    DATABASE m_database[2];             //���������µļ�¼
    DATABASE* m_preMonthDB;             //ָ����һ���µļ�¼
    DATABASE* m_curMonthDB;             //ָ��ǰ�µļ�¼
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