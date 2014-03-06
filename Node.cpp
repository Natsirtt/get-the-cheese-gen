#include "Node.hpp"
#include "IGraph.hpp"
#include "IGate.hpp"

Node::Node(IGraph* graph) : mGraph{graph}, mId{0} {
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
        if (g->canPass(p)) {
            mGatesMap[p].push_back(gid);
        }
    }
}
