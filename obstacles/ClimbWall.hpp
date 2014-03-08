#ifndef CLIMBWALL_HPP
#define	CLIMBWALL_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class ClimbWall : public Gate {
public:
    /*ClimbWall() : Gate() {
    }*/

    ClimbWall(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        if (origin == Gate::getFirstNode()) {
            return (p & Perso::Acrobate) != Perso::None;
        }
        return true;
    }

    void changeState() {
        //rien
    }
};

#endif	/* CLIMBWALL_HPP */

