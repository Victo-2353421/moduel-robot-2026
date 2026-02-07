#ifndef PIN_MAPPINGS_HPP
#define PIN_MAPPINGS_HPP

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
constexpr uint8_t ROUE_AVANT_DROITE_PIN = CRC_PWM_4;
constexpr uint8_t ROUE_ARRIERE_GAUCHE_PIN = CRC_PWM_2;
constexpr uint8_t ROUE_ARRIERE_DROITE_PIN = CRC_PWM_3;

constexpr uint8_t TRANSLATION_PIN = CRC_PWM_5;

constexpr uint8_t ANGLE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_7;
constexpr uint8_t ANGLE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_8;
constexpr uint8_t ANGLE_FOURCHE_BLOCAGE = CRC_DIG_1;

constexpr uint8_t OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_9;
constexpr uint8_t OUVERTURE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_10;
constexpr uint8_t OUVERTURE_FOURCHE_BLOCAGE = CRC_DIG_2;

#endif // PIN_MAPPINGS_HPP
