#ifndef T3DEXPORTER_H
#define T3DEXPORTER_H

#include <string>
#include <fstream>

#include "../3D/World.hpp"
#include "../Graph.hpp"
#include "NameFactory.hpp"

class T3DExporter {
    public:
        T3DExporter(World *world);
        T3DExporter(Graph *graph);
        virtual ~T3DExporter(){};

        void exportT3D(std::string filepath);
    protected:
    private:
        void exportPathsBrushes(std::ofstream& output, NameFactory *nameFactory);
        void exportRoomsBrushes(std::ofstream& output, NameFactory *nameFactory);
        void exportPlayerStart(std::ofstream& output, NameFactory *NameFactory);

        bool isPhysicalCell(long t);
    private:
        World *mWorld;
};

#endif // T3DEXPORTER_H
