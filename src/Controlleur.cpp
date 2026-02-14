#include "Controlleur.hpp"

#include <CrcLib.h>

#include "utils.hpp"

void Controlleur::update(const Actions& actions, uint32_t deltaTime)
{
    //actions.print();
    (void)deltaTime;
    this->gererMouvement(actions);
    this->gererTranslation(actions);
    this->gererRotationFourches(actions);
    this->gererOuvertureFourches(actions);
}

void Controlleur::gererMouvement(const Actions& actions)
{
    const int16_t avant = actions.avant;
    const int16_t lacet = actions.lacet;
    const int16_t lateral = actions.lateral;

    const int8_t min = minVitesseRoues;
    const int8_t max = maxVitesseRoues;
    const int8_t avantGauche = utils::conversionClamp(avant - lacet - lateral, min, max);
    const int8_t arriereGauche = utils::conversionClamp(avant - lacet + lateral, min, max);
    const int8_t avantDroite = utils::conversionClamp(avant + lacet + lateral, min, max);
    const int8_t arriereDroite = utils::conversionClamp(avant + lacet - lateral, min, max);

    CrcLib::SetPwmOutput(ROUE_AVANT_GAUCHE_PIN, avantGauche);
    CrcLib::SetPwmOutput(ROUE_ARRIERE_GAUCHE_PIN, arriereGauche);
    CrcLib::SetPwmOutput(ROUE_AVANT_DROITE_PIN, avantDroite);
    CrcLib::SetPwmOutput(ROUE_ARRIERE_DROITE_PIN, arriereDroite);
}

void Controlleur::gererTranslation(const Actions &actions)
{
    const int8_t translation = actions.translation;
    
    CrcLib::SetPwmOutput(TRANSLATION_PIN, translation);
}

void Controlleur::gererRotationFourches(const Actions &actions)
{
    int8_t deltaRotation = actions.deltaRotationFourches;
    SERIAL_PRINT(deltaRotation);
    SERIAL_PRINT(" ");

    const bool limitHaut = CrcLib::GetDigitalInput(ANGLE_FOURCHE_LIMIT_SWITCH_HAUT) == HIGH;
    const bool limitBas = CrcLib::GetDigitalInput(ANGLE_FOURCHE_LIMIT_SWITCH_BAS) == HIGH;
    if ((ACTIVER_ANGLE_FOURCHE_LIMIT_SWITCH_HAUT && limitHaut && (deltaRotation < 0)) ||
        (ACTIVER_ANGLE_FOURCHE_LIMIT_SWITCH_BAS && limitBas && (0 < deltaRotation))) {
        deltaRotation = 0;
    }
    rotationFourches = utils::conversionClamp<int16_t, int8_t>(rotationFourches + deltaRotation, minRotationFourches, maxRotationFourches);
    SERIAL_PRINT(deltaRotation);
    SERIAL_PRINT(" ");
    SERIAL_PRINT(rotationFourches);
    SERIAL_PRINTLN("");

    CrcLib::SetPwmOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN, rotationFourches);
    CrcLib::SetPwmOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN, rotationFourches);
}

void Controlleur::gererOuvertureFourches(const Actions &actions)
{
    int8_t ouverture = actions.vitesseOuvertureFourches;

    const bool limitMin = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN) == HIGH;
    const bool limitMax = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX) == HIGH;
    if ((ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN && limitMin && (ouverture < 0)) ||
        (ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX && limitMax && (0 < ouverture))) {
        ouverture = 0;
    }
    CrcLib::SetPwmOutput(OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN, ouverture);
    CrcLib::SetPwmOutput(OUVERTURE_FOURCHE_DROITE_SERVO_PIN, ouverture);
}
