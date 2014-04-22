#ifndef METALGATEDOOR_HPP
#define	METALGATEDOOR_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

/**
 * Une porte en barres de métal ne laissant passer, si fermée, que le mec qui se faufile
 */
class MetalGateDoor : public Gate {
private:
    bool mStateOn;

public:
    MetalGateDoor(IGraph* graph, Id first, Id second) : Gate(graph, first, second), mStateOn{false} {
    }

    bool canPass(Perso p, Id origin) {
        if (mStateOn) {
            return true;
        }
        return (p & Perso::Yamakasi) != Perso::None;
    }

    bool canPass(Perso p) {
        if (mStateOn) {
            return true;
        }
        return (p & Perso::Yamakasi) != Perso::None;
    }

    bool canPassWithoutTrigger(Perso p) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }

    bool canChangeState() {
        return !mStateOn;
    }
    std::string getName() {
        return "MetalGateDoor";
    }
    Area getArea() {
        return AreaManager::get().getRandomArea(std::string("GridRoom"));
    }
private:
    friend ObstacleChooser;
    MetalGateDoor() : Gate(), mStateOn{true} {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new MetalGateDoor(graph, first, second);
    }
};

#endif	/* METALGATEDOOR_HPP */

