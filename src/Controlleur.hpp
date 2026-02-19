#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "Actions.hpp"
#include "config.hpp"

class Controlleur
{
public:
    void update(const Actions& actions, US deltaTime);

    void gererMouvement(const Actions& actions);

    void gererTranslation(const Actions& actions);

    float rotationFourches = 0;
    void gererRotationFourches(const Actions& actions);

    bool signalArretFermeture = false;
    bool ignoreArretFermeture = false;
    void gererOuvertureFourches(const Actions& actions);
    
    void gererDELs();
};

#endif
