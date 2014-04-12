#include "T3DExporter.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>

#include "../3D/Grid.hpp"
#include "IActor.hpp"
#include "StaticMeshActor.hpp"
#include "BrushActor.hpp"
#include "PlayerStartActor.hpp"
#include "PlayerFinishActor.hpp"
#include "PointLightActor.hpp"
#include "../Utils/Vector.hpp"

#define CUBE_SIZE 100.0
#define REDUCED_SIZE 1.0
#define LIGHTS_MODULO 6

T3DExporter::T3DExporter(World *world) : mWorld{world} {
}

T3DExporter::T3DExporter(Graph *graph) : mWorld{new World(graph)} {
    mWorld->build();
}

//Legacy : fisrt T3D test
void staticCubesRepresentation(std::ofstream& output, Grid *g, NameFactory *nameFactory) {
    for (auto& itX : g->getMap()) {
        for (auto& itY : itX.second) {
            for (auto& itZ : itY.second) {
                std::cout << "Parsing : " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                if (g->get(itX.first, itY.first, itZ.first) != Grid::EMPTY_CELL) {
                    IActor *actor = new StaticMeshActor(itZ.first * CUBE_SIZE, itY.first * CUBE_SIZE, itX.first * CUBE_SIZE);
                    output << actor->getT3D(2, nameFactory);
                    delete actor;
                }
            }
        }
    }
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

    std::getline(input2, buffer);
    while (!buffer.empty()) {
        //buffer = buffer.substr(0, buffer.size()-1);
        output << buffer << std::endl;
        std::getline(input2, buffer);
    }
    input2.close();
    output.close();
}

