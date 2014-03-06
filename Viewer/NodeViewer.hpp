#ifndef NODEVIEWER_HPP
#define NODEVIEWER_HPP

#include "Shape.hpp"
#include "../Enum.hpp"

class IGraph;

class NodeViewer : public Shape {
public:
    NodeViewer(IGraph* graph, Id nid);
    void update(int dt);
    void draw();

    void setSize(int size);

    bool isInside(Vector p);

private:
    IGraph* mGraph;
    Id mId;

    int mNodeSize;
};

#endif // NODEVIEWER_HPP

