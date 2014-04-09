#include "Vector.hpp"

#include <sstream>
#include <cmath>

Vector::Vector() : mX(0.0), mY(0.0), mZ(0.0) {
}

Vector::Vector(double x, double y, double z) : mX(x), mY(y), mZ(z) {
}

Vector::Vector(const Vector& v) : mX(v.mX), mY(v.mY), mZ(v.mZ) {
}

double Vector::getX() const {
    return mX;
}

double Vector::getY() const {
    return mY;
}

double Vector::getZ() const {
    return mZ;
}

double Vector::norme() const {
    return std::sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
}

Vector Vector::normalize() {
    double n = norme();
    return Vector(mX / n, mY / n, mZ / n);
}

double Vector::scalar(const Vector& v) {
    return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

Vector Vector::vectoriel(const Vector& v) {
    return Vector(mY * v.mZ - mZ * v.mY,
                  mZ * v.mX - mX * v.mZ,
                  mX * v.mY - mY * v.mX);
}

double Vector::angle(const Vector& v) {
    double scal = scalar(v);

    return std::acos(scal / (norme() * v.norme())); // TODO
}

Vector Vector::add(const Vector v) {
    return Vector(v.mX + mX, v.mY + mY, v.mZ + mZ);
}

Vector Vector::sub(const Vector v) {
    return Vector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

Vector Vector::operator+(const Vector v) {
    return add(v);
}

Vector Vector::operator-(const Vector v) {
    return sub(v);
}

Vector Vector::mul(double m) {
    return Vector(mX * m, mY * m, mZ * m);
}

Vector Vector::operator*(double m) {
    return mul(m);
}

Vector Vector::neg() {
    return {-mX, -mY, -mZ};
}

bool Vector::operator==(const Vector v) {
    return (mX == v.mX) && (mY == v.mY) && (mZ == v.mZ);
}

bool Vector::operator!=(const Vector v) {
    return !(this->operator==(v));
}

bool Vector::operator<(const Vector v) {
    return (mX < v.mX) || ((mX == v.mX) && (mY < v.mY)) || (((mX == v.mX) && (mY == v.mY) && (mZ < v.mZ)));
}

bool Vector::operator>(const Vector v) {
    return (mX > v.mX) || ((mX == v.mX) && (mY > v.mY)) || (((mX == v.mX) && (mY == v.mY) && (mZ > v.mZ)));
}

bool Vector::operator<=(const Vector v) {
    return !(this->operator>(v));
}

bool Vector::operator>=(const Vector v) {
    return !(this->operator<(v));
}

double Vector::distance(Vector v) {
    double dx = (mX - v.mX);
    double dy = (mY - v.mY);
    return std::sqrt(dx * dx + dy * dy);
}

std::string Vector::toString() {
    std::stringstream ss;
    ss << "x : " << mX << ", y : " << mY << ", z : " << mZ;
    return ss.str();
}
