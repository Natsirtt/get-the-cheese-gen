#ifndef LAVAACTOR_HPP
#define LAVAACTOR_HPP

#include "IActor.hpp"

#include <string>
#include <vector>
#include <fstream>

#include "NameFactory.hpp"
#include "../Utils/Vector.hpp"
#include "../3D/Grid.hpp"

class LavaActor : public IActor {
    public:
        LavaActor(Vector location);
        LavaActor(double xLocation, double yLocation, double zLocation);
        LavaActor(Grid *g);
        virtual ~LavaActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *NameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;

        const std::string mBaseName = "LavaVolume";
};

#endif // LAVAACTOR_HPP
