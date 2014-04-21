#ifndef LAVAPOSTPROCESSACTOR_HPP
#define LAVAPOSTPROCESSACTOR_HPP

#include "IActor.hpp"

#include <string>
#include <vector>
#include <fstream>

#include "NameFactory.hpp"
#include "../Utils/Vector.hpp"
#include "../3D/Grid.hpp"

class LavaPostProcessActor : public IActor {
    public:
        LavaPostProcessActor(Vector location);
        LavaPostProcessActor(double xLocation, double yLocation, double zLocation);
        LavaPostProcessActor(Grid *g);
        virtual ~LavaPostProcessActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *NameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;

        const std::string mBaseName = "LavaPostProcessVolume";
};

#endif // LAVAACTOR_HPP
