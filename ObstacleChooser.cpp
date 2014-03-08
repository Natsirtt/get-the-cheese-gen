#include "ObstacleChooser.hpp"
#include "IGraph.hpp"
#include "Utils/Random.hpp"

#include <stdexcept>

#include "obstacles/ClimbWall.hpp"
#include "obstacles/Crusher.hpp"
#include "obstacles/DeathZone.hpp"
#include "obstacles/Door.hpp"
#include "obstacles/HeightHole.hpp"
#include "obstacles/Hole.hpp"
#include "obstacles/Laser.hpp"
#include "obstacles/MetalGate.hpp"
#include "obstacles/MetalGateDoor.hpp"
#include "obstacles/MovingPlatform.hpp"
#include "obstacles/MovingSidewalk.hpp"
#include "obstacles/SlideObstacle.hpp"
#include "obstacles/Trap.hpp"
#include "obstacles/Turret.hpp"
#include "obstacles/WallJumpZone.hpp"
#include "obstacles/WidthHole.hpp"

ObstacleChooser::ObstacleChooser() {
    mObstacles.push_back(std::unique_ptr<IGate>{new ClimbWall{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new Crusher{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new DeathZone{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new Door{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new HeightHole{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new Laser{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new MetalGate{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new MetalGateDoor{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new MovingPlatform{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new MovingSideWalk{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new SlideObstacle{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new Trap{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new Turret{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new WallJumpZone{}});
    mObstacles.push_back(std::unique_ptr<IGate>{new WidthHole{}});
}

IGate* ObstacleChooser::choose(IGraph* graph, Id first, Id second, Perso p) {
    int tryCount = 500; // Sécurité
    Rand_Int<> rand(0, mObstacles.size() - 1);
    while (tryCount-- > 0) {
        unsigned int r = rand();
        std::unique_ptr<IGate>& g = mObstacles.at(r);
        if (g->canPass(p)) {
            return g->allocate(graph, first, second);
        }
    }
    throw std::runtime_error("ObstacleChooser::choose -> Impossible de choisir une transition");
    return nullptr;
}

IGate* ObstacleChooser::getGateByName(IGraph* graph, Id first, Id second, std::string name) {
    for (auto& g : mObstacles) {
        if (name == g->getName()) {
            return g->allocate(graph, first, second);
        }
    }
    return nullptr;
}
