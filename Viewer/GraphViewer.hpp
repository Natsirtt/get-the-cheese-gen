#ifndef GRAPHVIEWER_HPP
#define GRAPHVIEWER_HPP

#include <vector>
#include "Shape.hpp"

class IGraph;
class Shape;

/**
 * Classe permettant de dessiner un graphe.
 */
class GraphViewer {
public:
    GraphViewer(IGraph* graph);

    void update(int dt);
    void draw();
    void postEvent(SDL_Event& event);

private:
    IGraph* mGraph;
    int mNodeSize;

    std::vector<Shape*> mShapes;
};

#endif // GRAPHVIEWER_HPP

