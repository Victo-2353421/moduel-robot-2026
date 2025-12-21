#include "controllers/MainController/main_controller.h"
#include "CrcLib.h"

void Movement();

MainController *mainController = nullptr;

void setup()
{
    CrcLib::Initialize(true);

    // Initialize movement
    CrcLib::InitializePwmOutput(FRONT_RIGHT_DRIVE_PIN);
    CrcLib::InitializePwmOutput(BACK_RIGHT_DRIVE_PIN, true);
    CrcLib::InitializePwmOutput(BACK_LEFT_DRIVE_PIN);
    CrcLib::InitializePwmOutput(FRONT_LEFT_DRIVE_PIN, true);

    // Initialize pince servos
    CrcLib::InitializePwmOutput(PINCE_VERTICAL_DRIVE_PIN);
    CrcLib::InitializePwmOutput(PINCE_HORIZONTAL_DRIVE_PIN, true);
    
    // Initialize limit switches
    CrcLib::SetDigitalPinMode(PINCE_UPPER_LIMIT_SWITCH_PIN, INPUT);
    CrcLib::SetDigitalPinMode(PINCE_LOWER_LIMIT_SWITCH_PIN, INPUT);
    CrcLib::SetDigitalPinMode(PINCE_LEFT_LIMIT_SWITCH_PIN, INPUT);
    CrcLib::SetDigitalPinMode(PINCE_RIGHT_LIMIT_SWITCH_PIN, INPUT);
    CrcLib::SetDigitalPinMode(PINCE_VERTICAL_RELOAD_LIMIT_SWITCH_PIN, INPUT);
    CrcLib::SetDigitalPinMode(PINCE_HORIZONTAL_RELOAD_LIMIT_SWITCH_PIN, INPUT);
    
    // Initialize propulseur
    CrcLib::SetDigitalPinMode(PROPULSEUR_MOTOR_PIN, OUTPUT);
    
    Serial.begin(9600);
    mainController = new MainController();
    mainController->initialize();
}

void loop()
{
    CrcLib::Update();

    if (!CrcLib::IsCommValid())
    {
        Serial.println("Waiting for controller connection...");
        delay(500);
        return;
    }

    mainController->update();
}