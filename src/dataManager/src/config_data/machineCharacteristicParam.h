#pragma once

#include "../driver/module.h"

struct MC_Setting {
    float fCalibrationVal;
    float fOffsetRange;
};

struct MachineCharacterSettings {
    MC_Setting contactDistance;
    MC_Setting separateBrakeRoute;
    MC_Setting separateBrakeTime;
    MC_Setting separateBrakeSpeedAvg;
    MC_Setting separatingBrakingSpeed;
    MC_Setting separateBrakeBounceAmp;
    MC_Setting separateBrakeAsyncCycleTime;

    MC_Setting contactOverRoute;
    MC_Setting closeBrakeRoute;
    MC_Setting closeBrakeTime;
    MC_Setting closeBrakeSpeedAvg;
    MC_Setting closingBrakeSpeed;
    MC_Setting closeBrakeBounceTime;
    MC_Setting closeBrakeAsyncCycleTime;

    MC_Setting storeTime;
};


class CMachineCharacterParam : public QObject
{
    Q_OBJECT

protected:
    CMachineCharacterParam(QObject* parent = 0);
    virtual ~CMachineCharacterParam(void);

public:
    static CMachineCharacterParam* getInstance();

signals:
    void settingsChanged(const MachineCharacterSettings& settings);

public:
    void machineCharacterSettings(MachineCharacterSettings* settings);
    void setMachineCharacterSettings(const MachineCharacterSettings& settings) ;

private:
    void load(const QString& fileName);
    void save(const QString& fileName);

private:
    //找不到对应的寄存器  暂时保存界面值
    MachineCharacterSettings m_settings;
    bool m_bInit;
};

