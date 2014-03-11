#ifndef MOVINGSIDEWALK_HPP
#define	MOVINGSIDEWALK_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class MovingSideWalk : public Gate {
private:
    bool mStateOn;

public:
    /*MovingSideWalk() : Gate(), mStateOn{true} {
    }*/

    MovingSideWalk(IGraph* graph, Id first, Id second) : Gate(graph, first, second), mStateOn{true} {
    }

    bool canPass(Perso p, Id origin) {
        //If the sidewalk is moving and we try to take it backwards
        if (mStateOn && (origin == Gate::getSecondNode())) {
            //only passes the fast running guy
            return (p & Perso::Yamakasi) != Perso::None;
        }
        //else, we can pass if the sidewalks doesn't move or if we try to take it in the right way
        return !mStateOn || (origin == Gate::getFirstNode());
    }

    bool canPass(Perso p) {
        return true;
    }
    bool canPassWithoutTrigger(Perso p) {
        return true;
    }
    void changeState() {
        mStateOn = !mStateOn;
    }

    bool canChangeState() {
        return mStateOn;
    }
    std::string getName() {
        return "MovingSideWalk";
    }
private:
    friend ObstacleChooser;
    MovingSideWalk() : Gate(), mStateOn{true} {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new MovingSideWalk(graph, first, second);
    }
};

#endif	/* MOVINGSIDEWALK_HPP */

