#include "LavaActor.hpp"

#include "T3DExporter.hpp"

#include <cmath>
#include <sstream>

LavaActor::LavaActor(Vector location) : mLocation{location} {
}

LavaActor::LavaActor(double xLocation, double yLocation, double zLocation) : mLocation{xLocation, yLocation, zLocation} {
}


LavaActor::LavaActor(Grid *g) : IActor(g) {}

Vector LavaActor::getLocation() {
    return mLocation;
}

std::string LavaActor::getT3D(int indentLevel, NameFactory *nameFactory) {

    std::vector<std::vector<Vector>> walls = T3DExporter::getCube(T3DExporter::DEMI_CUBE_SIZE);

    std::stringstream indentStream;
    std::string indentUnit = "   ";
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << indentUnit;
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed;
    std::string brushComponent = nameFactory->getName("BrushComponent");
    std::string model = nameFactory->getName("Model");
    std::string poly = nameFactory->getName("Polys");
    std::string lavaName = nameFactory->getName(mBaseName);

    stream << indentation << "Begin Actor Class=UTLavaVolume Name=" << lavaName << " Archetype=UTLavaVolume'utgame.Default__UTLavaVolume'" << std::endl;

    stream << indentation << indentUnit << "Begin Object Class=Polys Name=" << poly << std::endl;
    stream << indentation << indentUnit << indentUnit << "Name=\"" << poly << "\"" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ObjectArchetype=Polys'Engine.Default__Polys'" << std::endl;
    stream << indentation << indentUnit << "End Object" << std::endl;

    stream << indentation << indentUnit << "Begin Brush Name=" << model << std::endl;
    int i = 0;
    stream << indentation << indentUnit << "Begin PolyList" << std::endl;
    for (std::vector<Vector> poly : walls) {
        stream << indentation << "         Begin Polygon Flags=3584 Link=" << i << std::endl;
        for (Vector v : poly) {
            stream << indentation << "            Vertex   " << v.getX() << "," << v.getY() << "," << v.getZ() << std::endl;
        }
        stream << indentation << "         End Polygon" << std::endl;
        i++;
    }
    stream << indentation << indentUnit << "End PolyList" << std::endl;
    stream << indentation << indentUnit << "End Brush" << std::endl;

    stream << indentation << indentUnit << "Begin Object Class=BrushComponent Name=BrushComponent0 ObjName=" << brushComponent << " Archetype=BrushComponent'utgame.Default__UTLavaVolume:BrushComponent0'" << std::endl;
    stream << indentation << indentUnit << indentUnit << "Brush=Model'" << model << "'" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ReplacementPrimitive=None" << std::endl;
    stream << indentation << indentUnit << indentUnit << "RBChannel=RBCC_Water" << std::endl;
    stream << indentation << indentUnit << indentUnit << "bAcceptsLights=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "CollideActors=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "BlockZeroExtent=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "BlockNonZeroExtent=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "AlwaysLoadOnClient=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "AlwaysLoadOnServer=True" << std::endl;
    stream << indentation << indentUnit << indentUnit << "LightingChannels=(bInitialized=True,Dynamic=True)" << std::endl;
    stream << indentation << indentUnit << indentUnit << "Name=\"" << brushComponent << "\"" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ObjectArchetype=BrushComponent'utgame.Default__UTLavaVolume:BrushComponent0'" << std::endl;
    stream << indentation << indentUnit << "End Object" << std::endl;

    stream << indentation << indentUnit << "Brush=Model'" << model << "'" << std::endl;
    stream << indentation << indentUnit << "BrushComponent=BrushComponent'" << brushComponent << "'" << std::endl;
    stream << indentation << indentUnit << "Components(0)=BrushComponent'" << brushComponent << "'" << std::endl;
    stream << indentation << indentUnit << "Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << indentUnit << "Tag=\"UTLavaVolume\"" << std::endl;
    stream << indentation << indentUnit << "CollisionComponent=BrushComponent'" << brushComponent << "'" << std::endl;
    stream << indentation << indentUnit << "Name=\"" << lavaName << "\"" << std::endl;
    stream << indentation << indentUnit << "ObjectArchetype=UTLavaVolume'utgame.Default__UTLavaVolume'" << std::endl;
    stream << indentation << "End Actor" << std::endl;
    return stream.str();
}

void LavaActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;

        output << getT3D(indentLevel, nameFactory);
    }
}
