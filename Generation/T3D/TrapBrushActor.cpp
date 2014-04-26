#include "TrapBrushActor.hpp"

#include "T3DExporter.hpp"
#include "LavaActor.hpp"
#include "LavaPostProcessActor.hpp"
#include "FluidActor.hpp"

#include <sstream>
#include <vector>


TrapBrushActor::TrapBrushActor(Vector location) : mLocation{location}{
}

TrapBrushActor::TrapBrushActor(double xLocation, double yLocation, double zLocation) : mLocation{xLocation, yLocation, zLocation} {
}

TrapBrushActor::TrapBrushActor(Grid *g) : IActor(g), mSub{false} {}

Vector TrapBrushActor::getLocation() {
    return mLocation;
}

std::string TrapBrushActor::getT3D(int indentLevel, NameFactory *nameFactory) {
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
    std::string smcn = nameFactory->getName("StaticMeshComponent");

    stream << indentation << "Begin Actor Class=TERTrapBrush Name=" << actorName << " Archetype=TERTrapBrush'ter.Default__TERTrapBrush'" << std::endl;
    stream << indentation << "     Begin Object Class=StaticMeshComponent Name=MyStaticMeshComponent ObjName=" << smcn << " Archetype=StaticMeshComponent'ter.Default__TERTrapBrush:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "        StaticMesh=StaticMesh'LT_Floors.SM.Mesh.S_LT_Floors_SM_TileFloorBroken_4x4'" << std::endl;
    stream << indentation << "        ReplacementPrimitive=None" << std::endl;
    stream << indentation << "        LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "        Name=\"" << smcn << "\"" << std::endl;
    stream << indentation << "        ObjectArchetype=StaticMeshComponent'ter.Default__TERTrapBrush:MyStaticMeshComponent'" << std::endl;
    stream << indentation << "     End Object" << std::endl;
    stream << indentation << "     CustomMesh=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "     Components(0)=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "     Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() + T3DExporter::DEMI_CUBE_SIZE << ")" << std::endl;
    stream << indentation << "     Tag=\"" << actorName << "\"" << std::endl;
    stream << indentation << "     CollisionComponent=StaticMeshComponent'" << smcn << "'" << std::endl;
    stream << indentation << "     Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "     Size=" << T3DExporter::DEMI_CUBE_SIZE * 2.0 << std::endl;
    stream << indentation << "     DrawScale=" << T3DExporter::DEMI_CUBE_SIZE * 2.0 / 256.0 << std::endl;
    stream << indentation << "     ObjectArchetype=TERTrapBrush'ter.Default__TERTrapBrush'" << std::endl;
    stream << indentation << "End Actor" << std::endl;

    mName = actorName;
    stream << writeTrigger(indentLevel, nameFactory);

    LavaActor lava(mLocation);
    stream << lava.getT3D(indentLevel, nameFactory);
    LavaPostProcessActor lavapp(mLocation);
    stream << lavapp.getT3D(indentLevel, nameFactory);
    FluidActor fa(mLocation + Vector(0, 0, T3DExporter::DEMI_CUBE_SIZE - 10));
    stream << fa.getT3D(indentLevel, nameFactory);

    return stream.str();
}

void TrapBrushActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;
        //mLocation = mLocation - Vector(0, 0, T3DExporter::CUBE_SIZE);

        output << getT3D(indentLevel, nameFactory);
    }
}

std::string TrapBrushActor::writeTrigger(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << "   ";
    }

    auto cubeVextexList = T3DExporter::getCube(T3DExporter::DEMI_CUBE_SIZE);
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed; //Those two lines are for having +x.xxxxxx like float numbers
    std::string actorName = nameFactory->getName("TrapVolume");
    std::string componentName = nameFactory->getName("TrapVolumeComponent");
    std::string bcn = nameFactory->getName("BrushComponent");
    std::string modelName = nameFactory->getName("Model");
    std::string pn = nameFactory->getName("Polys");

    stream << indentation << "Begin Actor Class=TERTrapVolume Name=" << actorName << " Archetype=TERTrapVolume'ter.Default__TERTrapVolume'" << std::endl;

    stream << indentation << "   Begin Object Class=Polys Name=" << pn << std::endl;
    stream << indentation << "      Name=\"" << pn << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=Polys'Engine.Default__Polys'" << std::endl;
    stream << indentation << "   End Object" << std::endl;

    std::string operation("Add");
    if (mSub) {
        operation = std::string("Subtract");
    }
    stream << indentation << "   CsgOper=CSG_" << operation << std::endl;
    stream << indentation << "   Begin Brush Name=" << modelName << std::endl;
    stream << indentation << "      Begin PolyList" << std::endl;

    for (std::vector<Vector> poly : cubeVextexList) {
        stream << indentation << "         Begin Polygon Flags=3584" << std::endl;
        for (Vector v : poly) {
            stream << indentation << "            Vertex   " << v.getX() << "," << v.getY() << "," << v.getZ() << std::endl;
        }
        stream << indentation << "         End Polygon" << std::endl;
    }

    stream << indentation << "      End PolyList" << std::endl;
    stream << indentation << "   End Brush" << std::endl;

    stream << indentation << "   Begin Object Class=BrushComponent Name=BrushComponent0 ObjName=" << componentName << " Archetype=BrushComponent'ter.Default__TERTrapVolume:BrushComponent0'" << std::endl;
    stream << indentation << "      Brush=Model'" << modelName << "'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      bAcceptsLights=True" << std::endl;
    stream << indentation << "      CollideActors=True" << std::endl;
    stream << indentation << "      BlockNonZeroExtent=True" << std::endl;
    stream << indentation << "      bDisableAllRigidBody=True" << std::endl;
    stream << indentation << "      AlwaysLoadOnClient=True" << std::endl;
    stream << indentation << "      AlwaysLoadOnServer=True" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;

    stream << indentation << "      Name=\"" << componentName << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=BrushComponent'ter.Default__TERTrapVolume:BrushComponent0'" << std::endl;
    stream << indentation << "   End Object" << std::endl;

    stream << indentation << "   Brush=Model'" << modelName << "'" << std::endl;
    stream << indentation << "   BrushComponent=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Components(0)=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() + T3DExporter::DEMI_CUBE_SIZE * 2 << ")" << std::endl;
    stream << indentation << "   Tag=\"TERTrapVolume\"" << std::endl;
    stream << indentation << "   CollisionComponent=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   triggerableName=\"" << mName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=TERTrapVolume'ter.Default__TERTrapVolume'" << std::endl;
    stream << indentation << "End Actor";

    return stream.str();
}
