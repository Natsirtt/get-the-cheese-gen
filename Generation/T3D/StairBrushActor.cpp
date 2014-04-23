#include "StairBrushActor.hpp"

#include "T3DExporter.hpp"
#include "BrushActor.hpp"

#include <sstream>
#include <vector>

const Vector StairBrushActor::X_POS(1.0, 0.0, 0.0);
const Vector StairBrushActor::X_NEG(-1.0, 0.0, 0.0);
const Vector StairBrushActor::Y_POS(0.0, 1.0, 0.0);
const Vector StairBrushActor::Y_NEG(0.0, -1.0, 0.0);

/*StairBrushActor::StairBrushActor(Vector location, Vector gridPosition, Vector gridTranslation) : mLocation{location} {
}

StairBrushActor::StairBrushActor(double xLocation, double yLocation, double zLocation) : mLocation{xLocation, yLocation, zLocation} {
}*/

StairBrushActor::StairBrushActor(Grid *g) : IActor(g), mDirection{StairBrushActor::X_POS} {}

Vector StairBrushActor::getLocation() {
    return mLocation;
}

std::string StairBrushActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream stream;
    int stairHeight = 10;
    std::vector<std::vector<Vector>> polyList = T3DExporter::getWall(T3DExporter::DEMI_CUBE_SIZE, stairHeight,
                                                                    mDirection.getX() != 0.0,
                                                                    mDirection.getY() != 0.0,
                                                                    true);
    int nbStairs = (T3DExporter::DEMI_CUBE_SIZE * 2) / stairHeight;
    Vector start = mLocation - (mDirection + Vector(0.0, 0.0, 1.0)) * T3DExporter::DEMI_CUBE_SIZE;
    for (int i = 0; i < nbStairs; ++i) {
        Vector location = start + (mDirection + Vector(0.0, 0.0, 1.0)) * i * stairHeight;
        BrushActor ba(location, polyList, false);
        stream << ba.getT3D(indentLevel, nameFactory);
    }
    return stream.str();
}

/**
 * Just a cube on the gridPosition
 */
void StairBrushActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;
        mGridPosition = gridPosition;
        mGridTranslation = gridTranslation;

        output << getT3D(indentLevel, nameFactory);
    }
}
