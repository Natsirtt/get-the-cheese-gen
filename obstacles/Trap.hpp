#ifndef TRAP_HPP
#define	TRAP_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

/**
 * Une zone de pièges de pics ou pièges de trou.
 */
class Trap : public Gate {
public:
    Trap(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        //Non blocant, seulement pour embêter le joueur
        return true;
    }

    bool canPass(Perso p) {
        return true;
    }

    void changeState() {
    }

    bool canChangeState() {
        return true;
    }
    std::string getName() {
        return "Trap";
    }
private:
    friend ObstacleChooser;
    Trap() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new Trap(graph, first, second);
    }
};

#endif	/* TRAP_HPP */

