#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Enum.hpp"
#include "Grid.hpp"
#include "Area.hpp"

class IGraph;

class World {
public:
    World(IGraph* graph);

    void build();

private:
    bool addNode(Id nid, long x, long y, long z);
    bool addGate(Id nid, long x, long y, long z);

    IGraph* mGraph;
    Grid mGrid;

    // Associe à chaque noeud une représentation.
    std::map<Id, Id> mNodeArea;
    // Associe à chaque obstacle une représentation.
    std::map<Id, Id> mGateArea;
    // Associe à chaque représentation une position
    std::map<Id, std::tuple<long, long, long>> mAreaPos;
    // Tableau contenant toutes les représentations.
    std::vector<Area> mAreas;
};

#endif // WORLD_HPP

