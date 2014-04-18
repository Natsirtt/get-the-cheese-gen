#include "BrushActor.hpp"

#include "T3DExporter.hpp"

#include <sstream>
#include <vector>

//BrushActor::BrushActor() {}

BrushActor::BrushActor(Vector location, std::vector<std::vector<Vector>> polyList, bool sub) : mLocation{location}, mPolyList{polyList}, mSub{sub} {
}

BrushActor::BrushActor(double xLocation, double yLocation, double zLocation, std::vector<std::vector<Vector>> polyList, bool sub) : mLocation{Vector(xLocation, yLocation, zLocation)}, mPolyList{polyList}, mSub{sub} {
}

BrushActor::BrushActor(Grid *g) : IActor(g), mSub{false} {}

Vector BrushActor::getLocation() {
    return mLocation;
}

std::string BrushActor::getT3D(int indentLevel, NameFactory *nameFactory) {
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
    std::string bcn = nameFactory->getName("BrushComponent");
    std::string modelName = nameFactory->getName("Model");
    std::string pn = nameFactory->getName("Polys");

    stream << indentation << "Begin Actor Class=Brush Name=" << actorName << " Archetype=Brush'Engine.Default__Brush'" << std::endl;

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

    for (std::vector<Vector> poly : mPolyList) {
        stream << indentation << "         Begin Polygon Texture=LT_Floors.BSP.Materials.M_LT_Floors_BSP_Organic05b Flags=3584" << std::endl;
        for (Vector v : poly) {
            stream << indentation << "            Vertex   " << v.getX() << "," << v.getY() << "," << v.getZ() << std::endl;
        }
        stream << indentation << "         End Polygon" << std::endl;
    }

    stream << indentation << "      End PolyList" << std::endl;
    stream << indentation << "   End Brush" << std::endl;

    stream << indentation << "   Begin Object Class=BrushComponent Name=" << bcn << " ObjName=" << componentName << " Archetype=BrushComponent'Engine.Default__Brush:" << bcn << "'" << std::endl;
    stream << indentation << "      Brush=Model'" << modelName << "'" << std::endl;
    stream << indentation << "      ReplacementPrimitive=None" << std::endl;
    stream << indentation << "      CollideActors=True" << std::endl;
    stream << indentation << "      BlockActors=True" << std::endl;
    stream << indentation << "      BlockZeroExtent=True" << std::endl;
    stream << indentation << "      BlockNonZeroExtent=True" << std::endl;
    stream << indentation << "      BlockRigidBody=True" << std::endl;
    stream << indentation << "      LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << "      Name=\"" << componentName << "\"" << std::endl;
    stream << indentation << "      ObjectArchetype=BrushComponent'Engine.Default__Brush:" << bcn << "'" << std::endl;

    stream << indentation << "   End Object" << std::endl;

    stream << indentation << "   Brush=Model'" << modelName << "'" << std::endl;
    stream << indentation << "   BrushComponent=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Components(0)=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << "   CollisionType=COLLIDE_BlockAll" << std::endl;
    stream << indentation << "   BlockRigidBody=True" << std::endl;
    stream << indentation << "   bCollideActors=True" << std::endl;
    stream << indentation << "   bBlockActors=True" << std::endl;
    stream << indentation << "   bPathColliding=True" << std::endl;
    stream << indentation << "   Tag=\"Brush\"" << std::endl;
    stream << indentation << "   CollisionComponent=BrushComponent'" << componentName << "'" << std::endl;
    stream << indentation << "   Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << "   ObjectArchetype=Brush'Engine.Default__Brush'" << std::endl;
    stream << indentation << "End Actor";

    return stream.str();
}

/**
 * Just a cube on the gridPosition
 */
void BrushActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;
        //mLocation = mLocation - Vector(0, 0, T3DExporter::CUBE_SIZE);

        mPolyList = T3DExporter::getCube(T3DExporter::DEMI_CUBE_SIZE);
        output << getT3D(indentLevel, nameFactory);
    }
}
