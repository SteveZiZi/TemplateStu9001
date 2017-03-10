#pragma once

#include <QtGlobal>
#include <QString>

class stu_config {
public:
    enum {MODBUS_DEV_NUM = 4};

    static const QString& productName() {return getInstance()->m_productName;}
    static const QString& productModel() {return getInstance()->m_productModel;}
    static const QString& productSerial() {return getInstance()->m_productSerial;}
    static const QString& lan() {return getInstance()->m_lan;}
    static int cpId() {return getInstance()->m_cpId;}
    static bool isCP9000() {return (cpId() == 1);}
    static bool isCP6000() {return (cpId() == 2);}

    static const QString& appVersion() {return getInstance()->m_version.app;}
    static const QString& osVersion() {return getInstance()->m_version.os;}
    static const QString& smSoftwareVersion() {return getInstance()->m_version.smSoftware;}
    static const QString& smHardwareVersion() {return getInstance()->m_version.smHardware;}
    static const QString& cpSoftwareVersion() {return getInstance()->m_version.cpSoftware;}
    static const QString& cpHardwareVersion() {return getInstance()->m_version.cpHardware;}

    static const QString& devComPort(uint item) {
        Q_ASSERT(item < MODBUS_DEV_NUM);
        return getInstance()->m_devInfo[item].port; 
    }
    static int devComBaudRate(uint item) {
        Q_ASSERT(item < MODBUS_DEV_NUM);
        return getInstance()->m_devInfo[item].baudRate;
    }
    static int devComSlaveId(uint item) {
        Q_ASSERT(item < MODBUS_DEV_NUM);
        return getInstance()->m_devInfo[item].slaveId;
    }
    static int devComIsEnable(uint item) {
        Q_ASSERT(item < MODBUS_DEV_NUM);
        return getInstance()->m_devInfo[item].enable;
    }
    
private:
    struct machineVersion {
        QString app;
        QString os;
        QString smSoftware;
        QString smHardware;
        QString cpSoftware;
        QString cpHardware;
    };
    struct deviceCOM {
        QString port;
        int baudRate;
        int slaveId;
        bool enable;
    };
    stu_config();
    ~stu_config();

    void load(const QString& fileName);

    static stu_config* getInstance();

private:
    QString m_productName;
    QString m_productModel;
    QString m_productSerial;

    QString m_lan;
    int m_cpId;                     //综保装置的型号  1->YHCP9000   2->YHCP6000
    machineVersion m_version;
    deviceCOM m_devInfo[MODBUS_DEV_NUM];
};