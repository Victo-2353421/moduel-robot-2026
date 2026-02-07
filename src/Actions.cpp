#include "Actions.hpp"

#include "utils.hpp"

struct ControleVitesse {
    int8_t minVitesse;
    int8_t maxVitesse;
    int8_t derniereVitesse;
    float acceleration;
    float debutAcceleration;

    constexpr ControleVitesse(
        int8_t minVitesse,
        int8_t maxVitesse,
        int8_t derniereVitesse,
        float acceleration,
        float debutAcceleration
    )
      : minVitesse(minVitesse)
      , maxVitesse(maxVitesse)
      , derniereVitesse(derniereVitesse)
      , acceleration(acceleration)
      , debutAcceleration(debutAcceleration) {}

    int8_t obtenirVitesse(uint32_t tempsAppuie) const{
        return utils::conversionClamp<float, int8_t>(
            ceilf(static_cast<float>(tempsAppuie) / static_cast<float>(utils::MICROSECONDES_PAR_SECONDE))
                * acceleration + debutAcceleration,
            minVitesse,
            maxVitesse
        );
    }
};

constexpr static ControleVitesse controleRotationFourches{
    -128,
    127,
    0,
    1270.0f,
    0.0f,
};
constexpr static ControleVitesse controleOuvertureFourches{
    -128,
    127,
    0,
    64.0f,
    8.0f,
};

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
        if(joystick1y == -1) joystick1y = 0; // correction fucké de la précision.
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

    void print() const{
        PRINT("joystick1x : ");
        PRINTLN(joystick1x);
        PRINT("joystick1y : ");
        PRINTLN(joystick1y);
        PRINT("joystick2x : ");
        PRINTLN(joystick2x);

        PRINT("gachetteGauche : ");
        PRINTLN(gachetteGauche);
        PRINT("gachetteDroite : ");
        PRINTLN(gachetteDroite);

        if(tempsDepuisDernierAppuieA) {
            PRINT("A : ");
            PRINTLN(tempsDepuisDernierAppuieA);
        }
        if(tempsDepuisDernierAppuieB) {
            PRINT("B : ");
            PRINTLN(tempsDepuisDernierAppuieB);
        }
        if(tempsDepuisDernierAppuieX) {
            PRINT("X : ");
            PRINTLN(tempsDepuisDernierAppuieX);
        }
        if(tempsDepuisDernierAppuieY) {
            PRINT("Y : ");
            PRINTLN(tempsDepuisDernierAppuieY);
        }

        PRINTLN("");
    }
};

Actions Actions::lire(uint32_t deltaTime)
{
    static ControleManette controleManette;
    controleManette.lire(deltaTime);
    //controleManette.print();
    Actions actions;

    actions.avant = controleManette.joystick1y;
    actions.yaw = controleManette.joystick2x;
    actions.strafe = controleManette.joystick1x;

    actions.translation = utils::conversionClamp<int16_t, int8_t>(
        controleManette.gachetteDroite - controleManette.gachetteGauche,
        -128,
        127
    );

    if(controleManette.x && !controleManette.a) {
        actions.rotationFourches = controleRotationFourches.obtenirVitesse(controleManette.tempsDepuisDernierAppuieX);
    } else if(!controleManette.x && controleManette.a) {
        actions.rotationFourches = -controleRotationFourches.obtenirVitesse(controleManette.tempsDepuisDernierAppuieA);
    } else {
        actions.rotationFourches = 0;
    }

    if(controleManette.b && !controleManette.y) {
        actions.ouvertureFourches = controleOuvertureFourches.obtenirVitesse(controleManette.tempsDepuisDernierAppuieB);
    } else if(!controleManette.b && controleManette.y) {
        actions.ouvertureFourches = -controleOuvertureFourches.obtenirVitesse(controleManette.tempsDepuisDernierAppuieY);
    } else {
        actions.ouvertureFourches = 0;
    }
    //CrcLib::SetPwmOutput(CRC_PWM_10, actions.ouvertureFourches);

    return actions;
}

void Actions::print() const{
    PRINT("avant             : ");
    PRINTLN(avant);
    PRINT("yaw               : ");
    PRINTLN(yaw);
    PRINT("strafe            : ");
    PRINTLN(strafe);

    PRINT("translation       : ");
    PRINTLN(translation);

    PRINT("rotationFourches  : ");
    PRINTLN(rotationFourches);

    PRINT("ouvertureFourches : ");
    PRINTLN(ouvertureFourches);

    PRINTLN("");
}