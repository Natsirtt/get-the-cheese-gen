#include "MovableBrushActor.hpp"

#include "T3DExporter.hpp"

#include <sstream>
#include <vector>


MovableBrushActor::MovableBrushActor(Vector location) : mLocation{location} {
}

MovableBrushActor::MovableBrushActor(double xLocation, double yLocation, double zLocation) : mLocation{Vector(xLocation, yLocation, zLocation)} {
}

MovableBrushActor::MovableBrushActor(Grid *g) : IActor(g) {}

Vector MovableBrushActor::getLocation() {
    return mLocation;
}

std::string MovableBrushActor::getT3D(int indentLevel, NameFactory *nameFactory) {
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
    std::string bcn = nameFactory->getName("BrushComponent");

    stream << indentation << "Begin Actor Class=TERMovablePlatform Name=" << actorName << " Archetype=TERMovablePlatform'ter.Default__TERMovablePlatform'" << std::endl;
    stream << indentation << "   Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << bcn << " Archetype=StaticMeshComponent'ter.Default__TERMovablePlatform:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "      StaticMesh=StaticMesh'LT_Floors.SM.Mesh.S_LT_Floors_SM_TileFloorBroken_4x4'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << bcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=StaticMeshComponent'ter.Default__TERMovablePlatform:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   CustomMesh=StaticMeshComponent'" << bcn << "'" << std::endl;
    stream << indentation << "   Components(0)=StaticMeshComponent'" << bcn << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   Tag=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   CollisionComponent=StaticMeshComponent'" << bcn << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   Size=" << T3DExporter::DEMI_CUBE_SIZE * 2.0 << std::endl;
    stream << indentation << "   DrawScale=" << T3DExporter::DEMI_CUBE_SIZE * 2.0 / 256.0 << std::endl;
    stream << indentation << "   Speed=3.0" << std::endl;
    stream << indentation << "   ObjectArchetype=TERMovablePlatform'ter.Default__TERMovablePlatform'" << std::endl;
    stream << indentation << "End Actor" << std::endl;


    return stream.str();
}

void MovableBrushActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;

        output << getT3D(indentLevel, nameFactory);
    }
}
