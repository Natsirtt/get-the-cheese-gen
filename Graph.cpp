#include "Graph.hpp"
#include "Node.hpp"
#include "IGate.hpp"

#include <stdexcept>

Graph::Graph() {
    Node* n = new Node{this, NodeType::Start, 0};
    n->setId(mNodes.size() + 1);
    mNodes.push_back(n);
}

Graph::~Graph() {
    for (auto& n : mNodes) {
        delete n;
        n = nullptr;
    }
    for (auto& g : mGates) {
        delete g;
        g = nullptr;
    }
}

bool Graph::isValid() {
    // TODO
    return true;
}

INode* Graph::getNode(Id nid) {
    if ((nid == ID_ERROR) || (nid > mNodes.size())) {
        throw std::runtime_error("getNode : nid invalide");
    }
    return mNodes.at(nid - 1);
}

IGate* Graph::getGate(Id gid) {
    if ((gid == ID_ERROR) || (gid > mGates.size())) {
        throw std::runtime_error("getGate : gid invalide");
    }
    return mGates.at(gid - 1);
}

Id Graph::addNode(INode* node) {
    node->setId(mNodes.size() + 1);
    mNodes.push_back(node);
    return mNodes.size();
}

Id Graph::addGate(IGate* gate) {
    gate->setId(mGates.size() + 1);
    mGates.push_back(gate);

    INode* n1 = getNode(gate->getFirstNode());
    n1->addTransition(mGates.size());
    INode* n2 = getNode(gate->getSecondNode());
    n2->addTransition(mGates.size());
    return mGates.size();
}

bool Graph::isValidNode(Id nid) {
    return (nid != ID_ERROR) && (nid <= mNodes.size());
}

bool Graph::isValidGate(Id gid) {
    return (gid != ID_ERROR) && (gid <= mGates.size());
}

unsigned int Graph::getNodeCount() {
    return mNodes.size();
}
unsigned int Graph::getGateCount() {
    return mGates.size();
}
