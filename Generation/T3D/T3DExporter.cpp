#include "T3DExporter.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../3D/Grid.hpp"
#include "IActor.hpp"
#include "StaticMeshActor.hpp"
#include "NameFactory.hpp"

#define CUBE_SIZE 300

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
        buffer = buffer.substr(0, buffer.size()-1);
        output << buffer << std::endl;
        std::getline(input1, buffer);
        //i++;
        //if (i > 30) {
        //    throw std::runtime_error("too many iteration");
        //}
    }
    input1.close();

    NameFactory *nameFactory = new NameFactory();
    for (auto& itX : mWorld->getGrid()->getMap()) {
        for (auto& itY : itX.second) {
            for (auto& itZ : itY.second) {
                std::cout << "Parsing : " << itX.first << " " << itY.first << " " << itZ.first << std::endl;
                if (mWorld->getGrid()->get(itX.first, itY.first, itZ.first) != Grid::EMPTY_CELL) {
                    IActor *actor = new StaticMeshActor(itZ.first * CUBE_SIZE, itY.first * CUBE_SIZE, itX.first * CUBE_SIZE);
                    output << actor->getT3D(2, nameFactory);
                    delete actor;
                }
            }
        }
    }
    std::getline(input2, buffer);
    while (!buffer.empty()) {
        buffer = buffer.substr(0, buffer.size()-1);
        output << buffer << std::endl;
        std::getline(input2, buffer);
    }
    input2.close();
    output.close();
}
