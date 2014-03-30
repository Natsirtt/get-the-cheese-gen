#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "3D/Area.hpp"


void genRoom2();
void genRoom3();
void genRoom4();

int main(int argc, char* argv[]) {
    genRoom2();
    genRoom3();
    genRoom4();
    return 0;
}

void genRoom2() {
    Area a;
    int xSize = 3;
    int ySize = 4;
    int zSize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = -zSize / 2; z <= zSize / 2; ++z) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(-1, 0, -2));
    a.addInCell(std::make_tuple(-1, 0, -2));

    a.addOutCell(std::make_tuple(-1, 0, 2));
    a.addOutCell(std::make_tuple(-1, 0, 2));
    a.save(std::string("Room2.area"));
}

void genRoom3() {
    Area a;
    int xSize = 3;
    int ySize = 4;
    int zSize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = -zSize / 2; z <= zSize / 2; ++z) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(-1, 0, -2));
    a.addInCell(std::make_tuple(-1, 0, -2));
    a.addInCell(std::make_tuple(-2, 0, 0));

    a.addOutCell(std::make_tuple(-1, 0, 2));
    a.addOutCell(std::make_tuple(-1, 0, 2));
    a.addOutCell(std::make_tuple(2, 0, 0));

    a.save(std::string("Room3.area"));
}

void genRoom4() {
    Area a;
    int xSize = 3;
    int ySize = 4;
    int zSize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = -zSize / 2; z <= zSize / 2; ++z) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(-1, 0, -2));
    a.addInCell(std::make_tuple(-1, 0, -2));
    a.addInCell(std::make_tuple(-2, 0, 1));
    a.addInCell(std::make_tuple(-2, 0, -1));

    a.addOutCell(std::make_tuple(-1, 0, 2));
    a.addOutCell(std::make_tuple(-1, 0, 2));
    a.addOutCell(std::make_tuple(2, 0, 1));
    a.addOutCell(std::make_tuple(2, 0, -1));

    a.save(std::string("Room4.area"));
}

void genLaser() {
    Area a;
    int xSize = 4;
    int ySize = 4;
    int zSize = 4;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = -zSize / 2; z <= zSize / 2; ++z) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(-1, 0, -2));
    a.addOutCell(std::make_tuple(-1, 0, 2));

    a.save(std::string("Laser.area"));
}
