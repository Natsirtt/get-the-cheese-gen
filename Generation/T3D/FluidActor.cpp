#include "FluidActor.hpp"

#include "T3DExporter.hpp"

#include <cmath>
#include <sstream>

FluidActor::FluidActor(Vector location) : mLocation{location} {
}

FluidActor::FluidActor(double xLocation, double yLocation, double zLocation) : mLocation{xLocation, yLocation, zLocation} {
}


FluidActor::FluidActor(Grid *g) : IActor(g) {}

Vector FluidActor::getLocation() {
    return mLocation;
}

std::string FluidActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream indentStream;
    std::string indentUnit = "   ";
    for (int i = 0; i < indentLevel; ++i) {
        indentStream << indentUnit;
    }
    std::string indentation = indentStream.str();
    std::stringstream stream;
    stream.precision(6);
    stream << std::fixed;
    std::string fscn = nameFactory->getName("FluidSurfaceComponent");
    std::string actorName = nameFactory->getName(mBaseName);

    stream << indentation << "Begin Actor Class=FluidSurfaceActor Name=" << actorName << " Archetype=FluidSurfaceActor'Engine.Default__FluidSurfaceActor'" << std::endl;
    stream << indentation << indentUnit << "Begin Object Class=FluidSurfaceComponent Name=NewFluidComponent ObjName=" << fscn << " Archetype=FluidSurfaceComponent'Engine.Default__FluidSurfaceActor:NewFluidComponent'" << std::endl;
    stream << indentation << indentUnit << indentUnit << "FluidMaterial=Material'UDK_ProceduralSky.Materials.M_FluidActor_Water'" << std::endl;
    stream << indentation << indentUnit << indentUnit << "FluidWidth=" << T3DExporter::DEMI_CUBE_SIZE * 2 << std::endl;
    stream << indentation << indentUnit << indentUnit << "FluidHeight=" << T3DExporter::DEMI_CUBE_SIZE * 2 << std::endl;
    stream << indentation << indentUnit << indentUnit << "ReplacementPrimitive=None" << std::endl;
    stream << indentation << indentUnit << indentUnit << "LightingChannels=(bInitialized=True,Static=True)" << std::endl;
    stream << indentation << indentUnit << indentUnit << "Name=\"" << fscn << "\"" << std::endl;
    stream << indentation << indentUnit << indentUnit << "ObjectArchetype=FluidSurfaceComponent'Engine.Default__FluidSurfaceActor:NewFluidComponent'" << std::endl;
    stream << indentation << indentUnit << "End Object" << std::endl;
    stream << indentation << indentUnit << "FluidComponent=FluidSurfaceComponent'" << fscn << "'" << std::endl;
    stream << indentation << indentUnit << "Components(0)=FluidSurfaceComponent'" << fscn << "'" << std::endl;
    stream << indentation << indentUnit << "Location=(X=" << mLocation.getX() << ",Y=" << mLocation.getY() << ",Z=" << mLocation.getZ() << ")" << std::endl;
    stream << indentation << indentUnit << "Tag=\"FluidSurfaceActor\"" << std::endl;
    stream << indentation << indentUnit << "Name=\"" << actorName << "\"" << std::endl;
    stream << indentation << indentUnit << "ObjectArchetype=FluidSurfaceActor'Engine.Default__FluidSurfaceActor'" << std::endl;
    stream << indentation << "End Actor" << std::endl;

    return stream.str();
}

void FluidActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0 + Vector(0, 0, T3DExporter::DEMI_CUBE_SIZE);

        output << getT3D(indentLevel, nameFactory);
    }
}
