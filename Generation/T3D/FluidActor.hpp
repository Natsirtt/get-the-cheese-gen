#ifndef FLUIDACTOR_HPP
#define FLUIDACTOR_HPP

#include "IActor.hpp"

#include <string>
#include <vector>
#include <fstream>

#include "NameFactory.hpp"
#include "../Utils/Vector.hpp"
#include "../3D/Grid.hpp"

class FluidActor : public IActor {
    public:
        FluidActor(Vector location);
        FluidActor(double xLocation, double yLocation, double zLocation);
        FluidActor(Grid *g);
        virtual ~FluidActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *NameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;

        const std::string mBaseName = "FluidActor";
};

#endif // LAVAACTOR_HPP
