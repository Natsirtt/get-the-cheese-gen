#ifndef CRUSHER_HPP
#define	CRUSHER_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class Crusher : public Gate {
private:
    bool mStateOn;

public:
    Crusher(IGraph* graph, Id first, Id second) : Gate(graph, first, second), mStateOn{true} {
    }

    bool canPass(Perso p, Id origin) {
        return (mStateOn && ((p & Perso::Yamakasi) != Perso::None)) || !mStateOn;
    }

    bool canPass(Perso p) {
        return (mStateOn && ((p & Perso::Yamakasi) != Perso::None)) || !mStateOn;
    }

    bool canPassWithoutTrigger(Perso p) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }

    bool canChangeState() {
        return mStateOn;
    }
    std::string getName() {
        return "Crusher";
    }
private:
    friend ObstacleChooser;
    Crusher() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new Crusher(graph, first, second);
    }
};

#endif	/* CRUSHER_HPP */

