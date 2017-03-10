#include "stu_config.h"

#include <QFile>
#include <QDomDocument>
#include <QDir>
#include <debug.h>

stu_config::stu_config()
{
    QString path = QDir::currentPath();
    path += "/runtime_config/info.xml";
    load(path);
}

stu_config::~stu_config()
{

}

stu_config* stu_config::getInstance()
{
    static stu_config config;
    return &config;
}


void stu_config::load(const QString& fileName)
{
    if(fileName.isEmpty())
        return;  

    QFile file(fileName);  
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QString string(QString("stu_config::load open %1 fail.").arg(fileName));
        qDebug() << string;
        return;  
    }  

    QDomDocument document;  
    QString error;  
    int row = 0, column = 0;  
    if(!document.setContent(&file, false, &error, &row, &column)) {  
        qDebug() << QString("stu_config::load parse file failed at line row and column %1,%2").arg(row).arg(column);
        return;  
    }  

    if(document.isNull()) {  
        qDebug() << "stu_config::load document is null!";
        return;  
    }  

    QDomElement root = document.documentElement();  
    
    m_productName = root.firstChildElement(QString("productName")).attribute(QString("val"));
    m_productModel = root.firstChildElement(QString("productModel")).attribute(QString("val"));
    m_productSerial = root.firstChildElement(QString("productSerial")).attribute(QString("val"));
    m_lan = root.firstChildElement(QString("lan")).attribute(QString("val"));
    m_cpId = root.firstChildElement(QString("CP_Machine")).attribute(QString("id")).toInt();


    QDomElement node = root.firstChildElement(QString("version"));
    m_version.app = node.firstChildElement(QString("APP")).attribute(QString("val"));
    m_version.os = node.firstChildElement(QString("OS")).attribute(QString("val"));
    {
        QDomElement child = node.firstChildElement(QString("device"));
        m_version.smSoftware = child.firstChildElement(QString("software")).attribute(QString("val"));
        m_version.smHardware = child.firstChildElement(QString("hardware")).attribute(QString("val"));
        child = child.nextSiblingElement();
        if (m_cpId == 1) {
            m_version.cpSoftware = child.firstChildElement(QString("software")).attribute(QString("val"));
            m_version.cpHardware = child.firstChildElement(QString("hardware")).attribute(QString("val"));
        }
        else {
            child = child.nextSiblingElement();
            m_version.cpSoftware = child.firstChildElement(QString("software")).attribute(QString("val"));
            m_version.cpHardware = child.firstChildElement(QString("hardware")).attribute(QString("val"));
        }
    }

    node = root.firstChildElement(QString("COM"));
    {
        QDomElement child = node.firstChildElement(QString("device"));
        m_devInfo[0].port = child.firstChildElement(QString("port")).attribute(QString("val"));
        m_devInfo[0].baudRate = child.firstChildElement(QString("baud_rate")).attribute(QString("val")).toInt();
        m_devInfo[0].slaveId = child.firstChildElement(QString("slaveId")).attribute(QString("val")).toInt();
        m_devInfo[0].enable = child.firstChildElement(QString("enable")).attribute(QString("val")).toInt();

        for(int i = 1; i < MODBUS_DEV_NUM; i++) {
            child = child.nextSiblingElement(QString("device"));
            if (child.isNull()) {
                qDebug() << "stu_config::load \"device\" fail";
                break;
            }
            m_devInfo[i].port = child.firstChildElement(QString("port")).attribute(QString("val"));
            m_devInfo[i].baudRate = child.firstChildElement(QString("baud_rate")).attribute(QString("val")).toInt();
            m_devInfo[i].slaveId = child.firstChildElement(QString("slaveId")).attribute(QString("val")).toInt();
            m_devInfo[i].enable = child.firstChildElement(QString("enable")).attribute(QString("val")).toInt();
        }
    }
}