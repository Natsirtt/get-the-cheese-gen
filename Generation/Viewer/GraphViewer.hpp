#ifndef GRAPHVIEWER_HPP
#define GRAPHVIEWER_HPP

#include <vector>
#include "../Enum.hpp"
#include "Shape.hpp"

class IGraph;
class Shape;
class NodeViewer;
class GateViewer;

/**
 * Classe permettant de dessiner un graphe.
 */
class GraphViewer {
public:
    GraphViewer(IGraph* graph);
    ~GraphViewer();
    void clear();
    void reset(IGraph* graph);

    void update(int dt);
    void draw();
    void postEvent(SDL_Event& event);
    IGraph* getGraph();
    NodeViewer* getNodeViewer(Id nid);
    GateViewer* getGateViewer(Id gid);

    bool isNameVisible();

private:
    IGraph* mGraph;
    int mNodeSize;

    std::vector<NodeViewer*> mNodes;
    std::vector<GateViewer*> mGates;
    std::vector<Shape*> mShapes;

    bool mShowNames;
};

#endif // GRAPHVIEWER_HPP

