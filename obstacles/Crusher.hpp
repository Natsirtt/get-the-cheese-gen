#ifndef CRUSHER_HPP
#define	CRUSHER_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class Crusher : public Gate {
private:
    bool mStateOn;

public:

    Crusher() : Gate(), mStateOn{true} {
    }

    Crusher(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second), mStateOn{true} {
    }

    bool canPass(Perso p, Id origin) {
        return (mStateOn && p == Perso.Yamakasi) || !mStateOn;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }

};

#endif	/* CRUSHER_HPP */

