#ifndef WIDTHHOLE_HPP
#define	WIDTHHOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class WidthHole : public Gate {
public:
    WidthHole() : Gate(), mStateOn{false} {
    }

    WidthHole(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second), mStateOn{false} {
    }

    bool canPass(Perso p, Id origin) {
        return return p == Perso.Acrobate;
    }
    
    void changeState() {
    }
};

#endif	/* WIDTHHOLE_HPP */

