#ifndef METALGATE_HPP
#define	METALGATE_HPP

#include "../Gate.hpp"
#include "../Enum.hpp"

class IGraph;

class MetalGate : public Gate {
public:
    MetalGate(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
        //rien
    }
private:
    MetalGate() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new MetalGate(graph, first, second);
    }
};

#endif	/* METALGATE_HPP */

