#include "DoorActor.hpp"

#include <sstream>
#include <stdexcept>

#include "T3DExporter.hpp"

DoorActor::DoorActor(Vector location) : mLocation{location}, mName{""} {

}

DoorActor::DoorActor(double xLocation, double yLocation, double zLocation) : mLocation{Vector(xLocation, yLocation, zLocation)}, mName{""} {
}

DoorActor::DoorActor(Grid *g) : IActor(g), mName{""} {}

std::string DoorActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers

    mName = nameFactory->getName(mBaseName);

    std::string smcn = nameFactory->getName("StaticMeshComponent");

    stream << indentation << "Begin Actor Class=TERDoor Name=" << mName << " Archetype=TERDoor'ter.Default__TERDoor'" << std::endl;
    stream << indentation << "   Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << smcn << " Archetype=StaticMeshComponent'ter.Default__TERDoor:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "      StaticMesh=StaticMesh'NEC_WALLS.SM.Mesh.S_NEC_Walls_SM_CAWall_STRc'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      bAcceptsLights=true" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << smcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=StaticMeshComponent'ter.Default__TERDoor:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   CustomMesh=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Components(0)=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   Tag=\"" << mName << "\"" << std::endl;
    stream << indentation << "   CollisionComponent=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Name=\"" << mName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=TERDoor'ter.Default__TERDoor'" << std::endl;
    stream << indentation << "End Actor" << std::endl;

    return stream.str();
}

void DoorActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;
        mLocation = mLocation - Vector(0, 0, T3DExporter::DEMI_CUBE_SIZE);
    }
    output << getT3D(indentLevel, nameFactory);
}

std::string DoorActor::getName(NameFactory *nameFactory) {
    return mName;
}
