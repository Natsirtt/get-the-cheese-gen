#ifndef DOOR_HPP
#define	DOOR_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class Door : public Gate {
private:
    bool mStateOn;

public:
    /*Door() : Gate(), mStateOn{false} {
    }*/

    Door(IGraph* graph, Id first, Id second) : Gate(graph, first, second), mStateOn{false} {
    }

    bool canPass(Perso p, Id origin) {
        return mStateOn;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }
};

#endif	/* DOOR_HPP */

