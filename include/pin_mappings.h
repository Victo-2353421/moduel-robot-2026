#include <CrcLib.h>

#ifndef PIN_MAPPINGS_H
#define PIN_MAPPINGS_H

// 6 moteurs
// 4 pour les roues
// 2 pour fourches (monter/descendre), 1 contrôle. Elles tournent en sens opposé

// 4 servo
// 2 pour translation (2 tours à peu près)
// 2 pour rotation


/**
 * Connexions des moteurs omnidirectionnels
 */
constexpr uint8_t FRONT_RIGHT_DRIVE_PIN = CRC_PWM_3;
constexpr uint8_t BACK_RIGHT_DRIVE_PIN = CRC_PWM_2;
constexpr uint8_t BACK_LEFT_DRIVE_PIN = CRC_PWM_1;
constexpr uint8_t FRONT_LEFT_DRIVE_PIN = CRC_PWM_4;

constexpr int8_t MAXIMUM_MOVEMENT_SPEED = 90;

//en dessous à changer

/**
 * Connexions du piquet
 */
constexpr uint8_t PIQUET_ROTATOR_SERVO_PIN = CRC_PWM_11;
constexpr uint8_t PIQUET_STOPPER_SERVO_PIN = CRC_PWM_12;

constexpr int32_t PIQUET_IDLE_TARGET_ROTATION = 0;
constexpr int32_t PIQUET_RELOADING_TARGET_ROTATION = 140;
#define PIQUET_SPEED 15
#define PIQUET_MANUAL_ROTATOR_DELAY 1000
#define PIQUET_MANUAL_STOPPER_DELAY 500
#define PIQUET_STOPPER_CLOSING_OFFSET 20

/**
 * Connexions de la pince
 */
constexpr uint8_t PINCE_VERTICAL_DRIVE_PIN = CRC_PWM_5;
constexpr uint8_t PINCE_HORIZONTAL_DRIVE_PIN = CRC_PWM_6;
constexpr uint8_t PINCE_DOIGT_SERVO_1_PIN = CRC_PWM_7;
constexpr uint8_t PINCE_DOIGT_SERVO_2_PIN = CRC_PWM_8;
constexpr uint8_t PINCE_POIGNET_SERVO_PIN = CRC_PWM_9;
constexpr uint8_t PINCE_FLIP_SERVO_PIN = CRC_PWM_10;

constexpr uint8_t PINCE_UPPER_LIMIT_SWITCH_PIN = CRC_DIG_1;
constexpr uint8_t PINCE_LOWER_LIMIT_SWITCH_PIN = CRC_DIG_2;
constexpr uint8_t PINCE_LEFT_LIMIT_SWITCH_PIN = CRC_DIG_9;
constexpr uint8_t PINCE_RIGHT_LIMIT_SWITCH_PIN = CRC_DIG_10;
constexpr uint8_t PINCE_VERTICAL_RELOAD_LIMIT_SWITCH_PIN = CRC_DIG_11;
constexpr uint8_t PINCE_HORIZONTAL_RELOAD_LIMIT_SWITCH_PIN = CRC_DIG_12;

constexpr int32_t PINCE_FLIP_MIN_ANGLE = 0;
constexpr int32_t PINCE_FLIP_IDLE_ANGLE = 80;
constexpr int32_t PINCE_FLIP_MAX_ANGLE = 180;
constexpr uint32_t PINCE_FLIP_MANUAL_DELAY = 1000;
constexpr uint32_t PINCE_FLIP_SPEED = 40;
constexpr uint32_t PINCE_FLIP_DROP_DELAY = 5000;

constexpr int32_t PINCE_DOIGT_IDLE_ANGLE = 45;
constexpr int32_t PINCE_DOIGT_MAX_ANGLE = 180;

constexpr int16_t PINCE_POIGNET_MIN_ANGLE = 0;
constexpr int16_t PINCE_POIGNET_IDLE_ANGLE = 90;
constexpr int16_t PINCE_POIGNET_MAX_ANGLE = 180;
constexpr int16_t PINCE_POIGNET_DEBOUNCE_TIME = 250;

/**
 * Connexions du propulseur
 */
constexpr uint8_t PROPULSEUR_MOTOR_PIN = CRC_DIG_7;

/**
 * Mappings de la manette
 */
constexpr BUTTON CONTROLLER_PINCE_UP_MOVEMENT = BUTTON::ARROW_UP;
constexpr BUTTON CONTROLLER_PINCE_DOWN_MOVEMENT = BUTTON::ARROW_DOWN;
constexpr BUTTON CONTROLLER_PINCE_LEFT_MOVEMENT = BUTTON::ARROW_LEFT;
constexpr BUTTON CONTROLLER_PINCE_RIGHT_MOVEMENT = BUTTON::ARROW_RIGHT;
constexpr ANALOG CONTROLLER_PINCE_POIGNET_LEFT = ANALOG::GACHETTE_L;
constexpr ANALOG CONTROLLER_PINCE_POIGNET_RIGHT = ANALOG::GACHETTE_R;
constexpr BUTTON CONTROLLER_PINCE_MANUAL_FLIP = BUTTON::START;
constexpr BUTTON CONTROLLER_PINCE_DOIGTS = BUTTON::L1;
constexpr BUTTON CONTROLLER_PIQUET_TOGGLE_ROTATOR = BUTTON::COLORS_UP;
constexpr BUTTON CONTROLLER_PIQUET_TOGGLE_STOPPER = BUTTON::COLORS_RIGHT;

constexpr BUTTON SHOOT_KEY = BUTTON::R1;
constexpr BUTTON RELOAD_KEY = BUTTON::COLORS_LEFT;


#endif