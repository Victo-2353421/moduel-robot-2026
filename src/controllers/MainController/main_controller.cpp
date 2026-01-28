#include "main_controller.hpp"

#include <CrcLib.h>

static constexpr uint32_t MICROSECONDES_PAR_SECONDE = 1000000;

template<typename T, typename U>
static U conversionClamp(T valeur, U min, U max) {
    if(valeur < min)
        return min;
    else if(max < valeur)
        return max;
    else return static_cast<U>(valeur);
}

void MainController::update(const Actions& actions, uint32_t deltaTime)
{
    (void)deltaTime;
    this->gererMouvement(actions);
    this->gererRotationFourches(actions);
}

void MainController::gererMouvement(const Actions& actions)
{
    const int16_t avant = actions.avant;
    const int16_t yaw = actions.yaw;
    const int16_t strafe = actions.strafe;

    const int8_t min = -128;
    const int8_t max = MAXIMUM_MOVEMENT_SPEED;
    const int8_t avantGauche = conversionClamp(avant - yaw - strafe, min, max);
    const int8_t arriereGauche = conversionClamp(avant - yaw + strafe, min, max);
    const int8_t avantDroite = conversionClamp(avant + yaw + strafe, min, max);
    const int8_t arriereDroite = conversionClamp(avant + yaw - strafe, min, max);

    CrcLib::SetPwmOutput(ROUE_AVANT_GAUCHE_PIN, avantGauche);
    CrcLib::SetPwmOutput(ROUE_ARRIERE_GAUCHE_PIN, arriereGauche);
    CrcLib::SetPwmOutput(ROUE_AVANT_DROITE_PIN, avantDroite);
    CrcLib::SetPwmOutput(ROUE_ARRIERE_DROITE_PIN, arriereDroite);
}

void MainController::gererRotationFourches(const Actions &actions)
{
    const bool haut = actions.rotationFourchesHaut;
    const bool bas = actions.rotationFourchesBas;

    int8_t rotation;
    if(haut){
        rotation += vitesseRotationFourches;
    }
    if(bas){
        rotation -= vitesseRotationFourches;
    }

    CrcLib::SetDigitalOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN, haut);
    CrcLib::SetDigitalOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN, bas);
}
