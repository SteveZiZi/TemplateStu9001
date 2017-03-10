#include "machineCharacteristicParam.h"
#include "../driver/DevAttrMgr.h"

#include <QFile>
#include <QDir>
#include <QDomDocument>

#include "debug.h"

#define SETTINGS_FILE_NAME  "/runtime_config/machineCharacterSettings.xml"


CMachineCharacterParam::CMachineCharacterParam(QObject* parent)
: QObject(parent)
, m_bInit(false)
{
}

CMachineCharacterParam::~CMachineCharacterParam(void)
{
}


CMachineCharacterParam* CMachineCharacterParam::getInstance()
{
    static CMachineCharacterParam s_param;
    if (!s_param.m_bInit) {
        QString path = QDir::currentPath();
        path += SETTINGS_FILE_NAME;
        s_param.load(path);
    }
    return &s_param;
}


void CMachineCharacterParam::machineCharacterSettings(MachineCharacterSettings* settings)
{
    Q_ASSERT(settings);
    memcpy(settings, &m_settings, sizeof(MachineCharacterSettings));
}

void CMachineCharacterParam::setMachineCharacterSettings(const MachineCharacterSettings& settings)
{
    memcpy(&m_settings, &settings, sizeof(MachineCharacterSettings));
    QString path = QDir::currentPath();
    path += SETTINGS_FILE_NAME;
    save(path);
    emit settingsChanged(settings);
}


