#include "T3DExporter.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>

#include "../3D/Grid.hpp"
#include "IActor.hpp"
#include "StaticMeshActor.hpp"
#include "BrushActor.hpp"
#include "PlayerStartActor.hpp"
#include "PlayerFinishActor.hpp"
#include "PointLightActor.hpp"
#include "LadderActor.hpp"
#include "DoorActor.hpp"
#include "TriggerActor.hpp"
#include "TurretActor.h"
#include "LaserActor.hpp"
#include "LavaActor.hpp"
#include "LavaPostProcessActor.hpp"
#include "FluidActor.hpp"
#include "MovableBrushActor.hpp"
#include "StairBrushActor.hpp"

#define LIGHTS_MODULO 6

const float T3DExporter::DEG_TO_UNREAL = 182.0444;
const Vector T3DExporter::FACING_X_VECTOR = Vector(T3DExporter::DEG_0, T3DExporter::DEG_270, T3DExporter::DEG_0);
const Vector T3DExporter::FACING_NEG_X_VECTOR = Vector(T3DExporter::DEG_0, T3DExporter::DEG_90, T3DExporter::DEG_0);
const Vector T3DExporter::FACING_Y_VECTOR = Vector(T3DExporter::DEG_90, T3DExporter::DEG_0, T3DExporter::DEG_0);
const Vector T3DExporter::FACING_NEG_Y_VECTOR = Vector(T3DExporter::DEG_270, T3DExporter::DEG_0, T3DExporter::DEG_0);
const Vector T3DExporter::FACING_Z_VECTOR = Vector(T3DExporter::DEG_0, T3DExporter::DEG_0, T3DExporter::DEG_0);
const Vector T3DExporter::FACING_NEG_Z_VECTOR = Vector(T3DExporter::DEG_180, T3DExporter::DEG_0, T3DExporter::DEG_0);

T3DExporter::T3DExporter(World *world) : mWorld{world} {
}

T3DExporter::T3DExporter(Graph *graph) : mWorld{new World(graph)} {
    mWorld->build();
}

void T3DExporter::exportT3D(std::string filepath) {
    std::ofstream output(filepath);
    std::ifstream input1("T3D/t3d.begin");
    std::ifstream input2("T3D/t3d.end");
    std::string buffer;

    //int i = 0;
    std::getline(input1, buffer);
    while (!buffer.empty()) {
        //buffer = buffer.substr(0, buffer.size()-1);
        output << buffer << std::endl;
        std::getline(input1, buffer);
        //i++;
        //if (i > 30) {
        //    throw std::runtime_error("too many iteration");
        //}
    }
    input1.close();

    NameFactory nameFactory;

    //staticCubesRepresentation(output, mWorld->getGrid(), nameFactory); //Legacy
    exportPathsBrushes(output, &nameFactory);
    exportRoomsBrushes(output, &nameFactory);
    exportPlayerStart(output, &nameFactory);
    exportSpecialsCells(output, &nameFactory);

    std::getline(input2, buffer);
    while (!buffer.empty()) {
        //buffer = buffer.substr(0, buffer.size()-1);
        output << buffer << std::endl;
        std::getline(input2, buffer);
    }
    input2.close();
    output.close();
    std::cout << "t3d exported to " << filepath << "." << std::endl;
}

