#ifndef METALGATE_HPP
#define	METALGATE_HPP

#include "../Gate.hpp"
#include "../Enum.hpp"

class IGraph;

class MetalGate : public Gate {
public:
    /*MetalGate() : Gate() {
    }*/

    MetalGate(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
        //rien
    }
};

#endif	/* METALGATE_HPP */

