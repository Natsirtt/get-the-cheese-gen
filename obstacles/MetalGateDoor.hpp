#ifndef METALGATEDOOR_HPP
#define	METALGATEDOOR_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class MetalGateDoor : public Gate {
private:
    bool mStateOn;

public:
    /*MetalGateDoor() : Gate(), mStateOn{false} {
    }*/

    MetalGateDoor(IGraph* graph, Id first, Id second) : Gate(graph, first, second), mStateOn{false} {
    }

    bool canPass(Perso p, Id origin) {
        if (mStateOn) {
            return true;
        }
        return p == Perso::Yamakasi;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }
};

#endif	/* METALGATEDOOR_HPP */

