#include "AreaManager.hpp"

#include <dirent.h>
#include "Utils/Random.hpp"

AreaManager::AreaManager(std::string baseDir) : mBaseDir{baseDir} {
    std::vector<std::string> subDirs = readDir(mBaseDir);
    for (auto& s : subDirs) {
        try {
            auto& areas = mAreas[s];
            std::vector<std::string> subFiles = readDir(mBaseDir + s + "/");
            for (auto& f : subFiles) {
                std::cout << "Chargement de " << mBaseDir + s + "/" + f << std::endl;
                areas.push_back(Area(mBaseDir + s + "/" + f));
            }
        } catch(...) {
            // Rien
        }
    }
}

Area AreaManager::getRandomArea(std::string areaType) {
    auto& v = mAreas[areaType];
    if (v.size() > 0) {
        Rand_Int<> rand(0, v.size() - 1);
        int r = rand();
        std::cout << "Choose " << r << "/" << v.size() << std::endl;
        return v.at(r);
    }
    return Area();
}

std::vector<std::string> AreaManager::readDir(std::string dirName) {
    std::vector<std::string> ents;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(dirName.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                ents.push_back(std::string(ent->d_name));
            }
        }
        closedir(dir);
    } else {
        perror("");
        throw std::runtime_error("Impossible d'ouvrir le dossier d'area");
    }
    return ents;
}
