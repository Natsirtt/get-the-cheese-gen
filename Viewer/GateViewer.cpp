#include "GateViewer.hpp"

#include "../IGraph.hpp"
#include "../IGate.hpp"

#include <stdexcept>
#include <sstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

GateViewer::GateViewer(IGraph* graph, Id nid) : mGraph{graph}, mId{nid}, mNodeSize{20} {
    if (!graph->isValidNode(nid)) {
        throw std::runtime_error("GateViewer : nid invalide");
    }
}

void GateViewer::update(int dt) {

}

void GateViewer::draw() {
    glPointSize(mNodeSize);

    IGate* g = mGraph->getGate(mId);
    INode* n1 = mGraph->getNode(g->getFirstNode());
    INode* n2 = mGraph->getNode(g->getSecondNode());

    Vector v = getPosition();
    glBegin(GL_QUADS);
    glVertex2d(v.getX() - mNodeSize / 2, v.getY() + mNodeSize / 2);
    glVertex2d(v.getX() - mNodeSize / 2, v.getY() - mNodeSize / 2);
    glVertex2d(v.getX() + mNodeSize / 2, v.getY() - mNodeSize / 2);
    glVertex2d(v.getX() + mNodeSize / 2, v.getY() + mNodeSize / 2);
    glEnd();

    std::stringstream ss;
    ss << "Gate" << mId;
    std::string s = ss.str();
    glRasterPos2f(v.getX(), v.getY() + 10);
    for (unsigned j = 0; j < s.size(); ++j) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
    }
}

void GateViewer::setSize(int size) {
    mNodeSize = size;
}

bool GateViewer::isInside(Vector p) {
    Vector pos = getPosition();
    Vector ph(p.getX(), pos.getY(), 0.0);
    Vector pv(pos.getX(), p.getY(), 0.0);

    double dx = pos.distance(ph);
    double dy = pos.distance(pv);
    return (dx < mNodeSize / 2) && (dy < mNodeSize / 2);
}
