#ifndef T3DEXPORTER_H
#define T3DEXPORTER_H

#include <string>
#include <fstream>

#include "../3D/World.hpp"
#include "../Utils/Vector.hpp"
#include "../Graph.hpp"
#include "NameFactory.hpp"

class T3DExporter {
    public:
        T3DExporter(World *world);
        T3DExporter(Graph *graph);
        virtual ~T3DExporter(){};

        void exportT3D(std::string filepath);
        static std::vector<std::vector<Vector>> getWall(float sizeLen, bool reducedX, bool reducedY, bool reducedZ);
        static std::vector<std::vector<Vector>> getCube(float sizeLen);

        static const int DEMI_CUBE_SIZE = 100;
        static const int REDUCED_SIZE = 1;
    protected:
    private:
        void exportPathsBrushes(std::ofstream& output, NameFactory *nameFactory);
        void exportRoomsBrushes(std::ofstream& output, NameFactory *nameFactory);
        void exportPlayerStart(std::ofstream& output, NameFactory *nameFactory);
        void exportSpecialsCells(std::ofstream& output, NameFactory *nameFactory);

        bool isPhysicalCell(long t);
    private:
        World *mWorld;
};

#endif // T3DEXPORTER_H
