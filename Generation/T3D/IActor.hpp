#ifndef IACTOR_HPP
#define IACTOR_HPP

#include <string>
#include <fstream>

#include "../3D/Grid.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"

class IActor {
public:
    virtual ~IActor() {}

    virtual std::string getT3D(int indentLevel, NameFactory *nameFactory) = 0;
    virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition) = 0;
    void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, const long& xGridPos, const long& yGridPos, const long& zGridPos) {
        writeT3D(output, indentLevel, nameFactory, Vector(xGridPos, yGridPos, zGridPos));
    }

protected:
    IActor() : mGrid{nullptr} {}
    IActor(Grid *g) : mGrid{g} {}
    Grid* mGrid;

private:
};

#endif // IACTOR_HPP