void CMachineCharacterParam::load(const QString& fileName)
{
    QDomDocument document;  
    QString error;  
    int row = 0, column = 0;  
    QDomElement root;
    QFile file(fileName);

    if(fileName.isEmpty())
        goto defaultSettings;

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QString string(QString("CMachineCharacterParam::load open %1 fail.").arg(fileName));
        qDebug() << string;
        goto defaultSettings;
    }  

    if(!document.setContent(&file, false, &error, &row, &column)) {  
        qDebug() << QString("CMachineCharacterParam::load parse file failed at line row and column %1,%2").arg(row).arg(column);
        goto defaultSettings;
    }  

    if(document.isNull()) {  
        qDebug() << "CMachineCharacterParam::load document is null!";
        goto defaultSettings;
    }  

    root = document.documentElement();  
    m_settings.contactDistance.fCalibrationVal = root.firstChildElement(QString("contactDistance")).attribute(QString("calibrat")).toFloat();
    m_settings.contactDistance.fOffsetRange = root.firstChildElement(QString("contactDistance")).attribute(QString("offset")).toFloat();

    m_settings.separateBrakeRoute.fCalibrationVal = root.firstChildElement(QString("separateBrakeRoute")).attribute(QString("calibrat")).toFloat();
    m_settings.separateBrakeRoute.fOffsetRange = root.firstChildElement(QString("separateBrakeRoute")).attribute(QString("offset")).toFloat();

    m_settings.separateBrakeTime.fCalibrationVal = root.firstChildElement(QString("separateBrakeTime")).attribute(QString("calibrat")).toFloat();
    m_settings.separateBrakeTime.fOffsetRange = root.firstChildElement(QString("separateBrakeTime")).attribute(QString("offset")).toFloat();

    m_settings.separateBrakeSpeedAvg.fCalibrationVal = root.firstChildElement(QString("separateBrakeSpeedAvg")).attribute(QString("calibrat")).toFloat();
    m_settings.separateBrakeSpeedAvg.fOffsetRange = root.firstChildElement(QString("separateBrakeSpeedAvg")).attribute(QString("offset")).toFloat();

    m_settings.separateBrakeBounceAmp.fCalibrationVal = root.firstChildElement(QString("separateBrakeBounceAmp")).attribute(QString("calibrat")).toFloat();
    m_settings.separateBrakeBounceAmp.fOffsetRange = root.firstChildElement(QString("separateBrakeBounceAmp")).attribute(QString("offset")).toFloat();

    m_settings.separateBrakeAsyncCycleTime.fCalibrationVal = root.firstChildElement(QString("separateBrakeAsyncCycleTime")).attribute(QString("calibrat")).toFloat();
    m_settings.separateBrakeAsyncCycleTime.fOffsetRange = root.firstChildElement(QString("separateBrakeAsyncCycleTime")).attribute(QString("offset")).toFloat();

    
    m_settings.contactOverRoute.fCalibrationVal = root.firstChildElement(QString("contactOverRoute")).attribute(QString("calibrat")).toFloat();
    m_settings.contactOverRoute.fOffsetRange = root.firstChildElement(QString("contactOverRoute")).attribute(QString("offset")).toFloat();

    m_settings.closeBrakeRoute.fCalibrationVal = root.firstChildElement(QString("closeBrakeRoute")).attribute(QString("calibrat")).toFloat();
    m_settings.closeBrakeRoute.fOffsetRange = root.firstChildElement(QString("closeBrakeRoute")).attribute(QString("offset")).toFloat();

    m_settings.closeBrakeTime.fCalibrationVal = root.firstChildElement(QString("closeBrakeTime")).attribute(QString("calibrat")).toFloat();
    m_settings.closeBrakeTime.fOffsetRange = root.firstChildElement(QString("closeBrakeTime")).attribute(QString("offset")).toFloat();

    m_settings.closeBrakeSpeedAvg.fCalibrationVal = root.firstChildElement(QString("closeBrakeSpeedAvg")).attribute(QString("calibrat")).toFloat();
    m_settings.closeBrakeSpeedAvg.fOffsetRange = root.firstChildElement(QString("closeBrakeSpeedAvg")).attribute(QString("offset")).toFloat();

    m_settings.closeBrakeBounceTime.fCalibrationVal = root.firstChildElement(QString("closeBrakeBounceTime")).attribute(QString("calibrat")).toFloat();
    m_settings.closeBrakeBounceTime.fOffsetRange = root.firstChildElement(QString("closeBrakeBounceTime")).attribute(QString("offset")).toFloat();

    m_settings.closeBrakeAsyncCycleTime.fCalibrationVal = root.firstChildElement(QString("closeBrakeAsyncCycleTime")).attribute(QString("calibrat")).toFloat();
    m_settings.closeBrakeAsyncCycleTime.fOffsetRange = root.firstChildElement(QString("closeBrakeAsyncCycleTime")).attribute(QString("offset")).toFloat();


    m_settings.storeTime.fCalibrationVal = root.firstChildElement(QString("storeTime")).attribute(QString("calibrat")).toFloat();
    m_settings.storeTime.fOffsetRange = root.firstChildElement(QString("storeTime")).attribute(QString("offset")).toFloat();

    m_bInit = true;

defaultSettings:
    if (!m_bInit) {
        m_settings.contactDistance.fCalibrationVal = 25.0;
        m_settings.contactDistance.fOffsetRange = 5.0;
        m_settings.separateBrakeTime.fCalibrationVal = 38.0;
        m_settings.separateBrakeTime.fOffsetRange = 4.0;
        m_settings.separateBrakeBounceAmp.fCalibrationVal = 0.035;
        m_settings.separateBrakeBounceAmp.fOffsetRange = 0.015;
        m_settings.separateBrakeSpeedAvg.fCalibrationVal = 1.300;
        m_settings.separateBrakeSpeedAvg.fOffsetRange = 0.100;
        m_settings.separatingBrakingSpeed.fCalibrationVal = 1.500;
        m_settings.separatingBrakingSpeed.fOffsetRange = 0.500;
        m_settings.separateBrakeAsyncCycleTime.fCalibrationVal = 1.100;
        m_settings.separateBrakeAsyncCycleTime.fOffsetRange = 0.100;

        m_settings.contactOverRoute.fCalibrationVal = 25.00;
        m_settings.contactOverRoute.fOffsetRange = 5.0;
        m_settings.closeBrakeTime.fCalibrationVal = 43.0;
        m_settings.closeBrakeTime.fOffsetRange = 1.0;
        m_settings.closeBrakeBounceTime.fCalibrationVal = 0.2;
        m_settings.closeBrakeBounceTime.fOffsetRange = 0.1;
        m_settings.closeBrakeSpeedAvg.fCalibrationVal = 0.565;
        m_settings.closeBrakeSpeedAvg.fOffsetRange = 0.015;
        m_settings.closingBrakeSpeed.fCalibrationVal = 1.5;
        m_settings.closingBrakeSpeed.fOffsetRange = 0.5;
        m_settings.closeBrakeAsyncCycleTime.fCalibrationVal = 2.5;
        m_settings.closeBrakeAsyncCycleTime.fOffsetRange = 1.5;

        m_settings.storeTime.fCalibrationVal = 7.5;
        m_settings.storeTime.fOffsetRange = 7.5;

        save(fileName);
    }
}

