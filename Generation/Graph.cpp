#include "Graph.hpp"
#include "Node.hpp"
#include "IGate.hpp"
#include "ObstacleChooser.hpp"

#include <iostream>
#include <stdexcept>
#include <fstream>

Graph::Graph() {
    Node* n = new Node{this, NodeType::Start, 0};
    n->setOnEndPath(true);
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

void Graph::clear() {
    for (auto& n : mNodes) {
        delete n;
        n = nullptr;
    }
    mNodes = std::vector<INode*>();
    for (auto& g : mGates) {
        delete g;
        g = nullptr;
    }
    mGates = std::vector<IGate*>();

    Node* n = new Node{this, NodeType::Start, 0};
    n->setId(mNodes.size() + 1);
    n->setOnEndPath(true);
    mNodes.push_back(n);
}

bool Graph::isValid() {
    // TODO
    return true;
}

INode* Graph::getNode(Id nid) {
    if ((nid <= ID_ERROR) || (nid > mNodes.size())) {
        std::cout << "getNode : nid invalide " << nid << std::endl;
        throw std::runtime_error("getNode : nid invalide");
    }
    return mNodes.at(nid - 1);
}

IGate* Graph::getGate(Id gid) {
    if ((gid <= ID_ERROR) || (gid > mGates.size())) {
        std::cout << mGates.size() << std::endl;
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

void Graph::load(std::string filename) {
    for (auto& n : mNodes) {
        delete n;
        n = nullptr;
    }
    mNodes = std::vector<INode*>();
    for (auto& g : mGates) {
        delete g;
        g = nullptr;
    }
    mGates = std::vector<IGate*>();

    ObstacleChooser chooser;
    std::ifstream file(filename);
    int nodeNb = 0;
    file >> nodeNb;
    for (int i = 0; i < nodeNb; ++i) {
        std::string nodeTypeName;
        file >> nodeTypeName;
        int depth = 0;
        file >> depth;
        int gate = 0;
        file >> gate;
        INode* node = nullptr;
        if (nodeTypeName == "empty") {
            node = new Node(this, NodeType::Empty, depth);
        } else if (nodeTypeName == "room") {
            node = new Node(this, NodeType::Room, depth);
        } else if (nodeTypeName == "start") {
            node = new Node(this, NodeType::Start, depth);
        } else if (nodeTypeName == "finish") {
            node = new Node(this, NodeType::Finish, depth);
        } else if (nodeTypeName == "activator") {
            node = new Node(this, NodeType::Activator, depth);
        }
        node->linkGate(gate);
        addNode(node);
    }
    int gateNb = 0;
    file >> gateNb;
    for (int i = 0; i < gateNb; ++i) {
        std::string gateTypeName;
        file >> gateTypeName;
        int first = 0;
        file >> first;
        int second = 0;
        file >> second;
        IGate* gate = chooser.getGateByName(this, first, second, gateTypeName);
        addGate(gate);
    }
}

void Graph::save(std::string filename) {
    std::ofstream file(filename);
    file << mNodes.size() << "\n";
    for (auto& n : mNodes) {
        NodeType nt = n->getType();
        if (nt == NodeType::Empty) {
            file << "empty";
        } else if (nt == NodeType::Room) {
            file << "room";
        } else if (nt == NodeType::Start) {
            file << "start";
        } else if (nt == NodeType::Finish) {
            file << "finish";
        } else if (nt == NodeType::Activator) {
            file << "activator";
        }
        file << " " << n->getDepth() << " " << n->getLinkedGate() << "\n";
    }
    file << mGates.size() << "\n";
    for (auto& g : mGates) {
        file << g->getName() << " " << g->getFirstNode() << " " << g->getSecondNode() << "\n";
    }
}

