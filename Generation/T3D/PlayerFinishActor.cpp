#include "PlayerFinishActor.hpp"

#include <sstream>


PlayerFinishActor::PlayerFinishActor(Vector location) : mLocation{location} {
}

PlayerFinishActor::PlayerFinishActor(double xLocation, double yLocation, double zLocation) : mLocation{Vector(xLocation, yLocation, zLocation)} {
}


std::string PlayerFinishActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers
    std::string actorName = nameFactory->getName(mBaseName);
    std::string dlecn = nameFactory->getName("DynamicLightEnvironmentComponent");
    std::string smcn = nameFactory->getName("StaticMeshComponent");

    stream << indentation << "Begin Actor Class=FinishLine Name=" << actorName << " Archetype=FinishLine'ter.Default__FinishLine'" << std::endl;
    stream << indentation << "   Begin Object Class=DynamicLightEnvironmentComponent Name=MyLightEnvironment ObjName=" << dlecn << " Archetype=DynamicLightEnvironmentComponent'ter.Default__FinishLine:MyLightEnvironment'" << std::endl;
    stream << indentation << "      Name=\"" << smcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=DynamicLightEnvironmentComponent'ter.Default__FinishLine:MyLightEnvironment'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << smcn << " Archetype=StaticMeshComponent'ter.Default__FinishLine:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "      StaticMesh=StaticMesh'LT_Light.SM.Mesh.S_LT_Light_SM_Light01'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightEnvironment=DynamicLightEnvironmentComponent'" << dlecn << "'" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << smcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=StaticMeshComponent'ter.Default__FinishLine:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Components(0)=DynamicLightEnvironmentComponent'" << dlecn << "'" << std::endl;
    stream << indentation << "   Components(1)=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   Tag=\"FinishLine\"" << std::endl;
    stream << indentation << "   CollisionComponent=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=FinishLine'ter.Default__FinishLine'" << std::endl;
    stream << indentation << "End Actor" << std::endl;
    return stream.str();
}

