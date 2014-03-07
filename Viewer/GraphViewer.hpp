#ifndef GRAPHVIEWER_HPP
#define GRAPHVIEWER_HPP

#include <vector>
#include "../Enum.hpp"
#include "Shape.hpp"

class IGraph;
class Shape;
class NodeViewer;

/**
 * Classe permettant de dessiner un graphe.
 */
class GraphViewer {
public:
    GraphViewer(IGraph* graph);
    ~GraphViewer();

    void update(int dt);
    void draw();
    void postEvent(SDL_Event& event);
    IGraph* getGraph();
    NodeViewer* getNodeViewer(Id nid);

private:
    IGraph* mGraph;
    int mNodeSize;

    std::vector<NodeViewer*> mNodes;
    std::vector<Shape*> mShapes;
};

#endif // GRAPHVIEWER_HPP

