#include "Node.hpp"
#include "IGraph.hpp"
#include "IGate.hpp"

Node::Node(IGraph* graph, NodeType type) : mGraph{graph}, mId{0}, mType{type} {
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
    return mGatesMap[p];
}

std::vector<Id> Node::getTransitions() {
    return mGates;
}

void Node::addTransition(Id gid) {
    if (!mGraph->isValidGate(gid)) {
        throw std::runtime_error("Transition invalide");
    }
    mGates.push_back(gid);

    IGate* g = mGraph->getGate(gid);
    Perso persos[] = {Perso::Acrobate, Perso::Gadget,
                    Perso::Yamakasi, Perso::Costaud};
    for (auto p : persos) {
        if (g->canPass(p, 0)) { // TODO remplacer 0 par l'origine
            mGatesMap[p].push_back(gid);
        }
    }
}

NodeType Node::getType() {
    return mType;
}
