#pragma once

#ifdef _DEBUG

#if defined(_MSC_VER) && !defined(_WIN32_WCE)
//for memory leak check
#define _CRTDBG_MAP_ALLOC //使生成的内存dump包含内存块分配的具体代码为止

#include <malloc.h>    // 解决 malloc.h 与 crtdbg.h 顺序导致的 Debug Assertion Failed, "Corrupted pointer passed to _freea" 。 
#include <crtdbg.h> 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif
#endif
