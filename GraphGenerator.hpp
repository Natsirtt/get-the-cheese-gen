#ifndef GRAPHGENERATOR_HPP
#define GRAPHGENERATOR_HPP

#include <vector>
#include <map>
#include "ObstacleChooser.hpp"
#include "Enum.hpp"

class IGraph;

class GraphGenerator {
public:
    GraphGenerator(IGraph* graph);

    void operator()();

private:
    bool genGraph_Handler(int p, Id lastId, Id lastBranch, Perso perso);

    void addObstacles();

    Id getRandomNodeBetween(Id first, Id second);

    IGraph* mGraph;
    bool mFinished;
    ObstacleChooser mChooser;
    std::vector<Id> mCurrentPath;
    std::map<Id, std::vector<Id>> mActivatorsPath;
    std::vector<Id> mEndPath;
};

#endif // GRAPHGENERATOR_HPP

