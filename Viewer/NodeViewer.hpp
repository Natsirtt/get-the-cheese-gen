#ifndef NODEVIEWER_HPP
#define NODEVIEWER_HPP

#include "Shape.hpp"
#include "../Enum.hpp"

class GraphViewer;

class NodeViewer : public Shape {
public:
    NodeViewer(GraphViewer* gw, Id nid);
    void update(int dt);
    void draw();

    void setSize(int size);

    bool isInside(Vector p);

private:
    GraphViewer* mGraphViewer;
    Id mId;

    int mNodeSize;
};

#endif // NODEVIEWER_HPP

