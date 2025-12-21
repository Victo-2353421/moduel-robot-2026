#include "propulseur_controller.h"

void PropulseurController::initialize(BaseController *controller)
{
    this->_mainController = (MainController *)controller;

    Serial.println("> Contrôleur de propulseur initialisé.");
}

void PropulseurController::update()
{
    CrcLib::SetDigitalOutput(PROPULSEUR_MOTOR_PIN, CrcLib::ReadDigitalChannel(SHOOT_KEY));
}