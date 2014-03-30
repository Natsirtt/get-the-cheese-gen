#include "Point.hpp"
#include "Vector.hpp"

#include <iostream>
#include <sstream>
#include <GL/glut.h>

Point::Point() : mX(0.0), mY(0.0), mZ(0.0) {
}

Point::Point(double x, double y, double z) : mX(x), mY(y), mZ(z)  {
}

Point::Point(const Point& p) : mX(p.mX), mY(p.mY), mZ(p.mZ) {
}

double Point::getX() const {
    return mX;
}

double Point::getY() const {
    return mY;
}

double Point::getZ() const {
    return mZ;
}

Point Point::projectOnLine(const Point& p1Line, const Point& p2Line) const {
    Vector p1p2(p2Line.getX() - p1Line.getX(),
                p2Line.getY() - p1Line.getY(),
                p2Line.getZ() - p1Line.getZ());
    Vector p1this(getX() - p1Line.getX(),
                getY() - p1Line.getY(),
                getZ() - p1Line.getZ());

    double size = p1this.scalar(p1p2) / p1p2.norme();
    Vector n = p1p2.normalize();

    Point proj(p1Line.getX() + n.getX() * size,
               p1Line.getY() + n.getY() * size,
               p1Line.getZ() + n.getZ() * size);

    return proj;
}

Point Point::projectOnLine(const Vector& v) const {
    Point p1(0.0, 0.0, 0.0);
    Point p2(v.getX(), v.getY(), v.getZ());
    return projectOnLine(p1, p2);
}

Point Point::projectOnPlan(const Point& p, const Vector& n) const {
    // Vecteur de this vers p
    Vector thisp(p.getX() - getX(),
                p.getY() - getY(),
                p.getZ() - getZ());
    double size = thisp.scalar(n) / n.norme();

    return Point(getX() - n.getX() * size,
                  getY() - n.getY() * size,
                  getZ() - n.getZ() * size);
}

double Point::square_distance(Point& p) {
    double x = (mX - p.getX()) * (mX - p.getX());
    double y = (mY - p.getY()) * (mY - p.getY());
    double z = (mZ - p.getZ()) * (mZ - p.getZ());
    return (x + y + z);
}

Point Point::add(const Point p) {
    return Point(p.mX + mX, p.mY + mY, p.mZ + mZ);
}

Point Point::operator+(const Point p) {
    return Point(p.mX + mX, p.mY + mY, p.mZ + mZ);
}

Point Point::operator+(const Vector v) {
    return Point(v.getX() + mX, v.getY() + mY, v.getZ() + mZ);
}

Point Point::mul(double m) {
    return Point(mX * m, mY * m, mZ * m);
}

Point Point::operator*(double m) {
    return mul(m);
}

Point Point::operator=(const Point p) {
    mX = p.mX;
    mY = p.mY;
    mZ = p.mZ;
    return *this;
}

std::string Point::toString() {
    std::stringstream ss;
    ss << "x : " << mX << ", y : " << mY << ", z : " << mZ;
    return ss.str();
}

void Point::draw() const {
    glBegin(GL_POINTS);
    glVertex3f(getX(), getY(), getZ());
    glEnd();
}

void Point::drawLine(const Point& p) const {
    glBegin(GL_LINES);
    glVertex3f(getX(), getY(), getZ());
    glVertex3f(p.getX(), p.getY(), p.getZ());
    glEnd();
}
