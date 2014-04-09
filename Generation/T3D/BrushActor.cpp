#include "BrushActor.hpp"

#include <sstream>

//BrushActor::BrushActor() {}

BrushActor::BrushActor(Vector location, std::vector<std::vector<Vector>> polyList, bool sub) : mLocation{location}, mPolyList{polyList}, mSub{sub} {
}

BrushActor::BrushActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, bool sub) : mLocation{Vector(xLocation, yLocation, zLocation)}, mPolyList{polyList}, mSub{sub} {
}

Vector BrushActor::getLocation() {
    return mLocation;
}

std::string BrushActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers
    std::string actorName = nameFactory->getName(mBaseName);
    std::string componentName = nameFactory->getName(mBaseName + "Component");
    std::string modelName = nameFactory->getName("Model");

    stream << indentation << "Begin Actor Class=Brush Name=" << actorName << " Archetype=Brush'Engine.Default__Brush'" << std::endl;

    stream << indentation << "   Begin Object Class=BrushComponent Name=BrushComponent0 ObjName=" << componentName << " Archetype=BrushComponent'Engine.Default__Brush:BrushComponent0'" << std::endl;
    stream << indentation << "      Brush=Model'" << modelName << "'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << componentName << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=BrushComponent'Engine.Default__Brush:BrushComponent0'" << std::endl;

    stream << indentation << "   End Object" << std::endl;
    std::string operation("Add");
    if (mSub) {
        operation = std::string("Subtract");
    }
    stream << indentation << "   CsgOper=CSG_" << operation << std::endl;
    stream << indentation << "   Begin Brush Name=" << modelName << std::endl;
    stream << indentation << "      Begin PolyList" << std::endl;

    for (std::vector<Vector> poly : mPolyList) {
        stream << indentation << "         Begin Polygon" << std::endl;
        for (Vector v : poly) {
            stream << indentation << "            Vertex   " << v.getX() << "," << v.getY() << "," << v.getZ() << std::endl;
        }
        stream << indentation << "         End Polygon" << std::endl;
    }

    stream << indentation << "      End PolyList" << std::endl;
    stream << indentation << "   End Brush" << std::endl;

    stream << indentation << "   Brush=Model'" << modelName << "'" << std::endl;
    stream << indentation << "   BrushComponent=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Components(0)=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   Tag=\"Brush\"" << std::endl;
    stream << indentation << "   CollisionComponent=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=Brush'Engine.Default__Brush'" << std::endl;
    stream << indentation << "End Actor";

    return stream.str();
}
