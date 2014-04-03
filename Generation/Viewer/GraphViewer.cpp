#include "GraphViewer.hpp"

#include "../IGraph.hpp"
#include "../INode.hpp"
#include "NodeViewer.hpp"
#include "GateViewer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <map>

GraphViewer::GraphViewer(IGraph* graph) : mGraph{graph}, mNodeSize{10}, mShowNames{true} {
    reset(graph);
}

GraphViewer::~GraphViewer() {
    clear();
}

void GraphViewer::clear() {
    for (auto& shape : mShapes) {
        delete shape;
        shape = nullptr;
    }
    mGraph = nullptr;

    mNodes = std::vector<NodeViewer*>();
    mGates = std::vector<GateViewer*>();
    mShapes = std::vector<Shape*>();
}

void GraphViewer::reset(IGraph* graph) {
    clear();
    mGraph = graph;
    std::map<int, std::vector<Shape*>> shapeMap;
    int maxDepth = 0;
    for (unsigned int i = 1; i <= mGraph->getNodeCount(); ++i) {
        NodeViewer* nw = new NodeViewer{this, i};
        mShapes.push_back(nw);
        mNodes.push_back(nw);

        INode* n = mGraph->getNode(i);
        shapeMap[n->getDepth()].push_back(nw);
        maxDepth = std::max(maxDepth, n->getDepth());
    }
    const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
    double screenY = videoInfo->current_h - 20;
    double screenX = videoInfo->current_w - 20;
    double yPerDepth = screenY / maxDepth;

    for (auto& it : shapeMap) {
        int depth = it.first;
        std::vector<Shape*>& shapes = it.second;
        for (unsigned int i = 0; i < shapes.size(); ++i) {
            double halfSize = ((double)shapes.size() - 1.0) / 2.0;
            double x = screenX / 2.0 + (screenX) * ((double)i - halfSize) / (double)shapes.size();
            Vector v(x, depth * yPerDepth, 0.0);
            shapes[i]->setPosition(v);
        }
    }

    for (unsigned int i = 1; i <= mGraph->getGateCount(); ++i) {
        GateViewer* gw = new GateViewer{this, i};
        mShapes.push_back(gw);
        mGates.push_back(gw);
    }
}

void GraphViewer::update(int dt) {
    for (auto& shape : mShapes) {
        if (shape != nullptr) {
            shape->update(dt);
        }
    }
}

void GraphViewer::draw() {
    for (auto& shape : mShapes) {
        if (shape != nullptr) {
            shape->draw();
        }
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
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_v) {
            mShowNames = !mShowNames;
        }
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

GateViewer* GraphViewer::getGateViewer(Id gid) {
    try {
        GateViewer* gw = mGates.at(gid - 1);
        return gw;
    } catch (const std::exception& e) {
        std::cout << "getGateViewer : Erreur d'index, size : " << mGates.size()
                    << ", gid : " << gid << std::endl;
        throw e;
    }
    return nullptr;
}

bool GraphViewer::isNameVisible() {
    return mShowNames;
}
