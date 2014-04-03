#ifndef T3DEXPORTER_H
#define T3DEXPORTER_H

#include <string>

#include "../3D/World.hpp"
#include "../Graph.hpp"

class T3DExporter {
    public:
        T3DExporter(World *world);
        T3DExporter(Graph *graph);
        virtual ~T3DExporter(){};

        void exportT3D(std::string filepath);
    protected:
    private:
        World *mWorld;
};

#endif // T3DEXPORTER_H
