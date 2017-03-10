#include "measureTempRecord.h"
#include "../driver/DevAttrMgr.h"

#include <QDateTime>

#include <stu_global.h>

CMeasureTempRecorder::CMeasureTempRecorder()
: MThread()
, m_recordFlag(Record_Init)
{

}

CMeasureTempRecorder::~CMeasureTempRecorder()
{

}

CMeasureTempRecorder* CMeasureTempRecorder::recorder()
{
    static CMeasureTempRecorder record;
    return &record;
}


void CMeasureTempRecorder::run()
{
    //保留足够的空间保存数据
    m_database.reserve(24*3600/RECORD_INTERVAL+10);

    //第一次添加一个数据
    TempReordInfo tempInfo;
    quint32 preRecordTime;      //记录上一条记录的时间

    do
    {
        acquireNewTemp(&tempInfo);
        m_mutex.lock();
        if (m_recordFlag == Update_Time_And_Data) {
            if (tempInfo.time < preRecordTime) {
                tempInfo.time = preRecordTime;
            }
            if (tempInfo.time - preRecordTime < RECORD_INTERVAL) {
                m_database.replace(m_database.size()-1, tempInfo);
                emit dataUpdated(1);
            }
            else {
                m_database.append(tempInfo);
                preRecordTime = tempInfo.time;
                emit dataUpdated(0);
            }
        }
        else if (m_recordFlag == Update_Data_Only) {
            tempInfo.time = preRecordTime;  // 替换时间
            m_database.replace(m_database.size()-1, tempInfo);  //替换旧的数据
            emit dataUpdated(1);
        }
        else if (m_recordFlag == Clear_All_Record) {
            m_database.clear();
            m_recordFlag = Record_Init;
            emit dataUpdated(-1);
        }
        else {  //初始化
            m_database.append(tempInfo);
            preRecordTime = tempInfo.time;
            m_recordFlag = Update_Time_And_Data;
            emit dataUpdated(0);
        }
        m_mutex.unlock();
    }while(!waitCondition(UPDATE_INTERVAL));
}

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
void CMeasureTempRecorder::systemTimeException(int event)
{
    qDebug() << "CMeasureTempRecorder::systemTimeException event=" << event; 
    QMutexLocker locker(&m_mutex);

    if (event == DATE_TIME_EXCEPTION) {
        m_recordFlag = Update_Data_Only;
    }
    else if (event == DATE_TIME_MODIFY) {
        //时间被修改后 会有systemTimeNewDay信号通知
        //m_recordFlag = Clear_All_Record;
    }
    else if (event == DATE_TIME_EXCEPT_RESTORE) {
        m_recordFlag = Update_Time_And_Data;
    }
    else {

    }
}

void CMeasureTempRecorder::systemTimeNewDay()
{
    qDebug() << "CMeasureTempRecorder::systemTimeNewDay";
    QMutexLocker locker(&m_mutex);
    m_recordFlag = Clear_All_Record;
}

void CMeasureTempRecorder::acquireNewTemp(TempReordInfo* tempInfo)
{
    Q_ASSERT(tempInfo);
#if 1
    CModbusDevMgr::GetContactTemp(&tempInfo->temp.contact);
    CModbusDevMgr::GetBusbarTemp(&tempInfo->temp.busbar);
    QDateTime dateTime(QDateTime::currentDateTime());
    tempInfo->time = QDateTime(dateTime.date(), QTime(0, 0, 0)).secsTo(dateTime);
#else
#define PI 3.1415926535
    static int ncnt = 0;

    tempInfo->temp.contact.temp[0][0] = 80 + 10*qCos(PI*ncnt/80);
    tempInfo->temp.contact.temp[1][0] = 70 + 10*qCos(PI*ncnt/80);
    tempInfo->temp.contact.temp[2][0] = 60 + 10*qCos(PI*ncnt/80);

    tempInfo->temp.contact.temp[0][1] = 50 + 10*qCos(PI*ncnt/80);
    tempInfo->temp.contact.temp[1][1] = 40 + 10*qCos(PI*ncnt/80);
    tempInfo->temp.contact.temp[2][1] = 30 + 10*qCos(PI*ncnt/80);
    tempInfo->time = ncnt*120;
    ncnt++;
#endif
}

bool CMeasureTempRecorder::recordInfo(int pos, TempReordInfo* record)
{
    Q_ASSERT(record);
    QMutexLocker locker(&m_mutex);
    if (pos >= m_database.count()) {
        return false;
    }       

    memcpy(record, &m_database.at(pos++), sizeof(TempReordInfo));
    return true;
}