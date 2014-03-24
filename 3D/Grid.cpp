#include "Grid.hpp"


Grid::Grid() : mMinX{}, mMaxX{}, mMinY{}, mMaxY{}, mMinZ{}, mMaxZ{} {

}


void Grid::set(long type, long x, long y, long z) {
    mGrid[x][y][z] = type;
    mMinX = std::min(mMinX, x);
    mMaxX = std::max(mMaxX, x);
    mMinY = std::min(mMinZ, y);
    mMaxY = std::max(mMaxY, y);
    mMinZ = std::min(mMinZ, z);
    mMaxZ = std::max(mMaxZ, z);
}

long Grid::get(long x, long y, long z) {
    try {
        return mGrid.at(x).at(y).at(z);
    } catch (...) {

    }
    return EMPTY_CELL;
}

void Grid::add(Grid& g, long x, long y, long z) {
    for (auto& itX : g.mGrid) {
        for (auto& itY : itX.second) {
            for (auto& itZ : itY.second) {
                set(itZ.second, itX.first, itY.first, itZ.first);

            }
        }
    }
    mMinX = std::min(mMinX, g.mMinX + x);
    mMaxX = std::max(mMaxX, g.mMaxX + x);
    mMinY = std::min(mMinZ, g.mMinY + y);
    mMaxY = std::max(mMaxY, g.mMaxY + y);
    mMinZ = std::min(mMinZ, g.mMinZ + z);
    mMaxZ = std::max(mMaxZ, g.mMaxZ + z);
}

bool Grid::canAdd(Grid& g, long x, long y, long z) {
    for (auto& itX : g.mGrid) {
        for (auto& itY : itX.second) {
            for (auto& itZ : itY.second) {
                if (get(itX.first + x, itY.first + y, itZ.first + z) != EMPTY_CELL) {
                    return false;
                }
            }
        }
    }
    return true;
}
