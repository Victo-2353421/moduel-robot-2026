#ifndef CONFIG_HPP
#define CONFIG_HPP

/*****************************************************************************/
/* Ce fichier sert de configuration du robot. Modifiez les valeurs de ce     */
/* fichier selon vos besoins.                                                */
/*****************************************************************************/

#include <CrcLib.h>

// changer ceci de 1 ou 0 afin d'activer/désactiver le moniteur de série.
// Le moniteur de série peut causer beaucoup de latance. C'est utile pour le
// débogage mais ÇA DOIT _ABSOLUMENT_ ÊTRE DÉSACTIVÉ LORS DE LA COMPÉTITION.
#define SERIAL_ENABLE 1

// Les pins des roues. Ça correspond aux contrôles des moteurs des roues
constexpr uint8_t ROUE_AVANT_GAUCHE_PIN = CRC_PWM_1;
constexpr uint8_t ROUE_AVANT_DROITE_PIN = CRC_PWM_4;
constexpr uint8_t ROUE_ARRIERE_GAUCHE_PIN = CRC_PWM_2;
constexpr uint8_t ROUE_ARRIERE_DROITE_PIN = CRC_PWM_3;

// La pin du contrôle pour monter/descendre.
constexpr uint8_t TRANSLATION_PIN = CRC_PWM_5;

// Contrôles de la rotation des fourches.
// METTRE LES VALEURS « ACTIVER » À FALSE SI LES LIMIT
// SWITCH NE SONT PAS BRANCHÉES OU NON FONCTIONNELLES.
constexpr uint8_t ANGLE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_7;
constexpr uint8_t ANGLE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_8;
constexpr bool ACTIVER_ANGLE_FOURCHE_LIMIT_SWITCH_HAUT = true;
constexpr uint8_t ANGLE_FOURCHE_LIMIT_SWITCH_HAUT = CRC_DIG_3;
constexpr bool ACTIVER_ANGLE_FOURCHE_LIMIT_SWITCH_BAS = true;
constexpr uint8_t ANGLE_FOURCHE_LIMIT_SWITCH_BAS = CRC_DIG_4;

// La vitesse d'accélération de la rotation
constexpr float ANGLE_FOURCHE_ACCELERATION = 500.0f;
// Lorsqu'on commence à appuyer sur la touche de rotation, la vitesse à laquelle la rotation commence
constexpr float ANGLE_FOURCHE_ACCELERATION_INITIALE = 150.0f;
constexpr int8_t ANGLE_FOURCHE_VITESSE_MIN = -128;
constexpr int8_t ANGLE_FOURCHE_VITESSE_MAX = 127;

// Contrôles de l'ouverture des fourches.
// METTRE LES VALEURS « ACTIVER » À FALSE SI LES LIMIT
// SWITCH NE SONT PAS BRANCHÉES OU NON FONCTIONNELLES.
constexpr uint8_t OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_9;
constexpr uint8_t OUVERTURE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_10;
constexpr bool ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN = true;
constexpr uint8_t OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN = CRC_DIG_1;
constexpr bool ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX = true;
constexpr uint8_t OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX = CRC_DIG_2;

// La vitesse d'accélération de l'ouverture
constexpr float OUVERTURE_FOURCHE_ACCELERATION = 64.0f;
// Lorsqu'on commence à appuyer sur la touche d'ouverture, la vitesse à laquelle l'ouverture commence
constexpr float OUVERTURE_FOURCHE_ACCELERATION_INITIALE = 8.0f;
constexpr int8_t OUVERTURE_FOURCHE_VITESSE_MIN = -128;
constexpr int8_t OUVERTURE_FOURCHE_VITESSE_MAX = 127;

#endif // CONFIG_HPP
