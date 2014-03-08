#ifndef WALLJUMPZONE_HPP
#define	WALLJUMPZONE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class WallJumpZone : public Gate {
public:
    /*WallJumpZone() : Gate() {
    }*/

    WallJumpZone(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
        //rien
    }
};

#endif	/* WALLJUMPZONE_HPP */

