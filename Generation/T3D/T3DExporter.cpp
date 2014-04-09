#include "T3DExporter.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>

#include "../3D/Grid.hpp"
#include "IActor.hpp"
#include "StaticMeshActor.hpp"
#include "BrushActor.hpp"
#include "../Utils/Vector.hpp"

#define CUBE_SIZE 100
#define REDUCED_SIZE 1

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

    NameFactory *nameFactory = new NameFactory();

    //staticCubesRepresentation(output, mWorld->getGrid(), nameFactory); //Legacy
    exportPathsBrushes(output, nameFactory);

    std::getline(input2, buffer);
    while (!buffer.empty()) {
        //buffer = buffer.substr(0, buffer.size()-1);
        output << buffer << std::endl;
        std::getline(input2, buffer);
    }
    input2.close();
    output.close();
}

std::vector<std::vector<Vector>> getWall(int sizeLen, bool reducedX, bool reducedY, bool reducedZ) {
    int sizeX = sizeLen;
    int sizeY = sizeLen;
    int sizeZ = sizeLen;

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
        for (unsigned int i = 0; i < path.size(); ++i) {
            auto& v = path.at(i);

            Vector origin(std::get<0>(v), std::get<2>(v), std::get<1>(v));
            Vector pred(-1000000, -1000000, -1000000); //C'est moche
            if (i != 0) {
                auto& v2 = path.at(i-1);
                pred = Vector(std::get<0>(v2), std::get<2>(v2), std::get<1>(v2));
            }
            Vector next(-1000000, -1000000, -1000000); //Un cube a peu de chance d'être la
            if (i != path.size() - 1) {
                auto& v2 = path.at(i+1);
                next = Vector(std::get<0>(v2), std::get<2>(v2), std::get<1>(v2));
            }

            Vector predX(origin.getX() - 1, origin.getY(), origin.getZ());
            Vector nextX(origin.getX() + 1, origin.getY(), origin.getZ());
            Vector predY(origin.getX(), origin.getY() - 1, origin.getZ());
            Vector nextY(origin.getX(), origin.getY() + 1, origin.getZ());
            Vector predZ(origin.getX(), origin.getY(), origin.getZ() - 1);
            Vector nextZ(origin.getX(), origin.getY(), origin.getZ() + 1);

            if ((predX != pred) && (predX != next)) {
                IActor *brush = new BrushActor(predX * (CUBE_SIZE + 10) * 2, getWall(CUBE_SIZE, true, false, false));
                output << brush->getT3D(2, nameFactory) << std::endl;
                delete brush;
            }
            if ((predY != pred) && (predY != next)) {
                IActor *brush = new BrushActor(predY * (CUBE_SIZE + 10) * 2, getWall(CUBE_SIZE, false, true, false));
                output << brush->getT3D(2, nameFactory) << std::endl;
                delete brush;
            }

            if ((predZ != pred) && (predZ != next)) {
                IActor *brush = new BrushActor(predZ * (CUBE_SIZE + 10) * 2, getWall(CUBE_SIZE, false, false, true));
                output << brush->getT3D(2, nameFactory) << std::endl;
                delete brush;
            }
            if ((nextX != pred) && (nextX != next)) {
                IActor *brush = new BrushActor(nextX * (CUBE_SIZE + 10) * 2, getWall(CUBE_SIZE, true, false, false));
                output << brush->getT3D(2, nameFactory) << std::endl;
                delete brush;
            }

            if ((nextY != pred) && (nextY != next)) {
                IActor *brush = new BrushActor(nextY * (CUBE_SIZE + 10) * 2, getWall(CUBE_SIZE, false, true, false));
                output << brush->getT3D(2, nameFactory) << std::endl;
                delete brush;
            }
            if ((nextZ != pred) && (nextZ != next)) {
                IActor *brush = new BrushActor(nextZ * (CUBE_SIZE + 10) * 2, getWall(CUBE_SIZE, false, false, true));
                output << brush->getT3D(2, nameFactory) << std::endl;
                delete brush;
            }
        }
    }
}
