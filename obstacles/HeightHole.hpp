#ifndef HEIGHTHOLE_HPP
#define	HEIGHTHOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class HeightHole : public Gate {
public:
    HeightHole() : Gate(), mStateOn{false} {
    }

    HeightHole(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second), mStateOn{false} {
    }

    bool canPass(Perso p, Id origin) {
        return (origin == Gate::getFirstNode()) && (p == Perso.Acrobate) || origin == Gate::getSecondNode();
    }
    
    void changeState() {
    }
};

#endif	/* HEIGHTHOLE_HPP */

