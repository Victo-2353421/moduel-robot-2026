#ifndef PROPULSEUR_CONTROLLER_H
#define PROPULSEUR_CONTROLLER_H

#include <Servo.h>
#include "../MainController/main_controller.h"
#include "../BaseController/base_controller.h"

class MainController;

class PropulseurController : public BaseController
{
public:
    void initialize(BaseController *mainController = nullptr) override;
    void update() override;

    /**
     * Shoots the game pieces
     */
    void shoot();

private:
    MainController *_mainController = nullptr;
};

#endif
