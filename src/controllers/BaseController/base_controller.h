#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include "Arduino.h"
#include "../../state_machines/state.h"

class BaseController
{
public:
    virtual void initialize(BaseController *controller = nullptr) = 0;
    virtual void update() = 0;
    void changeState(State *state);

protected:
    State *currentState = nullptr;
};

#endif
