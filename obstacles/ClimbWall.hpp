#ifndef CLIMBWALL_HPP
#define	CLIMBWALL_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class ClimbWall : public Gate {
    ClimbWall() : Gate() {
    }
    
    ClimbWall(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second) {
    }
    
    bool canPass(Perso p, Id origin) {
        if (origin == Gate::getFirstNode()) {
            return p == Perso.Acrobate;
        }
        return true;
    }
    
    void changeState() {
        //rien
    }
};

#endif	/* CLIMBWALL_HPP */

