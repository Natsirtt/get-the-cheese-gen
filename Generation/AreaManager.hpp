#ifndef AREAMANAGER_HPP
#define AREAMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include "3D/Area.hpp"

class AreaManager {
public:
    static AreaManager& get() {
        static AreaManager am("Area/");
        return am;
    }

    /**
     * Renvoie une Area aléatoire pour une certain type.
     * @param areaType Le type de la Area.
     */
    Area getRandomArea(std::string areaType);

private:
    /**
     * @param baseDir Le dossier dans lequel les area sont stockées.
     */
    AreaManager(std::string baseDir);

    std::vector<std::string> readDir(std::string dirName);

    std::string mBaseDir;
    std::map<std::string, std::vector<Area>> mAreas;
};

#endif // AREAMANAGER8HPP

