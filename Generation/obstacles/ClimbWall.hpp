#ifndef CLIMBWALL_HPP
#define	CLIMBWALL_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"
#include "../3D/Area.hpp"

#include "../AreaManager.hpp"

/**
 * Un mur d'escalade à escalader avec ses compétences d'escaladeur.
 */
class ClimbWall : public Gate {
public:
    ClimbWall(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        if (origin == Gate::getFirstNode()) {
            return (p & Perso::Acrobate) != Perso::None;
        }
        return true;
    }

    bool canPass(Perso p) {
        return (p & Perso::Acrobate) != Perso::None;
    }

    bool canPassWithoutTrigger(Perso p) {
        return (p & Perso::Acrobate) != Perso::None;
    }

    void changeState() {
        //rien
    }

    bool canChangeState() {
        return false;
    }
    std::string getName() {
        return "ClimbWall";
    }
    Area getArea() {
        return AreaManager::get().getRandomArea(std::string("ClimbRoom"));
        //return Area("Area/ClimbWall.area");
    }
protected:
    friend ObstacleChooser;
    ClimbWall() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new ClimbWall(graph, first, second);
    }
};

#endif	/* CLIMBWALL_HPP */

