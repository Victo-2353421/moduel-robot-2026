#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <CrcLib.h>

// changer ceci de 1 ou 0 afin d'activer/désactiver le moniteur de série
#define SERIAL_ENABLE 1

constexpr uint8_t ROUE_AVANT_GAUCHE_PIN = CRC_PWM_1;
constexpr uint8_t ROUE_AVANT_DROITE_PIN = CRC_PWM_4;
constexpr uint8_t ROUE_ARRIERE_GAUCHE_PIN = CRC_PWM_2;
constexpr uint8_t ROUE_ARRIERE_DROITE_PIN = CRC_PWM_3;

constexpr uint8_t TRANSLATION_PIN = CRC_PWM_5;

constexpr uint8_t ANGLE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_7;
constexpr uint8_t ANGLE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_8;
constexpr uint8_t ANGLE_FOURCHE_LIMIT_SWITCH_HAUT = CRC_DIG_3;
constexpr uint8_t ANGLE_FOURCHE_LIMIT_SWITCH_BAS = CRC_DIG_4;

constexpr uint8_t OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_9;
constexpr uint8_t OUVERTURE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_10;
constexpr uint8_t OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN = CRC_DIG_1;
constexpr uint8_t OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX = CRC_DIG_2;

#endif // CONFIG_HPP
