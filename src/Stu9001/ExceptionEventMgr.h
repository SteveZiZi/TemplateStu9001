#pragma once

#include <QObject>

class CExceptionEventMgr : public QObject
{
    Q_OBJECT

public:
    static CExceptionEventMgr* getInstance();

    void init();
    void deinit();

protected:
    CExceptionEventMgr();
    ~CExceptionEventMgr();
};