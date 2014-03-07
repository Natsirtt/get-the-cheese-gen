#ifndef TURRET_HPP
#define	TURRET_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class Turret : public Gate {
private:
    bool mStateOn;

public:
    Turret() : Gate(), mStateOn{true} {
    }

    Turret(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second), mStateOn{true} {
    }

    bool canPass(Perso p, Id origin) {
        return mStateOn && (p == Perso.Yamakasi) || !mStateOn;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }
};

#endif	/* TURRET_HPP */

