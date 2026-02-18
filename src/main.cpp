#include <CrcLib.h>

#include "utils.hpp"
#include "config.hpp"
#include "Actions.hpp"

#include "Controlleur.hpp"

static_assert(sizeof(char) == 1);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 2);
static_assert(sizeof(long) == 4);
static_assert(sizeof(long long) == 8);

static Controlleur mainController;

static US microSecs{};

void setup()
{
    CrcLib::Initialize(true);

    CrcLib::InitializePwmOutput(ROUE_AVANT_GAUCHE_PIN, true);
    CrcLib::InitializePwmOutput(ROUE_AVANT_DROITE_PIN);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_GAUCHE_PIN, true);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_DROITE_PIN);

    CrcLib::InitializePwmOutput(TRANSLATION_PIN_GAUCHE, true);
    CrcLib::InitializePwmOutput(TRANSLATION_PIN_DROITE, true);
    CrcLib::SetDigitalPinMode(TRANSLATION_LIMIT_SWITCH_MIN, INPUT_PULLUP);
    CrcLib::SetDigitalPinMode(TRANSLATION_LIMIT_SWITCH_MAX, INPUT_PULLUP);

    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN, true);
    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN);

    CrcLib::InitializePwmOutput(OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN, true);
    CrcLib::InitializePwmOutput(OUVERTURE_FOURCHE_DROITE_SERVO_PIN, true);
    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN, INPUT_PULLUP);
    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX, INPUT_PULLUP);
    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_SIGNAL, INPUT_PULLUP);

    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN_DEL, OUTPUT);
    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX_DEL, OUTPUT);
    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_SIGNAL_DEL, OUTPUT);
    CrcLib::SetDigitalPinMode(TRANSLATION_LIMIT_SWITCH_MIN_DEL, OUTPUT);
    CrcLib::SetDigitalPinMode(TRANSLATION_LIMIT_SWITCH_MAX_DEL, OUTPUT);

    SERIAL_BEGIN();
    microSecs = micros();
}

void loop()
{
    CrcLib::Update();
    const US microSecsPrecedant = microSecs;
    microSecs = micros();
    const US deltaTime = microSecs - microSecsPrecedant;

    if (!CrcLib::IsCommValid())
    {
        SERIAL_PRINTLN("Waiting for controller connection...");
        delay(500);
        return;
    }
    
    {
        static uint8_t testVal = 0;
        const auto testTmp = CrcLib::GetDigitalInput(TRANSLATION_LIMIT_SWITCH_MIN);
        if(testVal != testTmp) {
            testVal = testTmp;
            SERIAL_PRINT("min : ");
            SERIAL_PRINTLN(testVal);
        }
    }
    {
        static uint8_t testVal = 0;
        const auto testTmp = CrcLib::GetDigitalInput(TRANSLATION_LIMIT_SWITCH_MAX);
        if(testVal != testTmp) {
            testVal = testTmp;
            SERIAL_PRINT("max : ");
            SERIAL_PRINTLN(testVal);
        }
    }

    const auto actions = Actions::lire(deltaTime);

    mainController.update(actions, deltaTime);
}
