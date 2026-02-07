#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <CrcLib.h>

struct Actions {
    int8_t avant{};
    int8_t yaw{};
    int8_t strafe{};

    int8_t translation{};

    int8_t rotationFourches{};

    int8_t ouvertureFourches{};

    static Actions lire(uint32_t deltaTime);

    void print() const;
};

#endif // ACTIONS_HPP
