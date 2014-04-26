#include "PointLightActor.hpp"

#include <sstream>


PointLightActor::PointLightActor(Vector location, float radius) : mLocation{location}, mRadius{radius} {
}

PointLightActor::PointLightActor(double xLocation, double yLocation, double zLocation, float radius) : mLocation{Vector(xLocation, yLocation, zLocation)}, mRadius{radius} {
}

PointLightActor::PointLightActor(Grid *g, float radius) : IActor(g), mRadius{radius} {}

std::string PointLightActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers
    std::string actorName = nameFactory->getName(mBaseName);
    std::string dlrcn1 = nameFactory->getName("DrawLightRadiusComponent");
    std::string dlrcn2 = nameFactory->getName("DrawLightRadiusComponent2");
    std::string plcn = nameFactory->getName("PointLightComponent");
    std::string scn = nameFactory->getName("SpriteComponent");

    stream << indentation << "Begin Actor Class=PointLight Name=" << actorName << " Archetype=PointLight'Engine.Default__PointLight'" << std::endl;
    stream << indentation << "   Begin Object Class=DrawLightRadiusComponent Name=DrawLightRadius0 ObjName=" << dlrcn1 << " Archetype=DrawLightRadiusComponent'Engine.Default__PointLight:DrawLightRadius0'" << std::endl;
    stream << indentation << "      SphereRadius=" << mRadius << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << dlrcn1 << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=DrawLightRadiusComponent'Engine.Default__PointLight:DrawLightRadius0'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=DrawLightRadiusComponent Name=DrawLightSourceRadius0 ObjName=" << dlrcn2 << " Archetype=DrawLightRadiusComponent'Engine.Default__PointLight:DrawLightSourceRadius0'" << std::endl;
    stream << indentation << "      SphereColor=(B=0,G=239,R=231,A=255)" << std::endl;
    stream << indentation << "      SphereRadius=32.000000" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << dlrcn2 << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=DrawLightRadiusComponent'Engine.Default__PointLight:DrawLightSourceRadius0'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=PointLightComponent Name=PointLightComponent0 ObjName=" << plcn << " Archetype=PointLightComponent'Engine.Default__PointLight:PointLightComponent0'" << std::endl;
    stream << indentation << "      CachedParentToWorld=(XPlane=(W=0.000000,X=1.000000,Y=0.000000,Z=0.000000),YPlane=(W=0.000000,X=0.000000,Y=1.000000,Z=-0.000000),ZPlane=(W=0.000000,X=-0.000000,Y=0.000000,Z=1.000000),WPlane=(W=1.000000,X=-96.000000,Y=-896.000000,Z=0.000000))" << std::endl;
    stream << indentation << "      PreviewLightRadius=DrawLightRadiusComponent'DrawLightRadiusComponent_0'" << std::endl;
    stream << indentation << "      LightmassSettings=(LightSourceRadius=32.000000)" << std::endl;
    stream << indentation << "      PreviewLightSourceRadius=DrawLightRadiusComponent'DrawLightRadiusComponent_1'" << std::endl;
    //stream << indentation << "      LightGuid=(A=653825264,B=1127919774,C=259772584,D=997455248)" << std::endl;
    //stream << indentation << "      LightmapGuid=(A=1175780442,B=1272834779,C=-1559076990,D=258521850)" << std::endl;
    stream << indentation << "      CastDynamicShadows=False" << std::endl;
    stream << indentation << "      UseDirectLightMap=True" << std::endl;
    stream << indentation << "      bPrecomputedLightingIsValid=true" << std::endl;
    stream << indentation << "      LightingChannels=(Dynamic=true)" << std::endl;
    stream << indentation << "      LightAffectsClassification=LAC_STATIC_AFFECTING" << std::endl;
    stream << indentation << "      Name=\"" << plcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=PointLightComponent'Engine.Default__PointLight:PointLightComponent0'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   Begin Object Class=SpriteComponent Name=Sprite ObjName=" << scn << " Archetype=SpriteComponent'Engine.Default__PointLight:Sprite'" << std::endl;
    stream << indentation << "      Sprite=Texture2D'EditorResources.LightIcons.Light_Point_Stationary_Statics'" << std::endl;
    stream << indentation << "      SpriteCategoryName=\"Lighting\"" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      HiddenGame=True" << std::endl;
    stream << indentation << "      AlwaysLoadOnClient=False" << std::endl;
    stream << indentation << "      AlwaysLoadOnServer=False" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Scale=0.250000" << std::endl;
    stream << indentation << "      Name=\"" << scn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=SpriteComponent'Engine.Default__PointLight:Sprite'" << std::endl;
    stream << indentation << "   End Object" << std::endl;
    stream << indentation << "   LightComponent=PointLightComponent'" << plcn << "'" << std::endl;
    stream << indentation << "   Components(0)=SpriteComponent'" << scn << "'" << std::endl;
    stream << indentation << "   Components(1)=DrawLightRadiusComponent'" << dlrcn1 << "'" << std::endl;
    stream << indentation << "   Components(2)=DrawLightRadiusComponent'" << dlrcn2 << "'" << std::endl;
    stream << indentation << "   Components(3)=PointLightComponent'" << plcn << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   Tag=\"PointLight\"" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=PointLight'Engine.Default__PointLight'" << std::endl;
    stream << indentation << "End Actor";

    return stream.str();
}

void PointLightActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = gridPosition;
    }
    output << getT3D(indentLevel, nameFactory);
}
