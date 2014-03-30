#ifndef POINT_HPP
#define POINT_HPP

#include <string>

class Vector;

class Point {
    public:
        Point();
        Point(double x, double y, double z);
        Point(const Point& p);

        double getX() const;
        double getY() const;
        double getZ() const;

        Point projectOnLine(const Point& p1Line, const Point& p2Line) const;
        Point projectOnLine(const Vector& v) const;
        Point projectOnPlan(const Point& p, const Vector& n) const;

        double square_distance(Point& p);

        Point add(const Point p);
        Point operator+(const Point p);
        Point operator+(const Vector v);

        Point mul(double m);
        Point operator*(double m);

        Point operator=(const Point p);

        std::string toString();

        void draw() const;
        void drawLine(const Point& p) const;

    private:
        double mX;
        double mY;
        double mZ;
};

inline Point operator+(double m, Point p) {
    return p.mul(m);
}

#endif // POINT_HPP
