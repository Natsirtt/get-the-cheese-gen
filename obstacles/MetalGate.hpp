#ifndef METALGATE_HPP
#define	METALGATE_HPP

#include "../Gate.hpp"
#include "../Enum.hpp"

class IGraph;

/**
 * Un mur de barres de métal ne laissant passer que le mec qui se faufile.
 */
class MetalGate : public Gate {
public:
    MetalGate(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    bool canPass(Perso p) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
    }

    bool canChangeState() {
        return false;
    }
    std::string getName() {
        return "MetalGate";
    }
private:
    friend ObstacleChooser;
    MetalGate() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new MetalGate(graph, first, second);
    }
};

#endif	/* METALGATE_HPP */

