#pragma once

#include <QThread>

class CBaseRecorder : public QThread
{
    Q_OBJECT
public:
    CBaseRecorder(QObject *parent = 0);
    ~CBaseRecorder();

    void exitThread() {m_bExitThread = true;}

protected:
    bool m_bExitThread;
};