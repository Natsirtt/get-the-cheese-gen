#include "NodeViewer.hpp"
#include "GateViewer.hpp"
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
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(mNodeSize);

    Vector v = getPosition();

    glBegin(GL_POINTS);
    glVertex2d(v.getX(), v.getY());
    glEnd();

    INode* n = mGraphViewer->getGraph()->getNode(mId);
    Id gid = n->getLinkedGate();
    if (gid != ID_ERROR) {
        glColor3f(0.0, 1.0, 0.0);
        GateViewer* g = mGraphViewer->getGateViewer(gid);
        Vector vg = g->getPosition();
        glBegin(GL_LINES);
        glVertex2d(v.getX(), v.getY());
        glVertex2d(vg.getX(), vg.getY());
        glEnd();
    }

    if (mGraphViewer->isNameVisible()) {
        std::stringstream ss;
        if (n->getType() == NodeType::Start) {
            ss << mId << " Start";
        } else if (n->getType() == NodeType::Finish) {
            ss << mId << " Finish";
        } else if (n->getType() == NodeType::Room) {
            ss << mId << " Room";
        } else if (n->getType() == NodeType::Activator) {
            ss << mId << " Activator";
        }else {
            ss << mId << " Null";
        }
        std::string s = ss.str();
        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2f(v.getX(), v.getY() + 10);
        for (unsigned j = 0; j < s.size(); ++j) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
        }
    }
    glColor3f(1.0, 1.0, 1.0);
}

void NodeViewer::setSize(int size) {
    mNodeSize = size;
}

bool NodeViewer::isInside(Vector p) {
    double d = getPosition().distance(p);
    return d < mNodeSize;
}
