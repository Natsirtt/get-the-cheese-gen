#include "NodeViewer.hpp"
#include "GraphViewer.hpp"
#include "../IGraph.hpp"
#include "../INode.hpp"

#include <stdexcept>
#include <sstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

NodeViewer::NodeViewer(GraphViewer* gw, Id nid) : mGraphViewer{gw}, mId{nid}, mNodeSize{10} {
    if (!gw->getGraph()->isValidNode(nid)) {
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

    INode* n = mGraphViewer->getGraph()->getNode(mId);

    std::stringstream ss;
    if (n->getType() == NodeType::Start) {
        ss << "Node" << mId << " Start";
    } else if (n->getType() == NodeType::Finish) {
        ss << "Node" << mId << " Finish";
    } else if (n->getType() == NodeType::Room) {
        ss << "Node" << mId << " Room";
    } else {
        ss << "Node" << mId << " Room";
    }

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