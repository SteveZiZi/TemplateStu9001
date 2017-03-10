#include "eventReportRecord.h"
#include "../driver/DevAttrMgr.h"

#include <QDateTime>
#include <QDir>

#include <stu_global.h>

using namespace Dev_CP6000;


CEventReportRecorder::CEventReportRecorder()
: MThread()
,m_curMonthDB(NULL)
, m_preMonthDB(NULL)
, m_recordFlag(Record_Init)
, m_recordNo(0)
{
    m_curEventFileName = QDir::currentPath() + "/event/current.dat";
    m_preEventFileName = QDir::currentPath() + "/event/previous.dat";
    m_curEventFileLength = 0;
}

CEventReportRecorder::~CEventReportRecorder()
{

}

CEventReportRecorder* CEventReportRecorder::recorder()
{
    static CEventReportRecorder record;
    return &record;
}


void CEventReportRecorder::run()
{
    RequestFileInfo_t request;
    ResultFileContent_t result;
    int newEventNum = 0;
    quint8* recordBuf = new quint8[6000*2];

#if 1
    do
    {
        m_mutex.lock();
        if (m_recordFlag == Record_NewData) {
            newEventNum = detectNewEvent();
            for (int i = 0; i < newEventNum; i++)
            {
                EventRecordItem* eventItem = new EventRecordItem();
                request.fileNo = 0x00;
                request.recordNo = 0x18*i;
                request.recordLength = 0x18;
                CModbusDevMgr::GetCP6000EventRecord(request, result);
                eventToEventRoport(result, *eventItem);
                if (eventItem->bRecord) {
                    getRecord(eventItem->recordNo, recordBuf);
                    eventItem->recordNo = ++m_recordNo;
                    saveRecordToFile(*eventItem, recordBuf, 480*24+24);
                }
                m_curMonthDB->push_back(eventItem);
            }
            dataUpdated(newEventNum);
        }
        else if (m_recordFlag == Record_NewMonth) {
            saveCurEventToFile();
            QFile::remove(m_preEventFileName);
            QFile::rename(m_curEventFileName, m_preEventFileName);
            m_curEventFileLength = 0;
            DATABASE* database = m_preMonthDB;
            m_preMonthDB = m_curMonthDB;
            m_curMonthDB = database;
            destroyDataBase(*database);
            dataUpdated(-1);
        }
        else if (m_recordFlag == Record_Init) {
            m_curMonth = QDate::currentDate().month();
            EventTag_t eventTag;
            CModbusDevMgr::GetCP6000EventTag(&eventTag);
            m_soeCnt = eventTag.soeCnt;
            m_diChangedCnt = eventTag.diChangedCnt;
            m_preMonthDB = &m_database[0];
            m_preMonthDB->reserve(1000);
            m_curMonthDB = &m_database[1];
            m_curMonthDB->reserve(1000);
            if (!loadDataBase(*m_preMonthDB, m_preEventFileName)) {
                break;
            }
            if (!loadDataBase(*m_curMonthDB, m_curEventFileName)) {
                break;
            }
            QString str = QDir::currentPath()+"/record/";
            QDir recordDir(str);
            QStringList recordFileNameList = recordDir.entryList(QDir::Files, QDir::Name);
            QString maxRecordNo = recordFileNameList[recordFileNameList.size()-1];
            int start = maxRecordNo.indexOf(QRegExp("_\\d."));
            int end = maxRecordNo.indexOf(QRegExp(".dat"));
            maxRecordNo = maxRecordNo.mid(start+1, end-start-1);
            m_recordNo = maxRecordNo.toInt();

            m_recordFlag = Record_NewData;
        }
        else {

        }
        m_mutex.unlock();
    }while(!waitCondition(UPDATE_INTERVAL_MS));
#endif
    m_mutex.unlock();
    delete[] recordBuf;
    qDebug() << "CEventReportRecorder::run exit";
}

void CEventReportRecorder::systemTimeNewDay()
{
    qDebug() << "CEventReportRecorder::systemTimeNewDay";
    if (QDate::currentDate().month() != m_curMonth) {
        QMutexLocker locker(&m_mutex);
        m_curMonth = QDate::currentDate().month();
        m_recordFlag = Record_NewMonth;
    }
}

bool CEventReportRecorder::loadDataBase(DATABASE& db, QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;

    destroyDataBase(db);
//     qint64 len = file.size();
//     while(len > sizeof(EventRecordItem)) {
//         
//     }
    return true;
}

void CEventReportRecorder::destroyDataBase(DATABASE& db)
{
    while(!db.isEmpty()) {
        EventRecordItem* item = db.takeFirst();
        if (item) {
            if (item->bRecord) {
                destoryRecordFile(*item);
            }
            delete item;
        }
    }
}


