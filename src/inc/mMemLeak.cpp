#include "mMemLeak.h"

//每个dll、exe工程下必须包含一个此文件

#pragma init_seg(lib)
class MMemLeak 
{
public:
    MMemLeak() 
    {
#ifdef _DEBUG
#ifndef _WIN32_WCE
        int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
        tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
        _CrtSetDbgFlag( tmpFlag );

        //可以设置断点
        //_CrtSetBreakAlloc(52);
#endif
#endif
    }

    ~MMemLeak()
    {
        //设置输出内存泄漏信息
        //_CrtDumpMemoryLeaks();
    }
}s_mmLeak;