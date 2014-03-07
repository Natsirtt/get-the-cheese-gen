#ifndef METALGATE_HPP
#define	METALGATE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class MetalGate : public Gate {
    MetalGate() : Gate() {
    }
    
    MetalGate(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second) {
    }
    
    bool canPass(Perso p, Id origin) {
        return p == Perso.Yamakasi;
    }
    
    void changeState() {
        //rien
    }
};

#endif	/* METALGATE_HPP */

