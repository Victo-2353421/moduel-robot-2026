#include "base_controller.h"
#include <utils_debug.h>

void BaseController::initialize(BaseController *controller)
{
    assert(false, "BaseController::initialize() not implemented");
}

void BaseController::update()
{
    assert(false, "BaseController::update() not implemented");
}

void BaseController::changeState(State *newState)
{
    if (currentState)
    {
        currentState->onExit();
    }
    currentState = newState;
    currentState->onEnter();
}