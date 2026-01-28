#include <CrcLib.h>

#include "pin_mappings.h"

#include "controllers/MainController/main_controller.h"

static_assert(sizeof(char) == 1);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 2);
static_assert(sizeof(long) == 4);
static_assert(sizeof(long long) == 8);

MainController mainController;

static uint32_t microSecs{};

void setup()
{
    CrcLib::Initialize(true);

    CrcLib::InitializePwmOutput(ROUE_AVANT_GAUCHE_PIN, true);
    CrcLib::InitializePwmOutput(ROUE_AVANT_DROITE_PIN);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_GAUCHE_PIN);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_DROITE_PIN, true);
    
    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN);
    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN);

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

    mainController.update(actions, deltaTime);
}
