#ifndef TURRETACTOR_HPP
#define TURRETACTOR_HPP

#include "IActor.hpp"

#include <string>
#include <fstream>

#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

class TurretActor : public IActor {
    public:
        TurretActor(Vector location);
        TurretActor(double xLocation, double yLocation, double zLocation);
        TurretActor(Grid *g);
        virtual ~TurretActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;
        const std::string mBaseName = "TERTurret";
};

#endif // TURRETACTOR_HPP
