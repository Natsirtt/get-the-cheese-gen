#ifndef LASER_HPP
#define	LASER_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

/**
 * Des lasers sont éparpiller pour rendre le passage plus difficile pour les personnages.
 */
class Laser : public Gate {
public:
    Laser(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        //Non blocant, seulement pour embêter le joueur
        return true;
    }

    bool canPass(Perso p) {
        return true;
    }
    bool canPassWithoutTrigger(Perso p) {
        return true;
    }
    void changeState() {
    }

    bool canChangeState() {
        return false;
    }
    std::string getName() {
        return "Laser";
    }
    Area getArea() {
        return AreaManager::get().getRandomArea(std::string("LaserRoom"));
        //return Area("Area/Laser.area");
    }
private:
    friend ObstacleChooser;
    Laser() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new Laser(graph, first, second);
    }
};

#endif	/* LASER_HPP */

