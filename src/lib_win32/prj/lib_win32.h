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
     *  初始化
     *  @Param：
     *      slaveId：modbus设备的从机号
     */
    bool init(int slaveId);
    void deinit(void);

    /**
     *  取得一组逻辑线圈的当前状态  ON/OFF
     *
     *  \param[in]
     *      addr        起始地址
     *      nb          读取的个数
     *  \param[out]
     *      dest        保存读取值的指针，有效内存数不得低于nb指定的大小
     *  \note
     *      对应modbus协议的功能码0x01
     */
    bool readBits(int addr, int nb, unsigned char* dest);  
    /**
     *  取得一组开关输入的当前状态  ON/OFF
     *
     *  \param[in]
     *      addr        起始地址
     *      nb          读取的个数
     *  \param[out]
     *      dest        保存读取值的指针，有效内存数不得低于nb指定的大小
     *  \note
     *      对应modbus协议的功能码0x02
     */
    bool readInputBits(int addr, int nb, unsigned char* dest);  
    /**
     *  在一个或多个保持寄存器中取得当前的二进制值
     *
     *  \param[in]
     *      addr        起始地址
     *      nb          读取的个数
     *  \param[out]
     *      dest        保存读取值的指针，有效内存数不得低于nb指定的大小
     *  \note
     *      对应modbus协议的功能码0x03
     */
    bool readRegisters(int addr, int nb, unsigned short* dest);  
    /**
     *  在一个或多个输入寄存器中取得当前的二进制值
     *
     *  \param[in]
     *      addr        起始地址
     *      nb          读取的个数
     *  \param[out]
     *      dest        保存读取值的指针， 一个地址16位宽
     *  \note
     *      对应modbus协议的功能码0x04
     */
    bool readInputRegisters(int addr, int nb, unsigned short* dest); 

    /**
     *  强置一个逻辑线圈的通断状态
     *
     *  \param[in]
     *      addr        起始地址
     *      val         配置的状态值  ON/OFF
     *  \note
     *      对应modbus协议的功能码0x05
     */
    bool writeBit(int addr, unsigned char val);  
    /**
     *  写入具体二进制数到一个保持寄存器
     *
     *  \param[in]
     *      addr        起始地址
     *      val         配置寄存器的二进制值   一个地址16位宽
     *  \note
     *      对应modbus协议的功能码0x07
     */
    bool writeRegister(int addr, unsigned short val);  
    /**
     *  强置一串连续逻辑线圈的通断
     *
     *  \param[in]
     *      addr        起始地址
     *      nb          配置线圈的个数
     *      data        配置线圈的状态值  ON/OFF
     *  \note
     *      对应modbus协议的功能码0x0F
     */
    bool writeBits(int addr, int nb, unsigned char* data); 
    /**
     *  把具体的二进制值装入一串连续的保持寄存器
     *
     *  \param[in]
     *      addr        起始地址
     *      nb          配置保持寄存器的个数
     *      data        配置保持寄存器的二进制值 一个地址16位宽
     *  \note
     *      对应modbus协议的功能码0x10
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