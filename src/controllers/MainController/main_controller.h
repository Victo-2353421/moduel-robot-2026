#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "pin_mappings.h"

class MainController
{
public:
    void update(const Actions& actions, uint32_t deltaTime);

    void gererMouvement(const Actions& actions);

    int8_t vitesseRotationFourches = 127;
    void gererRotationFourches(const Actions& actions);
};

#endif
