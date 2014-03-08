#ifndef WIDTHHOLE_HPP
#define	WIDTHHOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class WidthHole : public Gate {
public:
    WidthHole(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Acrobate) != Perso::None;
    }

    void changeState() {
    }

private:
    WidthHole() : Gate() {
    }

    WidthHole* allocate(IGraph* graph, Id first, Id second) {
        return new WidthHole(graph, first, second);
    }
};

#endif	/* WIDTHHOLE_HPP */

