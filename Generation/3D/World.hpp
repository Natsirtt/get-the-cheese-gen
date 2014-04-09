#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Enum.hpp"
#include "Grid.hpp"
#include "Area.hpp"

class IGraph;
class INode;
class IGate;

class World {
public:
    World(IGraph* graph);
    void build();

    Grid *getGrid();
    std::vector<std::vector<std::tuple<long, long, long>>> getPaths();
    std::vector<Area> getAreas();
    std::tuple<long, long, long> getAreaPosition(int areaNb);
private:
    bool addNode(INode* n, long x, long y, long z);
    bool addGate(IGate* g, long x, long y, long z);

    IGraph* mGraph;
    Grid mGrid;

    // Associe à chaque noeud une représentation.
    std::unordered_map<Id, Id> mNodeArea;
    // Associe à chaque obstacle une représentation.
    std::unordered_map<Id, Id> mGateArea;
    // Associe à chaque représentation une position
    std::unordered_map<Id, std::tuple<long, long, long>> mAreaPos;
    // Tableau contenant toutes les représentations.
    std::vector<Area> mAreas;
    // tableau des chemins dans le monde
    std::vector<std::vector<std::tuple<long, long, long>>> mPaths;
};

#endif // WORLD_HPP

