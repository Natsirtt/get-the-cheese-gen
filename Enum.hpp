#ifndef ENUM_HPP
#define ENUM_HPP

enum class Perso {
    /**
     * Saut en longueur
     * Saut en hauteur
     * Escalade
     */
    Acrobate,
    /**
     * Grappin
     * Lancé de projectiles
     */
    Gadget,
    /**
     * Cours vite
     * Faufilage
     * Wall Parkour
     * Glissade
     */
    Yamakasi,
    /**
     * Courte échelle
     * Lancer de personnage
     */
    Costaud
};

using Id = unsigned int;

#define ID_ERROR 0
#define FIRST_NODE 1

#endif // ENUM_HPP

