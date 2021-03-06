#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <unordered_map>
#include <tuple>
#include "../Utils/Vector.hpp"

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
    void set(long type, std::tuple<long, long, long> p);
    /**
     * Renvoie la valeur d'une case.
     * @param
     *   x La coordonn�e x dans le graphe
     *   y La coordonn�e y dans le graphe
     *   z La coordonn�e z dans le graphe
     */
    long get(long x, long y, long z);
    long get(std::tuple<long, long, long> p);
    /**
     * Renvoie la valeur d'une case.
     * @param
     * v le vecteur (x,y,z) des coordonn�es dans le graphe
     */
     long get(Vector v);

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

    long getOccupiedCellsCount();
    std::unordered_map<long, std::unordered_map<long, std::unordered_map<long, long>>>& getMap();

    static bool isPhysicalCell(long t);

    std::ostream& write(std::ostream& stream);

    static const long EMPTY_CELL = 0;
    static const long BLOCK_CELL = 1;
    static const long DEATH_CELL = 2;
    static const long TURRET_CELL = 3;
    static const long PLATFORM_CELL = 4;
    static const long IN_CELL = 5; // cellule d'entr�e dans une zone (invisible)
    static const long OUT_CELL = 6; // cellule de sortie d'une zone (invisible)
    static const long START_CELL = 7;
    static const long FINISH_CELL = 8;
    static const long TRIGGER_CELL = 9;
    static const long DOOR_CELL = 10;
    static const long CLIMB_CELL = 11;
    static const long GRIDDOOR_CELL = 12;
    static const long CRUSHER_CELL = 13;
    static const long GRIDWALL_CELL = 14;
    static const long FULLED_IDLE_CELL = 15; // Cellule r�serv�e
    static const long LASER_X_STICKED_CELL = 16;
    static const long LASER_Y_STICKED_CELL = 17;
    static const long LASER_Z_STICKED_CELL = 18;
    static const long MOVING_X_PLATFORM_CELL = 19;
    static const long MOVING_Y_PLATFORM_CELL = 20;
    static const long STAIRS_XPOS_CELL = 21;
    static const long STAIRS_XNEG_CELL = 22;
    static const long STAIRS_YPOS_CELL = 23;
    static const long STAIRS_YNEG_CELL = 24;
    static const long TRAP_CELL = 25;
    static const long LIGHT_CELL = 26;

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

