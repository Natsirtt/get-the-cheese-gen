#include "LadderActor.hpp"

#include <cmath>

const float LadderActor::DEG_TO_UNREAL = 182.0444;

LadderActor::LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, int yaw) : mLocation{location}, mPolyList{polyList}, mYaw{yaw} {
}

LadderActor::LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, int yaw) : mLocation{Vector(xLocation, yLocation, zLocation)}, mPolyList{polyList}, mYaw{yaw} {
}

LadderActor::LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, float degYaw) : mLocation{location}, mPolyList{polyList}, mYaw{(int) std::round(degYaw)} {
}

LadderActor::LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, float degYaw) : mLocation{Vector(xLocation, yLocation, zLocation)}, mPolyList{polyList}, mYaw{(int) std::round(degYaw)} {
}
