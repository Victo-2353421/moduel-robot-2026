#ifndef CONFIG_HPP
#define CONFIG_HPP

/*****************************************************************************/
/* Ce fichier sert de configuration du robot. Modifiez les valeurs de ce     */
/* fichier selon vos besoins.                                                */
/*****************************************************************************/

#include <CrcLib.h>

// numéro de pin.
using Pin = uint8_t;
// microsecondes μs
using US = uint32_t;

// changer ceci de 1 ou 0 afin d'activer/désactiver le moniteur de série.
// Le moniteur de série peut causer beaucoup de latence. C'est utile pour le
// débogage mais ÇA DOIT _ABSOLUMENT_ ÊTRE DÉSACTIVÉ LORS DE LA COMPÉTITION.
#define SERIAL_ENABLE 0

/******************************************/
/*          Contrôles des roues.          */
/******************************************/

constexpr Pin ROUE_AVANT_GAUCHE_PIN = CRC_PWM_1;
constexpr Pin ROUE_AVANT_DROITE_PIN = CRC_PWM_4;
constexpr Pin ROUE_ARRIERE_GAUCHE_PIN = CRC_PWM_2;
constexpr Pin ROUE_ARRIERE_DROITE_PIN = CRC_PWM_3;
constexpr int8_t ROUES_VITESSE_MIN = -128;
constexpr int8_t ROUES_VITESSE_MAX = 90;


/******************************************/
/*    Contrôles pour monter/descendre.    */
/******************************************/

constexpr Pin TRANSLATION_PIN_GAUCHE = CRC_PWM_5;
constexpr Pin TRANSLATION_PIN_DROITE = CRC_PWM_6;
constexpr bool ACTIVER_TRANSLATION_LIMIT_SWITCH_MIN = true;
constexpr Pin TRANSLATION_LIMIT_SWITCH_MIN = CRC_DIG_3;
constexpr bool ACTIVER_TRANSLATION_LIMIT_SWITCH_MAX = true;
constexpr Pin TRANSLATION_LIMIT_SWITCH_MAX = CRC_DIG_4;


/******************************************/
/* Contrôles de la rotation des fourches. */
/******************************************/

// METTRE LES VALEURS « ACTIVER » À FALSE SI LES LIMIT
// SWITCH NE SONT PAS BRANCHÉES OU NON FONCTIONNELLES.
constexpr Pin ANGLE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_7;
constexpr Pin ANGLE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_8;
constexpr int8_t ANGLE_FOURCHE_MINIMAL = -70; // angle de rotation minimale.
constexpr int8_t ANGLE_FOURCHE_MAXIMAL = 70; // angle de rotation maximale.

// La vitesse d'accélération de la rotation
constexpr float ANGLE_FOURCHE_ACCELERATION = 200.0f;
// Lorsqu'on commence à appuyer sur la touche de rotation, la vitesse à laquelle la rotation commence
constexpr float ANGLE_FOURCHE_ACCELERATION_INITIALE = 500.0f;
constexpr int8_t ANGLE_FOURCHE_VITESSE_MIN = -128;
constexpr int8_t ANGLE_FOURCHE_VITESSE_MAX = 127;


/******************************************/
/* Contrôles de l'ouverture des fourches. */
/******************************************/

// METTRE LES VALEURS « ACTIVER » À FALSE SI LES LIMIT
// SWITCH NE SONT PAS BRANCHÉES OU NON FONCTIONNELLES.
constexpr Pin OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN = CRC_PWM_9;
constexpr Pin OUVERTURE_FOURCHE_DROITE_SERVO_PIN = CRC_PWM_10;
constexpr bool ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN = true;
constexpr Pin OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN = CRC_DIG_1;
constexpr bool ACTIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX = true;
constexpr Pin OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX = CRC_DIG_2;
// Signal que les fourches sont accotées à un objet
constexpr bool ATIVER_OUVERTURE_FOURCHE_LIMIT_SWITCH_SIGNAL = true;
constexpr Pin OUVERTURE_FOURCHE_LIMIT_SWITCH_SIGNAL = CRC_DIG_3;

// La vitesse d'accélération de l'ouverture
constexpr float OUVERTURE_FOURCHE_ACCELERATION = 64.0f;
// Lorsqu'on commence à appuyer sur la touche d'ouverture, la vitesse à laquelle l'ouverture commence
constexpr float OUVERTURE_FOURCHE_ACCELERATION_INITIALE = 16.0f;
constexpr int8_t OUVERTURE_FOURCHE_VITESSE_MIN = -128;
constexpr int8_t OUVERTURE_FOURCHE_VITESSE_MAX = 127;


/******************************************/
/*            mapping des DEL             */
/******************************************/
constexpr Pin OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN_DEL = CRC_DIG_7;
constexpr Pin OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX_DEL = CRC_DIG_8;
constexpr Pin OUVERTURE_FOURCHE_LIMIT_SWITCH_SIGNAL_DEL = CRC_DIG_9;
constexpr Pin TRANSLATION_LIMIT_SWITCH_MIN_DEL = CRC_DIG_10;
constexpr Pin TRANSLATION_LIMIT_SWITCH_MAX_DEL = CRC_DIG_11;



#endif // CONFIG_HPP
