#include "MainController.hpp"

#include <CrcLib.h>

#include "utils.hpp"

void MainController::update(const Actions& actions, uint32_t deltaTime)
{
    //actions.print();
    (void)deltaTime;
    this->gererMouvement(actions);
    this->gererTranslation(actions);
    this->gererRotationFourches(actions);
    this->gererOuvertureFourches(actions);
}

void MainController::gererMouvement(const Actions& actions)
{
    const int16_t avant = actions.avant;
    const int16_t yaw = actions.yaw;
    const int16_t strafe = actions.strafe;

    const int8_t min = minVitesseRoues;
    const int8_t max = maxVitesseRoues;
    const int8_t avantGauche = utils::conversionClamp(avant - yaw - strafe, min, max);
    const int8_t arriereGauche = utils::conversionClamp(avant - yaw + strafe, min, max);
    const int8_t avantDroite = utils::conversionClamp(avant + yaw + strafe, min, max);
    const int8_t arriereDroite = utils::conversionClamp(avant + yaw - strafe, min, max);

    CrcLib::SetPwmOutput(ROUE_AVANT_GAUCHE_PIN, avantGauche);
    CrcLib::SetPwmOutput(ROUE_ARRIERE_GAUCHE_PIN, arriereGauche);
    CrcLib::SetPwmOutput(ROUE_AVANT_DROITE_PIN, avantDroite);
    CrcLib::SetPwmOutput(ROUE_ARRIERE_DROITE_PIN, arriereDroite);
}

void MainController::gererTranslation(const Actions &actions)
{
    const int8_t translation = actions.translation;
    
    CrcLib::SetPwmOutput(TRANSLATION_PIN, translation);
}

void MainController::gererRotationFourches(const Actions &actions)
{
    const int8_t rotation = actions.rotationFourches;

    CrcLib::SetPwmOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN, rotation);
    CrcLib::SetPwmOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN, rotation);
}

void MainController::gererOuvertureFourches(const Actions &actions)
{
    const int8_t ouverture = actions.ouvertureFourches;

    CrcLib::SetPwmOutput(OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN, ouverture);
    CrcLib::SetPwmOutput(OUVERTURE_FOURCHE_DROITE_SERVO_PIN, ouverture);
}
