#include "GraphViewer.hpp"

#include "../IGraph.hpp"
#include "../INode.hpp"
#include "NodeViewer.hpp"
#include "GateViewer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

GraphViewer::GraphViewer(IGraph* graph) : mGraph{graph}, mNodeSize{10} {
    for (unsigned int i = 1; i <= mGraph->getNodeCount(); ++i) {
        mShapes.push_back(new NodeViewer{mGraph, i});
    }
    for (unsigned int i = 1; i <= mGraph->getGateCount(); ++i) {
        mShapes.push_back(new GateViewer{mGraph, i});
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
    for (auto& shape : mShapes) {
        if (shape->postEvent(event)) {
            return;
        }
    }
}
