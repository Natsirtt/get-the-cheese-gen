#ifndef OBSTACLECHOOSER_HPP
#define OBSTACLECHOOSER_HPP

#include <vector>
#include <memory>
#include "Enum.hpp"

class IGate;
class IGraph;

class ObstacleChooser {
public:
    ObstacleChooser();

    IGate* choose(IGraph* graph, Id first, Id second, Perso p);

private:
    std::vector<std::unique_ptr<IGate>> mObstacles;
};

#endif // OBSTACLECHOOSER_HPP

