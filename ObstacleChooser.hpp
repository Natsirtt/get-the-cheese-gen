#ifndef OBSTACLECHOOSER_HPP
#define OBSTACLECHOOSER_HPP

#include <vector>
#include "Enum.hpp"

class IGate;

class ObstacleChooser {
public:
    ObstacleChooser();

    IGate* choose(Perso p);

private:
    std::vector<IGate*> mObstacles;
};

#endif // OBSTACLECHOOSER_HPP

