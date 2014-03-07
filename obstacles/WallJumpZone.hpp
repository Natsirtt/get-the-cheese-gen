#ifndef WALLJUMPZONE_HPP
#define	WALLJUMPZONE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class WallJumpZone : public Gate {
    WallJumpZone() : Gate() {
    }
    
    WallJumpZone(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second) {
    }
    
    bool canPass(Perso p, Id origin) {
        return p == Perso.Yamakasi;
    }
    
    void changeState() {
        //rien
    }
};

#endif	/* WALLJUMPZONE_HPP */

