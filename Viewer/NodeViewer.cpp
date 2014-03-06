#include "NodeViewer.hpp"

#include "../IGraph.hpp"

#include <stdexcept>
#include <sstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

NodeViewer::NodeViewer(IGraph* graph, Id nid) : mGraph{graph}, mId{nid}, mNodeSize{10} {
    if (!graph->isValidNode(nid)) {
        throw std::runtime_error("NodeViewer : nid invalide");
    }
}

void NodeViewer::update(int dt) {

}

void NodeViewer::draw() {
    glPointSize(mNodeSize);

    Vector v = getPosition();

    glBegin(GL_POINTS);
    glVertex2d(v.getX(), v.getY());
    glEnd();
    std::stringstream ss;
    ss << "Node" << mId;
    std::string s = ss.str();
    glRasterPos2f(v.getX(), v.getY() + 10);
    for (unsigned j = 0; j < s.size(); ++j) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
    }
}

void NodeViewer::setSize(int size) {
    mNodeSize = size;
}

bool NodeViewer::isInside(Vector p) {
    double d = getPosition().distance(p);
    return d < mNodeSize;
}
