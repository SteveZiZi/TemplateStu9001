// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIB_WIN32_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIB_WIN32_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIB_WIN32_EXPORTS
#define LIB_WIN32_API __declspec(dllexport)
#else
#define LIB_WIN32_API __declspec(dllimport)
#endif


typedef struct _fnlib_system_time_
{
    unsigned short year;
    unsigned short month;
    unsigned short dayOfWeek;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned short milliseconds;
} fnlib_SYSTEMTIME;
LIB_WIN32_API bool fnlib_setSystemTime(const fnlib_SYSTEMTIME &tm);
LIB_WIN32_API bool fnlib_setLocalTime(const fnlib_SYSTEMTIME &tm);


class CComModbusPrivate;
class LIB_WIN32_API CComModbus
{
public:
    enum Com_BaudRate {
        BR_110      =   110,
        BR_300      =   300,
        BR_600      =   600,
        BR_1200     =   1200,
        BR_2400     =   2400,
        BR_4800     =   4800,
        BR_9600     =   9600,
        BR_14400    =   14400,
        BR_19200    =   19200,
        BR_38400    =   38400,
        BR_56000    =   56000,
        BR_57600    =   57600,
        BR_115200   =   115200
    };

    enum Com_Parity {
        NO_PARITY   =   0,
        ODD_PARITY  =   1,
        EVEN_PARITY =   2
    };

    CComModbus(const char* comName,
               Com_BaudRate baud = BR_9600, 
               Com_Parity parity = NO_PARITY, 
               int data_bit = 8, 
               int stop_bit = 1);

    virtual ~CComModbus();

    /*
     *  ��ʼ��
     *  @Param��
     *      slaveId��modbus�豸�Ĵӻ���
     */
    bool init(int slaveId);
    void deinit(void);

    /**
     *  ȡ��һ���߼���Ȧ�ĵ�ǰ״̬  ON/OFF
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      nb          ��ȡ�ĸ���
     *  \param[out]
     *      dest        �����ȡֵ��ָ�룬��Ч�ڴ������õ���nbָ���Ĵ�С
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x01
     */
    bool readBits(int addr, int nb, unsigned char* dest);  
    /**
     *  ȡ��һ�鿪������ĵ�ǰ״̬  ON/OFF
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      nb          ��ȡ�ĸ���
     *  \param[out]
     *      dest        �����ȡֵ��ָ�룬��Ч�ڴ������õ���nbָ���Ĵ�С
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x02
     */
    bool readInputBits(int addr, int nb, unsigned char* dest);  
    /**
     *  ��һ���������ּĴ�����ȡ�õ�ǰ�Ķ�����ֵ
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      nb          ��ȡ�ĸ���
     *  \param[out]
     *      dest        �����ȡֵ��ָ�룬��Ч�ڴ������õ���nbָ���Ĵ�С
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x03
     */
    bool readRegisters(int addr, int nb, unsigned short* dest);  
    /**
     *  ��һ����������Ĵ�����ȡ�õ�ǰ�Ķ�����ֵ
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      nb          ��ȡ�ĸ���
     *  \param[out]
     *      dest        �����ȡֵ��ָ�룬 һ����ַ16λ��
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x04
     */
    bool readInputRegisters(int addr, int nb, unsigned short* dest); 

    /**
     *  ǿ��һ���߼���Ȧ��ͨ��״̬
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      val         ���õ�״ֵ̬  ON/OFF
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x05
     */
    bool writeBit(int addr, unsigned char val);  
    /**
     *  д��������������һ�����ּĴ���
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      val         ���üĴ����Ķ�����ֵ   һ����ַ16λ��
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x07
     */
    bool writeRegister(int addr, unsigned short val);  
    /**
     *  ǿ��һ�������߼���Ȧ��ͨ��
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      nb          ������Ȧ�ĸ���
     *      data        ������Ȧ��״ֵ̬  ON/OFF
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x0F
     */
    bool writeBits(int addr, int nb, unsigned char* data); 
    /**
     *  �Ѿ���Ķ�����ֵװ��һ�������ı��ּĴ���
     *
     *  \param[in]
     *      addr        ��ʼ��ַ
     *      nb          ���ñ��ּĴ����ĸ���
     *      data        ���ñ��ּĴ����Ķ�����ֵ һ����ַ16λ��
     *  \note
     *      ��ӦmodbusЭ��Ĺ�����0x10
     */
    bool writeRegisters(int addr, int nb, unsigned short* data); 


    bool sendRawRequest(unsigned char* raw_req, int length);
    bool receive_confirmation(unsigned char* rsp);

    int getErrorCode();


    void* modbusDev();
    int slaveId();
    bool hadInit();


protected:
    CComModbusPrivate* m_privateData;
};