std::vector<std::vector<Vector>> T3DExporter::getWall(float sizeLen, float reducedSize, bool reducedX, bool reducedY, bool reducedZ) {
    float sizeX = sizeLen;
    float sizeY = sizeLen;
    float sizeZ = sizeLen;

    if (reducedX) {
        sizeX = reducedSize;
    }
    if (reducedY) {
        sizeY = reducedSize;
    }
    if (reducedZ) {
        sizeZ = reducedSize;
    }

    std::vector<std::vector<Vector>> polyList;
    std::vector<Vector> f1;
    f1.push_back(Vector(-sizeX, -sizeY, sizeZ));
    f1.push_back(Vector(-sizeX, -sizeY, -sizeZ));
    f1.push_back(Vector(sizeX, -sizeY, -sizeZ));
    f1.push_back(Vector(sizeX, -sizeY, sizeZ));
    polyList.push_back(f1);
    std::vector<Vector> f2;
    f2.push_back(Vector(sizeX, -sizeY, sizeZ));
    f2.push_back(Vector(sizeX, -sizeY, -sizeZ));
    f2.push_back(Vector(sizeX, sizeY, -sizeZ));
    f2.push_back(Vector(sizeX, sizeY, sizeZ));
    polyList.push_back(f2);
    std::vector<Vector> f3;
    f3.push_back(Vector(sizeX, sizeY, sizeZ));
    f3.push_back(Vector(sizeX, sizeY, -sizeZ));
    f3.push_back(Vector(-sizeX, sizeY, -sizeZ));
    f3.push_back(Vector(-sizeX, sizeY, sizeZ));
    polyList.push_back(f3);
    std::vector<Vector> f4;
    f4.push_back(Vector(-sizeX, -sizeY, sizeZ));
    f4.push_back(Vector(-sizeX, sizeY, sizeZ));
    f4.push_back(Vector(-sizeX, sizeY, -sizeZ));
    f4.push_back(Vector(-sizeX, -sizeY, -sizeZ));
    polyList.push_back(f4);
    std::vector<Vector> f5;
    f5.push_back(Vector(-sizeX, -sizeY, -sizeZ));
    f5.push_back(Vector(-sizeX, sizeY, -sizeZ));
    f5.push_back(Vector(sizeX, sizeY, -sizeZ));
    f5.push_back(Vector(sizeX, -sizeY, -sizeZ));
    polyList.push_back(f5);
    std::vector<Vector> f6;
    f6.push_back(Vector(-sizeX, -sizeY, sizeZ));
    f6.push_back(Vector(sizeX, -sizeY, sizeZ));
    f6.push_back(Vector(sizeX, sizeY, sizeZ));
    f6.push_back(Vector(-sizeX, sizeY, sizeZ));
    polyList.push_back(f6);
    return polyList;
}

std::vector<std::vector<Vector>> T3DExporter::getCube(float sizeLen) {
    return getWall(sizeLen, REDUCED_SIZE, false, false, false);
}

