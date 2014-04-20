#ifndef LASERACTOR_HPP
#define LASERACTOR_HPP

#include "IActor.hpp"

#include <string>
#include <fstream>

#include "../Utils/Vector.hpp"
#include "../3D/Grid.hpp"
#include "NameFactory.hpp"

class LaserActor : public IActor {
    public:
        LaserActor(Vector location, Vector rotation, bool urealRotation = true);
        LaserActor(double xLocation, double yLocation, double zLocation, float degRoll, float degPitch, float degYaw);
        LaserActor(double xLocation, double yLocation, double zLocation, int unrealRoll, int unrealPitch, int unrealYaw);
        LaserActor(Grid *g);
        virtual ~LaserActor() {};

        Vector getLocation();
        Vector getUnrealRotation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;
        //X = Roll, Y = Pitch and Z = yaw
        Vector mRotation;
        const std::string mBaseName = "TERLaser";
};

#endif // LASERACTOR_HPP
