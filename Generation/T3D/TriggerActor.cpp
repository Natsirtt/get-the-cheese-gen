#include "TriggerActor.hpp"

#include <sstream>


TriggerActor::TriggerActor(Vector location, std::string triggerableName) : mLocation{location}, mTriggerableName{triggerableName} {
}

TriggerActor::TriggerActor(double xLocation, double yLocation, double zLocation, std::string triggerableName) : mLocation{Vector(xLocation, yLocation, zLocation)}, mTriggerableName{triggerableName} {
}


std::string TriggerActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers
    std::string actorName = nameFactory->getName(mBaseName);
    std::string smcn = nameFactory->getName("StaticMeshComponent");
    std::string pscn1 = nameFactory->getName("ParticleSystemComponent");
    std::string pscn2 = nameFactory->getName("ParticleSystemComponent");
    std::string ccn = nameFactory->getName("CylinderComponent");
    std::string scn = nameFactory->getName("SpriteComponent");

    stream << indentation << "Begin Actor Class=TERTrigger Name=" << actorName << " Archetype=TERTrigger'ter.Default__TERTrigger'" << std::endl;
    stream << indentation << "   Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << smcn << " Archetype=StaticMeshComponent'ter.Default__TERTrigger:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "      StaticMesh=StaticMesh'GP_Onslaught.Mesh.S_GP_Ons_Weapon_Locker'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << smcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=StaticMeshComponent'ter.Default__TERTrigger:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=ParticleSystemComponent Name=ParticleSystemComponent0 ObjName=" << pscn1 << " Archetype=ParticleSystemComponent'ter.Default__TERTrigger:ParticleSystemComponent0'" << std::endl;
    stream << indentation << "      Template=ParticleSystem'CTF_Flag_IronGuard.Effects.P_CTF_Flag_IronGuard_Idle_Blue'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << pscn1 << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=ParticleSystemComponent'ter.Default__TERTrigger:ParticleSystemComponent0'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=ParticleSystemComponent Name=ParticleSystemComponent1 ObjName=" << pscn2 << " Archetype=ParticleSystemComponent'ter.Default__TERTrigger:ParticleSystemComponent1'" << std::endl;
    stream << indentation << "      Template=ParticleSystem'CTF_Flag_IronGuard.Effects.P_CTF_Flag_IronGuard_Idle_Red'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << pscn2 << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=ParticleSystemComponent'ter.Default__TERTrigger:ParticleSystemComponent1'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=CylinderComponent Name=CollisionCylinder ObjName=" << ccn << " Archetype=CylinderComponent'ter.Default__TERTrigger:CollisionCylinder'" << std::endl;
    stream << indentation << "      CollisionHeight=100.000000" << std::endl;
    stream << indentation << "      CollisionRadius=40.000000" << std::endl;
    stream << indentation << "      bAlwaysRenderIfSelected=True" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      CollideActors=True" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << ccn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=CylinderComponent'ter.Default__TERTrigger:CollisionCylinder'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=SpriteComponent Name=Sprite ObjName=" << scn << " Archetype=SpriteComponent'ter.Default__TERTrigger:Sprite'" << std::endl;
    stream << indentation << "      Sprite=Texture2D'EditorResources.S_Trigger'" << std::endl;
    stream << indentation << "      SpriteCategoryName=\"Triggers\"" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      AlwaysLoadOnClient=False" << std::endl;
    stream << indentation << "      AlwaysLoadOnServer=False" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << scn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=SpriteComponent'ter.Default__TERTrigger:Sprite'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   triggerableName=\"" << mTriggerableName << "\"" << std::endl;
    stream << indentation << "   CustomMesh=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   BlueLight=ParticleSystemComponent'" << pscn1 << "'" << std::endl;
    stream << indentation << "   RedLight=ParticleSystemComponent'" << pscn2 << "'" << std::endl;
    stream << indentation << "   CylinderComponent=CylinderComponent'" << ccn << "'" << std::endl;
    stream << indentation << "   Components(0)=SpriteComponent'" << scn << "'" << std::endl;
    stream << indentation << "   Components(1)=CylinderComponent'" << ccn << "'" << std::endl;
    stream << indentation << "   Components(2)=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Components(3)=ParticleSystemComponent'" << pscn1 << "'" << std::endl;
    stream << indentation << "   Components(4)=ParticleSystemComponent'" << pscn2 << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   Tag=\"TERTrigger\"" << std::endl;
    stream << indentation << "   CollisionComponent=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=TERTrigger'ter.Default__TERTrigger'" << std::endl;
    stream << indentation << "End Actor" << std::endl;

    return stream.str();
}

