#include "Actions.hpp"

#include "utils.hpp"

Actions Actions::lire()
{
    Actions actions;
    actions.avant = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
    actions.yaw = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
    actions.strafe = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);

    const int8_t monterRead = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_L);
    actions.monter = utils::map<int8_t>(monterRead, -128, 127, 0, 127);
    const int8_t descendreRead = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R);
    actions.descendre = utils::map<int8_t>(descendreRead, -128, 127, 0, 127);

    actions.rotationFourchesHaut = CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT);
    actions.rotationFourchesBas = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);

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
    
    Serial.print("monter : ");
    Serial.println(monter);
    Serial.print("descendre : ");
    Serial.println(descendre);

    Serial.print(rotationFourchesHaut ? "X" : " ");
    Serial.print(rotationFourchesBas ? "A" : " ");

    Serial.print(ouvrirFourches ? "B" : " ");
    Serial.print(fermerFourches ? "Y" : " ");

    Serial.println("");
}