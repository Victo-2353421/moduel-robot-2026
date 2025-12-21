#ifndef STATE_H
#define STATE_H

class BaseController;

class State
{
public:
    virtual void onEnter() = 0;
    virtual void onExecute() = 0;
    virtual void onExit() = 0;
};

#endif