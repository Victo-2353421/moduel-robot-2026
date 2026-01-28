#include "Actions.hpp"

Actions Actions::lire()
{
    Actions actions;
    actions.avant = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
    actions.yaw = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
    actions.strafe = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);

    actions.rotationFourchesHaut = CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT);
    actions.rotationFourchesBas = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);

    actions.translationFourchesGauche = CrcLib::ReadDigitalChannel(BUTTON::L1);
    actions.translationFourchesDroite = CrcLib::ReadDigitalChannel(BUTTON::R1);
    
    actions.ouvrirFourches = CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT);
    actions.fermerFourches = CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP);
    return actions;
}

void Actions::print() {
    Serial.print("avant : ");
    Serial.println(avant);
    Serial.print("yaw : ");
    Serial.println(yaw);
    Serial.print("strafe : ");
    Serial.println(strafe);

    Serial.print(rotationFourchesHaut ? "X" : " ");
    Serial.print(rotationFourchesBas ? "A" : " ");

    Serial.print(translationFourchesGauche ? "G" : " ");
    Serial.print(translationFourchesDroite ? "D" : " ");

    Serial.print(ouvrirFourches ? "B" : " ");
    Serial.print(fermerFourches ? "Y" : " ");

    Serial.println("");
}