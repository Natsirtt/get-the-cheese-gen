#include "TurretActor.h"

#include "T3DExporter.hpp"

#include <sstream>
#include <iostream>

TurretActor::TurretActor(Vector location) : mLocation(location) {
}

TurretActor::TurretActor(double xLocation, double yLocation, double zLocation) : mLocation{Vector(xLocation, yLocation, zLocation)} {
}

TurretActor::TurretActor(Grid *g) : IActor(g) {
}

Vector TurretActor::getLocation() {
    return mLocation;
}

std::string TurretActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    std::string indent = "   ";
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << indent;
    }
    std::string indentBase = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed;

    std::string name = nameFactory->getName(mBaseName);
    std::string staticMeshComponent = nameFactory->getName("StaticMeshComponent");
    std::string particleComponent = nameFactory->getName("UTParticleSystemComponent");


    stream << indentBase << "Begin Actor Class=TERTurret Name=" << name << " Archetype=TERTurret'ter.Default__TERTurret'" << std::endl;

    stream << indentBase << indent << "Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << staticMeshComponent << " Archetype=StaticMeshComponent'ter.Default__TERTurret:MyStaticMeshComponent'" << std::endl;

    stream << indentBase << indent << indent << "StaticMesh=StaticMesh'NEC_Deco.SM.Mesh.S_NEC_Deco_SM_Cuchulainn_Pose3'" << std::endl;
    stream << indentBase << indent << indent << "ReplacementPrimitive=None" << std::endl;
    stream << indentBase << indent << indent << "LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentBase << indent << indent << "Rotation=(Pitch=0,Yaw=49140,Roll=0)" << std::endl;
    stream << indentBase << indent << indent << "Name=\"" << staticMeshComponent << "\"" << std::endl;
    stream << indentBase << indent << indent << "ObjectArchetype=StaticMeshComponent'ter.Default__TERTurret:MyStaticMeshComponent'" << std::endl;

    stream << indentBase << indent << "End Object" << std::endl;

    stream << indentBase << indent << "Begin Object Class=UTParticleSystemComponent Name=BeamEmitterComponent ObjName=" << particleComponent << std::endl;

    stream << indentBase << indent << indent << "Archetype=UTParticleSystemComponent'ter.Default__TERTurret:BeamEmitterComponent'" << std::endl;
    stream << indentBase << indent << indent << "Template=ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Altbeam'" << std::endl;
    stream << indentBase << indent << indent << "bUpdateComponentInTick=True" << std::endl;
    stream << indentBase << indent << indent << "ReplacementPrimitive=None" << std::endl;
    stream << indentBase << indent << indent << "LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentBase << indent << indent << "TickGroup=TG_PostUpdateWork" << std::endl;
    stream << indentBase << indent << indent << "Name=\"" << particleComponent << "\"" << std::endl;
    stream << indentBase << indent << indent << "ObjectArchetype=UTParticleSystemComponent'ter.Default__TERTurret:BeamEmitterComponent'" << std::endl;

    stream << indentBase << indent << "End Object" << std::endl;

    stream << indentBase << indent << "CustomMesh=StaticMeshComponent'" << staticMeshComponent << "'" << std::endl;
    stream << indentBase << indent << "BeamEmitter=UTParticleSystemComponent'" << particleComponent << "'" << std::endl;
    stream << indentBase << indent << "Components(0)=StaticMeshComponent'" << staticMeshComponent << "'" << std::endl;
    stream << indentBase << indent << "Components(1)=UTParticleSystemComponent'" << particleComponent << "'" << std::endl;
    stream << indentBase << indent << "Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY()<< ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentBase << indent << "Tag=\"TERTurret\"" << std::endl;
    stream << indentBase << indent << "CollisionComponent=StaticMeshComponent'" << staticMeshComponent << "'" << std::endl;
    stream << indentBase << indent << "Name=\"name\"" << std::endl;
    stream << indentBase << indent << "ObjectArchetype=TERTurret'ter.Default__TERTurret'" << std::endl;

    stream << indentBase << "End Actor" << std::endl;

    return stream.str();
}

void TurretActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;
        mLocation = mLocation - Vector(0, 0, T3DExporter::DEMI_CUBE_SIZE);
    }
    output << getT3D(indentLevel, nameFactory);
}
