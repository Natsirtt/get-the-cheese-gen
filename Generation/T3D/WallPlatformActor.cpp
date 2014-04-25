#include "WallPlatformActor.hpp"

#include "T3DExporter.hpp"
#include "BrushActor.hpp"

#include <sstream>
#include <vector>

const Vector WallPlatformActor::X_POS(1.0, 0.0, 0.0);
const Vector WallPlatformActor::X_NEG(-1.0, 0.0, 0.0);
const Vector WallPlatformActor::Y_POS(0.0, 1.0, 0.0);
const Vector WallPlatformActor::Y_NEG(0.0, -1.0, 0.0);

WallPlatformActor::WallPlatformActor(Grid *g) : IActor(g), mDirection{WallPlatformActor::X_POS} {}

Vector WallPlatformActor::getLocation() {
    return mLocation;
}

std::string WallPlatformActor::getT3D(int indentLevel, NameFactory *nameFactory) {
    std::stringstream stream;
    int platformHeight = 20;
    int platformLength = 75;
    std::vector<std::vector<Vector>> polyList = T3DExporter::getWall(platformLength, platformHeight,
                                                                    mDirection.getX() == 0.0,
                                                                    mDirection.getY() == 0.0,
                                                                    true);
    int nbPlatforms = (T3DExporter::DEMI_CUBE_SIZE * 2) / MAX_JUMP_HEIGHT;
    Vector start = mLocation - Vector(0, 0, T3DExporter::DEMI_CUBE_SIZE) +
                    mDirection * (T3DExporter::DEMI_CUBE_SIZE - platformLength);
    Vector normalDir(mDirection.getY(), mDirection.getX(), mDirection.getZ());
    for (int i = 1; i <= nbPlatforms; ++i) {
        Vector location = start + Vector(0.0, 0.0, i * MAX_JUMP_HEIGHT);
        if ((i % 2) == 0) {
            location = location + normalDir * (T3DExporter::DEMI_CUBE_SIZE / 2);
        } else {
            location = location - normalDir * (T3DExporter::DEMI_CUBE_SIZE / 2);
        }
        BrushActor ba(location, polyList, false);
        stream << ba.getT3D(indentLevel, nameFactory);
    }
    return stream.str();
}

void WallPlatformActor::setDirection(Vector dir) {
    mDirection = dir;
}

/**
 * Just a cube on the gridPosition
 */
void WallPlatformActor::writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation) {
    if (mGrid != nullptr) {
        mLocation = (gridPosition + gridTranslation) * T3DExporter::DEMI_CUBE_SIZE * 2.0;
        mGridPosition = gridPosition;
        mGridTranslation = gridTranslation;

        output << getT3D(indentLevel, nameFactory);
    }
}
