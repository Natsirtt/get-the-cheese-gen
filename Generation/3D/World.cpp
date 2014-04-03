#include "World.hpp"

#include "../IGraph.hpp"
#include "../INode.hpp"
#include "../IGate.hpp"
#include "../Utils/Random.hpp"
#include "Pathfinding.hpp"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <chrono>

World::World(IGraph* graph) : mGraph{graph} {

}

void World::build() {
    int tryCount = 0;
    bool success = false;

    while (!success && (tryCount < 50)) {
        std::cout << "essaie " << tryCount + 1 << std::endl;
        try {
            mGrid = Grid();

            mNodeArea.clear();
            mGateArea.clear();
            mAreaPos.clear();
            mAreas.clear();
            mPaths.clear();

            long x = 0;
            long y = 0;
            long z = 0;
            Rand_Int<> rand(-20, 20);
            Rand_Int<> randY(-5, 5);
            for (unsigned int i = 1; i <= mGraph->getNodeCount(); ++i) {
                auto now = std::chrono::high_resolution_clock::now();
                bool added = false;
                int tryCount = 0;
                INode* node = mGraph->getNode(i);
                while ((!added) && (tryCount < 1000)) {
                    added = addNode(node, x, y, z);
                    x += rand();
                    y += randY();
                    z += rand();
                    tryCount++;
                }
                if (!added) {
                    throw std::runtime_error("World::build -> Impossible d'ajouter un noeud au monde");
                }
                std::chrono::duration<double> dt = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - now);
                std::cout << "Noeud " << i << " ajoute en " << dt.count() << "s" << std::endl;
            }

            for (unsigned int i = 1; i <= mGraph->getGateCount(); ++i) {
                auto now = std::chrono::high_resolution_clock::now();
                bool added = false;
                int tryCount = 0;
                IGate* gate = mGraph->getGate(i);
                Id nid1 = gate->getFirstNode();
                Id aid1 = mNodeArea[nid1];
                std::tuple<long, long, long>& pos1 = mAreaPos[aid1];
                Id nid2 = gate->getSecondNode();
                Id aid2 = mNodeArea[nid2];
                std::tuple<long, long, long>& pos2 = mAreaPos[aid2];
                x = (std::get<0>(pos1) + std::get<0>(pos2)) / 2;
                y = (std::get<1>(pos1) + std::get<1>(pos2)) / 2;
                z = (std::get<2>(pos1) + std::get<2>(pos2)) / 2;

                while ((!added) && (tryCount < 1000)) {
                    added = addGate(gate, x, y, z);
                    x += rand();
                    y += rand();
                    z += rand();
                    tryCount++;
                }
                if (!added) {
                    throw std::runtime_error("World::build -> Impossible d'ajouter un obstacle au monde");
                }
                std::chrono::duration<double> dt = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - now);
                std::cout << "Gate " << i << " ajoute en " << dt.count() << "s" << std::endl;
            }
            std::cout << "Debut du pathfinding" << std::endl;
            Pathfinding pf(&mGrid);

            for (unsigned int gid = 1; gid <= mGraph->getGateCount(); ++gid) {
                std::cout << "Chemin " << gid << "/" << mGraph->getGateCount() << std::endl;
                IGate* gate = mGraph->getGate(gid);
                Id agid = mGateArea.at(gid);
                Id nid1 = gate->getFirstNode();
                Id anid1 = mNodeArea.at(nid1);
                Id nid2 = gate->getSecondNode();
                Id anid2 = mNodeArea.at(nid2);

                std::tuple<long, long, long> pos1 = mAreaPos.at(anid1) + mAreas.at(anid1).getNextOutCell();
                std::tuple<long, long, long> pos2 = mAreaPos.at(agid) + mAreas.at(agid).getNextInCell();
                std::tuple<long, long, long> pos3 = mAreaPos.at(agid) + mAreas.at(agid).getNextOutCell();
                std::tuple<long, long, long> pos4 = mAreaPos.at(anid2) + mAreas.at(anid2).getNextInCell();

                try {
                    std::vector<std::tuple<long, long, long>> p = pf.getPath(pos1, pos2);
                    for (auto& c : p) {
                        mGrid.set(gid + 1, c);
                    }
                    mPaths.push_back(p);
                    p = pf.getPath(pos3, pos4);
                    for (auto& c : p) {
                        mGrid.set(gid + 1, c);
                    }
                    mPaths.push_back(p);
                } catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                    throw std::runtime_error("Erreur lors de la création d'un chemin");
                }
            }
            std::cout << "Fin du pathfinding" << std::endl;
            success = true;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            if (tryCount >= 50) {
                throw std::runtime_error("Impossible de générer un niveau à partir du graphe."); // 1] on ne lance une exception ici que si le nombre d'essais est atteind
            }
        }
        tryCount++;
    }
    if (!success) {
        throw std::runtime_error("Impossible de générer un niveau à partir du graphe: nombre de tentatives atteind"); //Redondant avec 1] ?
    } else {
        std::fstream file("temp.g3d", std::fstream::out | std::fstream::trunc);
        file << mGrid;
    }
}

bool World::addNode(INode* n, long x, long y, long z) {
    Area a = n->getArea();
    if (mGrid.canAdd(a.getGrid(), x, y, z)) {
        mGrid.add(a.getGrid(), x, y, z);
        mAreas.push_back(a);
        Id aid = mAreas.size() - 1;
        mNodeArea[n->getID()] = aid;
        mAreaPos[aid] = std::make_tuple(x, y ,z);
        return true;
    }
    return false;
}

bool World::addGate(IGate* g, long x, long y, long z) {
    Area a = g->getArea();
    if (mGrid.canAdd(a.getGrid(), x, y, z)) {
        mGrid.add(a.getGrid(), x, y, z);
        mAreas.push_back(a);
        Id aid = mAreas.size() - 1;
        mGateArea[g->getID()] = aid;
        mAreaPos[aid] = std::make_tuple(x, y ,z);
        return true;
    }
    return false;
}

Grid *World::getGrid() {
    return &mGrid;
}
