#include "PlayerStartActor.hpp"

#include <sstream>


PlayerStartActor::PlayerStartActor(Vector location) : mLocation{location} {
}

PlayerStartActor::PlayerStartActor(double xLocation, double yLocation, double zLocation) : mLocation{Vector(xLocation, yLocation, zLocation)} {
}


std::string PlayerStartActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers
    std::string actorName = nameFactory->getName(mBaseName);
    std::string componentName = nameFactory->getName("CylinderComponent");
    std::string scn1 = nameFactory->getName("SpriteComponent");
    std::string scn2 = nameFactory->getName("SpriteComponent");
    std::string acn = nameFactory->getName("ArrowComponent");
    std::string prcn = nameFactory->getName("PathRenderingComponent");
    std::string modelName = nameFactory->getName("Model");

    stream << indentation << "Begin Actor Class=PlayerStart Name=" << actorName << " Archetype=PlayerStart'Engine.Default__PlayerStart'" << std::endl;

    stream << indentation << "   Begin Object Class=CylinderComponent Name=CollisionCylinder ObjName=" << componentName << " Archetype=CylinderComponent'Engine.Default__PlayerStart:CollisionCylinder'" << std::endl;
    stream << indentation << "      CollisionHeight=20.000000" << std::endl;
    stream << indentation << "      CollisionRadius=20.000000" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << componentName << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=CylinderComponent'Engine.Default__PlayerStart:CollisionCylinder'" << std::endl;
    stream << indentation << "   End Object" << std::endl;

    stream << indentation << "   Begin Object Class=SpriteComponent Name=Sprite ObjName=" << scn1 << " Archetype=SpriteComponent'Engine.Default__PlayerStart:Sprite'" << std::endl;
    stream << indentation << "      Sprite=Texture2D'EditorResources.S_Player'" << std::endl;
    stream << indentation << "      SpriteCategoryName=\"PlayerStart\"" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      HiddenGame=True" << std::endl;
    stream << indentation << "      AlwaysLoadOnClient=False" << std::endl;
    stream << indentation << "      AlwaysLoadOnServer=False" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << scn1 << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=SpriteComponent'Engine.Default__PlayerStart:Sprite'" << std::endl;
    stream << indentation << "   End Object" << std::endl;

    stream << indentation << "   Begin Object Class=SpriteComponent Name=Sprite2 ObjName=" << scn2 << " Archetype=SpriteComponent'Engine.Default__PlayerStart:Sprite2'" << std::endl;
    stream << indentation << "      Sprite=Texture2D'EditorResources.Bad'" << std::endl;
    stream << indentation << "      SpriteCategoryName=\"Navigation\"" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      HiddenGame=True" << std::endl;
    stream << indentation << "      HiddenEditor=True" << std::endl;
    stream << indentation << "      AlwaysLoadOnClient=False" << std::endl;
    stream << indentation << "      AlwaysLoadOnServer=False" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Scale=0.250000" << std::endl;
    stream << indentation << "      Name=\"" << scn2 << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=SpriteComponent'Engine.Default__PlayerStart:Sprite2'" << std::endl;
    stream << indentation << "   End Object" << std::endl;

    stream << indentation << "   Begin Object Class=ArrowComponent Name=Arrow ObjName=" << acn << " Archetype=ArrowComponent'Engine.Default__PlayerStart:Arrow'" << std::endl;
    stream << indentation << "      ArrowColor=(B=255,G=200,R=150,A=255)" << std::endl;
    stream << indentation << "      ArrowSize=0.500000" << std::endl;
    stream << indentation << "      bTreatAsASprite=True" << std::endl;
    stream << indentation << "      SpriteCategoryName=\"Navigation\"" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << acn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=ArrowComponent'Engine.Default__PlayerStart:Arrow'" << std::endl;
    stream << indentation << "   End Object" << std::endl;

    stream << indentation << "   Begin Object Class=PathRenderingComponent Name=PathRenderer ObjName=" << prcn << " Archetype=PathRenderingComponent'Engine.Default__PlayerStart:PathRenderer'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << prcn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=PathRenderingComponent'Engine.Default__PlayerStart:PathRenderer'" << std::endl;
    stream << indentation << "   End Object" << std::endl;

    stream << indentation << "   NavGuid=(A=1934644062,B=1091775275,C=417243325,D=-889815397)" << std::endl;
    stream << indentation << "   NetworkID=0" << std::endl;
    stream << indentation << "   CylinderComponent=CylinderComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Components(0)=SpriteComponent'" << scn2 << "'" << std::endl;
    stream << indentation << "   Components(1)=SpriteComponent'" << scn1 << "'" << std::endl;
    stream << indentation << "   Components(2)=ArrowComponent'" << acn << "'" << std::endl;
    stream << indentation << "   Components(3)=CylinderComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Components(4)=PathRenderingComponent'" << prcn << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getZ() << ",Z=" << mLocation.getY() << ")" << std::endl;
    stream << indentation << "   Rotation=(Pitch=0,Yaw=20480,Roll=0)" << std::endl;
    stream << indentation << "   Tag=\"PlayerStart\"" << std::endl;
    stream << indentation << "   CollisionComponent=CylinderComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=PlayerStart'Engine.Default__PlayerStart'" << std::endl;
    stream << indentation << "End Actor";

    return stream.str();
}

