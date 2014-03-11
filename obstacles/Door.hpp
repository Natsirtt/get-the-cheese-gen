#ifndef DOOR_HPP
#define	DOOR_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

/**
 * Une porte. No comment.
 */
class Door : public Gate {
private:
    bool mStateOn;

public:
    Door(IGraph* graph, Id first, Id second) : Gate(graph, first, second), mStateOn{false} {
    }

    bool canPass(Perso p, Id origin) {
        return mStateOn;
    }

    bool canPass(Perso p) {
        return mStateOn;
    }

    bool canPassWithoutTrigger(Perso p) {
        return false;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }

    bool canChangeState() {
        return !mStateOn;
    }
    std::string getName() {
        return "Door";
    }
private:
    friend ObstacleChooser;
    Door() : Gate(), mStateOn{true} {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new Door(graph, first, second);
    }
};

#endif	/* DOOR_HPP */

