// lib_win32.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "lib_win32.h"

#include "mMemLeak.h"

LIB_WIN32_API bool fnlib_setSystemTime(const fnlib_SYSTEMTIME &tm)
{
    SYSTEMTIME sysTm;
    sysTm.wYear = tm.year;
    sysTm.wMonth = tm.month;
    sysTm.wDay = tm.day;
    sysTm.wHour = tm.hour;
    sysTm.wMinute = tm.minute;
    sysTm.wSecond = tm.second;
    sysTm.wMilliseconds = tm.milliseconds;
    sysTm.wDayOfWeek = tm.dayOfWeek;
    
    return (SetSystemTime(&sysTm) == TRUE);
}

LIB_WIN32_API bool fnlib_setLocalTime(const fnlib_SYSTEMTIME &tm)
{
    SYSTEMTIME sysTm;
    sysTm.wYear = tm.year;
    sysTm.wMonth = tm.month;
    sysTm.wDay = tm.day;
    sysTm.wHour = tm.hour;
    sysTm.wMinute = tm.minute;
    sysTm.wSecond = tm.second;
    sysTm.wMilliseconds = tm.milliseconds;
    sysTm.wDayOfWeek = tm.dayOfWeek;

    return (SetLocalTime(&sysTm) == TRUE);
}

