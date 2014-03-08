#ifndef TRAP_HPP
#define	TRAP_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class Trap : public Gate {
public:
    /*Trap() : Gate() {
    }*/

    Trap(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        //Non blocant, seulement pour embêter le joueur
        return true;
    }

    void changeState() {
        //rien
    }

};

#endif	/* TRAP_HPP */

