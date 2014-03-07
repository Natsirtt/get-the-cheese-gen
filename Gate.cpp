#include "Gate.hpp"
#include "IGraph.hpp"

#include <stdexcept>

/**
 * Constructeur d'une transition.
 * @param graph Le graphe dans lequel se situe la transition.
 * @param first Le noeud d'origine.
 * @param second Le noeud destination.
 */
Gate::Gate(IGraph* graph, Id first, Id second) : mGraph{graph}, mId{0}, mFirst{first}, mSecond{second} {
    if (!mGraph->isValidNode(first)) {
        throw std::runtime_error("Noeud d'origine invalide");
    }
    if (!mGraph->isValidNode(second)) {
        throw std::runtime_error("Noeud destination invalide");
    }
}

Gate::~Gate() {
}

void Gate::setId(Id gid) {
    mId = gid;
}

Id Gate::getID() {
    return mId;
}

Id Gate::getFirstNode() {
    return mFirst;
}

Id Gate::getSecondNode() {
    return mSecond;
}

Id Gate::getOtherNode(INode n) {
    if ((n.getID() != mFirst) && (n.getID() != mSecond)) {
        throw std::runtime_error("Le noeud n'appartient pas à la transition");
    }
    if (n.getID() == mFirst) {
        return mFirst;
    }
    return mSecond;
}
