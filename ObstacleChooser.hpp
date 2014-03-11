#ifndef OBSTACLECHOOSER_HPP
#define OBSTACLECHOOSER_HPP

#include <vector>
#include <memory>
#include <string>
#include "Enum.hpp"

class IGate;
class IGraph;

class ObstacleChooser {
public:
    ObstacleChooser();

    IGate* chooseWithoutTrigger(IGraph* graph, Id first, Id second, Perso p);
    IGate* chooseWithTrigger(IGraph* graph, Id first, Id second, Perso p);

    IGate* getGateByName(IGraph* graph, Id first, Id second, std::string name);

private:
    std::vector<std::unique_ptr<IGate>> mObstacles;
};

#endif // OBSTACLECHOOSER_HPP

