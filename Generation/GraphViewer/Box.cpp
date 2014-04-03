#include "Box.hpp"
#include <GL/glut.h>

Box::Box(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax) :
        mXMin{xMin}, mXMax{xMax}, mYMin{yMin}, mYMax{yMax}, mZMin{zMin}, mZMax{zMax} {

}

std::vector<Box> Box::divide() {
    std::vector<Box> boxes;

    double xm = (mXMax + mXMin) / 2.0;
    double ym = (mYMax + mYMin) / 2.0;
    double zm = (mZMax + mZMin) / 2.0;

    boxes.push_back({mXMin, xm, mYMin, ym, mZMin, zm});
    boxes.push_back({mXMin, xm, mYMin, ym, zm, mZMax});
    boxes.push_back({mXMin, xm, ym, mYMax, mZMin, zm});
    boxes.push_back({mXMin, xm, ym, mYMax, zm, mZMax});

    boxes.push_back({xm, mXMax, mYMin, ym, mZMin, zm});
    boxes.push_back({xm, mXMax, mYMin, ym, zm, mZMax});
    boxes.push_back({xm, mXMax, ym, mYMax, mZMin, zm});
    boxes.push_back({xm, mXMax, ym, mYMax, zm, mZMax});

    return boxes;
}

void Box::draw() {
    glBegin(GL_QUADS);
    glVertex3d(mXMin, mYMax, mZMax); // Face avant
    glVertex3d(mXMin, mYMin, mZMax);
    glVertex3d(mXMax, mYMin, mZMax);
    glVertex3d(mXMax, mYMax, mZMax);

    glVertex3d(mXMax, mYMax, mZMin); // Face arrière
    glVertex3d(mXMax, mYMin, mZMin);
    glVertex3d(mXMin, mYMin, mZMin);
    glVertex3d(mXMin, mYMax, mZMin);

    glVertex3d(mXMin, mYMax, mZMin); // Face gauche
    glVertex3d(mXMin, mYMin, mZMin);
    glVertex3d(mXMin, mYMin, mZMax);
    glVertex3d(mXMin, mYMax, mZMax);

    glVertex3d(mXMax, mYMax, mZMax); // Face droite
    glVertex3d(mXMax, mYMin, mZMax);
    glVertex3d(mXMax, mYMin, mZMin);
    glVertex3d(mXMax, mYMax, mZMin);

    glVertex3d(mXMin, mYMax, mZMin); // Face supérieure
    glVertex3d(mXMin, mYMax, mZMax);
    glVertex3d(mXMax, mYMax, mZMax);
    glVertex3d(mXMax, mYMax, mZMin);

    glVertex3d(mXMin, mYMin, mZMax); // Face inférieure
    glVertex3d(mXMin, mYMin, mZMin);
    glVertex3d(mXMax, mYMin, mZMin);
    glVertex3d(mXMax, mYMin, mZMax);
    glEnd();
}

Point Box::getMinCorner() {
    return Point(mXMin, mYMin, mZMin);
}
Point Box::getMaxCorner() {
    return Point(mXMax, mYMax, mZMax);
}

std::vector<Point> Box::getPoints() {
    std::vector<Point> points;
    points.push_back({mXMin, mYMin, mZMin});
    points.push_back({mXMin, mYMin, mZMax});
    points.push_back({mXMin, mYMax, mZMin});
    points.push_back({mXMin, mYMax, mZMax});

    points.push_back({mXMax, mYMin, mZMin});
    points.push_back({mXMax, mYMin, mZMax});
    points.push_back({mXMax, mYMax, mZMin});
    points.push_back({mXMax, mYMax, mZMax});

    return points;
}

void Box::update(Box b) {
    Point cMin = b.getMinCorner();
    Point cMax = b.getMaxCorner();

    mXMin = std::min(mXMin, cMin.getX());
    mXMax = std::max(mXMax, cMax.getX());
    mYMin = std::min(mYMin, cMin.getY());
    mYMax = std::max(mYMax, cMax.getY());
    mZMin = std::min(mZMin, cMin.getZ());
    mZMax = std::max(mZMax, cMax.getZ());
}
