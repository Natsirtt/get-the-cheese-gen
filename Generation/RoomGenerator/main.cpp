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
void genRoom2_2();
void genRoom3();
void genRoom4();
void genLaser();
void genLaser2();
void genDoor();
void genTurret();
void genTurret2();
void genGridDoor();
void genClimbRoom();
void genDeathRoom();
void genDeathRoom_2();
void genDeathRoom_3();

int main(int argc, char* argv[]) {
    genStartRoom();
    genFinishRoom();
    genTriggerRoom();
    genRoom1();
    genRoom2();
    genRoom2_2();
    genRoom3();
    genRoom4();
    genLaser();
    genLaser2();
    genDoor();
    genTurret();
    genTurret2();
    genGridDoor();
    genClimbRoom();
    genDeathRoom();
    genDeathRoom_2();
    genDeathRoom_3();

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

    a.save(std::string("Area/StartRoom/StartRoom.area"));
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

    a.save(std::string("Area/FinishRoom/FinishRoom.area"));
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

    a.save(std::string("Area/TriggerRoom/TriggerRoom.area"));
}

void genRoom1() {
    Area a(false);

    a.getGrid().set(Grid::BLOCK_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 1, 0));
    a.addOutCell(std::make_tuple(0, -1, 0));

    a.save(std::string("Area/Room1/Room1.area"));
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
    a.save(std::string("Area/Room2/Room2.area"));
}

void genRoom2_2() {
    Area a(false);
    int xSize = 1;
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
    g.set(Grid::PLATFORM_CELL, 0, 1, 1);
    g.set(Grid::PLATFORM_CELL, 0, -1, 1);

    a.addInCell(std::make_tuple(0, 2, 0));
    a.addInCell(std::make_tuple(0, 2, 2));

    a.addOutCell(std::make_tuple(0, -2, 0));
    a.addOutCell(std::make_tuple(0, -2, 2));
    a.save(std::string("Area/Room2/Room2-2.area"));
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

    a.save(std::string("Area/Room3/Room3.area"));
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

    a.save(std::string("Area/Room4/Room4.area"));
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

    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = -ySize / 2; y <= ySize / 2; ++y) {
            g.set(Grid::LASER_Z_STICKED_CELL, x, y, zSize - 1);
        }
    }

    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        g.set(Grid::LASER_Y_STICKED_CELL, x, -ySize / 2, 0);
        g.set(Grid::LASER_Y_STICKED_CELL, x, ySize / 2, 0);
    }

    for (int y = -ySize / 2; y <= ySize / 2; ++y) {
        g.set(Grid::LASER_X_STICKED_CELL, -xSize / 2, y, 0);
        g.set(Grid::LASER_X_STICKED_CELL, xSize / 2, y, 0);
    }

    a.addInCell(std::make_tuple(0, 3, 0));
    g.set(1, 0, 2, 0);
    a.addOutCell(std::make_tuple(0, -3, 0));
    g.set(1, 0, -2, 0);

    a.save(std::string("Area/LaserRoom/Laser.area"));
}

void genLaser2() {
    Area a(false);
    int xSize = 4;
    int zSize = 6;
    int ySize = 6;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(1, x, y, z);
            }
        }
    }

    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        g.set(Grid::LASER_Y_STICKED_CELL, x, -3, 0);
        g.set(Grid::LASER_Y_STICKED_CELL, x, -3, 1);
        g.set(Grid::LASER_Y_STICKED_CELL, x, -3, 2);
        g.set(Grid::LASER_Y_STICKED_CELL, x, -3, 3);
    }
    for (int y = -ySize / 2; y <= ySize / 2; ++y) {
        g.set(Grid::LASER_X_STICKED_CELL, 2, y, 0);
        g.set(Grid::LASER_X_STICKED_CELL, 2, y, 1);
        g.set(Grid::LASER_X_STICKED_CELL, 2, y, 2);
        g.set(Grid::LASER_X_STICKED_CELL, 2, y, 3);
    }

    g.set(Grid::FULLED_IDLE_CELL, 2, 2, 1);
    for (int x = 0; x <= 2; ++x) {
        for (int y = 1; y <= 3; ++y) {
            g.set(Grid::FULLED_IDLE_CELL, x, y, 0);
            g.set(Grid::LASER_X_STICKED_CELL, -1, y, 0);
        }
        g.set(Grid::LASER_Y_STICKED_CELL, x, 0, 0);
    }

    a.addOutCell(std::make_tuple(3, 2, 2));
    g.set(1, 2, 2, 2);
    a.addInCell(std::make_tuple(0, -4, 0));
    g.set(1, 0, -3, 0);

    a.save(std::string("Area/LaserRoom/Laser2.area"));
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

    a.save(std::string("Area/TurretRoom/Turret.area"));
}

void genTurret2() {
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
    g.set(Grid::TURRET_CELL, xSize / 2, ySize / 2, 0);
    g.set(Grid::TURRET_CELL, -xSize / 2, ySize / 2, 0);
    g.set(Grid::TURRET_CELL, -xSize / 2, -ySize / 2, 0);
    g.set(Grid::TURRET_CELL, xSize / 2, -ySize / 2, 0);

    a.addInCell(std::make_tuple(0, 3, 0));
    a.addOutCell(std::make_tuple(0, -3, 0));

    a.save(std::string("Area/TurretRoom/Turret2.area"));
}

void genDoor() {
    Area a(false);
    int ySize = 4;
    int zSize = 1;

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

    g.set(Grid::LIGHT_CELL, 0, -ySize / 2, 0);
    g.set(Grid::LIGHT_CELL, 0, ySize / 2, 0);

    g.set(Grid::DOOR_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, (ySize / 2) + 1, 0));
    a.addOutCell(std::make_tuple(0, -(ySize / 2) - 1, 0));

    a.save(std::string("Area/DoorRoom/Door.area"));
}