void T3DExporter::exportPathsBrushes(std::ofstream& output, NameFactory *nameFactory) {
    Grid* g = mWorld->getGrid();
    for (auto& path : mWorld->getPaths()) {
        std::vector<bool> needFloor(path.size(), true);
        int lightCpt = 0;
        for (unsigned int i = 0; i < path.size(); ++i) {
            auto& v = path.at(i);
            long x = std::get<0>(v);
            long y = std::get<1>(v);
            long z = std::get<2>(v);
            Vector origin(x, y, z);
            Vector pred = origin;
            Vector next = origin;
            if (i > 0) {
                auto& v2 = path.at(i-1);
                pred = Vector(std::get<0>(v2), std::get<1>(v2), std::get<2>(v2));
            }
            if (i < (path.size() - 1)) {
                auto& v2 = path.at(i+1);
                next = Vector(std::get<0>(v2), std::get<1>(v2), std::get<2>(v2));
            }
            bool isFirstOrLast = (i == 0) || (i == (path.size() - 1));
            bool needStair = pathNeedStairs(path, i);
            Vector stairLocation = origin;
            Vector stairDir;
            if (needStair) {
                stairLocation = Vector(path[i + 2]);
                stairLocation = stairLocation - Vector(0, 0, 1);
                if ((g->get(stairLocation.getX(), stairLocation.getY(), stairLocation.getZ()) != Grid::EMPTY_CELL) &&
                    (g->get(stairLocation.getX(), stairLocation.getY(), stairLocation.getZ()) != Grid::FULLED_IDLE_CELL)) {
                    stairLocation = origin;
                    needStair = false;
                } else {
                    stairDir = stairLocation - Vector(path[i]);
                    StairBrushActor sba(g);
                    sba.setDirection(stairDir);
                    sba.writeT3D(output, 2, nameFactory, stairLocation, Vector(0, 0, 0));
                    needFloor[i + 2] = false;

                    Vector pos = stairLocation * 2.0 * DEMI_CUBE_SIZE;
                    Vector dir(stairDir.getY(), stairDir.getX(), 0);
                    BrushActor brush(pos + dir * DEMI_CUBE_SIZE, getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, stairDir.getX() == 0, stairDir.getY() == 0, false));
                    output << brush.getT3D(2, nameFactory) << std::endl;
                    BrushActor brush2(pos - dir * DEMI_CUBE_SIZE, getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, stairDir.getX() == 0, stairDir.getY() == 0, false));
                    output << brush2.getT3D(2, nameFactory) << std::endl;
                }
            }

            Vector predX(origin.getX() - 1, origin.getY(), origin.getZ());
            Vector nextX(origin.getX() + 1, origin.getY(), origin.getZ());
            Vector predY(origin.getX(), origin.getY() - 1, origin.getZ());
            Vector nextY(origin.getX(), origin.getY() + 1, origin.getZ());
            Vector predZ(origin.getX(), origin.getY(), origin.getZ() - 1);
            Vector nextZ(origin.getX(), origin.getY(), origin.getZ() + 1);

            Vector pos = origin * 2.0 * DEMI_CUBE_SIZE;

            if ((!isFirstOrLast && (predX != pred) && (predX != next) && (predX != stairLocation)) ||
                (isFirstOrLast && g->get(x - 1, y, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos - Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, true, false, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((!isFirstOrLast && (predY != pred) && (predY != next) && (predY != stairLocation)) ||
                (isFirstOrLast && g->get(x, y - 1, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos - Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, true, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if (((!isFirstOrLast && (predZ != pred) && (predZ != next)) ||
                (isFirstOrLast && g->get(x, y, z - 1) == Grid::EMPTY_CELL)) && needFloor[i]) {
                BrushActor brush(pos - Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, false, true));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((!isFirstOrLast && (nextX != pred) && (nextX != next) && (nextX != stairLocation)) ||
                (isFirstOrLast && g->get(x + 1, y, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos + Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, true, false, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if ((!isFirstOrLast && (nextY != pred) && (nextY != next) && (nextY != stairLocation)) ||
                (isFirstOrLast && g->get(x, y + 1, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos + Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, true, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((!isFirstOrLast && (nextZ != pred) && (nextZ != next)) ||
                (isFirstOrLast && g->get(x, y, z + 1) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos + Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, false, true));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if (lightCpt == 0) {
                PointLightActor pla(pos, DEMI_CUBE_SIZE);
                output << pla.getT3D(2, nameFactory) << std::endl;
            }
            lightCpt = (lightCpt + 1) % LIGHTS_MODULO;
        }
    }
}

bool T3DExporter::pathNeedStairs(std::vector<std::tuple<long, long, long>>& path, unsigned int cellNb) {
    if ((cellNb + 2) < path.size()) {
        Vector c1 = Vector(path[cellNb]);
        Vector c2 = Vector(path[cellNb + 1]);
        Vector c3 = Vector(path[cellNb + 2]);

        bool res = false;

        if ((c1.getX() == c2.getX()) && (c2.getX() == c3.getX()) &&
            (c1.getZ() == (c2.getZ() - 1)) && (c2.getZ() == c3.getZ())) {
            res = true;
        } else if ((c1.getX() == c2.getX()) && (c2.getX() == c3.getX()) &&
            (c1.getZ() == (c2.getZ() - 1)) && (c2.getZ() == c3.getZ())) {
            res = true;
        } else {
            return false;
        }

        if (res) {
            Vector stairLocation = Vector(path[cellNb + 2]);
            stairLocation = stairLocation - Vector(0, 0, 1);
            if (cellNb > 0) {
                Vector pred = Vector(path[cellNb - 1]);
                Vector down = Vector(path[cellNb]) - Vector(0, 0, 1);
                if ((pred == stairLocation) || (pred == down)) {
                    return false;
                }
            }

        }
        return true;
    }
    return false;
}

void T3DExporter::exportRoomsBrushes(std::ofstream& output, NameFactory *nameFactory) {
    for (unsigned int i = 0; i < mWorld->getAreas().size(); ++i) {
        Grid g = mWorld->getAreas().at(i).getGrid();
        std::cout << "Exporting room n°" << i << std::endl;
        std::tuple<long, long, long> posTuple = mWorld->getAreaPosition(i);
        Vector areaPositon(std::get<0>(posTuple), std::get<1>(posTuple), std::get<2>(posTuple));
        bool addLight = true;
//        std::cout << "Grid occupied cells nb = " << g.getOccupiedCellsCount() << std::endl;
        for (auto& itX : g.getMap()) {
//            std::cout << "itX" << std::endl;
            for (auto& itY : itX.second) {
//                std::cout << "\titY" << std::endl;
                for (auto& itZ : itY.second) {
//                    std::cout << "\t\titZ" << std::endl;
                    if (Grid::isPhysicalCell(itZ.second)) {
//                        Vector origin = (areaPositon + Vector(itX.first, itZ.first, itY.first)) * (CUBE_SIZE + 10) * 2;
//                        std::cout << "Detected room cell at " << origin.getX() << " " << origin.getY() << " " << origin.getZ() << std::endl;
                        long predX = g.get(itX.first - 1, itY.first, itZ.first);
                        long nextX = g.get(itX.first + 1, itY.first, itZ.first);
                        long predY = g.get(itX.first, itY.first - 1, itZ.first);
                        long nextY = g.get(itX.first, itY.first + 1, itZ.first);
                        long predZ = g.get(itX.first, itY.first, itZ.first - 1);
                        long nextZ = g.get(itX.first, itY.first, itZ.first + 1);

                        Vector pos = (areaPositon + Vector(itX.first, itY.first, itZ.first)) * DEMI_CUBE_SIZE * 2.0;
                        if (predX == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, true, false, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }
                        if (nextX == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, true, false, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }

                        if (predY == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, true, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }
                        if (nextY == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, true, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }

                        if (predZ == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, false, true));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }
                        if (nextZ == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, REDUCED_SIZE, false, false, true));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }

                        if (addLight) {
                            PointLightActor pla(pos, DEMI_CUBE_SIZE);
                            output << pla.getT3D(2, nameFactory) << std::endl;
                            addLight = false;
                        }
                    }
                }
            }
        }
    }
}

void T3DExporter::exportPlayerStart(std::ofstream& output, NameFactory *nameFactory) {
    for (unsigned int i = 0; i < mWorld->getAreas().size(); ++i) {
        std::tuple<long, long, long> posTuple = mWorld->getAreaPosition(i);
        Vector areaPositon(std::get<0>(posTuple), std::get<1>(posTuple), std::get<2>(posTuple));
        Grid g = mWorld->getAreas().at(i).getGrid();
        for (auto& itX : g.getMap()) {
            for (auto& itY : itX.second) {
                for (auto& itZ : itY.second) {
                    if (itZ.second == Grid::START_CELL) {
                        std::cout << "Detected player start at " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                        Vector pos = (areaPositon + Vector(itX.first, itY.first, itZ.first)) * DEMI_CUBE_SIZE * 2.0;
                        pos = Vector(pos.getX(), pos.getY(), pos.getZ() - DEMI_CUBE_SIZE);
                        PlayerStartActor psa(pos);
                        output << psa.getT3D(2, nameFactory) << std::endl;
                        //return; //To avoid doing lot of unecessary loops
                    } else if (itZ.second == Grid::FINISH_CELL) {
                        std::cout << "Detected player Finish at " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                        Vector pos = (areaPositon + Vector(itX.first, itY.first, itZ.first)) * DEMI_CUBE_SIZE * 2.0;
                        pos = Vector(pos.getX(), pos.getY(), pos.getZ() - DEMI_CUBE_SIZE);
                        PlayerFinishActor pfa(pos);
                        output << pfa.getT3D(2, nameFactory) << std::endl;
                    }
                }
            }
        }
    }
    //PlayerStartActor psa(Vector(0, -50, 0));
    //output << psa.getT3D(2, nameFactory) << std::endl;
}

void T3DExporter::exportSpecialsCells(std::ofstream& output, NameFactory *nameFactory) {
    std::map<Id, std::string> triggerPositionDoorNameMap;
    std::map<Id, Id>& doorTriggerMap = mWorld->getTriggerDoorMap();
    for (unsigned int i = 0; i < mWorld->getAreas().size(); ++i) {
        std::tuple<long, long, long> posTuple = mWorld->getAreaPosition(i);
        Vector areaPositon(std::get<0>(posTuple), std::get<1>(posTuple), std::get<2>(posTuple));
        Grid g = mWorld->getAreas().at(i).getGrid();
        //std::cout << "area : " << i << std::endl;
        for (auto& itX : g.getMap()) {
            for (auto& itY : itX.second) {
                for (auto& itZ : itY.second) {
                    //std::cout << itZ.second << std::endl;
                    Vector pos = Vector(itX.first, itY.first, itZ.first);
                    //*******************FULLED IDLE CELLS*****************//
                    if (itZ.second == Grid::FULLED_IDLE_CELL) {
                        std::cout << "Detecting a FULLED_IDLE_CELL" << std::endl;
                        BrushActor brush(&g);
                        brush.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //**********************PLATFORMS**********************//
                    else if (itZ.second == Grid::PLATFORM_CELL) {
                        std::cout << "Detecting a PLATFORM_CELL" << std::endl;
                        BrushActor brush((areaPositon + pos) * DEMI_CUBE_SIZE * 2.0 + Vector(0, 0, DEMI_CUBE_SIZE / 4.), getWall(DEMI_CUBE_SIZE, DEMI_CUBE_SIZE / 4., false, false, true));
                        output << brush.getT3D(2, nameFactory) << std::endl;
                    }
                    //**********************MOVING PLATFORMS**********************//
                    else if (itZ.second == Grid::MOVING_PLATFORM_CELL) {
                        // MARCHE PAS !!
                        //std::cout << "Detecting a MOVING_PLATFORM_CELL" << std::endl;
                        //MovableBrushActor brush((areaPositon + pos) * DEMI_CUBE_SIZE * 2.0 + Vector(0, 0, DEMI_CUBE_SIZE / 4.), getWall(DEMI_CUBE_SIZE, DEMI_CUBE_SIZE / 4., false, false, true));
                        //output << brush.getT3D(2, nameFactory) << std::endl;
                    }
                    //********************CLIMBING AREAS*******************//
                    else if (itZ.second == Grid::CLIMB_CELL) {
                        std::cout << "Detecting a CLIMB_CELL at " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                        //Le bloc physique
                        BrushActor brush(&g);
                        brush.setTexture("FoliageDemo.Materials.M_PaintableRock_MasterOpt");
                                        //"GenericFoliage01.Trees.Material.M_GEN_Foliage01_Trees_BarkComplex_MASTER"
                        brush.writeT3D(output, 2, nameFactory, pos, areaPositon);
                        //Les blocs ladder autour
                        LadderActor ladder(&g);
                        if (g.get(itX.first - 1, itY.first, itZ.first) == Grid::BLOCK_CELL) {
                            ladder.writeT3D(output, 2, nameFactory, Vector(itX.first - 1, itY.first, itZ.first), areaPositon);
                        }
                        if (g.get(itX.first + 1, itY.first, itZ.first) == Grid::BLOCK_CELL) {
                            ladder.writeT3D(output, 2, nameFactory, Vector(itX.first + 1, itY.first, itZ.first), areaPositon);
                        }
                        if (g.get(itX.first, itY.first - 1, itZ.first) == Grid::BLOCK_CELL) {
                            ladder.writeT3D(output, 2, nameFactory, Vector(itX.first, itY.first - 1, itZ.first), areaPositon);
                        }
                        if (g.get(itX.first, itY.first + 1, itZ.first) == Grid::BLOCK_CELL) {
                            ladder.writeT3D(output, 2, nameFactory, Vector(itX.first, itY.first + 1, itZ.first), areaPositon);
                        }
                    }
                    //********************DOORS*************************//
                    else if (itZ.second == Grid::DOOR_CELL) {
                        std::cout << "Detecting a DOOR_CELL" << std::endl;
                        DoorActor door(&g);
                        door.writeT3D(output, 2, nameFactory, pos, areaPositon);
                        //On dit au trigger de la door quel est le nom de cette dernière
                        std::cout << "Door id = " << i << std::endl;
                        Id tmpId = doorTriggerMap.at(i);
                        std::cout << "value = " << tmpId << std::endl;
                        std::cout << "name = " << door.getName() << std::endl;
                        triggerPositionDoorNameMap[tmpId] = door.getName();
                        //triggerPositionDoorNameMap[tmpId] = door.getName();
                        //std::cout << triggerPositionDoorNameMap[tmpId] << std::endl;
                    }
                    //********************TURRETS*************************//
                    else if (itZ.second == Grid::TURRET_CELL) {
                        std::cout << "Detecting a TURRET_CELL" << std::endl;
                        TurretActor turret(&g);
                        turret.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //********************LASERS**************************//
                    else if ((itZ.second == Grid::LASER_X_STICKED_CELL) || (itZ.second == Grid::LASER_Y_STICKED_CELL) || (itZ.second == Grid::LASER_Z_STICKED_CELL)) {
                        std::cout << "Detecting a LASER_CELL" << std::endl;
                        LaserActor laser(&g);
                        laser.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //********************Lave**************************//
                    else if (itZ.second == Grid::DEATH_CELL) {
                        std::cout << "Detecting a DEATH_CELL" << std::endl;
                        LavaActor lava(&g);
                        lava.writeT3D(output, 2, nameFactory, pos, areaPositon);
                        LavaPostProcessActor lavapp(&g);
                        lavapp.writeT3D(output, 2, nameFactory, pos, areaPositon);
                        FluidActor fa(&g);
                        fa.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //********************Escalier**************************//
                    else if (itZ.second == Grid::STAIRS_XPOS_CELL) {
                        std::cout << "Detecting a STAIRS_XPOS_CELL" << std::endl;
                        StairBrushActor sba(&g);
                        sba.setDirection(Vector(1, 0, 0));
                        sba.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //********************Escalier**************************//
                    else if (itZ.second == Grid::STAIRS_XNEG_CELL) {
                        std::cout << "Detecting a STAIRS_XNEG_CELL" << std::endl;
                        StairBrushActor sba(&g);
                        sba.setDirection(Vector(-1, 0, 0));
                        sba.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //********************Escalier**************************//
                    else if (itZ.second == Grid::STAIRS_YPOS_CELL) {
                        std::cout << "Detecting a STAIRS_YPOS_CELL" << std::endl;
                        StairBrushActor sba(&g);
                        sba.setDirection(Vector(0, 1, 0));
                        sba.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //********************Escalier**************************//
                    else if (itZ.second == Grid::STAIRS_YNEG_CELL) {
                        std::cout << "Detecting a STAIRS_YNEG_CELL" << std::endl;
                        StairBrushActor sba(&g);
                        sba.setDirection(Vector(0, -1, 0));
                        sba.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                }
            }
        }
    }
    //Toutes les portes doivent être exportées pour exporter leurs triggers, alors on fait une dernière boucle juste pour eux
    for (unsigned int i = 0; i < mWorld->getAreas().size(); ++i) {
        std::tuple<long, long, long> posTuple = mWorld->getAreaPosition(i);
        Vector areaPositon(std::get<0>(posTuple), std::get<1>(posTuple), std::get<2>(posTuple));
        Grid g = mWorld->getAreas().at(i).getGrid();
        for (auto& itX : g.getMap()) {
            for (auto& itY : itX.second) {
                for (auto& itZ : itY.second) {
                    Vector pos = Vector(itX.first, itY.first, itZ.first);
                     if (itZ.second == Grid::TRIGGER_CELL) {
                        std::cout << "Trigger at " << itX.first << " " << itY.first << " " << itZ.first << " with id = " << i
                                    << " and door name = " << triggerPositionDoorNameMap.at(i) << std::endl;
                        TriggerActor trigger(&g, triggerPositionDoorNameMap.at(i));
                        trigger.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                }
            }
        }
    }
}
