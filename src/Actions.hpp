#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <CrcLib.h>

struct Actions {
    int8_t avant{};
    int8_t yaw{};
    int8_t strafe{};

    int8_t monter{};
    int8_t descendre{};

    bool rotationFourchesHaut{};
    bool rotationFourchesBas{};

    bool ouvrirFourches{};
    bool fermerFourches{};

    static Actions lire();

    void print();
};

#endif // ACTIONS_HPP
