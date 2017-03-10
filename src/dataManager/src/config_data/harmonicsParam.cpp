#include "harmonicsParam.h"
#include "../driver/DevAttrMgr.h"

#include <QFile>
#include <QDir>
#include <QDomDocument>

#include "debug.h"

#define SETTINGS_FILE_NAME  "/runtime_config/harmonicsParamSettings.xml"


CHarmonicParam::CHarmonicParam(QObject* parent)
: QObject(parent)
, m_bInit(false)
{
}

CHarmonicParam::~CHarmonicParam(void)
{
}


CHarmonicParam* CHarmonicParam::getInstance()
{
    static CHarmonicParam s_param;
    if (!s_param.m_bInit) {
        QString path = QDir::currentPath();
        path += SETTINGS_FILE_NAME;
        s_param.load(path);
    }
    return &s_param;
}

void CHarmonicParam::harmonicParam(HarmonicParam* param)
{
    Q_ASSERT(param);
    memcpy(param, &m_param, sizeof(HarmonicParam));
}


void CHarmonicParam::setHarmonicParam(const HarmonicParam& param)
{
    memcpy(&m_param, &param, sizeof(HarmonicParam));
    QString path = QDir::currentPath();
    path += SETTINGS_FILE_NAME;
    save(path);
    emit settingsChanged(m_param);
}

void CHarmonicParam::load(const QString& fileName)
{
    QDomDocument document;  
    QString error;  
    int row = 0, column = 0;  
    QFile file(fileName);

    if(fileName.isEmpty())
        goto defaultSettings;

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QString string(QString("CHarmonicParam::load open %1 fail.").arg(fileName));
        qDebug() << string;
        goto defaultSettings;
    }  

    if(!document.setContent(&file, false, &error, &row, &column)) {  
        qDebug() << QString("CHarmonicParam::load parse file failed at line row and column %1,%2").arg(row).arg(column);
        goto defaultSettings;
    }  

    if(document.isNull()) {  
        qDebug() << "CHarmonicParam::load document is null!";
        goto defaultSettings;
    }  

    {
        QDomElement root = document.documentElement();  
        QDomElement cur = root.firstChildElement(QString("current"));

        for(int i = 2; i <= MAX_HARMONIC_ORDER; i++) {
            m_param.cur[i] = cur.firstChildElement(QString("harm_%1").arg(i)).attribute(QString("val")).toFloat();
        }
        QDomElement vol = root.firstChildElement(QString("voltage"));
        for(int i = 2; i <= MAX_HARMONIC_ORDER; i++) {
            m_param.vol[i] = vol.firstChildElement(QString("harm_%1").arg(i)).attribute(QString("val")).toFloat();
        }
    }
    m_bInit = true;
defaultSettings:
    if (!m_bInit) {
        memset(&m_param, 0, sizeof(m_param));
        save(fileName);
    }
}


void CHarmonicParam::save(const QString& fileName)
{
    if(fileName.isEmpty())
        return;  

    QDomDocument doc;  
    QDomElement root = doc.createElement("settings");
    doc.appendChild(root);

    QDomElement cur = doc.createElement("current");
    for(int i = 2; i <= MAX_HARMONIC_ORDER; i++) {
        QDomElement child = doc.createElement(QString("harm_%1").arg(i));
        child.setAttribute(QString("val"), m_param.cur[i]);
        cur.appendChild(child);
    }
    root.appendChild(cur);

    QDomElement vol = doc.createElement("voltage");
    for(int i = 2; i <= MAX_HARMONIC_ORDER; i++) {
        QDomElement child = doc.createElement(QString("harm_%1").arg(i));
        child.setAttribute(QString("val"), m_param.vol[i]);
        vol.appendChild(child);
    }
    root.appendChild(vol);

    QFile file(fileName);  
    if(!file.open(QFile::ReadWrite | QFile::Truncate | QFile::Text)) {
        QString string(QString("CHarmonicParam::save open %1 fail.").arg(fileName));
        qDebug() << string;
        return;  
    }  

    QByteArray text(doc.toByteArray());
    file.write(text.data(), text.size());
    file.flush();
    file.close();
}