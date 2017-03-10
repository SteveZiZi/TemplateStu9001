#include "machineCharacterRecord.h"
#include "../driver/DevAttrMgr.h"
#include "debug.h"

using namespace Dev_SM;

///
/// @brief
///    构造函数
///
CMachineCharacterRecorder::CMachineCharacterRecorder(void)
: MThread()
{
}

///
/// @brief
///    析构函数
///
CMachineCharacterRecorder::~CMachineCharacterRecorder(void)
{
}


CMachineCharacterRecorder* CMachineCharacterRecorder::recorder()
{
    static CMachineCharacterRecorder record;

    return &record;
}


void CMachineCharacterRecorder::run()
{
    m_separateBrake.reserve(MAX_RECORD);
    m_closeBrake.reserve(MAX_RECORD);
    m_storeEnergy.reserve(MAX_RECORD);

    machineCharaterUpdateFlag updateFlag;

    do
    {
        if (m_recordFlag == Record_NewData) {
            if (CModbusDevMgr::GetMachineCharaterUpdateFlag(&updateFlag)) {
                if (updateFlag.flag&MC_UPDATE_SEPARATE_BRAKE_DATA) {
                    m_mutex.lock();
                    MC_SeparateBrakeRecordItem* item = nextSeparateBrakeItem();
                    CModbusDevMgr::GetSeparateBrakeInfo(&item->info);
                    CModbusDevMgr::GetSeparateBrakeShiftA(&item->shift[PHASE_A]);
                    CModbusDevMgr::GetSeparateBrakeShiftB(&item->shift[PHASE_B]);
                    CModbusDevMgr::GetSeparateBrakeShiftC(&item->shift[PHASE_C]);
                    CModbusDevMgr::GetSeparateBrakeCoilCur(&item->cur);
                    m_separateBrake.push_back(item);
                    m_mutex.unlock();
                }
                if (updateFlag.flag&MC_UPDATE_CLOSE_BRAKE_DATA) {
                    m_mutex.lock();
                    MC_CloseBrakeRecordItem* item = nextCloseBrakeItem();
                    CModbusDevMgr::GetCloseBrakeInfo(&item->info);
                    CModbusDevMgr::GetCloseBrakeShiftA(&item->shift[PHASE_A]);
                    CModbusDevMgr::GetCloseBrakeShiftB(&item->shift[PHASE_B]);
                    CModbusDevMgr::GetCloseBrakeShiftC(&item->shift[PHASE_C]);
                    CModbusDevMgr::GetCloseBrakeCoilCur(&item->cur);
                    m_closeBrake.push_back(item);
                    m_mutex.unlock();
                }
                if (updateFlag.flag&MC_UPDATE_STORE_ENERGY_DATA) {
                    m_mutex.lock();
                    MC_StoreEnergyRecordItem* item = nextStoreEnergyItem();
                    CModbusDevMgr::GetStoreEnergyInfo(&item->info);
                    CModbusDevMgr::GetStoreEnergyMotorCur(&item->cur);
                    m_storeEnergy.push_back(item);
                    m_mutex.unlock();
                }
                if (updateFlag.flag) {
                    emit dataUpdated(updateFlag.flag);
                }
            }
        }
        else if (m_recordFlag == Record_Init) {

        }
    }while(!waitCondition(1000));
    
    destroySeparateBrakeDataBase(m_separateBrake);
    destroyCloseBrakeDataBase(m_closeBrake);
    destroyStoreEnergyDataBase(m_storeEnergy);
}



void CMachineCharacterRecorder::destroySeparateBrakeDataBase(DATABASE_SEPARATE& db)
{
    while(!db.isEmpty()) {
        MC_SeparateBrakeRecordItem* item = db.takeFirst();
        if (item) {
            delete item;
        }
    }
}

void CMachineCharacterRecorder::destroyCloseBrakeDataBase(DATABASE_CLOSE& db)
{
    while(!db.isEmpty()) {
        MC_CloseBrakeRecordItem* item = db.takeFirst();
        if (item) {
            delete item;
        }
    }
}

void CMachineCharacterRecorder::destroyStoreEnergyDataBase(DATABASE_STORE& db)
{
    while(!db.isEmpty()) {
        MC_StoreEnergyRecordItem* item = db.takeFirst();
        if (item) {
            delete item;
        }
    }
}


