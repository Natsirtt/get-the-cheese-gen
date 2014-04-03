#include "Area.hpp"

#include <fstream>

Area::Area() : mCurrentInCell{}, mCurrentOutCell{} {
    mGrid.set(1, 0, 0, 0);
    mInCells.push_back(std::make_tuple(0, 0, -1));
    mOutCells.push_back(std::make_tuple(0, 0, 1));
}

Area::Area(std::string filename) : mCurrentInCell{}, mCurrentOutCell{} {
    std::fstream file(filename, std::fstream::in);

    int nbIn = 0;
    int nbOut = 0;
    int nbCell = 0;
    file >> nbIn >> nbOut >> nbCell;
    long x, y, z, t;
    for (int i = 0; i < nbIn; ++i) {
        file >> x >> y >> z;
        mInCells.push_back(std::make_tuple(x, y, z));
    }
    for (int i = 0; i < nbOut; ++i) {
        file >> x >> y >> z;
        mOutCells.push_back(std::make_tuple(x, y, z));
    }
    for (int i = 0; i < nbCell; ++i) {
        file >> x >> y >> z >> t;
        mGrid.set(t, x, y, z);
    }
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

void Area::save(std::string filename) {
    std::fstream file(filename, std::fstream::out | std::fstream::trunc);

    file << mInCells.size() << " " << mOutCells.size() << " " << mGrid.getOccupiedCellsCount() << "\n";
    for (auto& t : mInCells) {
        file << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t) << "\n";
    }
    for (auto& t : mOutCells) {
        file << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t) << "\n";
    }
    file << mGrid;
}
