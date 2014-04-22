#include "LaserActor.hpp"

#include <cmath>
#include <sstream>

#include "T3DExporter.hpp"

LaserActor::LaserActor(Vector location, Vector rotation, bool unrealRotation) : mLocation{location}, mRotation{rotation} {
    if (!unrealRotation) {
        mRotation = Vector(std::round(mRotation.getX() * T3DExporter::DEG_TO_UNREAL),
                           std::round(mRotation.getY() * T3DExporter::DEG_TO_UNREAL),
                           std::round(mRotation.getZ() * T3DExporter::DEG_TO_UNREAL));
    }
}

LaserActor::LaserActor(double xLocation, double yLocation, double zLocation, float degRoll, float degPitch, float degYaw) : mLocation{Vector(xLocation, yLocation, zLocation)}, mRotation{Vector(std::round(degRoll * T3DExporter::DEG_TO_UNREAL),
                                                                                                                                                                                                 std::round(degPitch * T3DExporter::DEG_TO_UNREAL),
                                                                                                                                                                                                 std::round(degYaw * T3DExporter::DEG_TO_UNREAL))} {}
LaserActor::LaserActor(double xLocation, double yLocation, double zLocation, int unrealRoll, int unrealPitch, int unrealYaw) : mLocation{Vector(xLocation, yLocation, zLocation)}, mRotation{Vector(unrealRoll, unrealPitch, unrealYaw)} {}
LaserActor::LaserActor(Grid *g) : IActor(g) {}

Vector LaserActor::getLocation() {
    return mLocation;
}

Vector LaserActor::getUnrealRotation() {
    return mRotation;
}

std::string LaserActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    std::string indent = "   ";
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << indent;
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed;

    std::string name = nameFactory->getName(mBaseName);
    std::string dynamicLightComponent = nameFactory->getName("DynamicLightEnvironmentComponent");
    std::string particleSystemComponent = nameFactory->getName("UTParticleSystemComponent");
    std::string staticMeshComponent = nameFactory->getName("StaticMeshComponent");

    stream << indentation << "Begin Actor Class=TERLaser Name=" << name << " Archetype=TERLaser'ter.Default__TERLaser'" << std::endl;

    stream << indentation << indent << "Begin Object Class=DynamicLightEnvironmentComponent Name=MyLightEnvironment ObjName=" << dynamicLightComponent << " Archetype=DynamicLightEnvironmentComponent'ter.Default__TERLaser:MyLightEnvironment'" << std::endl;

    stream << indentation << indent << indent << "Name=\"" <<  dynamicLightComponent << "\"" << std::endl;
    stream << indentation << indent << indent << "ObjectArchetype=DynamicLightEnvironmentComponent'ter.Default__TERLaser:MyLightEnvironment'" << std::endl;

    stream << indentation << indent << "End Object" << std::endl;

    stream << indentation << indent << "Begin Object Class=UTParticleSystemComponent Name=BeamEmitterComponent ObjName=" << particleSystemComponent << " Archetype=UTParticleSystemComponent'ter.Default__TERLaser:BeamEmitterComponent'" << std::endl;

    stream << indentation << indent << indent << "Template=ParticleSystem'WP_LinkGun.Effects.P_WP_Linkgun_Altbeam'" << std::endl;
    stream << indentation << indent << indent << "bUpdateComponentInTick=True" << std::endl;
    stream << indentation << indent << indent << "ReplacementPrimitive=None" << std::endl;
    stream << indentation << indent << indent << "LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << indent << indent << "Rotation=(Pitch=16380,Yaw=0,Roll=0)" << std::endl;
    stream << indentation << indent << indent << "TickGroup=TG_PostUpdateWork" << std::endl;
    stream << indentation << indent << indent << "Name=\"" << particleSystemComponent << "\"" << std::endl;
    stream << indentation << indent << indent << "ObjectArchetype=UTParticleSystemComponent'ter.Default__TERLaser:BeamEmitterComponent'" << std::endl;

    stream << indentation << indent << "End Object" << std::endl;

    stream << indentation << indent << "Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << staticMeshComponent << " Archetype=StaticMeshComponent'ter.Default__TERLaser:MyStaticMeshComponent'" << std::endl;

    stream << indentation << indent << indent << "StaticMesh=StaticMesh'LT_Light.SM.Mesh.S_LT_Light_SM_Light01'" << std::endl;
    stream << indentation << indent << indent << "ReplacementPrimitive=None" << std::endl;
    stream << indentation << indent << indent << "LightEnvironment=DynamicLightEnvironmentComponent'" << dynamicLightComponent << "'" << std::endl;
    stream << indentation << indent << indent << "LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << indent << indent << "Name=\"" << staticMeshComponent << "\"" << std::endl;
    stream << indentation << indent << indent << "ObjectArchetype=StaticMeshComponent'ter.Default__TERLaser:MyStaticMeshComponent'" << std::endl;

    stream << indentation << indent << "End Object" << std::endl;

    stream << indentation << indent << "BeamEmitter=UTParticleSystemComponent'" << particleSystemComponent << "'" << std::endl;
    stream << indentation << indent << "Components(0)=DynamicLightEnvironmentComponent'" << dynamicLightComponent << "'" << std::endl;
    stream << indentation << indent << "Components(1)=StaticMeshComponent'" << staticMeshComponent << "'" << std::endl;
    stream << indentation << indent << "Components(2)=UTParticleSystemComponent'" << particleSystemComponent << "'" << std::endl;
    stream << indentation << indent << "Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << indent << indent << "Rotation=(Pitch=" << mRotation.getY() << ",Yaw=" << mRotation.getZ() << ",Roll=" << mRotation.getX() << ")" << std::endl;
    stream << indentation << indent << "Tag=\"TERLaser\"" << std::endl;
    stream << indentation << indent << "CollisionComponent=StaticMeshComponent'" << staticMeshComponent << "'" << std::endl;
    stream << indentation << indent << "Name=\"" << name << "\"" << std::endl;
    stream << indentation << indent << "ObjectArchetype=TERLaser'ter.Default__TERLaser'" << std::endl;

    stream << indentation << "End Actor" << std::endl;

    return stream.str();
}

void LaserActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;
        long predX = mGrid->get(gridPosition.getX() - 1, gridPosition.getY(), gridPosition.getZ());
        long predY = mGrid->get(gridPosition.getX(), gridPosition.getY() - 1, gridPosition.getZ());
        long predZ = mGrid->get(gridPosition.getX(), gridPosition.getY(), gridPosition.getZ() - 1);
        //long nextX = mGrid->get(gridPosition.getX() + 1, gridPosition.getY(), gridPosition.getZ());
        //long nextY = mGrid->get(gridPosition.getX(), gridPosition.getY() + 1, gridPosition.getZ());
        //long nextZ = mGrid->get(gridPosition.getX(), gridPosition.getY(), gridPosition.getZ() + 1);

        if (mGrid->get(gridPosition) == Grid::LASER_X_STICKED_CELL) {
            if (!Grid::isPhysicalCell(predX)) {
                mRotation = T3DExporter::FACING_X_VECTOR;
            } else {
                mRotation = T3DExporter::FACING_NEG_X_VECTOR;
            }
        } else if (mGrid->get(gridPosition) == Grid::LASER_Y_STICKED_CELL) {
            if (!Grid::isPhysicalCell(predY)) {
                mRotation = T3DExporter::FACING_Y_VECTOR;
            } else {
                mRotation = T3DExporter::FACING_NEG_Y_VECTOR;
            }
        } else {
            if (!Grid::isPhysicalCell(predZ)) {
                mRotation = T3DExporter::FACING_Z_VECTOR;
            } else {
                mRotation = T3DExporter::FACING_NEG_Z_VECTOR;
            }
        }

        double offset = T3DExporter::DEMI_CUBE_SIZE - 5;
        if (mRotation == T3DExporter::FACING_X_VECTOR) {
            mLocation = mLocation - Vector(offset, 0, 0);
        } else if (mRotation == T3DExporter::FACING_NEG_X_VECTOR) {
            mLocation = mLocation + Vector(offset, 0, 0);
        } else if (mRotation == T3DExporter::FACING_Y_VECTOR) {
            mLocation = mLocation - Vector(0, offset, 0);
        } else if (mRotation == T3DExporter::FACING_NEG_Y_VECTOR) {
            mLocation = mLocation + Vector(0, offset, 0);
        } else if (mRotation == T3DExporter::FACING_Z_VECTOR) {
            mLocation = mLocation - Vector(0, 0, offset);
        } else if (mRotation == T3DExporter::FACING_NEG_Z_VECTOR) {
            mLocation = mLocation + Vector(0, 0, offset);
        }
    }
    output << getT3D(indentLevel, nameFactory);
}
