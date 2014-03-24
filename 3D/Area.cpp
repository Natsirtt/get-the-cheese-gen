#include "Area.hpp"

Area::Area() : mCurrentInCell{}, mCurrentOutCell{} {
    mGrid.set(1, 0, 0, 0);
    mInCells.push_back(std::make_tuple(0, 0, -1));
    mOutCells.push_back(std::make_tuple(0, 0, 1));
}

std::tuple<long, long, long> Area::getNextInCell() {
    return mInCells.at(mCurrentInCell++);
}

bool Area::hasInCellLeft() {
    return mCurrentInCell < mInCells.size();
}

std::tuple<long, long, long> Area::getNextOutCell() {
    return mOutCells.at(mCurrentOutCell++);
}

bool Area::hasOutCellLeft() {
    return mCurrentOutCell < mOutCells.size();
}

Grid& Area::getGrid() {
    return mGrid;
}
