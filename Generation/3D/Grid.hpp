#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <unordered_map>

/**
 * Représente une grille 3D.
 */
class Grid {
public:
    Grid();

    /**
     * Modifie la valeur d'une case.
     * @param
     *   x La coordonnée x dans le graphe
     *   y La coordonnée y dans le graphe
     *   z La coordonnée z dans le graphe
     *   type La nouvelle valeur de la case
     */
    void set(long type, long x, long y, long z);
    void set(long type, std::tuple<long, long, long> p);
    /**
     * Renvoie la valeur d'une case.
     * @param
     *   x La coordonnée x dans le graphe
     *   y La coordonnée y dans le graphe
     *   z La coordonnée z dans le graphe
     *   type La nouvelle valeur de la case
     */
    long get(long x, long y, long z);
    long get(std::tuple<long, long, long> p);
    /**
     * Fusionne une grille avec la grille courante.
     * @param
     *   x La coordonnée x dans le graphe où on ajoute la grille
     *   y La coordonnée y dans le graphe où on ajoute la grille
     *   z La coordonnée z dans le graphe où on ajoute la grille
     *   g La grille à fusionner
     */
    void add(Grid& g, long x, long y, long z);
    /**
     * Test si l'on peut ajouter la grille à la grille courante sans
     *   modifier une case déjà existante.
     * @param
     *   x La coordonnée x dans le graphe où on ajoute la grille
     *   y La coordonnée y dans le graphe où on ajoute la grille
     *   z La coordonnée z dans le graphe où on ajoute la grille
     *   g La grille à fusionner
     */
    bool canAdd(Grid& g, long x, long y, long z);

    long getOccupiedCellsCount();
    std::unordered_map<long, std::unordered_map<long, std::unordered_map<long, long>>> getMap();

    std::ostream& write(std::ostream& stream);

    static const long EMPTY_CELL = 0;
    static const long BLOCK_CELL = 1;
    static const long DEATH_CELL = 2;
    static const long TURRET_CELL = 3;
    static const long PLATFORM_CELL = 4;
    static const long IN_CELL = 5; // cellule d'entrée dans une zone (invisible)
    static const long OUT_CELL = 6; // cellule de sortie d'une zone (invisible)
    static const long START_CELL = 7;
    static const long FINISH_CELL = 8;
    static const long TRIGGER_CELL = 9;
    static const long DOOR_CELL = 10;
    static const long ESCALADE_CELL = 11;
    static const long GRIDDOOR_CELL = 12;

private:
    //  x -> y -> z -> type
    std::unordered_map<long, std::unordered_map<long, std::unordered_map<long, long>>> mGrid;

    long mMinX;
    long mMaxX;
    long mMinY;
    long mMaxY;
    long mMinZ;
    long mMaxZ;

    long mCellsCount;
};

inline std::ostream& operator<<(std::ostream& stream, Grid& g) {
    return g.write(stream);
}

#endif // GRID_HPP

