#include "DevAttrMgr.h"

#include "debug.h"

#define MODBUS_RTU_MAX_ADU_LENGTH  256

CModbusDev::CModbusDev(const char* comName,
                       Com_BaudRate baud/* = BR_9600*/, 
                       Com_Parity parity/* = NO_PARITY*/, 
                       int data_bit/* = 8*/, 
                       int stop_bit/* = 1*/)
: CComModbus(comName, baud, parity, data_bit, stop_bit)
, m_enable(false)
{

}

CModbusDev::~CModbusDev()
{

}

bool CModbusDev::Init(int slaveId)
{
    m_enable = CComModbus::init(slaveId);
    return m_enable;
}

void CModbusDev::Deinit(void)
{
    CComModbus::deinit();
}

bool CModbusDev::GetAttrs(AttrInfo_t& attr, void* dests)
{
    QMutexLocker locker(&mutex);

    switch(attr.type)
    {
    case AT_COILS:
        return readBits(attr.addr, attr.nb, (quint8 *)dests);
        break;
    case AT_INPUT_COILS:
        return readInputBits(attr.addr, attr.nb, (quint8 *)dests);
        break;
    case AT_REGISTERS:
        return readRegisters(attr.addr, attr.nb, (quint16 *)dests);
        break;
    case AT_INPUT_REGISTERS:
        return readInputRegisters(attr.addr, attr.nb, (quint16 *)dests);
        break;
    default:
        Q_ASSERT(false);
        break;
    }

    return FALSE;
}

bool CModbusDev::SetAttrs(AttrInfo_t& attr, void* dests)
{
    QMutexLocker locker(&mutex);

    switch(attr.type)
    {
    case AT_COILS:
        if (attr.nb == 1) 
            return writeBit(attr.addr, *((quint8 *)dests));
        else 
            return writeBits(attr.addr, attr.nb, (quint8 *)dests);
        break;
    case AT_REGISTERS:
        if (attr.nb == 1)
            return writeRegister(attr.addr, *((quint16 *)dests));
        else 
            return writeRegisters(attr.addr, attr.nb, (quint16 *)dests);
        break;
    default:
        Q_ASSERT(false);
        break;
    }

    return FALSE;
}


bool CModbusDev::readRecordFile(const RequestFileInfo_t& request, ResultFileContent_t& content)
{
    quint8 req[MODBUS_RTU_MAX_ADU_LENGTH];
    req[0] = slaveId();
    req[1] = 0x14;      //Modbus FC
    req[2] = 1+sizeof(RequestFileInfo_t);

    int pos = 3;
    req[pos++] = 6;
    req[pos++] = request.fileNo >> 8;
    req[pos++] = request.fileNo & 0x00FF;
    req[pos++] = request.recordNo >> 8;
    req[pos++] = request.recordNo & 0x00FF;
    req[pos++] = request.recordLength >> 8;
    req[pos++] = request.recordLength & 0x00FF;

    if (sendRawRequest(req, pos) && receive_confirmation(req)) {
        if (req[0] != slaveId() || req[1] != 0x14) {
            return false;
        }
        pos = 3;

        content.length = req[pos++];
        if (req[pos] != 6) {
            return false;
        }
        if (pos+content.length > MODBUS_RTU_MAX_ADU_LENGTH) {
            return false;
        }
        //跳过参考类型
        memcpy(content.content, &req[pos+1], content.length-1);
    }
    else {
        return false;
    }

    return true;
}



CModbusDevMgr::CModbusDevMgr()
{
    memset(m_arrDev, 0, sizeof(m_arrDev));
}

CModbusDevMgr::~CModbusDevMgr()
{
    for(int i = 0; i < MAX_DEV_NUM; i ++)
    {
        if (m_arrDev[i]) 
        {
            m_arrDev[i]->Deinit();
            delete m_arrDev[i];
            m_arrDev[i] = NULL;
        }
    }
}

CModbusDevMgr* CModbusDevMgr::getInstance()
{
    static CModbusDevMgr s_mgr;

    return &s_mgr;
}


void CModbusDevMgr::init(const ModbusConfig* cfg, int num)
{
    int devNum = qMin<int>(num, MAX_DEV_NUM);
    for(int i = 0; i < devNum; i++) {
        getInstance()->m_arrDev[i] = new CModbusDev(cfg[i].port, (CComModbus::Com_BaudRate)(cfg[i].baudRate));
        if (cfg[i].enable)
            getInstance()->m_arrDev[i]->Init(cfg[i].slaveId);
    }
}



