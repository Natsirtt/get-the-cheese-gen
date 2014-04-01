#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "../../Utils/Tuple.hpp"
#include <vector>
#include <map>

class Grid;

/**
 * Permet de trouver un chemin dans une grille.
 */
class Pathfinding {
public:
    using Cell = std::tuple<long, long, long>;

    Pathfinding(Grid* grid);
    /**
     * Renvoie un chemin entre start et end.
     * NOTE : renvoie une exception si aucun chemin n'est trouv�.
     */
    std::vector<Cell> getPath(Cell start, Cell end);

private:
    struct Node {
        long cout_g; // Le cout pour aller du d�part � this
        long cout_h; // Le cout pour aller de this � l'arriv�e
        long cout_f; // La somme de cout_g et cout_h
        Cell parent; // Le parent de ce noeud
    };

    Cell getBestNode();

    /**
     * Renvoie la distance entre 2 case de la grille.
     * Note : On utilise la distance de Manhattan.
     */
    long distance(Cell c1, Cell c2);
    /**
     * Test si un noeud est d�j� pr�sent dans une map.
     */
    bool isInside(std::map<Cell, Node>& nodeMap, Cell cell);
    /**
     *
     */
    void addNeighbors(Cell cell);
    /**
     * Transf�re un noeud de la liste ouverte � la liste ferm�e.
     */
    void addToClosedMap(Cell cell);

    std::vector<Cell> getPathFromClosedMap();

    // ATTRIBUTS

    Grid* mGrid;
    std::map<Cell, Node> mOpenedNodes;
    std::map<Cell, Node> mClosedNodes;
    Cell mStart;
    Cell mEnd;
};

#endif // PATHFINDING_HPP

