#ifndef BOX_HPP
#define BOX_HPP

#include <vector>
#include "Point.hpp"

class Box {
public:
    Box(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
    std::vector<Box> divide();

    void draw();

    Point getMinCorner();
    Point getMaxCorner();

    void update(Box b);

    std::vector<Point> getPoints();

private:
    double mXMin;
    double mXMax;
    double mYMin;
    double mYMax;
    double mZMin;
    double mZMax;
};

#endif // BOX_HPP

