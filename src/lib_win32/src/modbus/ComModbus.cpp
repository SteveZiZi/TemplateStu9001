#include "stdafx.h"
#include "stdint.h"
#include "modbus.h"
#include "modbus-rtu.h"

#include <lib_win32>
#include "mMemLeak.h"

#define MODBUS_DEBUG_EN 0

class CComModbusPrivate 
{
public:
    CComModbusPrivate() : m_bInit(FALSE)
                        , m_dev(NULL)
                        , m_slaveId(-1)
    {
    }

    ~CComModbusPrivate() 
    {
    }

private:
    modbus_t* m_dev;
    int m_slaveId;
    bool m_bInit;

    friend class CComModbus;
};



void* CComModbus::modbusDev()
{
    return m_privateData->m_dev;
}

int CComModbus::slaveId()
{
    return m_privateData->m_slaveId;
}

bool CComModbus::hadInit()
{
    return m_privateData->m_bInit;
}


int CComModbus::getErrorCode()
{
    return errno;
}


CComModbus::CComModbus(const char* comName,
                       Com_BaudRate baud /* = BR_9600 */, 
                       Com_Parity parity /* = NO_PARITY */, 
                       int data_bit /* = 8 */, 
                       int stop_bit /* = 1 */)
: m_privateData(new CComModbusPrivate())
{
    TCHAR szParity[] = {_T('N'), _T('O'), _T('E')};

    TCHAR com[20];  
#ifdef UNICODE  
    MultiByteToWideChar(CP_ACP, 0, comName, -1, com, 20);  
#else  
    strcpy(com, comName);  
#endif 

    TRACE(_T("%s\r\n"), com);

    m_privateData->m_dev = modbus_new_rtu(com, baud, szParity[parity], data_bit, stop_bit);
    ASSERT(m_privateData->m_dev);

    modbus_set_debug(m_privateData->m_dev, MODBUS_DEBUG_EN);

    //modbus_set_debug(m_dev, TRUE);
    modbus_set_error_recovery(m_privateData->m_dev, MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL);
}

CComModbus::~CComModbus()
{
    deinit();
    delete m_privateData;
    m_privateData = NULL;
}

bool CComModbus::init(int slaveId)
{
    UINT32 old_response_to_sec;
    UINT32 old_response_to_usec;
    UINT32 new_response_to_sec;
    UINT32 new_response_to_usec;

    modbus_set_slave(m_privateData->m_dev, slaveId);

    modbus_get_response_timeout(m_privateData->m_dev, &old_response_to_sec, &old_response_to_usec);
    if (modbus_connect(m_privateData->m_dev) == -1) {
        modbus_free(m_privateData->m_dev);
        m_privateData->m_dev = NULL;
        return FALSE;
    }
    modbus_get_response_timeout(m_privateData->m_dev, &new_response_to_sec, &new_response_to_usec);

    m_privateData->m_slaveId = slaveId;
    m_privateData->m_bInit = (old_response_to_sec == new_response_to_sec && old_response_to_usec == new_response_to_usec);

    return m_privateData->m_bInit;
}

void CComModbus::deinit()
{
    if (m_privateData->m_dev) {
        if (m_privateData->m_bInit)
            modbus_close(m_privateData->m_dev);
        modbus_free(m_privateData->m_dev);
        m_privateData->m_dev = NULL;
        m_privateData->m_bInit = FALSE;
    }
}

bool CComModbus::readBits(int addr, int nb, unsigned char* dest)
{
    ASSERT(m_privateData && m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(dest);
    bool rc = true;
    do {
        if (nb <= MODBUS_MAX_READ_BITS) {
            rc = (nb == modbus_read_bits(m_privateData->m_dev, addr, nb, dest));
            nb = 0;
        }
        else {
            if (MODBUS_MAX_READ_BITS == modbus_read_bits(m_privateData->m_dev, addr, MODBUS_MAX_READ_BITS, dest)) {
                addr += MODBUS_MAX_READ_BITS;
                dest += MODBUS_MAX_READ_BITS;
                nb -= MODBUS_MAX_READ_BITS;
            }
            else {
                rc = false;
            }
        }
    }while(nb&&rc);

    return rc;
}

bool CComModbus::readInputBits(int addr, int nb, unsigned char* dest)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(dest);

    bool rc = true;
    do {
        if (nb <= MODBUS_MAX_READ_BITS) {
            rc = (nb == modbus_read_input_bits(m_privateData->m_dev, addr, nb, dest));
            nb = 0;
        }
        else {
            if (MODBUS_MAX_READ_BITS == modbus_read_input_bits(m_privateData->m_dev, addr, MODBUS_MAX_READ_BITS, dest)) {
                addr += MODBUS_MAX_READ_BITS;
                dest += MODBUS_MAX_READ_BITS;
                nb -= MODBUS_MAX_READ_BITS;
            }
            else {
                rc = false;
            }
        }
    }while(nb&&rc);

    return rc;
}

