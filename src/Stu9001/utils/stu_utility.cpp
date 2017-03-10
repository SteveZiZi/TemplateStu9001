#include "stu_utility.h"

#include <QtGui>
#include <QDateTime>

#include <DataLevelMisc>

#include <lib_win32>

#include "debug.h"

enum {
    STU_SHOW_OS_TIME,
    STU_SHOW_MC_TIME,
    STU_SHOW_CP6000_TIME,
    STU_SHOW_CP9000_TIME
};

#define STU_SHOW_TIME_METHOD    STU_SHOW_OS_TIME

#define STU_SET_OS_TIME         1
#define STU_SET_MC_TIME         0
#define STU_SET_CP6000_TIME     0
#define STU_SET_CP9000_TIME     0

#if STU_SET_CP6000_TIME && STU_SET_CP9000_TIME
#error "STU9001 Only one CP Machine"
#endif


QString stu_getStyleSheetFromFile(QString fileName)
{
    QFile file(fileName);
    
    QString styleSheet("");
    if (file.open(QFile::ReadOnly))  {
        styleSheet = QLatin1String(file.readAll());
        file.close();
    }

    return styleSheet;
}

;

bool stu_setSystemTime(const QDateTime* dateTime)
{
#if STU_SET_OS_TIME
    fnlib_SYSTEMTIME tm;
    tm.year = dateTime->date().year();
    tm.month = dateTime->date().month();
    tm.day = dateTime->date().day();
    tm.dayOfWeek = dateTime->date().dayOfWeek();
    tm.hour = dateTime->time().hour();
    tm.minute = dateTime->time().minute();
    tm.second = dateTime->time().second();
    tm.milliseconds = dateTime->time().msec();
    fnlib_setLocalTime(tm);
#endif

#if STU_SET_CP6000_TIME
    CDataLevelMisc::getInstance()->SetCP6000Time(*dateTime);
#endif

#if STU_SET_CP9000_TIME
#error "no object for Set CP9000 Time"
#endif

#if STU_SET_MC_TIME
    CDataLevelMisc::getInstance()->SetMachineCharacterTime(*dateTime);
#endif
    return true;
}

bool stu_getSystemTime(QDateTime* dateTime)
{
#if (STU_SHOW_TIME_METHOD == STU_SHOW_OS_TIME)
    *dateTime = QDateTime::currentDateTime();
    return true;
#elif (STU_SHOW_TIME_METHOD == STU_SHOW_CP6000_TIME)
    return CDataLevelMisc::getInstance()->GetCP6000Time(dateTime);
#elif (STU_SHOW_TIME_METHOD == STU_SHOW_CP9000_TIME)
#error "not object for Get CP9000 Time"
    return false;
#elif (STU_SHOW_TIME_METHOD == STU_SHOW_MC_TIME)
    return CDataLevelMisc::getInstance()->GetMachineCharacterTime(dateTime);
#else
    return false;
#endif
}