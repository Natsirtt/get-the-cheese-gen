#ifndef POINTLIGHTACTOR_H
#define POINTLIGHTACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

#include <string>
#include <vector>
#include <fstream>

class PointLightActor : public IActor {
    public:
        PointLightActor(Vector location, float radius);
        PointLightActor(double xLocation, double yLocation, double zLocation, float radius);
        PointLightActor(Grid *g, float radius);
        virtual ~PointLightActor() {};

        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition);

    protected:
    private:
        Vector mLocation;
        float mRadius;
        const std::string mBaseName = "PointLight";
};

#endif // BRUSHACTOR_H

