#pragma once

class CMachine;

class CStateBase
{
public:
    CStateBase(CMachine* pMachine);
    virtual ~CStateBase();

    //启动 与 结束本状态
    virtual void run()  { }
    virtual void end()  { }
    virtual void tick() { }

    //命令
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
    //命令
    virtual void close();
    virtual void stop();
};

class COpeningState : public CStateBase
{
public:
    COpeningState(CMachine* pMachine);
    virtual ~COpeningState();

    //启动 与 结束本状态
    virtual void run();
    virtual void end();
    virtual void tick();

    //命令
    virtual void close();
    virtual void stop();
};


class CClosedState : public CStateBase
{
public:
    CClosedState(CMachine* pMachine);
    virtual ~CClosedState();

    virtual void run();
    //命令
    virtual void open();
};


class CClosingState : public CStateBase
{
public:
    CClosingState(CMachine* pMachine);
    virtual ~CClosingState();

    //启动 与 结束本状态
    virtual void run();
    virtual void end();
    virtual void tick();

    //命令
    virtual void open();
    virtual void stop();
};


class CMiddleState : public CStateBase
{
public:
    CMiddleState(CMachine* pMachine);
    virtual ~CMiddleState();

    //命令
    virtual void open();
    virtual void close();
};