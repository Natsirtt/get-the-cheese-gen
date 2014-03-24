#ifndef GRID_HPP
#define GRID_HPP

#include <map>

/**
 * Repr�sente une grille 3D.
 */
class Grid {
public:
    Grid();

    /**
     * Modifie la valeur d'une case.
     * @param
     *   x La coordonn�e x dans le graphe
     *   y La coordonn�e y dans le graphe
     *   z La coordonn�e z dans le graphe
     *   type La nouvelle valeur de la case
     */
    void set(long type, long x, long y, long z);
    /**
     * Renvoie la valeur d'une case.
     * @param
     *   x La coordonn�e x dans le graphe
     *   y La coordonn�e y dans le graphe
     *   z La coordonn�e z dans le graphe
     *   type La nouvelle valeur de la case
     */
    long get(long x, long y, long z);
    /**
     * Fusionne une grille avec la grille courante.
     * @param
     *   x La coordonn�e x dans le graphe o� on ajoute la grille
     *   y La coordonn�e y dans le graphe o� on ajoute la grille
     *   z La coordonn�e z dans le graphe o� on ajoute la grille
     *   g La grille � fusionner
     */
    void add(Grid& g, long x, long y, long z);
    /**
     * Test si l'on peut ajouter la grille � la grille courante sans
     *   modifier une case d�j� existante.
     * @param
     *   x La coordonn�e x dans le graphe o� on ajoute la grille
     *   y La coordonn�e y dans le graphe o� on ajoute la grille
     *   z La coordonn�e z dans le graphe o� on ajoute la grille
     *   g La grille � fusionner
     */
    bool canAdd(Grid& g, long x, long y, long z);

    static const long EMPTY_CELL = {};

private:
    //  x -> y -> z -> type
    std::map<long, std::map<long, std::map<long, long>>> mGrid;

    long mMinX;
    long mMaxX;
    long mMinY;
    long mMaxY;
    long mMinZ;
    long mMaxZ;
};

#endif // GRID_HPP

