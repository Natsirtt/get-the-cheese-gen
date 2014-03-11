#include "GraphGenerator.hpp"

#include <iostream>

#include "IGraph.hpp"
#include "ObstacleChooser.hpp"
#include "Utils/Random.hpp"
#include "Node.hpp"
#include "Gate.hpp"

GraphGenerator::GraphGenerator(IGraph* graph) : mGraph{graph}, mFinished{false} {
}

void GraphGenerator::operator()() {
    mFinished = false;
    mCurrentPath.clear();
    mCurrentPath.push_back(1);
    mActivatorsPath.clear();
    mEndPath.clear();
    genGraph_Handler(0, 1, 1, Perso::All);
    addObstacles();
}

bool GraphGenerator::genGraph_Handler(int p, Id lastId, Id lastBranch, Perso perso) {
    do {
        int branch = 0;
        { // Permet de se débarrasser des variables locales inutiles
            double interval[] = {0, 1, 2, 3, 4};
            double first = std::min(p * 0.05, 1.0);
            if (mFinished) {
                first = 0.0;
            }
            double second = std::min((1.0 - first) * p * 0.1, 1.0);
            double weights[] =  {first,
                                second,
                                (1.0 - second) * 0.7,
                                (1.0 - second) * 0.3};
            std::piecewise_constant_distribution<> dist(std::begin(interval),
                                                        std::end(interval),
                                                        std::begin(weights));
            Rand_Int<std::piecewise_constant_distribution<>> rand(dist);
            branch = rand();
        }

        if (branch == 0) { // Fin du level
            Node* node = new Node{mGraph, NodeType::Finish, p + 1};
            node->setOnEndPath(true);
            Id nid = mGraph->addNode(node);
            mCurrentPath.push_back(nid);
            // On le relie au dernier noeud
            IGate* gate = mChooser.chooseWithoutTrigger(mGraph, lastId, nid, perso);
            mGraph->addGate(gate);
            mFinished = true;
            mEndPath = mCurrentPath;
            mCurrentPath.pop_back();
            return true;
        } else if (branch == 1) { // Repliage
            Node* node = new Node{mGraph, NodeType::Activator, p + 1};
            Id nid = mGraph->addNode(node);
            mCurrentPath.push_back(nid);
            // On le relie au dernier noeud
            IGate* gate = mChooser.chooseWithoutTrigger(mGraph, lastId, nid, perso);
            mGraph->addGate(gate);
            // On boucle
            gate = mChooser.chooseWithoutTrigger(mGraph, nid, lastBranch, perso);
            mGraph->addGate(gate);
            mActivatorsPath[nid] = mCurrentPath;
            mCurrentPath.pop_back();
        } else {
            Node* node = new Node{mGraph, NodeType::Room, p + 1};
            Id nid = mGraph->addNode(node);
            mCurrentPath.push_back(nid);
            // On le relie au dernier noeud
            IGate* gate = mChooser.chooseWithoutTrigger(mGraph, lastId, nid, perso);
            mGraph->addGate(gate);
            Id newOldBranch = lastBranch;
            if (branch > 2) {
                newOldBranch = nid;
            }
            bool f = false;
            for (int i = 0; i < branch - 1; ++i) {
                f = f || genGraph_Handler(p + 1, nid, newOldBranch, perso);
            }
            if ((newOldBranch == nid) && (!f)) {
                // On boucle
                IGate* gate = mChooser.chooseWithoutTrigger(mGraph, nid, lastBranch, perso);
                mGraph->addGate(gate);
            }
            if (f) {
                // ATTENTION pas de "return f;"
                node->setOnEndPath(true);
                return true;
            }
            mCurrentPath.pop_back();
        }
    } while ((lastId == 1) && (!mFinished)); // Si on est le noeud de départ et qu'aucun noeud de fin n'à été créé

    return false;
}

void GraphGenerator::addObstacles() {
    Id endNid = mEndPath.back();
    for (auto& it : mActivatorsPath) {
        Id furtherNid = 1;
        for (auto& nid : it.second) {
            INode* node = mGraph->getNode(nid);
            if (!node->isOnEndPath()) {
                break;
            }
            furtherNid = nid;
        }
        INode* trigger = mGraph->getNode(it.first);
        Id rid = furtherNid;
        if (furtherNid < (endNid - 1)) {
            rid = getRandomNodeBetween(furtherNid, endNid);
        }
        // On récupére un noeud aléatoire
        //std::cout << it.first << " " << furtherNid << " " << endNid << " " << rid << std::endl;
        INode* rNode = mGraph->getNode(rid);
        // On récupére une transition aléatoire sortant du noeud
        Id gid = rNode->getTransitions()[0];
        IGate* rGate = mGraph->getGate(gid);
        // On récupére les deux noeuds entre lesquelle on ajoute une porte
        Id first = rGate->getFirstNode();
        INode* n1 = mGraph->getNode(first);
        Id second = rGate->getSecondNode();
        INode* n2 = mGraph->getNode(second);
        // On ajoute un nouveau noed vide
        INode* newNode = new Node(mGraph, NodeType::Empty, n2->getDepth());
        Id newNid = mGraph->addNode(newNode);
        // On ajoute un nouvel obstacle
        IGate* newGate = mChooser.chooseWithoutTrigger(mGraph, first, newNid, Perso::All); // TODO
        Id newGid = mGraph->addGate(newGate);
        // On lie le trigger et l'obstacle
        trigger->linkGate(newGid);
        // On modifie l'ancien obstacle
        rGate->changeFirst(newNid);
    }
}

Id GraphGenerator::getRandomNodeBetween(Id first, Id end) {
    Id next = first;
    for (unsigned int i = 0; i < (mEndPath.size() - 1); ++i) {
        if (mEndPath[i] == first) {
            if (mEndPath[i + 1] == end) {
                return first;
            } else {
                next = mEndPath[i + 1];
                break;
            }
        }
    }
    Rand_Int<> rand(next, end - 1);
    return rand();
}
