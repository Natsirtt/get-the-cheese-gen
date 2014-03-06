#ifndef GATEVIEWER_HPP
#define GATEVIEWER_HPP

#include "Shape.hpp"
#include "../Enum.hpp"

class GraphViewer;

class GateViewer : public Shape {
public:
    GateViewer(GraphViewer* gw, Id gid);
    void update(int dt);
    void draw();

    void setSize(int size);

    bool isInside(Vector p);

private:
    void drawArrow(Vector p1, Vector p2);

    GraphViewer* mGraphViewer;
    Id mId;

    int mNodeSize;
};

#endif // NODEVIEWER_HPP

