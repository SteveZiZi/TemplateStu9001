#include "Machine.h"
#include "MachineState.h"

#include <QTimer>

#include "debug.h"

CMachine::CMachine(QWidget* parent)
: CImageShow(parent)
, m_interval(500)
{
    m_state[STATE_UNDEFINED] = new CUndefinedState(this);
    m_state[STATE_OPEN] = new COpenState(this);
    m_state[STATE_OPENING] = new COpeningState(this);
    m_state[STATE_CLOSED] = new CClosedState(this);
    m_state[STATE_CLOSING] = new CClosingState(this);
    m_state[STATE_MIDDLE] = new CMiddleState(this);

    m_currentState = m_state[STATE_UNDEFINED];

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(tick()));
}

CMachine::~CMachine()
{
    end();

    for(int i = 0; i < MAX_STATE; i++) {
        if (m_state[i]) {
            delete m_state[i];
            m_state[i] = NULL;
        }
    }

    if (m_timer) {
        delete m_timer;
    }
}


void CMachine::tick()
{
    m_currentState->tick();
}

void CMachine::SetState(CStateBase* pState)
{
    m_currentState->end();
    m_currentState = pState;
    m_currentState->run();
}

CStateBase* CMachine::GetState(STATE_ENUM item)
{
    return m_state[item];
}

void CMachine::run()
{
    end();
    if (m_timer)
        m_timer->start(m_interval);
}

void CMachine::end()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
    }
}

void CMachine::ExceptState(STATE_ENUM newState)
{
    m_currentState->state_exception(m_state[newState]);
}

void CMachine::close()  
{ 
    m_currentState->close(); 
}

void CMachine::open() 
{ 
    m_currentState->open();
}

void CMachine::stop() 
{ 
    m_currentState->stop(); 
}

void CMachine::state_exception(CStateBase* newState) 
{
    m_currentState->state_exception(newState);
}