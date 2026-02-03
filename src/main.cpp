#include <CrcLib.h>

#include "pin_mappings.hpp"
#include "actions.hpp"

#include "MainController.hpp"

static_assert(sizeof(char) == 1);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 2);
static_assert(sizeof(long) == 4);
static_assert(sizeof(long long) == 8);

static MainController mainController;

static uint32_t microSecs{};

void setup()
{
    CrcLib::Initialize(true);

    CrcLib::InitializePwmOutput(ROUE_AVANT_GAUCHE_PIN, true);
    CrcLib::InitializePwmOutput(ROUE_AVANT_DROITE_PIN);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_GAUCHE_PIN);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_DROITE_PIN, true);
    
    CrcLib::InitializePwmOutput(TRANSLATION_MONTER_PIN);
    CrcLib::InitializePwmOutput(TRANSLATION_DESCENDRE_PIN);
    
    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN);
    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN);

    CrcLib::InitializePwmOutput(OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN);
    CrcLib::InitializePwmOutput(OUVERTURE_FOURCHE_DROITE_SERVO_PIN);

    Serial.begin(9600);
    microSecs = micros();
}

void loop()
{
    CrcLib::Update();
    const uint32_t microSecsPrecedant = microSecs;
    microSecs = micros();
    const uint32_t deltaTime = microSecs - microSecsPrecedant;
    
    if (!CrcLib::IsCommValid())
    {
        Serial.println("Waiting for controller connection...");
        delay(500);
        return;
    }

    const auto actions = Actions::lire(deltaTime);

    mainController.update(actions, deltaTime);
}
