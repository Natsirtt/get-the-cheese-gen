#ifndef STAIRBRUSHACTOR_H
#define STAIRBRUSHACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

#include <string>
#include <vector>

class StairBrushActor : public IActor {
    public:
        /*StairBrushActor(Vector location, Vector gridPosition, Vector gridTranslation);
        StairBrushActor(double xLocation, double yLocation, double zLocation);*/
        StairBrushActor(Grid *g);
        virtual ~StairBrushActor() {};

        static const Vector X_POS;
        static const Vector X_NEG;
        static const Vector Y_POS;
        static const Vector Y_NEG;

        Vector getLocation();
        void setDirection(Vector dir);
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;
        Vector mGridPosition;
        Vector mGridTranslation;
        Vector mDirection;

        const std::string mBaseName = "StairBrushActor";
};

//const std::string BrushActor::mBaseName = std::string("BrushActor");

#endif // BRUSHACTOR_H
