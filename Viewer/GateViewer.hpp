#ifndef GATEVIEWER_HPP
#define GATEVIEWER_HPP

#include "Shape.hpp"
#include "../Enum.hpp"

class IGraph;

class GateViewer : public Shape {
public:
    GateViewer(IGraph* graph, Id gid);
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

