#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "../3D/Area.hpp"

void genStartRoom();
void genFinishRoom();
void genTriggerRoom();
void genRoom1();
void genRoom2();
void genRoom3();
void genRoom4();
void genLaser();
void genDoor();
void genTurret();
void genGridDoor();
void genClimbRoom();

int main(int argc, char* argv[]) {
    genStartRoom();
    genFinishRoom();
    genTriggerRoom();
    genRoom1();
    genRoom2();
    genRoom3();
    genRoom4();
    genLaser();
    genDoor();
    genTurret();
    genGridDoor();
    genClimbRoom();

    std::cout << "Rooms generated" << std::endl;
    return 0;
}

void genStartRoom() {
    Area a(false);
    int xSize = 3;
    int zSize = 4;
    int ySize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }
    // On positionne la zone de départ
    g.set(Grid::START_CELL, 0, 0, 0);

    a.addOutCell(std::make_tuple(0, -2, 0));

    a.save(std::string("StartRoom.area"));
}

void genFinishRoom() {
    Area a(false);
    int xSize = 3;
    int zSize = 4;
    int ySize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }
    // On positionne la zone de départ
    g.set(Grid::FINISH_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 2, 0));

    a.save(std::string("FinishRoom.area"));
}

void genTriggerRoom() {
    Area a(false);
    int xSize = 3;
    int zSize = 4;
    int ySize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }
    // On positionne la zone de départ
    g.set(Grid::TRIGGER_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 2, 0));
    a.addOutCell(std::make_tuple(0, -2, 0));

    a.save(std::string("TriggerRoom.area"));
}

void genRoom1() {
    Area a(false);

    a.getGrid().set(Grid::BLOCK_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 1, 0));
    a.addOutCell(std::make_tuple(0, -1, 0));

    a.save(std::string("Room1.area"));
}


void genRoom2() {
    Area a(false);
    int xSize = 3;
    int zSize = 4;
    int ySize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(-1, 2, 0));
    a.addInCell(std::make_tuple( 1, 2, 0));

    a.addOutCell(std::make_tuple(-1, -2, 0));
    a.addOutCell(std::make_tuple( 1, -2, 0));
    a.save(std::string("Room2.area"));
}

void genRoom3() {
    Area a(false);
    int xSize = 3;
    int zSize = 4;
    int ySize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(-1, -2, 0));
    a.addInCell(std::make_tuple( 1, -2, 0));
    a.addInCell(std::make_tuple(-2, 0, 0));

    a.addOutCell(std::make_tuple(-1, 2, 0));
    a.addOutCell(std::make_tuple( 1, 2, 0));
    a.addOutCell(std::make_tuple( 2, 0, 0));

    a.save(std::string("Room3.area"));
}

void genRoom4() {
    Area a(false);
    int xSize = 3;
    int zSize = 4;
    int ySize = 3;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(-1, -2, 0));
    a.addInCell(std::make_tuple( 1, -2, 0));
    a.addInCell(std::make_tuple(-2, 1,  0));
    a.addInCell(std::make_tuple(-2, -1, 0));

    a.addOutCell(std::make_tuple(-1, 2,  0));
    a.addOutCell(std::make_tuple( 1, 2,  0));
    a.addOutCell(std::make_tuple( 2, 1,  0));
    a.addOutCell(std::make_tuple( 2, -1, 0));

    a.save(std::string("Room4.area"));
}

void genLaser() {
    Area a(false);
    int xSize = 4;
    int zSize = 4;
    int ySize = 4;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(1, x, y, z);
            }
        }
    }
    a.addInCell(std::make_tuple(0, 3, 0));
    a.addOutCell(std::make_tuple(0, -3, 0));

    a.save(std::string("Laser.area"));
}

void genTurret() {
    Area a(false);
    int xSize = 4;
    int ySize = 4;
    int zSize = 4;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(1, x, y, z);
            }
        }
    }
    g.set(Grid::TURRET_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 3, 0));
    a.addOutCell(std::make_tuple(0, -3, 0));

    a.save(std::string("Turret.area"));
}

void genDoor() {
    Area a(false);
    int ySize = 4;
    int zSize = 2;

    Grid& g = a.getGrid();
    for (int z = 0; z < zSize; ++z) {
        for (int y = -ySize / 2; y <= ySize / 2; ++y) {
            //some useless brushes to avoid the door to cross some paths next to the room
            g.set(Grid::FULLED_IDLE_CELL, -2, y, z);
            g.set(Grid::FULLED_IDLE_CELL, -1, y, z);
            g.set(Grid::BLOCK_CELL, 0, y, z);
            g.set(Grid::FULLED_IDLE_CELL, 1, y, z);
            g.set(Grid::FULLED_IDLE_CELL, 2, y, z);
        }
    }

    g.set(Grid::DOOR_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 3, 0));
    a.addOutCell(std::make_tuple(0, -3, 0));

    a.save(std::string("Door.area"));
}

void genGridDoor() {
    Area a(false);

    a.getGrid().set(Grid::GRIDDOOR_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 1, 0));
    a.addOutCell(std::make_tuple(0, -1, 0));

    a.save(std::string("GridDoor.area"));
}

void genClimbRoom() {
    Area a(false);
    int xSize = 5;
    int ySize = 5;
    int zSize = 5;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }

    g.set(Grid::CLIMB_CELL, 0, 1, 0);
    g.set(Grid::CLIMB_CELL, 0, 1, 1);
    g.set(Grid::CLIMB_CELL, 0, 1, 2);
    g.set(Grid::CLIMB_CELL, 0, 2, 0);
    g.set(Grid::CLIMB_CELL, 0, 2, 1);
    g.set(Grid::CLIMB_CELL, 0, 2, 2);
    g.set(Grid::CLIMB_CELL, 0, 3, 0);
    g.set(Grid::CLIMB_CELL, 0, 3, 1);
    g.set(Grid::CLIMB_CELL, 0, 3, 2);

    a.addInCell(std::make_tuple(0, -3, 0));
    a.addOutCell(std::make_tuple(0, 2, 3));

    a.save(std::string("ClimbWall.area"));
}
