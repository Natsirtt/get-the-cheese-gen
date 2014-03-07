#ifndef HOLE_HPP
#define	HOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class WidthHole : public Gate {
public:
    Hole() : Gate(), mStateOn{false} {
    }

    Hole(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second), mStateOn{false} {
    }

    bool canPass(Perso p, Id origin) {
        return true;
    }
    
    void changeState() {
    }
};

#endif	/* HOLE_HPP */
