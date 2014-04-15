#ifndef LADDERACTOR_HPP
#define LADDERACTOR_HPP

#include "IActor.hpp"

#include <string>
#include <vector>

#include "NameFactory.hpp"
#include "../Utils/Vector.hpp"

class LadderActor : public IActor {
    public:
        LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, int yaw);
        LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, int yaw);
        LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, float degYaw);
        LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, float degYaw);
        virtual ~LadderActor() {};

        Vector getLocation();
        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);

        //CF unreal rotators conversions
        static const float DEG_TO_UNREAL;
        static const int X_YAW = 0;
        static const int NEG_X_YAW = 32768;
        static const int Y_YAW = 16384;
        static const int NEG_Y_YAW = 49152;
    protected:
    private:
        Vector mLocation;
        std::vector<std::vector<Vector>> mPolyList;
        int mYaw;

        const std::string mBaseName = "LadderVolume";
};

#endif // LADDERACTOR_HPP
