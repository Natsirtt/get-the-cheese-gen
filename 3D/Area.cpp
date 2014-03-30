#include "Area.hpp"

#include <fstream>

Area::Area() : mCurrentInCell{}, mCurrentOutCell{} {
    mGrid.set(1, 0, 0, 0);
    mInCells.push_back(std::make_tuple(0, 0, -1));
    mOutCells.push_back(std::make_tuple(0, 0, 1));
    for (auto& t : mInCells) {
        mGrid.set(1, t);
    }
    for (auto& t : mOutCells) {
        mGrid.set(1, t);
    }
}

Area::Area(std::string filename) : mCurrentInCell{}, mCurrentOutCell{} {
    std::fstream file(filename, std::fstream::in);

    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier de repr�sentation");
    }

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
    for (auto& t : mInCells) {
        mGrid.set(1, t);
    }
    for (auto& t : mOutCells) {
        mGrid.set(1, t);
    }
}

std::tuple<long, long, long> Area::getNextInCell() {
    if (hasInCellLeft()) {
        return mInCells.at(mCurrentInCell++);
    }
    std::cout << "Entr�e " << mCurrentInCell << "/" << mInCells.size() << std::endl;
    throw std::runtime_error("Impossible de trouver une nouvelle entr�e");
}

bool Area::hasInCellLeft() {
    return mCurrentInCell < mInCells.size();
}

std::tuple<long, long, long> Area::getNextOutCell() {
    if (hasOutCellLeft()) {
        return mOutCells.at(mCurrentOutCell++);
    }
    std::cout << "Sortie " << mCurrentOutCell << "/" << mOutCells.size() << std::endl;
    throw std::runtime_error("Impossible de trouver une nouvelle sortie");
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

void Area::addInCell(std::tuple<long, long, long> in) {
    mInCells.push_back(in);
    mGrid.set(1, in);
}
void Area::addOutCell(std::tuple<long, long, long> out) {
    mOutCells.push_back(out);
    mGrid.set(1, out);
}
