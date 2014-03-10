#include "GateViewer.hpp"
#include "NodeViewer.hpp"
#include "GraphViewer.hpp"
#include "../IGraph.hpp"
#include "../IGate.hpp"

#include <stdexcept>
#include <sstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

GateViewer::GateViewer(GraphViewer* gw, Id nid) : mGraphViewer{gw}, mId{nid}, mNodeSize{20} {
    if (!gw->getGraph()->isValidGate(nid)) {
        throw std::runtime_error("GateViewer : nid invalide");
    }
    IGate* g = mGraphViewer->getGraph()->getGate(mId);
    Vector vn1 = mGraphViewer->getNodeViewer(g->getFirstNode())->getPosition();
    Vector vn2 = mGraphViewer->getNodeViewer(g->getSecondNode())->getPosition();
    Vector v = (vn1 + vn2 ) * 0.5;
    setPosition(v);
}

void GateViewer::update(int dt) {

}

void GateViewer::draw() {
    glPointSize(mNodeSize);

    IGate* g = mGraphViewer->getGraph()->getGate(mId);

    Vector vg = getPosition();
    Vector vn1 = mGraphViewer->getNodeViewer(g->getFirstNode())->getPosition();
    Vector vn2 = mGraphViewer->getNodeViewer(g->getSecondNode())->getPosition();

    glBegin(GL_LINES);
    drawArrow(vn1, vg);
    drawArrow(vg, vn2);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(vg.getX() - mNodeSize / 2, vg.getY() + mNodeSize / 2);
    glVertex2d(vg.getX() - mNodeSize / 2, vg.getY() - mNodeSize / 2);
    glVertex2d(vg.getX() + mNodeSize / 2, vg.getY() - mNodeSize / 2);
    glVertex2d(vg.getX() + mNodeSize / 2, vg.getY() + mNodeSize / 2);
    glEnd();

    if (mGraphViewer->isNameVisible()) {
        glColor3f(1.0, 0.0, 0.0);
        std::stringstream ss;
        ss << g->getName() << " " << mId;
        std::string s = ss.str();
        glRasterPos2f(vg.getX(), vg.getY() + 10);
        for (unsigned j = 0; j < s.size(); ++j) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[j]);
        }
    }
    glColor3f(1.0, 1.0, 1.0);
}

void GateViewer::setSize(int size) {
    mNodeSize = 2 * size;
}

bool GateViewer::isInside(Vector p) {
    Vector pos = getPosition();
    Vector ph(p.getX(), pos.getY(), 0.0);
    Vector pv(pos.getX(), p.getY(), 0.0);

    double dx = pos.distance(ph);
    double dy = pos.distance(pv);
    return (dx < mNodeSize / 2) && (dy < mNodeSize / 2);
}

void GateViewer::drawArrow(Vector p1, Vector p2) {
    Vector v = p2 + p1.neg();
    v = v.normalize();

    Vector v0 = p2 + v.neg() * 30;
    Vector v1(v.getY(), -v.getX(), 0.0);
    Vector v2 = v0 + v1.neg() * 10;
    v1 = v0 + v1 * 10;

    glVertex2d(p1.getX(), p1.getY());
    glVertex2d(v0.getX(), v0.getY());

    glVertex2d(v1.getX(), v1.getY());
    glVertex2d(v2.getX(), v2.getY());

    glVertex2d(v1.getX(), v1.getY());
    glVertex2d(p2.getX(), p2.getY());

    glVertex2d(v2.getX(), v2.getY());
    glVertex2d(p2.getX(), p2.getY());
}
