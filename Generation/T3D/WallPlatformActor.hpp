#ifndef WALLPLATFORMACTOR_HPP
#define WALLPLATFORMACTOR_HPP

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

#include <string>
#include <vector>

class WallPlatformActor : public IActor {
    public:
        WallPlatformActor(Grid *g);
        virtual ~WallPlatformActor() {};

        static const Vector X_POS;
        static const Vector X_NEG;
        static const Vector Y_POS;
        static const Vector Y_NEG;

        const float MAX_JUMP_HEIGHT = 200;

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
};

//const std::string BrushActor::mBaseName = std::string("BrushActor");

#endif // BRUSHACTOR_H
