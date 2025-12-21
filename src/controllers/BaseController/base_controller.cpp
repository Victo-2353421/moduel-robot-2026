#include "base_controller.h"

void BaseController::initialize(BaseController *controller)
{
    Serial.println("BaseController::initialize() not implemented.");
    while (true);
}

void BaseController::update()
{
    Serial.println("BaseController::update() not implemented.");
    while (true);
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