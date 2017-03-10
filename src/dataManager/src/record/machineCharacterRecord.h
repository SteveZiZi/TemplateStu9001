
#pragma once

#include <mThread>
#include "../driver/module.h"
#include <QMutex>

using namespace Dev_SM;


struct MC_SeparateBrakeRecordItem {
    separateBrakeInfo_t info;
    shiftInfo_t shift[MAX_PHASE_NUM];
    coilCurrent_t cur;
};

struct MC_CloseBrakeRecordItem {
    closeBrakeInfo_t info;
    shiftInfo_t shift[MAX_PHASE_NUM];
    coilCurrent_t cur;
};

struct MC_StoreEnergyRecordItem {
    storeEnergyInfo_t info;
    motorCurrent_t cur;
};

enum MC_DATA_TYPE {
    MC_SEPARATE_BRAKE,
    MC_CLOSE_BRAKE,
    MC_STORE_ENERGY
};
class CMachineCharacterRecorder : public MThread
{
    Q_OBJECT
protected:
    CMachineCharacterRecorder(void);
    virtual ~CMachineCharacterRecorder(void);

public:
    enum RecordFlag {
        Record_NewData,
        Record_Init
    };
    enum {MAX_RECORD = 3};

    typedef QList<MC_SeparateBrakeRecordItem*> DATABASE_SEPARATE;
    typedef QList<MC_CloseBrakeRecordItem*> DATABASE_CLOSE;
    typedef QList<MC_StoreEnergyRecordItem*> DATABASE_STORE;
    static CMachineCharacterRecorder* recorder();

signals:
    /*
     *  @dataType:   取值 MC_DataUpdateFlag 或的关系
     */
    void dataUpdated(int dataType);

public:
    bool separateBrakeRecord(int pos, MC_SeparateBrakeRecordItem* record);
    bool closeBrakeRecord(int pos, MC_CloseBrakeRecordItem* record);
    bool storeEnergyRecord(int pos, MC_StoreEnergyRecordItem* record);

    bool lastestSeparateBrakeRecord(MC_SeparateBrakeRecordItem* record) {return separateBrakeRecord(0, record);}
    bool lastestCloseBrakeRecord(MC_CloseBrakeRecordItem* record) {return closeBrakeRecord(0, record);}
    bool lastestStoreEnergyRecord(MC_StoreEnergyRecordItem* record) {return storeEnergyRecord(0, record);}

    int separateBrakeRecordCount() {return m_separateBrake.size();}
    int closeBrakeRecordCount() {return m_closeBrake.size();}
    int storeEnergyRecordCount() {return m_storeEnergy.size();}

private:
    virtual void run();

    MC_SeparateBrakeRecordItem* nextSeparateBrakeItem();
    MC_CloseBrakeRecordItem* nextCloseBrakeItem();
    MC_StoreEnergyRecordItem* nextStoreEnergyItem();

    void destroySeparateBrakeDataBase(DATABASE_SEPARATE& db);
    void destroyCloseBrakeDataBase(DATABASE_CLOSE& db);
    void destroyStoreEnergyDataBase(DATABASE_STORE& db);

private:
    DATABASE_SEPARATE   m_separateBrake;
    DATABASE_CLOSE      m_closeBrake;
    DATABASE_STORE      m_storeEnergy;
    QMutex              m_mutex;
    RecordFlag          m_recordFlag;
};

inline MC_SeparateBrakeRecordItem* CMachineCharacterRecorder::nextSeparateBrakeItem()
{
    MC_SeparateBrakeRecordItem* item = NULL;
    if (m_separateBrake.size() == MAX_RECORD) {
        item = m_separateBrake.takeFirst();
    }
    else {
        item = new MC_SeparateBrakeRecordItem;
    }
    return item;
}

inline MC_CloseBrakeRecordItem* CMachineCharacterRecorder::nextCloseBrakeItem()
{
    MC_CloseBrakeRecordItem* item = NULL;
    if (m_closeBrake.size() == MAX_RECORD) {
        item = m_closeBrake.takeFirst();
    }
    else {
        item = new MC_CloseBrakeRecordItem;
    }
    return item;
}

inline MC_StoreEnergyRecordItem* CMachineCharacterRecorder::nextStoreEnergyItem()
{
    MC_StoreEnergyRecordItem* item = NULL;
    if (m_storeEnergy.size() == MAX_RECORD) {
        item = m_storeEnergy.takeFirst();
    }
    else {
        item = new MC_StoreEnergyRecordItem;
    }
    return item;
}


inline bool CMachineCharacterRecorder::separateBrakeRecord(int pos, MC_SeparateBrakeRecordItem* record)
{
    QMutexLocker lock(&m_mutex);
    if (pos < separateBrakeRecordCount() && record) {
        memcpy(record, m_separateBrake[pos], sizeof(MC_SeparateBrakeRecordItem));
        return true;
    }

    return false;
}

inline bool CMachineCharacterRecorder::closeBrakeRecord(int pos, MC_CloseBrakeRecordItem* record)
{
    QMutexLocker lock(&m_mutex);
    if (pos < closeBrakeRecordCount() && record) {
        memcpy(record, m_closeBrake[pos], sizeof(MC_CloseBrakeRecordItem));
        return true;
    }

    return false;
}

inline bool CMachineCharacterRecorder::storeEnergyRecord(int pos, MC_StoreEnergyRecordItem* record)
{
    QMutexLocker lock(&m_mutex);
    if (pos < storeEnergyRecordCount() && record) {
        memcpy(record, m_storeEnergy[pos], sizeof(MC_StoreEnergyRecordItem));
        return true;
    }

    return false;
}
