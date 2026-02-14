#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "Actions.hpp"
#include "config.hpp"

class Controlleur
{
public:
    void update(const Actions& actions, uint32_t deltaTime);

    int8_t minVitesseRoues = -128;
    int8_t maxVitesseRoues = 90;
    void gererMouvement(const Actions& actions);

    void gererTranslation(const Actions& actions);

    int8_t rotationFourches = 0;
    int8_t minRotationFourches = -70;
    int8_t maxRotationFourches = 70;
    void gererRotationFourches(const Actions& actions);

    void gererOuvertureFourches(const Actions& actions);
};

#endif
