#ifndef PIN_MAPPINGS_H
#define PIN_MAPPINGS_H

#include <CrcLib.h>

// 6 moteurs
// 4 pour les roues
// 2 pour fourches (monter/descendre), 1 contrôle. Elles tournent en sens opposé

// 4 servo
// 2 pour translation (2 tours à peu près)
// 2 pour rotation


/**
 * Connexions des moteurs omnidirectionnels
 */
constexpr uint8_t ROUE_AVANT_GAUCHE_PIN = CRC_PWM_1;
constexpr uint8_t ROUE_AVANT_DROITE_PIN = CRC_PWM_2;
constexpr uint8_t ROUE_ARRIERE_GAUCHE_PIN = CRC_PWM_3;
constexpr uint8_t ROUE_ARRIERE_DROITE_PIN = CRC_PWM_4;

constexpr int8_t MAXIMUM_MOVEMENT_SPEED = 90;

constexpr uint8_t ANGLE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_5;
constexpr uint8_t ANGLE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_6;

constexpr uint8_t ANGLE_FOURCHE_BLOCAGE = CRC_DIG_1;

struct Actions {
    int8_t avant{};
    int8_t yaw{};
    int8_t strafe{};

    bool rotationFourchesHaut{};
    bool rotationFourchesBas{};

    bool translationFourchesGauche{};
    bool translationFourchesDroite{};

    bool ouvrirFourches{};
    bool fermerFourches{};

    inline void print() {
        Serial.print("avant : ");
        Serial.println(avant);
        Serial.print("yaw : ");
        Serial.println(yaw);
        Serial.print("strafe : ");
        Serial.println(strafe);

        Serial.print(rotationFourchesHaut ? "X" : " ") ;
        Serial.print(rotationFourchesBas ? "A" : " ") ;
        Serial.print(translationFourchesGauche ? "G" : " ") ;
        Serial.print(translationFourchesDroite ? "D" : " ") ;
        Serial.print(ouvrirFourches ? "B" : " ") ;
        Serial.print(fermerFourches ? "Y" : " ") ;

        Serial.println("");
    }
};

#endif