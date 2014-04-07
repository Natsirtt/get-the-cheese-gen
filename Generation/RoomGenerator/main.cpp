#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "../3D/Area.hpp"

void genStartRoom();
void genFinishRoom();
void genTriggerRoom();
void genRoom2();
void genRoom3();
void genRoom4();
void genLaser();
void genDoor();
void genTurret();
void genGridDoor();

int main(int argc, char* argv[]) {
    genStartRoom();
    genFinishRoom();
    genTriggerRoom();
    genRoom2();
    genRoom3();
    genRoom4();
    genLaser();
    genDoor();
    genTurret();
    genGridDoor();

    return 0;
}

void genStartRoom() {
    Area a(false);
    int xSize = 3;
    int ySize = 4;
    int zSize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = -zSize / 2; z <= zSize / 2; ++z) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }
    // On positionne la zone de départ
    g.set(Grid::START_CELL, 0, 0, 0);

    a.addOutCell(std::make_tuple(0, 0, -2));

    a.save(std::string("StartRoom.area"));
}

void genFinishRoom() {
    Area a(false);
    int xSize = 3;
    int ySize = 4;
    int zSize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = -zSize / 2; z <= zSize / 2; ++z) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }
    // On positionne la zone de départ
    g.set(Grid::FINISH_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 0, 2));

    a.save(std::string("FinishRoom.area"));
}

void genTriggerRoom() {
    Area a(false);
    int xSize = 3;
    int ySize = 4;
    int zSize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = 0; y < ySize; ++y) {
            for (int z = -zSize / 2; z <= zSize / 2; ++z) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }
    // On positionne la zone de départ
    g.set(Grid::TRIGGER_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 0, 2));
    a.addOutCell(std::make_tuple(0, 0, -2));

    a.save(std::string("TriggerRoom.area"));
}

void genRoom2() {
    Area a(false);
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
    a.addInCell(std::make_tuple( 1, 0, -2));

    a.addOutCell(std::make_tuple(-1, 0, -2));
    a.addOutCell(std::make_tuple( 1, 0, -2));
    a.save(std::string("Room2.area"));
}

void genRoom3() {
    Area a(false);
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
    a.addInCell(std::make_tuple( 1, 0, -2));
    a.addInCell(std::make_tuple(-2, 0, 0));

    a.addOutCell(std::make_tuple(-1, 0, 2));
    a.addOutCell(std::make_tuple( 1, 0, 2));
    a.addOutCell(std::make_tuple( 2, 0, 0));

    a.save(std::string("Room3.area"));
}

void genRoom4() {
    Area a(false);
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
    a.addInCell(std::make_tuple( 1, 0, -2));
    a.addInCell(std::make_tuple(-2, 0,  1));
    a.addInCell(std::make_tuple(-2, 0, -1));

    a.addOutCell(std::make_tuple(-1, 0,  2));
    a.addOutCell(std::make_tuple( 1, 0,  2));
    a.addOutCell(std::make_tuple( 2, 0,  1));
    a.addOutCell(std::make_tuple( 2, 0, -1));

    a.save(std::string("Room4.area"));
}

void genLaser() {
    Area a(false);
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
    a.addInCell(std::make_tuple(0, 0, 5));
    a.addOutCell(std::make_tuple(0, 0, -5));

    a.save(std::string("Laser.area"));
}

void genTurret() {
    Area a(false);
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
    g.set(Grid::TURRET_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 0, 5));
    a.addOutCell(std::make_tuple(0, 0, -5));

    a.save(std::string("Turret.area"));
}

void genDoor() {
    Area a(false);

    a.getGrid().set(Grid::DOOR_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 0, 1));
    a.addOutCell(std::make_tuple(0, 0, -1));

    a.save(std::string("Door.area"));
}

void genGridDoor() {
    Area a(false);

    a.getGrid().set(Grid::GRIDDOOR_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 0, 1));
    a.addOutCell(std::make_tuple(0, 0, -1));

    a.save(std::string("GridDoor.area"));
}
