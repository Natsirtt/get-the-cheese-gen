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
        //CF unreal rotators conversions
        static const float DEG_TO_UNREAL;
        static const int DEG_0 = 0;
        static const int DEG_90 = 16384;
        static const int DEG_180 = 32768;
        static const int DEG_270 = 49152;
        static const int X_YAW = DEG_0;
        static const int NEG_X_YAW = DEG_180;
        static const int Y_YAW = DEG_90;
        static const int NEG_Y_YAW = DEG_270;
        static const Vector FACING_X_VECTOR;
        static const Vector FACING_NEG_X_VECTOR;
        static const Vector FACING_Y_VECTOR;
        static const Vector FACING_NEG_Y_VECTOR;
        static const Vector FACING_Z_VECTOR;
        static const Vector FACING_NEG_Z_VECTOR;
    protected:
    private:
        void exportPathsBrushes(std::ofstream& output, NameFactory *nameFactory);
        void exportRoomsBrushes(std::ofstream& output, NameFactory *nameFactory);
        void exportPlayerStart(std::ofstream& output, NameFactory *nameFactory);
        void exportSpecialsCells(std::ofstream& output, NameFactory *nameFactory);

    private:
        World *mWorld;
};

#endif // T3DEXPORTER_H
