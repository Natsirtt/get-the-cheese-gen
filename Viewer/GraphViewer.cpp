#include "GraphViewer.hpp"

#include "../IGraph.hpp"
#include "../INode.hpp"
#include "NodeViewer.hpp"
#include "GateViewer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

GraphViewer::GraphViewer(IGraph* graph) : mGraph{graph}, mNodeSize{10} {
    for (unsigned int i = 1; i <= mGraph->getNodeCount(); ++i) {
        NodeViewer* nw = new NodeViewer{this, i};
        mShapes.push_back(nw);
        mNodes.push_back(nw);
    }
    for (unsigned int i = 1; i <= mGraph->getGateCount(); ++i) {
        mShapes.push_back(new GateViewer{this, i});
    }
}

void GraphViewer::update(int dt) {
    for (auto& shape : mShapes) {
        shape->update(dt);
    }
}

void GraphViewer::draw() {
    for (auto& shape : mShapes) {
        shape->draw();
    }
}

void GraphViewer::postEvent(SDL_Event& event) {
    if ((event.type == SDL_MOUSEBUTTONUP) &&
        (event.button.button == SDL_BUTTON_WHEELUP)) {
        mNodeSize++;
        for (auto& shape : mShapes) {
            shape->setSize(mNodeSize);
        }
        return;
    } else if ((event.type == SDL_MOUSEBUTTONUP) &&
                (event.button.button == SDL_BUTTON_WHEELDOWN)) {
        mNodeSize = std::max(mNodeSize - 1, 1);
        for (auto& shape : mShapes) {
            shape->setSize(mNodeSize);
        }
        return;
    }
    for (auto& shape : mShapes) {
        if (shape->postEvent(event)) {
            return;
        }
    }
}

IGraph* GraphViewer::getGraph() {
    return mGraph;
}

NodeViewer* GraphViewer::getNodeViewer(Id nid) {
    try {
        NodeViewer* nw = mNodes.at(nid - 1);
        return nw;
    } catch (const std::exception& e) {
        std::cout << "getNodeViewer : Erreur d'index, size : " << mNodes.size()
                    << ", nid : " << nid << std::endl;
        throw e;
    }
    return nullptr;
}
