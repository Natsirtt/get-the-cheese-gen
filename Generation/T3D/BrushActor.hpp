#ifndef BRUSHACTOR_H
#define BRUSHACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

#include <string>
#include <vector>

class BrushActor : public IActor {
    public:
        //BrushActor();
        BrushActor(Vector location, std::vector<std::vector<Vector>> polyList, bool sub = false);
        BrushActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, bool sub = false);
        BrushActor(Grid *g);
        virtual ~BrushActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition);
    protected:
    private:
        Vector mLocation;
        std::vector<std::vector<Vector>> mPolyList;
        bool mSub;

        const std::string mBaseName = "BrushActor";
};

//const std::string BrushActor::mBaseName = std::string("BrushActor");

#endif // BRUSHACTOR_H
