#include "DoorActor.hpp"

#include <sstream>


DoorActor::DoorActor(Vector location) : mLocation{location} {

}

DoorActor::DoorActor(double xLocation, double yLocation, double zLocation) : mLocation{Vector(xLocation, yLocation, zLocation)} {
}


std::string DoorActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers
    std::string actorName = nameFactory->getName(mBaseName);
    mName = actorName;
    std::string smcn = nameFactory->getName("StaticMeshComponent");

    stream << indentation << "Begin Actor Class=TERDoor Name=" << actorName << " Archetype=TERDoor'ter.Default__TERDoor'" << std::endl;
    stream << indentation << "   Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << smcn << " Archetype=StaticMeshComponent'ter.Default__TERDoor:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "      StaticMesh=StaticMesh'NEC_WALLS.SM.Mesh.S_NEC_Walls_SM_CAWall_STRc'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << smcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=StaticMeshComponent'ter.Default__TERDoor:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   CustomMesh=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Components(0)=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   Tag=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   CollisionComponent=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=TERDoor'ter.Default__TERDoor'" << std::endl;
    stream << indentation << "End Actor" << std::endl;

    return stream.str();
}

std::string DoorActor::getName() {
    return mName;
}
