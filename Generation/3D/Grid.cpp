#include "Grid.hpp"

#include <vector>

Grid::Grid() : mMinX{}, mMaxX{}, mMinY{}, mMaxY{}, mMinZ{}, mMaxZ{}, mCellsCount{} {

}


void Grid::set(long type, long x, long y, long z) {
    if (mGrid[x][y][z] == EMPTY_CELL) {
        mCellsCount++;
    }
    mGrid[x][y][z] = type;
    mMinX = std::min(mMinX, x);
    mMaxX = std::max(mMaxX, x);
    mMinY = std::min(mMinZ, y);
    mMaxY = std::max(mMaxY, y);
    mMinZ = std::min(mMinZ, z);
    mMaxZ = std::max(mMaxZ, z);
}

void Grid::set(long type, std::tuple<long, long, long> p) {
    set(type, std::get<0>(p), std::get<1>(p), std::get<2>(p));
}

long Grid::get(long x, long y, long z) {
    try {
        return mGrid.at(x).at(y).at(z);
    } catch (...) {

    }
    return EMPTY_CELL;
}

long Grid::get(Vector v) {
    return get(v.getX(), v.getY(), v.getZ());
}

long Grid::get(std::tuple<long, long, long> p) {
    return get(std::get<0>(p), std::get<1>(p), std::get<2>(p));
}

void Grid::add(Grid& g, long x, long y, long z) {
    for (auto& itX : g.mGrid) {
        for (auto& itY : itX.second) {
            for (auto& itZ : itY.second) {
                set(itZ.second, itX.first + x, itY.first + y, itZ.first + z);
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
                if ((itZ.second == IN_CELL) || (itZ.second == OUT_CELL)) {
                    std::vector<std::tuple<long, long, long>> neighbors{
                        std::make_tuple(itX.first + x + 1, itY.first + y, itZ.first + z),
                        std::make_tuple(itX.first + x - 1, itY.first + y, itZ.first + z),
                        std::make_tuple(itX.first + x, itY.first + y + 1, itZ.first + z),
                        std::make_tuple(itX.first + x, itY.first + y - 1, itZ.first + z),
                        std::make_tuple(itX.first + x, itY.first + y, itZ.first + z + 1),
                        std::make_tuple(itX.first + x, itY.first + y, itZ.first + z - 1),
                    };
                    for (auto& t : neighbors) {
                        long type = get(t);
                        if ((type == IN_CELL) || (type == OUT_CELL)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

std::ostream& Grid::write(std::ostream& stream) {
    for (auto& itX : mGrid) {
        for (auto& itY : itX.second) {
            for (auto& itZ : itY.second) {
                stream << itX.first << " " << itY.first << " " << itZ.first << " " << itZ.second << std::endl;
            }
        }
    }
    return stream;
}

long Grid::getOccupiedCellsCount() {
    return mCellsCount;
}

std::unordered_map<long, std::unordered_map<long, std::unordered_map<long, long>>>& Grid::getMap() {
    return mGrid;
}

bool Grid::isPhysicalCell(long t) {
    return (t != Grid::EMPTY_CELL) && (t != Grid::IN_CELL) && (t != Grid::OUT_CELL);
}
