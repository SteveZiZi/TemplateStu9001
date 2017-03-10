#pragma once


enum SystemTimeEvent
{
    DATE_TIME_NORMAL,               //时间正常
    DATE_TIME_EXCEPTION,            //时间出现异常
    DATE_TIME_MODIFY,               //时间被修改
    DATE_TIME_EXCEPT_RESTORE        //时间异常后 自动恢复以前的时间
};