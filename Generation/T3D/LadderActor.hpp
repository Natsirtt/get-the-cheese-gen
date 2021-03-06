#ifndef LADDERACTOR_HPP
#define LADDERACTOR_HPP

#include "IActor.hpp"

#include <string>
#include <vector>
#include <fstream>

#include "NameFactory.hpp"
#include "../Utils/Vector.hpp"
#include "../3D/Grid.hpp"

class LadderActor : public IActor {
    public:
        LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, int yaw);
        LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, int yaw);
        LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, float degYaw);
        LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, float degYaw);
        LadderActor(Grid *g);
        virtual ~LadderActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *NameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;
        std::vector<std::vector<Vector>> mPolyList;
        int mYaw;

        const std::string mBaseName = "LadderVolume";
};

#endif // LADDERACTOR_HPP