int CEventReportRecorder::detectNewEvent()
{
    EventTag_t eventTag;
    int nNewEvent = 0;
    if (CModbusDevMgr::GetCP6000EventTag(&eventTag)) {
        if (eventTag.soeCnt > m_soeCnt) {
            nNewEvent += eventTag.soeCnt - m_soeCnt;
            m_soeCnt = eventTag.soeCnt;
        }
        if (eventTag.diChangedCnt > m_diChangedCnt) {
            nNewEvent += eventTag.diChangedCnt - m_diChangedCnt;
            m_diChangedCnt = eventTag.diChangedCnt;
        }
    }

    return nNewEvent;
}

void CEventReportRecorder::eventToEventRoport(const ResultFileContent_t& content, EventRecordItem& eventReport)
{
    eventReport.eventTime.year = content.content[0*2+1];
    eventReport.eventTime.month = content.content[1*2+1];
    eventReport.eventTime.day = content.content[2*2+1];
    eventReport.eventTime.hour = content.content[3*2+1];
    eventReport.eventTime.minute = content.content[4*2+1];
    eventReport.eventTime.second = content.content[5*2+1];
    eventReport.eventTime.ms = content.content[6*2+1]*256 + content.content[7*2+1];
    eventReport.eventStyle = content.content[8*2+1];

    if (eventReport.eventStyle <= ET_DI_CHANGED) {
        eventReport.diStatus = (content.content[9*2+1]) ? true : false;
    }
    else if (eventReport.eventStyle <= ET_ACTION_EVENT) {
        eventReport.fActionValue = (content.content[13*2+1] + content.content[14*2+1]*256) / 100.0f;
    }
    eventReport.recordNo = content.content[20*2+1];
    eventReport.bRecord = (eventReport.recordNo) ? true : false;
}


void CEventReportRecorder::getRecord(quint32 recordNo, quint8* buf)
{
    CModbusDevMgr::requestCP6000RecordFile(recordNo);
    msleep(500);

    RequestFileInfo_t request;
    ResultFileContent_t result;
    quint32 pos = 0;
    request.fileNo = 0x01;
    request.recordNo = 0x00;
    request.recordLength = 0x0C;
    CModbusDevMgr::GetCP6000EventRecord(request, result);
    memcpy(buf+pos, result.content, 24);
    pos += 24;
    /*
     *  一共有480条采样值  一个采样值占12个16位寄存器
     *  一次读取20条采样值
     */
    for(int record = 0; record < 24; record++) {
        request.fileNo = 0x01;
        request.recordNo = 12+record*12;
        request.recordLength = 240; 
        CModbusDevMgr::GetCP6000EventRecord(request, result);
        memcpy(buf+pos, result.content, 480);
        pos += 480;
    }
}

bool CEventReportRecorder::saveRecordToFile(const EventRecordItem& eventItem, const quint8* record, quint32 len)
{
    QString fileName = QString("/record/%1-%2-%3_%4.dat").arg(eventItem.eventTime.year, 4, 10, QChar('0'))
                                                         .arg(eventItem.eventTime.month, 2, 10, QChar('0'))
                                                         .arg(eventItem.eventTime.day, 2, 10, QChar('0'))
                                                         .arg(eventItem.recordNo);

    QFile file(QDir::currentPath()+fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    file.write(reinterpret_cast<const char*>(record), len);
    file.flush();
    file.close();
    return true;
}


void CEventReportRecorder::destoryRecordFile(const EventRecordItem& eventItem)
{
    QString fileName = QString("/record/%1-%2-%3_%4.dat").arg(eventItem.eventTime.year, 4, 10, QChar('0'))
                                                         .arg(eventItem.eventTime.month, 2, 10, QChar('0'))
                                                         .arg(eventItem.eventTime.day, 2, 10, QChar('0'))
                                                         .arg(eventItem.recordNo);

    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }
}


bool CEventReportRecorder::saveCurEventToFile()
{
    int pos = m_curEventFileLength/sizeof(EventRecordItem);
    if (pos >= m_curMonthDB->size()) {
        return false;
    }
    if (m_curEventFileLength-pos*sizeof(EventRecordItem)) {
        return false;
    }
    QFile file(m_curEventFileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
        return false;

    file.seek(m_curEventFileLength);
    for(; pos < m_curMonthDB->size(); pos++) {
        file.write(reinterpret_cast<const char*>((*m_curMonthDB)[pos]), sizeof(EventRecordItem));
    }
    file.flush();
    file.close();

    return true;
}