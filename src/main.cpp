#include <CrcLib.h>

#include "utils.hpp"
#include "config.hpp"
#include "Actions.hpp"

#include "MainController.hpp"

static_assert(sizeof(char) == 1);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 2);
static_assert(sizeof(long) == 4);
static_assert(sizeof(long long) == 8);

static MainController mainController;

static uint32_t microSecs{};

static volatile int32_t testA = 0;
static volatile int32_t testB = 0;

static void testAfn() {
    if(digitalRead(CRC_SERIAL_TXD1) == HIGH) {
        testA++;
    }
}
static void testBfn() {
    if(digitalRead(CRC_SERIAL_RXD1) == HIGH) {
        testB++;
    }
}
static void testLimitfn(){
}

void setup()
{
    CrcLib::Initialize(true);

    CrcLib::InitializePwmOutput(ROUE_AVANT_GAUCHE_PIN, true);
    CrcLib::InitializePwmOutput(ROUE_AVANT_DROITE_PIN);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_GAUCHE_PIN, true);
    CrcLib::InitializePwmOutput(ROUE_ARRIERE_DROITE_PIN);

    CrcLib::InitializePwmOutput(TRANSLATION_PIN);

    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_GAUCHE_SERVO_PIN);
    CrcLib::InitializePwmOutput(ANGLE_FOURCHE_DROITE_SERVO_PIN);
    CrcLib::SetDigitalPinMode(ANGLE_FOURCHE_LIMIT_SWITCH_HAUT, INPUT_PULLUP);
    CrcLib::SetDigitalPinMode(ANGLE_FOURCHE_LIMIT_SWITCH_BAS, INPUT_PULLUP);

    CrcLib::InitializePwmOutput(OUVERTURE_FOURCHE_GAUCHE_SERVO_PIN);
    CrcLib::InitializePwmOutput(OUVERTURE_FOURCHE_DROITE_SERVO_PIN);
    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN, INPUT_PULLUP);
    CrcLib::SetDigitalPinMode(OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX, INPUT_PULLUP);

    //pinMode(CRC_SERIAL_TXD1, INPUT_PULLUP);
    //pinMode(CRC_SERIAL_RXD1, INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(CRC_SERIAL_TXD1), testAfn, CHANGE);
    //attachInterrupt(digitalPinToInterrupt(CRC_SERIAL_RXD1), testBfn, CHANGE);

    SERIAL_BEGIN();
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
        SERIAL_PRINTLN("Waiting for controller connection...");
        delay(500);
        return;
    }
    
    {
        static uint8_t testVal = 0;
        const auto testTmp = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MIN);
        if(testVal != testTmp) {
            testVal = testTmp;
            SERIAL_PRINT("min : ");
            SERIAL_PRINTLN(testVal);
        }
    }
    {
        static uint8_t testVal = 0;
        const auto testTmp = CrcLib::GetDigitalInput(OUVERTURE_FOURCHE_LIMIT_SWITCH_MAX);
        if(testVal != testTmp) {
            testVal = testTmp;
            SERIAL_PRINT("max : ");
            SERIAL_PRINTLN(testVal);
        }
    }

    const auto actions = Actions::lire(deltaTime);

    mainController.update(actions, deltaTime);
}
