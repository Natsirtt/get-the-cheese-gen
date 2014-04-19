#include "T3DExporter.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <map>

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

#define LIGHTS_MODULO 6

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

std::vector<std::vector<Vector>> T3DExporter::getWall(float sizeLen, bool reducedX, bool reducedY, bool reducedZ) {
    float sizeX = sizeLen;
    float sizeY = sizeLen;
    float sizeZ = sizeLen;

    if (reducedX) {
        sizeX = REDUCED_SIZE;
    }
    if (reducedY) {
        sizeY = REDUCED_SIZE;
    }
    if (reducedZ) {
        sizeZ = REDUCED_SIZE;
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
    return getWall(sizeLen, false, false, false);
}

void T3DExporter::exportPathsBrushes(std::ofstream& output, NameFactory *nameFactory) {
    Grid* g = mWorld->getGrid();
    for (auto& path : mWorld->getPaths()) {
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

            Vector predX(origin.getX() - 1, origin.getY(), origin.getZ());
            Vector nextX(origin.getX() + 1, origin.getY(), origin.getZ());
            Vector predY(origin.getX(), origin.getY() - 1, origin.getZ());
            Vector nextY(origin.getX(), origin.getY() + 1, origin.getZ());
            Vector predZ(origin.getX(), origin.getY(), origin.getZ() - 1);
            Vector nextZ(origin.getX(), origin.getY(), origin.getZ() + 1);

            Vector pos = origin * 2.0 * DEMI_CUBE_SIZE;

            if ((!isFirstOrLast && (predX != pred) && (predX != next)) ||
                (isFirstOrLast && g->get(x - 1, y, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos - Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, true, false, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((!isFirstOrLast && (predY != pred) && (predY != next)) ||
                (isFirstOrLast && g->get(x, y - 1, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos - Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, false, true, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if ((!isFirstOrLast && (predZ != pred) && (predZ != next)) ||
                (isFirstOrLast && g->get(x, y, z - 1) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos - Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, false, false, true));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((!isFirstOrLast && (nextX != pred) && (nextX != next)) ||
                (isFirstOrLast && g->get(x + 1, y, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos + Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, true, false, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if ((!isFirstOrLast && (nextY != pred) && (nextY != next)) ||
                (isFirstOrLast && g->get(x, y + 1, z) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos + Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, false, true, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((!isFirstOrLast && (nextZ != pred) && (nextZ != next)) ||
                (isFirstOrLast && g->get(x, y, z + 1) == Grid::EMPTY_CELL)) {
                BrushActor brush(pos + Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, false, false, true));
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
                    if (isPhysicalCell(itZ.second)) {
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
                            BrushActor brush(pos - Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, true, false, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }
                        if (nextX == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(DEMI_CUBE_SIZE, 0, 0), getWall(DEMI_CUBE_SIZE, true, false, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }

                        if (predY == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, false, true, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }
                        if (nextY == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(0, DEMI_CUBE_SIZE, 0), getWall(DEMI_CUBE_SIZE, false, true, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }

                        if (predZ == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, false, false, true));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                        }
                        if (nextZ == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(0, 0, DEMI_CUBE_SIZE), getWall(DEMI_CUBE_SIZE, false, false, true));
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
                        //std::cout << "Detected player start at " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                        Vector pos = (areaPositon + Vector(itX.first, itY.first, itZ.first)) * DEMI_CUBE_SIZE * 2.0;
                        pos = Vector(pos.getX(), pos.getY(), pos.getZ() - DEMI_CUBE_SIZE);
                        PlayerStartActor psa(pos);
                        output << psa.getT3D(2, nameFactory) << std::endl;
                        //return; //To avoid doing lot of unecessary loops
                    } else if (itZ.second == Grid::FINISH_CELL) {
                        //std::cout << "Detected player Finish at " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
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
                    //******************FULLING IDLE CELLS*****************//
                    if (itZ.second == Grid::FULLED_IDLE_CELL) {
                        BrushActor brush(&g);
                        brush.writeT3D(output, 2, nameFactory, pos, areaPositon);
                    }
                    //********************CLIMBING AREAS*******************//
                    if (itZ.second == Grid::CLIMB_CELL) {
                        std::cout << "Detecting a CLIMB_CELL at " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                        //Le bloc physique
                        BrushActor brush(&g);
                        //brush.IActor::writeT3D(...) ?! SERIOUSLY ?!!
                        brush.writeT3D(output, 2, nameFactory, pos, areaPositon);
                        //Les blocs ladder autour
                        LadderActor ladder(&g);
                        if (g.get(itX.first - 1, itY.first, itZ.first) == Grid::BLOCK_CELL) {
                            //std::cout << "ok1" << std::endl;
                            ladder.writeT3D(output, 2, nameFactory, Vector(itX.first - 1, itY.first, itZ.first), areaPositon);
                        }
                        if (g.get(itX.first + 1, itY.first, itZ.first) == Grid::BLOCK_CELL) {
                            //std::cout << "ok2" << std::endl;
                            ladder.writeT3D(output, 2, nameFactory, Vector(itX.first + 1, itY.first, itZ.first), areaPositon);
                        }
                        if (g.get(itX.first, itY.first - 1, itZ.first) == Grid::BLOCK_CELL) {
                            //std::cout << "ok3" << std::endl;
                            ladder.writeT3D(output, 2, nameFactory, Vector(itX.first, itY.first - 1, itZ.first), areaPositon);
                        }
                        if (g.get(itX.first, itY.first + 1, itZ.first) == Grid::BLOCK_CELL) {
                            //std::cout << "ok4" << std::endl;
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
                        std::cout << "mamamama" << std::endl;
                        //std::cout << triggerPositionDoorNameMap[tmpId] << std::endl;
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

bool T3DExporter::isPhysicalCell(long t) {
    return (t != Grid::EMPTY_CELL) && (t != Grid::IN_CELL) && (t != Grid::OUT_CELL);
}
