
#pragma once

#include "../driver/module.h"

class CDataLevelMisc
{
protected:
    CDataLevelMisc(void);
    virtual ~CDataLevelMisc(void);

public:
    ///
    /// @brief
    ///     获取配置实例接口
    ///
    static CDataLevelMisc* getInstance();

public:
    bool GetCP6000Time(QDateTime* dateTime);
    bool SetCP6000Time(const QDateTime& dateTime);

    bool GetMachineCharacterTime(QDateTime* dateTime);
    bool SetMachineCharacterTime(const QDateTime& dateTime);

private:
};