bool CComModbus::readRegisters(int addr, int nb, unsigned short* dest)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(dest);

    bool rc = true;
    do {
        if (nb <= MODBUS_MAX_READ_REGISTERS) {
            rc = (nb == modbus_read_registers(m_privateData->m_dev, addr, nb, dest));
            nb = 0;
        }
        else {
            if (MODBUS_MAX_READ_REGISTERS == modbus_read_registers(m_privateData->m_dev, addr, MODBUS_MAX_READ_REGISTERS, dest)) {
                addr += MODBUS_MAX_READ_REGISTERS;
                dest += MODBUS_MAX_READ_REGISTERS;
                nb -= MODBUS_MAX_READ_REGISTERS;
            }
            else {
                rc = false;
            }
        }
    }while(nb&&rc);

    return rc;
}

bool CComModbus::readInputRegisters(int addr, int nb, unsigned short* dest)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(dest);

    bool rc = true;
    do {
        if (nb <= MODBUS_MAX_READ_REGISTERS) {
            rc = (nb == modbus_read_input_registers(m_privateData->m_dev, addr, nb, dest));
            nb = 0;
        }
        else {
            if (MODBUS_MAX_READ_REGISTERS == modbus_read_input_registers(m_privateData->m_dev, addr, nb, dest)) {
                addr += MODBUS_MAX_READ_REGISTERS;
                dest += MODBUS_MAX_READ_REGISTERS;
                nb -= MODBUS_MAX_READ_REGISTERS;
            }
            else {
                rc = false;
            }
        }
    }while(nb&&rc);

    return rc;
}


bool CComModbus::writeBit(int addr, unsigned char val)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    return 1 == modbus_write_bit(m_privateData->m_dev, addr, val);
}

bool CComModbus::writeRegister(int addr, unsigned short val)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    return 1 == modbus_write_register(m_privateData->m_dev, addr, val);
}

bool CComModbus::writeBits(int addr, int nb, unsigned char* data)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(data);

    bool rc = true;
    do {
        if (nb <= MODBUS_MAX_WRITE_BITS) {
            rc = (nb == modbus_write_bits(m_privateData->m_dev, addr, nb, data));
            nb = 0;
        }
        else {
            if (MODBUS_MAX_WRITE_BITS == modbus_write_bits(m_privateData->m_dev, addr, MODBUS_MAX_WRITE_BITS, data)) {
                addr += MODBUS_MAX_WRITE_BITS;
                data += MODBUS_MAX_WRITE_BITS;
                nb -= MODBUS_MAX_WRITE_BITS;
            }
            else {
                rc = false;
            }
        }
    }while(nb&&rc);

    return rc;
}

bool CComModbus::writeRegisters(int addr, int nb, unsigned short* data)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(data);

    bool rc = true;
    do {
        if (nb <= MODBUS_MAX_WRITE_REGISTERS) {
            rc = (nb == modbus_write_registers(m_privateData->m_dev, addr, nb, data));
            nb = 0;
        }
        else {
            if (MODBUS_MAX_WRITE_REGISTERS == modbus_write_registers(m_privateData->m_dev, addr, MODBUS_MAX_WRITE_REGISTERS, data)) {
                addr += MODBUS_MAX_WRITE_REGISTERS;
                data += MODBUS_MAX_WRITE_REGISTERS;
                nb -= MODBUS_MAX_WRITE_REGISTERS;
            }
            else {
                rc = false;
            }
        }
    }while(nb&&rc);

    return rc;
}



bool CComModbus::sendRawRequest(unsigned char* raw_req, int length)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(raw_req);
    return -1 != modbus_send_raw_request(m_privateData->m_dev, raw_req, length);
}

bool CComModbus::receive_confirmation(unsigned char* rsp)
{
    ASSERT(m_privateData->m_dev && m_privateData->m_bInit);
    ASSERT(rsp);
    return -1 != modbus_receive_confirmation(m_privateData->m_dev, rsp);
}
