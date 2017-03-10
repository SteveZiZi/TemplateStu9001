#include "harmonicRecord.h"
#include "../driver/DevAttrMgr.h"
#include "debug.h"

using namespace Dev_SM;

///
/// @brief
///    ���캯��
///
CHarmonicRecorder::CHarmonicRecorder(void)
: MThread()
{
}

///
/// @brief
///    ��������
///
CHarmonicRecorder::~CHarmonicRecorder(void)
{
}


CHarmonicRecorder* CHarmonicRecorder::recorder()
{
    static CHarmonicRecorder record;

    return &record;
}


void CHarmonicRecorder::run()
{
    m_database.reserve(100);

    machineCharaterUpdateFlag updateFlag;

    do
    {
        if (m_recordFlag == Record_NewData) {

        }
        else if (m_recordFlag == Record_Init) {

        }
    }while(!waitCondition(1000));
    
    destroyDataBase(m_database);
}



void CHarmonicRecorder::destroyDataBase(DATABASE& db)
{
    while(!db.isEmpty()) {
        HarmonicRecordItem* item = db.takeFirst();
        if (item) {
            delete item;
        }
    }
}