void genGridDoor() {
    Area a(false);

    a.getGrid().set(Grid::GRIDDOOR_CELL, 0, 0, 0);

    a.addInCell(std::make_tuple(0, 1, 0));
    a.addOutCell(std::make_tuple(0, -1, 0));

    a.save(std::string("Area/GridRoom/GridDoor.area"));
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

    a.save(std::string("Area/ClimbRoom/ClimbWall.area"));
}

void genDeathRoom() {
    Area a(false);
    int xSize = 10;
    int ySize = 10;
    int zSize = 5;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                g.set(Grid::BLOCK_CELL, x, y, z);
            }
        }
    }
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int y = -ySize / 2; y <= ySize / 2; ++y) {
            if ((((x % 2) == 0) && ((y % 2) == 0)) ||
                (((x % 2) != 0) && ((y % 2) != 0))) {
                g.set(Grid::DEATH_CELL, x, y, -1);
            }
        }
    }

    a.addInCell(std::make_tuple(0, -6, 0));
    a.addOutCell(std::make_tuple(0, 6, 0));

    a.save(std::string("Area/DeathRoom/DeathRoom.area"));
}


void genDeathRoom_2() {
    Area a(false);
    int xSize = 6;
    int ySize = 6;
    int zSize = 10;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                if (z == 0) {
                    g.set(Grid::DEATH_CELL, x, y, z);
                } else {
                    g.set(Grid::BLOCK_CELL, x, y, z);
                }
            }
        }
    }
    g.set(Grid::LIGHT_CELL, -2, 3, 4);
    g.set(Grid::LIGHT_CELL, 2, -1, 4);
    g.set(Grid::PLATFORM_CELL, -2, 3, 3);
    g.set(Grid::PLATFORM_CELL, -2, -1, 3);
    g.set(Grid::PLATFORM_CELL, 2, -1, 3);
    g.set(Grid::PLATFORM_CELL, 2, 3, 3);

    g.set(Grid::MOVING_Y_PLATFORM_CELL, -2, 1, 3);
    g.set(Grid::MOVING_X_PLATFORM_CELL, 0, -1, 3);
    g.set(Grid::MOVING_Y_PLATFORM_CELL, 2, 1, 3);

    g.set(Grid::LIGHT_CELL, 1, 3, 4);
    g.set(Grid::LIGHT_CELL, -1, 3, 6);
    g.set(Grid::STAIRS_XNEG_CELL, 1, 3, 3);
    g.set(Grid::STAIRS_XNEG_CELL, 0, 3, 4);
    g.set(Grid::STAIRS_XNEG_CELL, -1, 3, 5);

    g.set(Grid::LIGHT_CELL, -2, 1, 7);
    g.set(Grid::LIGHT_CELL, -3, 1, 7);
    g.set(Grid::PLATFORM_CELL, -2, 3, 6);
    g.set(Grid::PLATFORM_CELL, -2, 1, 6);
    g.set(Grid::MOVING_X_PLATFORM_CELL, 0, 1, 6);

    g.set(Grid::LIGHT_CELL, 3, -3, 7);
    g.set(Grid::PLATFORM_CELL, 3, 1, 6);
    g.set(Grid::TRAP_CELL, 3, 0, 5);
    g.set(Grid::TRAP_CELL, 3, -1, 5);
    g.set(Grid::TRAP_CELL, 3, -2, 5);
    g.set(Grid::PLATFORM_CELL, 3, -3, 6);
    g.set(Grid::PLATFORM_CELL, 2, -2, 6);

    g.set(Grid::LIGHT_CELL, -3, -3, 7);
    g.set(Grid::PLATFORM_CELL, -3, -3, 6);
    g.set(Grid::PLATFORM_CELL, -3, -2, 6);
    g.set(Grid::MOVING_X_PLATFORM_CELL, 0, -2, 6);

    a.addInCell(std::make_tuple(-2, 4, 3));
    a.addOutCell(std::make_tuple(-3, -4, 6));

    a.save(std::string("Area/DeathRoom/DeathRoom2.area"));
}

void genDeathRoom_3() {
    Area a(false);
    int xSize = 10;
    int ySize = 10;
    int zSize = 4;

    Grid& g = a.getGrid();
    for (int x = -xSize / 2; x <= xSize / 2; ++x) {
        for (int z = 0; z < zSize; ++z) {
            for (int y = -ySize / 2; y <= ySize / 2; ++y) {
                if (((x == (-(xSize / 2) + 1)) || (x == ((xSize / 2) - 1)) ||
                    (y == (-(ySize / 2) + 1)) || (y == ((ySize / 2) - 1))) && (z == 0)) {
                    g.set(Grid::TRAP_CELL, x, y, z);
                } else if (z == 0) {
                    g.set(Grid::DEATH_CELL, x, y, z);
                } else if ((x >= -xSize / 4) && (x <= xSize / 4) && (y >= -ySize / 4) && (y <= ySize / 4)) {
                    g.set(Grid::EMPTY_CELL, x, y, z);
                } else {
                    g.set(Grid::BLOCK_CELL, x, y, z);
                }
            }
        }
    }

    g.set(Grid::TRAP_CELL, 0, 5, 0);
    a.addInCell(std::make_tuple(0, 6, 1));
    g.set(Grid::TRAP_CELL, 0, -5, 0);
    a.addOutCell(std::make_tuple(0, -6, 1));

    a.save(std::string("Area/DeathRoom/DeathRoom3.area"));
}
