#pragma once

class CMachine;

class CStateBase
{
public:
    CStateBase(CMachine* pMachine);
    virtual ~CStateBase();

    //���� �� ������״̬
    virtual void run()  { }
    virtual void end()  { }
    virtual void tick() { }

    //����
    virtual void close()  { }
    virtual void open()  { }
    virtual void stop()  { }
    virtual void state_exception(CStateBase* newState);

public:
    void SetMachine(CMachine* pMachine) {m_pMachine = pMachine;}
    CMachine* GetMachine(void) {return m_pMachine;}

protected:
    CMachine* m_pMachine;
};

class CUndefinedState : public CStateBase
{
public:
    CUndefinedState(CMachine* pMachine);
    virtual ~CUndefinedState();
};

class COpenState : public CStateBase
{
public:
    COpenState(CMachine* pMachine);
    virtual ~COpenState();

    virtual void run();
    //����
    virtual void close();
    virtual void stop();
};

class COpeningState : public CStateBase
{
public:
    COpeningState(CMachine* pMachine);
    virtual ~COpeningState();

    //���� �� ������״̬
    virtual void run();
    virtual void end();
    virtual void tick();

    //����
    virtual void close();
    virtual void stop();
};


class CClosedState : public CStateBase
{
public:
    CClosedState(CMachine* pMachine);
    virtual ~CClosedState();

    virtual void run();
    //����
    virtual void open();
};


class CClosingState : public CStateBase
{
public:
    CClosingState(CMachine* pMachine);
    virtual ~CClosingState();

    //���� �� ������״̬
    virtual void run();
    virtual void end();
    virtual void tick();

    //����
    virtual void open();
    virtual void stop();
};


class CMiddleState : public CStateBase
{
public:
    CMiddleState(CMachine* pMachine);
    virtual ~CMiddleState();

    //����
    virtual void open();
    virtual void close();
};