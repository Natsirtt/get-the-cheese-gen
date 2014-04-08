#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>

class Vector {
    public:
        Vector();
        Vector(double x, double y, double z);
        Vector(const Vector& v);

        double getX() const;
        double getY() const;
        double getZ() const;

        double norme() const;
        Vector normalize();
        double scalar(const Vector& v);
        Vector vectoriel(const Vector& v);
        double angle(const Vector& v);

        Vector neg();

        Vector add(const Vector v);
        Vector operator+(const Vector v);
        Vector mul(double m);
        Vector operator*(double m);
        bool operator==(const Vector v);
        bool operator!=(const Vector v);
        bool operator<(const Vector v);
        bool operator>(const Vector v);
        bool operator<=(const Vector v);
        bool operator>=(const Vector v);

        std::string toString();

        double distance(Vector v);

    private:
        double mX;
        double mY;
        double mZ;
};

inline Vector operator*(double m, Vector v) {
    return v.mul(m);
}

#endif // VECTOR_HPP

