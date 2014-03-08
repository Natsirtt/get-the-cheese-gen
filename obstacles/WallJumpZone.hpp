#ifndef WALLJUMPZONE_HPP
#define	WALLJUMPZONE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class WallJumpZone : public Gate {
public:
    WallJumpZone(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
        //rien
    }

private:
    WallJumpZone() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new WallJumpZone(graph, first, second);
    }
};

#endif	/* WALLJUMPZONE_HPP */

