#include "Node.hpp"
#include "IGraph.hpp"
#include "IGate.hpp"

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
        if (mGates.size() % 2 != 0) {
            count++;
        }
        switch(count) {
        case 1:
            return Area("Area/Room1.area");
            break;
        case 2:
            return Area("Area/Room2.area");
            break;
        case 3:
            return Area("Area/Room3.area");
            break;
        case 4:
            return Area("Area/Room4.area");
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
