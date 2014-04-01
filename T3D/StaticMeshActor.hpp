#ifndef STATICMESHACTOR_HPP
#define STATICMESHACTOR_HPP

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"

class StaticMeshActor : public IActor {
    public:
        StaticMeshActor();
        StaticMeshActor(Vector location);
        StaticMeshActor(double x, double y, double z);
        virtual ~StaticMeshActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
    protected:
    private:
        const std::string mBaseName = "StaticMeshActor";
        Vector mLocation;
};

#endif // STATICMESHACTOR_HPP
