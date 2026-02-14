#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <CrcLib.h>
#include "config.hpp"

/**
 * Cette struct représente les actions à effectuer pour une itération de la boucle
 * `loop` du programme. C'est les instructions que Controlleur lit.
 */
struct Actions {
    // Avancement / recul du robot
    int8_t avant{};
    // Rotation du robot https://fr.wikipedia.org/wiki/Lacet_(mouvement)
    int8_t lacet{};
    // Mouvement latéral du robot
    int8_t lateral{};

    // Monter/descendre
    int8_t translation{};

    // Le *delta* de rotation des fourches.
    int8_t deltaRotationFourches{};

    // La *vitesse* de l'ouverture des fourches.
    int8_t vitesseOuvertureFourches{};

    /**
     * Lire l'état de la manette et retourner son Actions correspondant.
     */
    static Actions lire(US deltaTime);

    /**
     * Affiche la struct dans le moniteur de série
     */
    void print() const;
};

#endif // ACTIONS_HPP
