#ifndef STATICMESHACTOR_HPP
#define STATICMESHACTOR_HPP

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "../3D/Grid.hpp"
#include "NameFactory.hpp"

#include <fstream>

class StaticMeshActor : public IActor {
    public:
        StaticMeshActor();
        StaticMeshActor(Vector location);
        StaticMeshActor(double x, double y, double z);
        StaticMeshActor(Grid *g) : IActor(g) {};
        virtual ~StaticMeshActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition);

    protected:
    private:
        const std::string mBaseName = "StaticMeshActor";
        Vector mLocation;
};

#endif // STATICMESHACTOR_HPP
