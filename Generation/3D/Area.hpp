#ifndef AREA_HPP
#define AREA_HPP

#include "Grid.hpp"
#include <vector>
#include <string>
#include "../Utils/Tuple.hpp"


/**
 * Représentation 3D d'une zone.
 */
class Area {
public:
    Area(bool defaut = true);
    Area(const char* filename);
    Area(std::string filename);
    Area(const Area& a);// = default;
    Area& operator=(const Area& a);// = default;
//    Area(Area&& a) = default;
//    Area& operator=(Area&& a) = default;

    /**
     * Renvoie une cellule d'entrée libre.
     * @return Un tuple contenant les coordonnées x, y, z de la cellule.
     */
    std::tuple<long, long, long> getNextInCell();
    /**
     * Renvoie si il reste des cellule d'entrée dans la zone.
     */
    bool hasInCellLeft();
    /**
     * Renvoie une cellule de sortie libre.
     * @return Un tuple contenant les coordonnées x, y, z de la cellule.
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

    void save(std::string filename);

    void addInCell(std::tuple<long, long, long> in);
    void addOutCell(std::tuple<long, long, long> out);

private:
    void load(std::string filename);

    Grid mGrid;
    unsigned int mCurrentInCell;
    std::vector<std::tuple<long, long, long>> mInCells;
    unsigned int mCurrentOutCell;
    std::vector<std::tuple<long, long, long>> mOutCells;
};

#endif // AREA_HPP

