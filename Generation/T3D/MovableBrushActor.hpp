#ifndef MOVABLEBRUSHACTOR_H
#define MOVABLEBRUSHACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

#include <string>
#include <vector>

class MovableBrushActor : public IActor {
    public:
        //BrushActor();
        MovableBrushActor(Vector location);
        MovableBrushActor(double xLocation, double yLocation, double zLocation);
        MovableBrushActor(Grid *g);
        virtual ~MovableBrushActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;

        const std::string mBaseName = "MovableBrushActor";
};

//const std::string BrushActor::mBaseName = std::string("BrushActor");

#endif // BRUSHACTOR_H
