#ifndef MOVINGSIDEWALK_HPP
#define	MOVINGSIDEWALK_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class MovingSideWalk : public Gate {
private:
    bool mStateOn;

public:
    MovingSideWalk() : Gate(), mStateOn{true} {
    }

    MovingSideWalk(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second), mStateOn{true} {
    }

    bool canPass(Perso p, Id origin) {
        //If the sidewalk is moving and we try to take it backwards
        if (mStateOn && (origin == Gate::getSecondNode())) {
            //only passes the fast running guy
            return p == Perso.Yamakasi;
        }
        //else, we can pass if the sidewalks doesn't move or if we try to take it in the right way
        return !mStateOn || (origin == Gate::getFirstNode());
    }

    void changeState() {
        mStateOn = !mStateOn;
    }
};

#endif	/* MOVINGSIDEWALK_HPP */

