#pragma once

#include <imageShow>

class CStateBase;

class CMachine : public CImageShow
{
    Q_OBJECT
public:
    enum STATE_ENUM {
        STATE_UNDEFINED,
        STATE_OPEN,
        STATE_OPENING,
        STATE_CLOSED,
        STATE_CLOSING,
        STATE_MIDDLE,
        MAX_STATE
    };

    CMachine(QWidget* parent = 0);
    virtual ~CMachine();

    //
    void SetState(CStateBase* pState);
    CStateBase* GetState(STATE_ENUM item);

    //√¸¡Ó
    virtual void close();
    virtual void open();
    virtual void stop();
    virtual void state_exception(CStateBase* newState);

public:
    void run();
    void end();
    void setInterval(int interval) {m_interval = interval;}

    int openItem(void) {return 0;}
    int closedItem(void) {return count()-1;}

protected slots:
    void tick();

private:
    void ExceptState(STATE_ENUM newState);

private:
    CStateBase* m_currentState;
    CStateBase* m_state[MAX_STATE];
    QTimer*     m_timer;
    int         m_interval;
};