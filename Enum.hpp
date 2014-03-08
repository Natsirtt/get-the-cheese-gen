#ifndef ENUM_HPP
#define ENUM_HPP

enum class Perso {
    /**
     * Saut en longueur
     * Saut en hauteur
     * Escalade
     */
    Acrobate = 1,
    /**
     * Grappin
     * Lancé de projectiles
     */
    Gadget = 2,
    /**
     * Cours vite
     * Faufilage
     * Wall Parkour
     * Glissade
     */
    Yamakasi = 4,
    /**
     * Courte échelle
     * Lancer de personnage
     */
    Costaud = 8,
    /**
     * Les Différentes combinaisons
     */
    AcGa = 3,
    AcYa = 5,
    AcCo = 9,
    AcGaYa = 7,
    All = 15,
    AcGaCo = 11,
    AcYaCo = 13,
    GaYa = 6,
    GaCo = 10,
    GaYaCo = 14,
    YaCo = 12,
    // Pour les tests
    None = 0
};

inline Perso operator&(Perso p1, Perso p2) {
    unsigned int pi1 = (unsigned int) p1;
    unsigned int pi2 = (unsigned int) p2;
    return (Perso) (pi1 & pi2);
}
inline Perso operator|(Perso p1, Perso p2) {
    unsigned int pi1 = (unsigned int) p1;
    unsigned int pi2 = (unsigned int) p2;
    return (Perso) (pi1 | pi2);
}

enum class NodeType {
    Start,
    Finish,
    Room,
    Empty
};

using Id = unsigned int;

#define ID_ERROR 0
#define FIRST_NODE 1

#endif // ENUM_HPP

