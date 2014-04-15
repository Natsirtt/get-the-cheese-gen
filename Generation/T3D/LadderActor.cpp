#include "LadderActor.hpp"

#include <cmath>
#include <sstream>

const float LadderActor::DEG_TO_UNREAL = 182.0444;

LadderActor::LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, int yaw) : mLocation{location}, mPolyList{polyList}, mYaw{yaw} {
}

LadderActor::LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, int yaw) : mLocation{Vector(xLocation, yLocation, zLocation)}, mPolyList{polyList}, mYaw{yaw} {
}

LadderActor::LadderActor(Vector location, std::vector<std::vector<Vector>> polyList, float degYaw) : mLocation{location}, mPolyList{polyList}, mYaw{(int) std::round(degYaw)} {
}

LadderActor::LadderActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, float degYaw) : mLocation{Vector(xLocation, yLocation, zLocation)}, mPolyList{polyList}, mYaw{(int) std::round(degYaw)} {
}

Vector LadderActor::getLocation() {
    return mLocation;
}

std::string LadderActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    std::string indentUnit = "   ";
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << indentUnit;
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed;
    std::string arrowComponent = nameFactory->getName("ArrowComponent");
    std::string brushComponent = nameFactory->getName("BrushComponent");
    std::string model = nameFactory->getName("Model");
    std::string ladderName = nameFactory->getName(mBaseName);

    stream << indentation << "Begin Actor Class=LadderVolume Name=" << ladderName << " Archetype=LadderVolume'Engine.Default__LadderVolume'" << std::endl;

    stream << indentation << indentUnit << "Begin Object Class=ArrowComponent Name=Arrow ObjName=" << arrowComponent << " Archetype=ArrowComponent'Engine.Default__LadderVolume:Arrow'" << std::endl;

    stream << indentation << indentUnit << indentUnit << "ArrowColor=(B=150,G=100,R=150,A=255)" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ArrowSize=5.000000" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ReplacementPrimitive=None" << std::endl;
    stream << indentation << indentUnit << indentUnit << "LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << indentUnit << indentUnit << "Rotation=(Pitch=0,Yaw=" << mYaw << ",Roll=0)" << std::endl;
    stream << indentation << indentUnit << indentUnit << "Name=\"" << arrowComponent << "\"" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ObjectArchetype=ArrowComponent'Engine.Default__LadderVolume:Arrow'" << std::endl;

    stream << indentation << indentUnit << "End Object" << std::endl;
    stream << indentation << indentUnit << "Begin Object Class=BrushComponent Name=BrushComponent0 ObjName=" << brushComponent << " Archetype=BrushComponent'Engine.Default__LadderVolume:BrushComponent0'" << std::endl;

    stream << indentation << indentUnit << indentUnit << "Brush=Model'" << model << "'" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ReplacementPrimitive=None" << std::endl;
    stream << indentation << indentUnit << indentUnit << "bAcceptsLights=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "CollideActors=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "BlockZeroExtent=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "BlockNonZeroExtent=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "bDisableAllRigidBody=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "AlwaysLoadOnClient=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "AlwaysLoadOnServer=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << indentUnit << indentUnit << "Name=\"" << brushComponent << "\"" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ObjectArchetype=BrushComponent'Engine.Default__LadderVolume:BrushComponent0'" << std::endl;

    stream << indentation << indentUnit << "End Object" << std::endl;

    stream << indentation << indentUnit << "WallDir=(Pitch=0,Yaw=" << mYaw << ",Roll=0)" << std::endl;
    stream << indentation << indentUnit << "WallDirArrow=ArrowComponent'" << arrowComponent << "'" << std::endl;

    stream << indentation << indentUnit << "Begin Brush Name=" << model << std::endl;
    stream << indentation << indentUnit << indentUnit << "Begin PolyList" << std::endl;
    for (std::vector<Vector> vertices : mPolyList) {
        stream << indentation << indentUnit << indentUnit << indentUnit << "Begin Polygon" << std::endl;
        for (Vector v : vertices) {
            stream << indentation << indentUnit << indentUnit << indentUnit << indentUnit << "Vertex   " << v.getX() << "," << v.getY() << "," << v.getZ() << std::endl;
        }
        stream << indentation << indentUnit << indentUnit << indentUnit << "End Polygon" << std::endl;
    }
    stream << indentation << indentUnit << indentUnit << "End PolyList" << std::endl;
    stream << indentation << indentUnit << "End Brush" << std::endl;

    stream << indentation << indentUnit << "Brush=Model'" << model << "'" << std::endl;
    stream << indentation << indentUnit << "BrushComponent=BrushComponent'" << brushComponent << "'" << std::endl;
    stream << indentation << indentUnit << "Components(0)=BrushComponent'" << brushComponent << "'" << std::endl;
    stream << indentation << indentUnit << "Components(1)=ArrowComponent'" << arrowComponent << "'" << std::endl;
    stream << indentation << indentUnit << "Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << indentUnit << "Tag=\"LadderVolume\"" << std::endl;
    stream << indentation << indentUnit << "CollisionComponent=BrushComponent'" << brushComponent << "'" << std::endl;
    stream << indentation << indentUnit << "Name=\"" << ladderName << "\"" << std::endl;
    stream << indentation << indentUnit << "ObjectArchetype=LadderVolume'Engine.Default__LadderVolume'" << std::endl;
    stream << indentation << "End Actor" << std::endl;

    return stream.str();
}
