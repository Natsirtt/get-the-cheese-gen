#ifndef HOLE_HPP
#define	HOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class Hole : public Gate {
public:
    /*Hole() : Gate() {
    }*/

    Hole(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return true;
    }

    void changeState() {
    }
};

#endif	/* HOLE_HPP */
