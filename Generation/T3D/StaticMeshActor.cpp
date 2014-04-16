#include "StaticMeshActor.hpp"

#include <sstream>

StaticMeshActor::StaticMeshActor() : mLocation{Vector(0., 0., 0.)} {
}

StaticMeshActor::StaticMeshActor(Vector location) : mLocation{Vector(location)} {
}

StaticMeshActor::StaticMeshActor(double x, double y, double z) : mLocation{Vector(x, y, z)} {
}

Vector StaticMeshActor::getLocation() {
    return mLocation;
}

std::string StaticMeshActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "\t";
    }
    std::string indent = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed;
    std::string staticMeshActorName = nameFactory->getName(mBaseName);
    std::string staticMeshComponentName = nameFactory->getName("StaticMeshComponent");

    stream << indent << "Begin Actor Class=StaticMeshActor " << "Name=" << staticMeshActorName << " Archetype=StaticMeshActor'Engine.Default__StaticMeshActor'" << std::endl;

    stream << indent << "\tBegin Object Class=StaticMeshComponent Name=StaticMeshComponent0 ObjName=" << staticMeshComponentName << " Archetype=StaticMeshComponent'Engine.Default__StaticMeshActor:StaticMeshComponent0'" << std::endl;

    stream << indent << "\t\tBegin Object Class=ShadowMap2D Name=ShadowMap2D_7" << std::endl;
    stream << indent << "\t\t\tTexture=ShadowMapTexture2D'ShadowMapTexture2D_9'" << std::endl;
    stream << indent << "\t\t\tCoordinateScale=(X=0.992188,Y=0.992188)" << std::endl;
    stream << indent << "\t\t\tCoordinateBias=(X=0.003906,Y=0.003906)" << std::endl;
    stream << indent << "\t\t\tLightGuid=(A=646288634,B=1240968536,C=300149945,D=1775641691)" << std::endl;
    stream << indent << "\t\t\tbIsShadowFactorTexture=False" << std::endl;
    stream << indent << "\t\t\tName=\"ShadowMap2D_7\"" << std::endl;
    stream << indent << "\t\t\tObjectArchetype=ShadowMap2D'Engine.Default__ShadowMap2D'" << std::endl;

    stream << indent << "\t\tEnd Object" << std::endl;

    stream << indent << "\t\tStaticMesh=StaticMesh'EditorMeshes.TexPropCube'" << std::endl;
    stream << indent << "\t\tbOverrideLightMapRes=True" << std::endl;
    stream << indent << "\t\tOverriddenLightMapRes=256" << std::endl;
    stream << indent << "\t\tLODData(0)=(ShadowMaps=(ShadowMap2D'ShadowMap2D_7'))" << std::endl;
    stream << indent << "\t\tMaterials(0)=Material'Engine_MI_Shaders.M_ES_Phong_Opaque_Master_01'" << std::endl;
    stream << indent << "\t\tReplacementPrimitive=None" << std::endl;
    stream << indent << "\t\tPreviewEnvironmentShadowing=213" << std::endl;
    stream << indent << "\t\tbAllowApproximateOcclusion=True" << std::endl;
    stream << indent << "\t\tbForceDirectLightMap=True" << std::endl;
    stream << indent << "\t\tbUsePrecomputedShadows=True" << std::endl;
    stream << indent << "\t\tBlockRigidBody=False" << std::endl;
    stream << indent << "\t\tVisibilityId=1" << std::endl;
    stream << indent << "\t\tLightingChannels=(bInitialized=True,Static=True)" << std::endl;
    stream << indent << "\t\tName=\"" << staticMeshComponentName << "\"" << std::endl;
    stream << indent << "\t\tObjectArchetype=StaticMeshComponent'Engine.Default__StaticMeshActor:StaticMeshComponent0'" << std::endl;
    stream << indent << "\t\tCustomProperties" << std::endl;

    stream << indent << "\tEnd Object" << std::endl;

    stream << indent << "\tStaticMeshComponent=StaticMeshComponent'" << staticMeshComponentName << "'" << std::endl;
    stream << indent << "\tComponents(0)=StaticMeshComponent'" << staticMeshComponentName << "'" << std::endl;
    stream << indent << "\tLocation=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indent << "\tBlockRigidBody=False" << std::endl;
    stream << indent << "\tTag=\"StaticMeshActor\"" << std::endl;
    stream << indent << "\tCollisionComponent=StaticMeshComponent'" << staticMeshComponentName << "'" << std::endl;
    stream << indent << "\tName=\"" << staticMeshActorName << "\"" << std::endl;
    stream << indent << "\tObjectArchetype=StaticMeshActor'Engine.Default__StaticMeshActor'" << std::endl;
    stream << indent << "End Actor" << std::endl;

    return stream.str();
}

void StaticMeshActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition) {
    if (mGrid != nullptr) {
        mLocation = gridPosition;
    }
    output << getT3D(indentLevel, nameFactory);
}
