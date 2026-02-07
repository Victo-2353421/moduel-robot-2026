#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "Actions.hpp"
#include "config.hpp"

class MainController
{
public:
    void update(const Actions& actions, uint32_t deltaTime);

    int8_t minVitesseRoues = -128;
    int8_t maxVitesseRoues = 90;
    void gererMouvement(const Actions& actions);

    void gererTranslation(const Actions& actions);

    int8_t vitesseRotationFourches = 127;
    void gererRotationFourches(const Actions& actions);

    int8_t vitesseOuvertureFourches = 127;
    void gererOuvertureFourches(const Actions& actions);
};

#endif
