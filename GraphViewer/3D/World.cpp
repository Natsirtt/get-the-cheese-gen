#include "World.hpp"

#include "../IGraph.hpp"
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
        std::cout << "essaie " << tryCount << std::endl;
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
            Rand_Int<> rand(1, 20);
            for (unsigned int i = 0; i < mGraph->getNodeCount(); ++i) {
                auto now = std::chrono::high_resolution_clock::now();
                bool added = false;
                int tryCount = 0;
                while ((!added) && (tryCount < 1000)) {
                    x += rand();
                    y += rand();
                    z += rand();
                    added = addNode(i, x, y, z);
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
                    added = addGate(i, x, y, z);
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
                Id agid = mGateArea[gid];

                Id nid1 = gate->getFirstNode();
                Id anid1 = mNodeArea[nid1];
                Id nid2 = gate->getSecondNode();
                Id anid2 = mNodeArea[nid2];

                std::tuple<long, long, long> pos1 = mAreaPos[anid1] + mAreas[anid1].getNextOutCell();
                std::tuple<long, long, long> pos2 = mAreaPos[agid] + mAreas[agid].getNextInCell();
                std::tuple<long, long, long> pos3 = mAreaPos[agid] + mAreas[agid].getNextOutCell();
                std::tuple<long, long, long> pos4 = mAreaPos[anid2] + mAreas[anid2].getNextInCell();

                std::vector<std::tuple<long, long, long>> p = pf.getPath(pos1, pos2);
                for (auto& c : p) {
                    mGrid.set(1, c);
                }
                mPaths.push_back(p);
                p = pf.getPath(pos3, pos4);
                mPaths.push_back(p);
            }
            std::cout << "Fin du pathfinding" << std::endl;
            success = true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Impossible de générer un niveau à partir du graphe.");
        }
        tryCount++;
    }
    if (!success) {
        throw std::runtime_error("Impossible de générer un niveau à partir du graphe: nombre de tentatives atteind");
    } else {
        std::fstream file("temp.g3d", std::fstream::out | std::fstream::trunc);
        file << mGrid;
    }
}

bool World::addNode(Id nid, long x, long y, long z) {
    Area a;
    if (mGrid.canAdd(a.getGrid(), x, y, z)) {
        mGrid.add(a.getGrid(), x, y, z);
        mAreas.push_back(a);
        Id aid = mAreas.size() - 1;
        mNodeArea[nid] = aid;
        mAreaPos[aid] = std::make_tuple(x, y ,z);
        return true;
    }
    return false;
}

bool World::addGate(Id gid, long x, long y, long z) {
    Area a;
    if (mGrid.canAdd(a.getGrid(), x, y, z)) {
        mGrid.add(a.getGrid(), x, y, z);
        mAreas.push_back(a);
        Id aid = mAreas.size() - 1;
        mGateArea[gid] = aid;
        mAreaPos[aid] = std::make_tuple(x, y ,z);
        return true;
    }
    return false;
}
