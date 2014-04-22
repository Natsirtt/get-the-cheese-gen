#include "Node.hpp"
#include "IGraph.hpp"
#include "IGate.hpp"

#include "AreaManager.hpp"

Node::Node(IGraph* graph, NodeType type, int depth) : mGraph{graph}, mId{0}, mType{type}, mDepth{depth},
                                                    mIsOnEndPath{false}, mGate{ID_ERROR} {
}

Node::~Node() {

}

void Node::setId(Id nid) {
    mId = nid;
}

Id Node::getID() {
    return mId;
}

std::vector<Id> Node::getTransitions(Perso p) {
    std::vector<Id> trans;
    for (auto& gid : mGates) {
        IGate* g = mGraph->getGate(gid);
        if (g->canPass(p)) {
            trans.push_back(gid);
        }
    }
    return trans;
}

std::vector<Id> Node::getTransitions() {
    return mGates;
}

void Node::addTransition(Id gid) {
    if (!mGraph->isValidGate(gid)) {
        throw std::runtime_error("Transition invalide");
    }
    mGates.push_back(gid);
}

NodeType Node::getType() {
    return mType;
}

int Node::getDepth() {
    return mDepth;
}

void Node::setOnEndPath(bool endPath) {
    mIsOnEndPath = endPath;
}

bool Node::isOnEndPath() {
    return mIsOnEndPath;
}

void Node::deleteGate(Id gate) {
    for (auto it = mGates.begin(); it != mGates.end(); ++it) {
        if (*it == gate) {
            mGates.erase(it);
            break;
        }
    }
}

void Node::changeGate(Id oldGate, Id newGate) {
    for (auto& id : mGates) {
        if (id == oldGate) {
            id = newGate;
        }
    }
}

void Node::linkGate(Id gid) {
    mGate = gid;
}

Id Node::getLinkedGate() {
    return mGate;
}

Area Node::getArea() {
    try {
        int count = mGates.size() / 2;
        if ((mGates.size() % 2) != 0) {
            count++;
        }
        switch (mType) {
        case NodeType::Activator:
            return AreaManager::get().getRandomArea(std::string("TriggerRoom"));
        case NodeType::Start:
            return AreaManager::get().getRandomArea(std::string("StartRoom"));
        case NodeType::Finish:
            return AreaManager::get().getRandomArea(std::string("FinishRoom"));
        case NodeType::Room:
            switch(count) {
            case 1:
                return AreaManager::get().getRandomArea(std::string("Room1"));
            case 2:
                return AreaManager::get().getRandomArea(std::string("Room2"));
            case 3:
                return AreaManager::get().getRandomArea(std::string("Room3"));
            case 4:
                return AreaManager::get().getRandomArea(std::string("Room4"));
            default:
                return Area();
            }
            break;
            default:
                return Area();
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("Erreur lors du chargement de la représentation d'un noeud");
    }

    return Area();
}
