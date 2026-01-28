#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <CrcLib.h>

struct Actions {
    int8_t avant{};
    int8_t yaw{};
    int8_t strafe{};

    bool rotationFourchesHaut{};
    bool rotationFourchesBas{};

    bool translationFourchesGauche{};
    bool translationFourchesDroite{};

    bool ouvrirFourches{};
    bool fermerFourches{};

    static Actions lire();

    void print();
};

#endif // ACTIONS_HPP
