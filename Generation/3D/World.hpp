#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Enum.hpp"
#include "Grid.hpp"
#include "Area.hpp"

#include <tuple>
#include <vector>
#include <map>

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
    std::map<Id, Id>& getTriggerDoorMap();
private:
    bool addNode(INode* n, long x, long y, long z);
    bool addGate(IGate* g, long x, long y, long z);

    IGraph* mGraph;
    Grid mGrid;

    // Associe � chaque noeud une repr�sentation.
    std::unordered_map<Id, Id> mNodeArea;
    // Associe � chaque obstacle une repr�sentation.
    std::unordered_map<Id, Id> mGateArea;
    // Associe � chaque repr�sentation une position
    std::unordered_map<Id, std::tuple<long, long, long>> mAreaPos;
    // Tableau contenant toutes les repr�sentations.
    std::vector<Area> mAreas;
    // tableau des chemins dans le monde
    std::vector<std::vector<std::tuple<long, long, long>>> mPaths;
    // Association emplacement d'une porte <=> emplacement de son trigger
    std::map<Id, Id> mMapDoorTrigger;
    std::map<Id, Id> mTmpMap;
};

#endif // WORLD_HPP