void CMachineCharacterParam::save(const QString& fileName)
{
    if(fileName.isEmpty())
        return;  

    QDomDocument doc;  
    QDomElement root = doc.createElement("settings");
    doc.appendChild(root);

    QDomElement childEle = doc.createElement("contactDistance");
    childEle.setAttribute(QString("calibrat"), m_settings.contactDistance.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.contactDistance.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("separateBrakeRoute");
    childEle.setAttribute(QString("calibrat"), m_settings.separateBrakeRoute.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.separateBrakeRoute.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("separateBrakeTime");
    childEle.setAttribute(QString("calibrat"), m_settings.separateBrakeTime.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.separateBrakeTime.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("separateBrakeSpeedAvg");
    childEle.setAttribute(QString("calibrat"), m_settings.separateBrakeSpeedAvg.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.separateBrakeSpeedAvg.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("separateBrakeBounceAmp");
    childEle.setAttribute(QString("calibrat"), m_settings.separateBrakeBounceAmp.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.separateBrakeBounceAmp.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("separateBrakeAsyncCycleTime");
    childEle.setAttribute(QString("calibrat"), m_settings.separateBrakeAsyncCycleTime.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.separateBrakeAsyncCycleTime.fOffsetRange);
    root.appendChild(childEle);


    childEle = doc.createElement("contactOverRoute");
    childEle.setAttribute(QString("calibrat"), m_settings.contactOverRoute.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.contactOverRoute.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("closeBrakeRoute");
    childEle.setAttribute(QString("calibrat"), m_settings.closeBrakeRoute.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.closeBrakeRoute.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("closeBrakeTime");
    childEle.setAttribute(QString("calibrat"), m_settings.closeBrakeTime.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.closeBrakeTime.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("closeBrakeSpeedAvg");
    childEle.setAttribute(QString("calibrat"), m_settings.closeBrakeSpeedAvg.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.closeBrakeSpeedAvg.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("closeBrakeBounceTime");
    childEle.setAttribute(QString("calibrat"), m_settings.closeBrakeBounceTime.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.closeBrakeBounceTime.fOffsetRange);
    root.appendChild(childEle);

    childEle = doc.createElement("closeBrakeAsyncCycleTime");
    childEle.setAttribute(QString("calibrat"), m_settings.closeBrakeAsyncCycleTime.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.closeBrakeAsyncCycleTime.fOffsetRange);
    root.appendChild(childEle);


    root.appendChild(childEle);
    childEle = doc.createElement("storeTime");
    childEle.setAttribute(QString("calibrat"), m_settings.storeTime.fCalibrationVal);
    childEle.setAttribute(QString("offset"), m_settings.storeTime.fOffsetRange);
    root.appendChild(childEle);

    QFile file(fileName);  
    if(!file.open(QFile::ReadWrite | QFile::Truncate | QFile::Text)) {
        QString string(QString("CMachineCharacterParam::save open %1 fail.").arg(fileName));
        qDebug() << string;
        return;  
    }  

    QByteArray text(doc.toByteArray());
    file.write(text.data(), text.size());
    file.flush();
    file.close();
}