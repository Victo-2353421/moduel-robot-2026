#include "Actions.hpp"

#include "utils.hpp"

struct ControleVitesse {
    int8_t minVitesse;
    int8_t maxVitesse;
    float acceleration;
    float debutAcceleration;

    constexpr ControleVitesse(
        int8_t minVitesse,
        int8_t maxVitesse,
        float acceleration,
        float debutAcceleration
    )
      : minVitesse(minVitesse)
      , maxVitesse(maxVitesse)
      , acceleration(acceleration)
      , debutAcceleration(debutAcceleration) {}

    int8_t obtenirVitesse(US tempsAppuie) const{
        const float valeur =
            ceilf(static_cast<float>(tempsAppuie) / static_cast<float>(utils::MICROSECONDES_PAR_SECONDE))
            * acceleration + debutAcceleration;
        return utils::conversionClamp<float, int8_t>(
            valeur,
            minVitesse,
            maxVitesse
        );
    }

    int8_t obtenirDelta(US tempsAppuie, US deltaTime) const{
        if (0 < tempsAppuie)
            return 1;
        else
            return 0;
        /*
        const float valeur =
            (static_cast<float>(tempsAppuie) / static_cast<float>(utils::MICROSECONDES_PAR_SECONDE) * acceleration + debutAcceleration)
            * (static_cast<float>(deltaTime) / static_cast<float>(utils::MICROSECONDES_PAR_SECONDE));
        return utils::conversionClamp<float, int8_t>(
            valeur,
            minVitesse,
            maxVitesse
        );
        */
    }
};

constexpr static ControleVitesse controleRotationFourches{
    ANGLE_FOURCHE_VITESSE_MIN,
    ANGLE_FOURCHE_VITESSE_MAX,
    ANGLE_FOURCHE_ACCELERATION,
    ANGLE_FOURCHE_ACCELERATION_INITIALE,
};
constexpr static ControleVitesse controleOuvertureFourches{
    OUVERTURE_FOURCHE_VITESSE_MIN,
    OUVERTURE_FOURCHE_VITESSE_MAX,
    OUVERTURE_FOURCHE_ACCELERATION,
    OUVERTURE_FOURCHE_ACCELERATION_INITIALE,
};

/**
 * Cette struct représente l'état de la manette pour une itération de la boucle
 * `loop` principale du programme.
 */
struct ControleManette {
    int8_t joystick1x = 0;
    int8_t joystick1y = 0;
    int8_t joystick2x = 0;

    int8_t gachetteGauche = 0;
    int8_t gachetteDroite = 0;

    US tempsDepuisDernierAppuieA = 0;
    bool a = false;
    US tempsDepuisDernierAppuieB = 0;
    bool b = false;
    US tempsDepuisDernierAppuieX = 0;
    bool x = false;
    US tempsDepuisDernierAppuieY = 0;
    bool y = false;

    bool start = false;

    /**
     * Lire l'état de la manette.
     */
    void lire(US deltaTime) {
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

        start = CrcLib::ReadDigitalChannel(BUTTON::START);
    }

    void print() const{
        SERIAL_PRINT("joystick1x : ");
        SERIAL_PRINTLN(joystick1x);
        SERIAL_PRINT("joystick1y : ");
        SERIAL_PRINTLN(joystick1y);
        SERIAL_PRINT("joystick2x : ");
        SERIAL_PRINTLN(joystick2x);

        SERIAL_PRINT("gachetteGauche : ");
        SERIAL_PRINTLN(gachetteGauche);
        SERIAL_PRINT("gachetteDroite : ");
        SERIAL_PRINTLN(gachetteDroite);

        if(tempsDepuisDernierAppuieA) {
            SERIAL_PRINT("A : ");
            SERIAL_PRINTLN(tempsDepuisDernierAppuieA);
        }
        if(tempsDepuisDernierAppuieB) {
            SERIAL_PRINT("B : ");
            SERIAL_PRINTLN(tempsDepuisDernierAppuieB);
        }
        if(tempsDepuisDernierAppuieX) {
            SERIAL_PRINT("X : ");
            SERIAL_PRINTLN(tempsDepuisDernierAppuieX);
        }
        if(tempsDepuisDernierAppuieY) {
            SERIAL_PRINT("Y : ");
            SERIAL_PRINTLN(tempsDepuisDernierAppuieY);
        }

        SERIAL_PRINTLN("");
    }
};
static ControleManette controleManette;

Actions Actions::lire(US deltaTime)
{
    controleManette.lire(deltaTime);
    //controleManette.print();
    Actions actions;

    actions.avant = controleManette.joystick1y;
    actions.lacet = controleManette.joystick2x;
    actions.lateral = controleManette.joystick1x;

    actions.translation = utils::conversionClamp<int16_t, int8_t>(
        controleManette.gachetteDroite - controleManette.gachetteGauche,
        -128,
        127
    );

    if(controleManette.a && !controleManette.x) {
        actions.deltaRotationFourches = controleRotationFourches.obtenirDelta(controleManette.tempsDepuisDernierAppuieA, deltaTime);
    } else if(!controleManette.a && controleManette.x) {
        actions.deltaRotationFourches = -controleRotationFourches.obtenirDelta(controleManette.tempsDepuisDernierAppuieX, deltaTime);
    } else {
        actions.deltaRotationFourches = 0;
    }

    if(controleManette.b && !controleManette.y) {
        actions.vitesseOuvertureFourches = controleOuvertureFourches.obtenirVitesse(controleManette.tempsDepuisDernierAppuieB);
    } else if(!controleManette.b && controleManette.y) {
        actions.vitesseOuvertureFourches = -controleOuvertureFourches.obtenirVitesse(controleManette.tempsDepuisDernierAppuieY);
    } else {
        actions.vitesseOuvertureFourches = 0;
    }

    return actions;
}

/**
 * Affiche la struct dans le moniteur de série
 */
void Actions::print() const{
    SERIAL_PRINT("avant             : ");
    SERIAL_PRINTLN(avant);
    SERIAL_PRINT("lacet               : ");
    SERIAL_PRINTLN(lacet);
    SERIAL_PRINT("lateral            : ");
    SERIAL_PRINTLN(lateral);

    SERIAL_PRINT("translation       : ");
    SERIAL_PRINTLN(translation);

    SERIAL_PRINT("deltaRotationFourches  : ");
    SERIAL_PRINTLN(deltaRotationFourches);

    SERIAL_PRINT("vitesseOuvertureFourches : ");
    SERIAL_PRINTLN(vitesseOuvertureFourches);

    SERIAL_PRINTLN("");
}