std::vector<std::vector<Vector>> getWall(float sizeLen, bool reducedX, bool reducedY, bool reducedZ) {
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

void T3DExporter::exportPathsBrushes(std::ofstream& output, NameFactory *nameFactory) {
    for (auto& path : mWorld->getPaths()) {
        int lightCpt = 0;
        for (unsigned int i = 0; i < path.size(); ++i) {
            auto& v = path.at(i);
            long x = std::get<0>(v);
            long y = std::get<1>(v);
            long z = std::get<2>(v);
            Vector origin(x, y, z);
            Vector pred = origin;
            if (i != 0) {
                auto& v2 = path.at(i-1);
                pred = Vector(std::get<0>(v2), std::get<1>(v2), std::get<2>(v2));
            } else {
                //First block of the path, we search where to open it
                if (mWorld->getGrid()->get(x - 1, y, z) == Grid::BLOCK_CELL) {
                    pred = Vector(x - 1, y, z);
                } else if (mWorld->getGrid()->get(x + 1, y, z) == Grid::BLOCK_CELL) {
                    pred = Vector(x + 1, y, z);
                } else if (mWorld->getGrid()->get(x, y - 1, z) == Grid::BLOCK_CELL) {
                    pred = Vector(x, y - 1, z);
                } else if (mWorld->getGrid()->get(x, y + 1, z) == Grid::BLOCK_CELL) {
                    pred = Vector(x, y + 1, z);
                } else if (mWorld->getGrid()->get(x, y, z  - 1) == Grid::BLOCK_CELL) {
                    pred = Vector(x, y, z  - 1);
                } else if (mWorld->getGrid()->get(x, y, z + 1) == Grid::BLOCK_CELL) {
                    pred = Vector(x, y, z  + 1);
                }
            }
            Vector next = origin;
            if (i != path.size() - 1) {
                auto& v2 = path.at(i+1);
                next = Vector(std::get<0>(v2), std::get<1>(v2), std::get<2>(v2));
            } else {
                //Last block, we search where to open the path
                if (mWorld->getGrid()->get(x - 1, y, z) == Grid::BLOCK_CELL) {
                    next = Vector(x - 1, y, z);
                } else if (mWorld->getGrid()->get(x + 1, y, z) == Grid::BLOCK_CELL) {
                    next = Vector(x + 1, y, z);
                } else if (mWorld->getGrid()->get(x, y - 1, z) == Grid::BLOCK_CELL) {
                    next = Vector(x, y - 1, z);
                } else if (mWorld->getGrid()->get(x, y + 1, z) == Grid::BLOCK_CELL) {
                    next = Vector(x, y + 1, z);
                } else if (mWorld->getGrid()->get(x, y, z  - 1) == Grid::BLOCK_CELL) {
                    next = Vector(x, y, z  - 1);
                } else if (mWorld->getGrid()->get(x, y, z + 1) == Grid::BLOCK_CELL) {
                    next = Vector(x, y, z  + 1);
                }
            }

            Vector predX(origin.getX() - 1, origin.getY(), origin.getZ());
            Vector nextX(origin.getX() + 1, origin.getY(), origin.getZ());
            Vector predY(origin.getX(), origin.getY() - 1, origin.getZ());
            Vector nextY(origin.getX(), origin.getY() + 1, origin.getZ());
            Vector predZ(origin.getX(), origin.getY(), origin.getZ() - 1);
            Vector nextZ(origin.getX(), origin.getY(), origin.getZ() + 1);

            Vector pos = origin * 2.0 * CUBE_SIZE;

            if ((predX != pred) && (predX != next)) {
                BrushActor brush(pos - Vector(CUBE_SIZE, 0, 0), getWall(CUBE_SIZE, true, false, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((predY != pred) && (predY != next)) {
                BrushActor brush(pos - Vector(0, CUBE_SIZE, 0), getWall(CUBE_SIZE, false, true, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if ((predZ != pred) && (predZ != next)) {
                BrushActor brush(pos - Vector(0, 0, CUBE_SIZE), getWall(CUBE_SIZE, false, false, true));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((nextX != pred) && (nextX != next)) {
                BrushActor brush(pos + Vector(CUBE_SIZE, 0, 0), getWall(CUBE_SIZE, true, false, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if ((nextY != pred) && (nextY != next)) {
                BrushActor brush(pos + Vector(0, CUBE_SIZE, 0), getWall(CUBE_SIZE, false, true, false));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }
            if ((nextZ != pred) && (nextZ != next)) {
                BrushActor brush(pos + Vector(0, 0, CUBE_SIZE), getWall(CUBE_SIZE, false, false, true));
                output << brush.getT3D(2, nameFactory) << std::endl;
            }

            if (lightCpt == 0) {
                PointLightActor pla(pos, CUBE_SIZE);
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
//        std::cout << "Grid occupied cells nb = " << g.getOccupiedCellsCount() << std::endl;
        for (auto& itX : g.getMap()) {
//            std::cout << "itX" << std::endl;
            for (auto& itY : itX.second) {
//                std::cout << "\titY" << std::endl;
                for (auto& itZ : itY.second) {
//                    std::cout << "\t\titZ" << std::endl;
                    if (itZ.second != Grid::EMPTY_CELL) {
//                        Vector origin = (areaPositon + Vector(itX.first, itZ.first, itY.first)) * (CUBE_SIZE + 10) * 2;
//                        std::cout << "Detected room cell at " << origin.getX() << " " << origin.getY() << " " << origin.getZ() << std::endl;
                        long predX = g.get(itX.first - 1, itY.first, itZ.first);
                        long nextX = g.get(itX.first + 1, itY.first, itZ.first);
                        long predY = g.get(itX.first, itY.first - 1, itZ.first);
                        long nextY = g.get(itX.first, itY.first + 1, itZ.first);
                        long predZ = g.get(itX.first, itY.first, itZ.first - 1);
                        long nextZ = g.get(itX.first, itY.first, itZ.first + 1);

                        Vector pos = (areaPositon + Vector(itX.first, itY.first, itZ.first)) * CUBE_SIZE * 2.0;
                        bool addLight = false;
                        if (predX == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(CUBE_SIZE, 0, 0), getWall(CUBE_SIZE, true, false, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                            addLight = true;
                        }
                        if (nextX == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(CUBE_SIZE, 0, 0), getWall(CUBE_SIZE, true, false, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                            addLight = true;
                        }

                        if (predY == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(0, CUBE_SIZE, 0), getWall(CUBE_SIZE, false, true, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                            addLight = true;
                        }
                        if (nextY == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(0, CUBE_SIZE, 0), getWall(CUBE_SIZE, false, true, false));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                            addLight = true;
                        }

                        if (predZ == Grid::EMPTY_CELL) {
                            BrushActor brush(pos - Vector(0, 0, CUBE_SIZE), getWall(CUBE_SIZE, false, false, true));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                            addLight = true;
                        }
                        if (nextZ == Grid::EMPTY_CELL) {
                            BrushActor brush(pos + Vector(0, 0, CUBE_SIZE), getWall(CUBE_SIZE, false, false, true));
                            output << brush.getT3D(2, nameFactory) << std::endl;
                            addLight = true;
                        }

                        if (addLight) {
                            PointLightActor pla(pos, CUBE_SIZE);
                            output << pla.getT3D(2, nameFactory) << std::endl;
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
                        Vector pos = (areaPositon + Vector(itX.first, itY.first, itZ.first)) * CUBE_SIZE * 2.0;
                        PlayerStartActor psa(pos);
                        output << psa.getT3D(2, nameFactory) << std::endl;
                        //return; //To avoid doing lot of unecessary loops
                    } else if (itZ.second == Grid::FINISH_CELL) {
                        //std::cout << "Detected player Finish at " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                        Vector pos = (areaPositon + Vector(itX.first, itY.first, itZ.first)) * CUBE_SIZE * 2.0;
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
