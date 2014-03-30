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

    std::ostream& write(std::ostream& stream);

    static const long EMPTY_CELL = {};

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

