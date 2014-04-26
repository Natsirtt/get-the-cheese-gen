#ifndef TRAPBRUSHACTOR_H
#define TRAPBRUSHACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

#include <string>
#include <vector>

class TrapBrushActor : public IActor {
    public:
        TrapBrushActor(Vector location);
        TrapBrushActor(double xLocation, double yLocation, double zLocation);
        TrapBrushActor(Grid *g);
        virtual ~TrapBrushActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        std::string writeTrigger(int indentLevel, NameFactory *nameFactory);

        Vector mLocation;
        bool mSub;

        std::string mName;

        const std::string mBaseName = "TrapActor";
};

//const std::string BrushActor::mBaseName = std::string("BrushActor");

#endif // BRUSHACTOR_H
