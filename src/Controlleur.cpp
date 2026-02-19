#include "Controlleur.hpp"

#include <CrcLib.h>

#include "utils.hpp"

void Controlleur::update(const Actions& actions, US deltaTime)
{
    //actions.print();
    (void)deltaTime;
    this->gererMouvement(actions);
    this->gererTranslation(actions);
    this->gererRotationFourches(actions);
    this->gererOuvertureFourches(actions);
    this->gererDELs();
}

void Controlleur::gererMouvement(const Actions& actions)
{
    const int16_t avant = actions.avant;
    const int16_t lacet = actions.lacet;
    const int16_t lateral = actions.lateral;

    const int8_t min = ROUES_VITESSE_MIN;
    const int8_t max = ROUES_VITESSE_MAX;
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
    int8_t translation = actions.translation;

    const bool limitMin = CrcLib::GetDigitalInput(TRANSLATION_LIMIT_SWITCH_MIN) == HIGH;
    const bool limitMax = CrcLib::GetDigitalInput(TRANSLATION_LIMIT_SWITCH_MAX) == HIGH;
    if ((ACTIVER_TRANSLATION_LIMIT_SWITCH_MIN && limitMin && (translation < 0)) ||
        (ACTIVER_TRANSLATION_LIMIT_SWITCH_MAX && limitMax && (0 < translation))) {
        translation = 0;
    }
    CrcLib::SetPwmOutput(TRANSLATION_PIN_GAUCHE, translation);
    CrcLib::SetPwmOutput(TRANSLATION_PIN_DROITE, translation);
}

void Controlleur::gererRotationFourches(const Actions &actions)
{
    float deltaRotation = actions.deltaRotationFourches;

    rotationFourches = utils::conversionClamp<float, float>(
        rotationFourches + deltaRotation,
        ANGLE_FOURCHE_MINIMAL,
        ANGLE_FOURCHE_MAXIMAL
    );
    CrcLib::SetPwmOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN, rotationFourches);
    CrcLib::SetPwmOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN, rotationFourches);
}

void Controlleur::gererOuvertureFourches(const Actions &actions)
{
    int8_t ouverture = actions.vitesseOuvertureFourches;

    if(ATIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_SIGNAL) {
        signalArretFermeture = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_SIGNAL) == HIGH;
        if (signalArretFermeture) {
            if(!ignoreArretFermeture && (ouverture < 0)){
                // Empêcher de fermer plus
                ouverture = 0;
            } else if(0 <= ouverture) {
                ignoreArretFermeture = true;
            }
        } else {
            ignoreArretFermeture = false;
        }
    }

    const bool limitMin = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN) == LOW;
    const bool limitMax = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX) == HIGH;
    if ((ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN && limitMin && (ouverture < 0)) ||
        (ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX && limitMax && (0 < ouverture))) {
        ouverture = 0;
    }
    CrcLib::SetPwmOutput(OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN, ouverture);
    CrcLib::SetPwmOutput(OUVERTURE_FOURCHE_DROITE_SERVO_PIN, ouverture);
}

void Controlleur::gererDELs(){
    const bool limitOuvertureMax = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX);
    CrcLib::SetDigitalOutput(DEL_ROUGE_1, limitOuvertureMax);
    CrcLib::SetDigitalOutput(DEL_ROUGE_2, limitOuvertureMax);
    const bool limitOuvertureMin = !CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN);
    CrcLib::SetDigitalOutput(DEL_BLANCHE_1, limitOuvertureMin);
    CrcLib::SetDigitalOutput(DEL_BLANCHE_2, limitOuvertureMin);
    
    const bool avantGauche = (20 < CrcLib::GetAnalogInput(AVANT_GAUCHE_LIMIT_SWITCH));
    const bool avantDroite = (20 < CrcLib::GetAnalogInput(AVANT_DROITE_LIMIT_SWITCH));
    CrcLib::SetDigitalOutput(
        DEL_VERT_2,
        avantGauche
    );
    CrcLib::SetDigitalOutput(
        DEL_VERT_1,
        avantDroite
    );
}