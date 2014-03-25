#ifndef AREA_HPP
#define AREA_HPP

#include "Grid.hpp"
#include <vector>
#include "../Utils/Tuple.hpp"
/**
 * Repr�sentation 3D d'une zone.
 */
class Area {
public:
    Area();
    Area(const Area& a) = default;
    Area& operator=(const Area& a) = default;
    Area(Area&& a) = default;
    Area& operator=(Area&& a) = default;

    /**
     * Renvoie une cellule d'entr�e libre.
     * @return Un tuple contenant les coordonn�es x, y, z de la cellule.
     */
    std::tuple<long, long, long> getNextInCell();
    /**
     * Renvoie si il reste des cellule d'entr�e dans la zone.
     */
    bool hasInCellLeft();
    /**
     * Renvoie une cellule de sortie libre.
     * @return Un tuple contenant les coordonn�es x, y, z de la cellule.
     */
    std::tuple<long, long, long> getNextOutCell();
    /**
     * Renvoie si il reste des cellule de sortie dans la zone.
     */
    bool hasOutCellLeft();
    /**
     * Renvoie la grille de la zone.
     */
    Grid& getGrid();

private:
    Grid mGrid;
    unsigned int mCurrentInCell;
    std::vector<std::tuple<long, long, long>> mInCells;
    unsigned int mCurrentOutCell;
    std::vector<std::tuple<long, long, long>> mOutCells;
};

#endif // AREA_HPP

