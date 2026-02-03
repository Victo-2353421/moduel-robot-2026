#include "Actions.hpp"

#include "utils.hpp"

struct ControleVitesse {
    int8_t minVitesse = -128;
    int8_t maxVitesse = 127;
    int8_t derniereVitesse = 0;
    const int8_t acceleration = 127;
};

static ControleVitesse controleRotationFourches;
static ControleVitesse controleOuvertureFourches;

struct ControleManette {
    int8_t joystick1x = 0;
    int8_t joystick1y = 0;
    int8_t joystick2x = 0;

    int8_t gachetteGauche = 0;
    int8_t gachetteDroite = 0;

    uint32_t tempsDepuisDernierAppuieA = 0;
    bool a = false;
    uint32_t tempsDepuisDernierAppuieB = 0;
    bool b = false;
    uint32_t tempsDepuisDernierAppuieX = 0;
    bool x = false;
    uint32_t tempsDepuisDernierAppuieY = 0;
    bool y = false;

    void lire(uint32_t deltaTime) {
        joystick1x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_X);
        joystick1y = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK1_Y);
        joystick2x = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);

        const int8_t gachetteGaucheLecture = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_L);
        const int8_t gachetteDroiteLecture = CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_R);
        gachetteGauche = utils::map<int8_t>(gachetteGaucheLecture, -128, 127, 0, 127);
        gachetteDroite = utils::map<int8_t>(gachetteDroiteLecture, -128, 127, 0, 127);
        
        a = CrcLib::ReadDigitalChannel(BUTTON::COLORS_DOWN);
        if(a)
            tempsDepuisDernierAppuieA += deltaTime;
        else
            tempsDepuisDernierAppuieA = 0;

        b = CrcLib::ReadDigitalChannel(BUTTON::COLORS_RIGHT);
        if(b)
            tempsDepuisDernierAppuieB += deltaTime;
        else
            tempsDepuisDernierAppuieB = 0;

        x = CrcLib::ReadDigitalChannel(BUTTON::COLORS_LEFT);
        if(x)
            tempsDepuisDernierAppuieX += deltaTime;
        else
            tempsDepuisDernierAppuieX = 0;

        y = CrcLib::ReadDigitalChannel(BUTTON::COLORS_UP);
        if(y)
            tempsDepuisDernierAppuieY += deltaTime;
        else
            tempsDepuisDernierAppuieY = 0;
    }

    void print() {
        Serial.print("joystick1x : ");
        Serial.println(joystick1x);
        Serial.print("joystick1y : ");
        Serial.println(joystick1y);
        Serial.print("joystick2x : ");
        Serial.println(joystick2x);
        
        Serial.print("gachetteGauche : ");
        Serial.println(gachetteGauche);
        Serial.print("gachetteDroite : ");
        Serial.println(gachetteDroite);

        Serial.print("A : ");
        if(tempsDepuisDernierAppuieA) Serial.println(tempsDepuisDernierAppuieA);
        Serial.print("B : ");
        if(tempsDepuisDernierAppuieB) Serial.println(tempsDepuisDernierAppuieB);
        Serial.print("X : ");
        if(tempsDepuisDernierAppuieX) Serial.println(tempsDepuisDernierAppuieX);
        Serial.print("Y : ");
        if(tempsDepuisDernierAppuieY) Serial.println(tempsDepuisDernierAppuieY);

        Serial.println("");
    }
};

Actions Actions::lire(uint32_t deltaTime)
{
    static ControleManette controleManette;
    controleManette.lire(deltaTime);
    Actions actions;

    actions.avant = controleManette.joystick1y;
    actions.yaw = controleManette.joystick1x;
    actions.strafe = controleManette.joystick2x;
    
    actions.translation = utils::conversionClamp<int16_t, int8_t>(
        controleManette.gachetteDroite - controleManette.gachetteGauche,
        -128,
        127
    );

    if(controleManette.x && !controleManette.a) {
        actions.rotationFourches = utils::conversionClamp<uint32_t, int8_t>(
            (controleManette.tempsDepuisDernierAppuieX / utils::MICROSECONDES_PAR_SECONDE) * controleRotationFourches.acceleration,
            controleRotationFourches.minVitesse,
            controleRotationFourches.maxVitesse
        );
    } else if(!controleManette.x && controleManette.a) {
        actions.rotationFourches = utils::conversionClamp<uint32_t, int8_t>(
            -(controleManette.tempsDepuisDernierAppuieA / utils::MICROSECONDES_PAR_SECONDE) * controleRotationFourches.acceleration,
            controleRotationFourches.minVitesse,
            controleRotationFourches.maxVitesse
        );
    } else {
        actions.rotationFourches = 0;
    }
    
    if(controleManette.b && !controleManette.y) {
        actions.ouvertureFourches = utils::conversionClamp<uint32_t, int8_t>(
            (controleManette.tempsDepuisDernierAppuieB / utils::MICROSECONDES_PAR_SECONDE) * controleOuvertureFourches.acceleration,
            controleOuvertureFourches.minVitesse,
            controleOuvertureFourches.maxVitesse
        );
    } else if(!controleManette.b && controleManette.y) {
        actions.ouvertureFourches = utils::conversionClamp<uint32_t, int8_t>(
            -(controleManette.tempsDepuisDernierAppuieY / utils::MICROSECONDES_PAR_SECONDE) * controleOuvertureFourches.acceleration,
            controleOuvertureFourches.minVitesse,
            controleOuvertureFourches.maxVitesse
        );
    } else {
        actions.ouvertureFourches = 0;
    }

    return actions;
}

void Actions::print() {
    Serial.print("avant             : ");
    Serial.println(avant);
    Serial.print("yaw               : ");
    Serial.println(yaw);
    Serial.print("strafe            : ");
    Serial.println(strafe);
    
    Serial.print("translation       : ");
    Serial.println(translation);

    Serial.print("rotationFourches  : ");
    Serial.println(rotationFourches);

    Serial.print("ouvertureFourches : ");
    Serial.println(ouvertureFourches);

    Serial.println("");
}