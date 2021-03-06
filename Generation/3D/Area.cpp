#include "Area.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

Area::Area(bool defaut) : mCurrentInCell{}, mCurrentOutCell{} {
    if (defaut) {
        mGrid.set(1, 0, 0, 0);
        addInCell(std::make_tuple(0, -1, 0));
        addOutCell(std::make_tuple(0, 1, 0));
    }
}

Area::Area(const Area& a) : mGrid{a.mGrid}, mCurrentInCell{a.mCurrentInCell}, mInCells{a.mInCells}, mCurrentOutCell{a.mCurrentOutCell}, mOutCells{a.mOutCells} {
}

Area& Area::operator=(const Area& a) {
    mGrid = a.mGrid;
    mCurrentInCell = a.mCurrentInCell;
    mInCells = a.mInCells;
    mCurrentOutCell = a.mCurrentOutCell;
    mOutCells = a.mOutCells;
    return *this;
}

Area::Area(const char* filename) : mCurrentInCell{}, mCurrentOutCell{} {
    load(std::string(filename));
}

Area::Area(std::string filename) : mCurrentInCell{}, mCurrentOutCell{} {
    load(filename);
}

void Area::load(std::string filename) {
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
        addInCell(std::make_tuple(x, y, z));
    }
    for (int i = 0; i < nbOut; ++i) {
        file >> x >> y >> z;
        addOutCell(std::make_tuple(x, y, z));
    }
    for (int i = 0; i < nbCell; ++i) {
        file >> x >> y >> z >> t;
        mGrid.set(t, x, y, z);
    }
    std::random_shuffle(mInCells.begin(), mInCells.end());
    std::random_shuffle(mOutCells.begin(), mOutCells.end());
}

std::tuple<long, long, long> Area::getNextInCell() {
    if (hasInCellLeft()) {
        auto t = mInCells.at(mCurrentInCell);
        mCurrentInCell++;
        return t;
    }
    std::cout << "Entr�e " << mCurrentInCell << "/" << mInCells.size() << std::endl;
    throw std::runtime_error("Impossible de trouver une nouvelle entr�e");
}

bool Area::hasInCellLeft() {
    return mCurrentInCell < mInCells.size();
}

std::tuple<long, long, long> Area::getNextOutCell() {
    if (hasOutCellLeft()) {
        auto t = mOutCells.at(mCurrentOutCell);
        mCurrentOutCell++;
        return t;
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
    file.close();
    std::cout << "File " << filename << " saved." << std::endl;
}

void Area::addInCell(std::tuple<long, long, long> in) {
    mInCells.push_back(in);
    mGrid.set(Grid::IN_CELL, in);
}
void Area::addOutCell(std::tuple<long, long, long> out) {
    mOutCells.push_back(out);
    mGrid.set(Grid::OUT_CELL, out);
}
