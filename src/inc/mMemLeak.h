#pragma once

#ifdef _DEBUG

#if defined(_MSC_VER) && !defined(_WIN32_WCE)
//for memory leak check
#define _CRTDBG_MAP_ALLOC //ʹ���ɵ��ڴ�dump�����ڴ�����ľ������Ϊֹ

#include <malloc.h>    // ��� malloc.h �� crtdbg.h ˳���µ� Debug Assertion Failed, "Corrupted pointer passed to _freea" �� 
#include <crtdbg.h> 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif
#endif
