#include "MachineState.h"
#include "Machine.h"

#include "debug.h"

/************************************************************************/
/*  CCubicleStateBase                                                   */
/************************************************************************/
CStateBase::CStateBase(CMachine* pMachine)
: m_pMachine(pMachine)
{

}

CStateBase::~CStateBase()
{

}

void CStateBase::state_exception(CStateBase* newState)
{
    m_pMachine->SetState(newState);
}

/************************************************************************/
/*  CUndefinedState                                                     */
/************************************************************************/
CUndefinedState::CUndefinedState(CMachine* pMachine)
: CStateBase(pMachine)
{

}

CUndefinedState::~CUndefinedState()
{

}


/************************************************************************/
/*  COpenState                                                          */
/************************************************************************/
COpenState::COpenState(CMachine* pMachine)
: CStateBase(pMachine)
{

}

COpenState::~COpenState()
{

}

void COpenState::run()
{
    m_pMachine->showImage(m_pMachine->openItem());
}

void COpenState::close()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_CLOSING));
}

void COpenState::stop()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_MIDDLE));
}


/************************************************************************/
/*  COpeningState                                                       */
/************************************************************************/
COpeningState::COpeningState(CMachine* pMachine)
: CStateBase(pMachine)
{

}

COpeningState::~COpeningState()
{

}


void COpeningState::run()
{
    m_pMachine->run();
}

void COpeningState::end()
{
    m_pMachine->end();
}

void COpeningState::tick()
{
    m_pMachine->showImage(m_pMachine->preItem());
    if (m_pMachine->item() == m_pMachine->openItem()) {
        m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_OPEN));
    }
}

void COpeningState::close()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_CLOSING));
}

void COpeningState::stop()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_MIDDLE));
}

/************************************************************************/
/*  CClosedState                                                       */
/************************************************************************/
CClosedState::CClosedState(CMachine* pMachine)
: CStateBase(pMachine)
{

}

CClosedState::~CClosedState()
{

}

void CClosedState::run()
{
    m_pMachine->showImage(m_pMachine->closedItem());
}

void CClosedState::open()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_OPENING));
}


/************************************************************************/
/*  CClosingState                                                       */
/************************************************************************/
CClosingState::CClosingState(CMachine* pMachine)
: CStateBase(pMachine)
{

}

CClosingState::~CClosingState()
{

}

void CClosingState::run()
{
    m_pMachine->run();
}

void CClosingState::end()
{
    m_pMachine->end();
}

void CClosingState::tick()
{
    m_pMachine->showImage(m_pMachine->nextItem());
    if (m_pMachine->item() == m_pMachine->closedItem()) {
        m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_CLOSED));
    }
}

void CClosingState::open()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_OPENING));
}

void CClosingState::stop()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_MIDDLE));
}

/************************************************************************/
/*  CClosingState                                                       */
/************************************************************************/
CMiddleState::CMiddleState(CMachine* pMachine)
: CStateBase(pMachine)
{

}

CMiddleState::~CMiddleState()
{

}

void CMiddleState::open()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_OPENING));
}

void CMiddleState::close()
{
    m_pMachine->SetState(m_pMachine->GetState(CMachine::STATE_CLOSING));
}