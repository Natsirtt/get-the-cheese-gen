#ifndef LASER_HPP
#define	LASER_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


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
private:
    friend ObstacleChooser;
    Laser() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new Laser(graph, first, second);
    }
};

#endif	/* LASER_HPP */

